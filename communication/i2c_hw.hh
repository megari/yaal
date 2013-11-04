
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <yaal.hh>

#define DEBUG 0

namespace yaal {


    class HWI2CBus {
        typedef HWI2CBus self_type;

        volatile uint8_t databyte;
        volatile uint8_t addressbyte;

        volatile bool sending;
        volatile bool receiving;

        Serial0 serial;
        volatile bool startSent;

uint8_t hbyte_to_hex(uint8_t hbyte) {
    return hbyte < 10 ? '0' + hbyte : 'a' + hbyte - 10;
}

uint16_t byte_to_hex(uint8_t byte) {
    return hbyte_to_hex(byte >> 4) << 8 | hbyte_to_hex(byte & 0x0f);
}
    public:

        void setup(uint16_t speed = 100) {
            // 1. Set bitrate
            // TWBR = ((F_CPU / F_SCL) - 16)/(2 * Prescaler)
            // FIXME: select prescaler dynamically instead of just using 1.
            const uint8_t prescaler = 1;
            TWSR &= ~(1 << TWPS0);
            TWSR &= ~(1 << TWPS1);

            TWBR = ((F_CPU/speed/1000UL) - 16UL)/prescaler/2UL;

            // 2. Enable TWI acknowledge, enable TWI, enable TWI interrupt
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE);

#if DEBUG
            serial.setup(9600, DATA_EIGHT, STOP_ONE, PARITY_DISABLED);
            serial.put('I');
#endif
        }

        void write(uint8_t address, uint8_t data) {
            databyte = data;
            addressbyte = address;
            sending = true;
#if DEBUG
            serial.put('A');
#endif

            TWCR |= (1 << TWSTA);
            startSent = false;
            while (!startSent);
            //serial.put('B');
            while (sending);

#if DEBUG
            serial.put('\n');
            serial.put('-');
            serial.put('\n');
#endif            
        }

        uint8_t read(uint8_t address) {
            addressbyte = address;
            databyte = 0x00;
            receiving = true;
#if DEBUG
            serial.put('X');
#endif

            TWCR |= (1 << TWSTA);
            while (receiving) ;

#if DEBUG
            serial.put('\n');
            uint16_t tmp = byte_to_hex(databyte);
            serial.put(tmp >> 8);
            serial.put(tmp);
            serial.put('\n');
            serial.put('-');
            serial.put('\n');
#endif
            return databyte;
        }

        void isr() {
            uint8_t status = TW_STATUS;
            switch (status) {
                case TW_START:
                case TW_REP_START:
                    if (receiving)
                        TWDR = (addressbyte << 1) | 0x01;
                    else
                        TWDR = (addressbyte << 1) & 0xFE;
                    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
#if DEBUG
                    serial.put('B');
#endif
                    startSent = true;
                    break;
                case TW_MT_SLA_ACK:
                    // Should send data byte.
                    TWDR = databyte;
                    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
#if DEBUG
                    serial.put('C');
#endif
                    break;
                case TW_MR_DATA_NACK:
                    // Should get byte and then stop.
                    databyte = TWDR;
                    // Intentional fall-through.
#if DEBUG
                    serial.put('Z');
#endif
                case TW_MT_DATA_ACK:
                    // All went well. Send stop.
                    // Intentional fall-through.
#if DEBUG
                    serial.put('D');
#endif
                case TW_MR_SLA_NACK:
                case TW_MT_SLA_NACK:
#if DEBUG
                    serial.put('b');
#endif
                case TW_MT_DATA_NACK:
                    // Send stop.
                    TWCR = (1 << TWEA) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT); 
                    //serial.put('b');
                    sending = false;
                    receiving = false;
                    break;
                case TW_MR_SLA_ACK:
                    // Should get data byte. Need to NACK.
                    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
#if DEBUG
                    serial.put('Y');
#endif
                    break;
            }
        }
        
    };


    HWI2CBus I2c_HW;
}


SIGNAL(TWI_vect) {
    yaal::I2c_HW.isr();
}
