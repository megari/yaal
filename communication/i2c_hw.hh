#ifndef __YAAL_COMMUNICATION__I2C_HW__
#define __YAAL_COMMUNICATION__I2C_HW__ 1
#include "../requirements.hh"
#ifdef __YAAL__

#include <../types/helpers.hh>

#include <avr/interrupt.h>
#include <compat/twi.h>

namespace yaal {

    using yaal::internal::enable_if_t;
    using yaal::integer_type;
    using yaal::integer_types;

    class HWI2CBus {
        typedef HWI2CBus self_type;

        volatile uint8_t databyte;
        volatile const uint8_t *data_start;
        volatile const uint8_t *data_end;
        volatile uint8_t addressbyte;

        volatile bool sending;
        volatile bool receiving;
        volatile bool send_stop;

    public:
        typedef void (*trace_func_t)(uint8_t, const uint8_t *, const uint8_t *, bool, bool);
        trace_func_t trace_func = nullptr;

        volatile bool got_sla_ack;
        volatile bool wrote_all;
        volatile bool got_data_ack;

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
        }

        void deinit() {
            TWCR = 0;
        }

        void set_trace(trace_func_t f) {
            trace_func = f;
        }

        template<bool s_start = true, bool stop = true>
        void write(uint8_t address, uint8_t reg) {
            data_start = &reg;
            data_end = data_start + 1;
            addressbyte = address;
            sending = true;
            send_stop = stop;
            got_sla_ack = wrote_all = got_data_ack = false;

            if (s_start)
                TWCR |= (1 << TWSTA) | (1 << TWIE) | (1 << TWINT);
            else
                TWCR |= (1 << TWIE) | (1 << TWINT);

            while (sending);
        }

        template<bool s_start = true, bool stop = true>
        void write(uint8_t address, const uint8_t *start, const uint8_t *end) {
            data_start = start;
            data_end = end;
            addressbyte = address;
            sending = true;
            send_stop = stop;
            got_sla_ack = wrote_all = got_data_ack = false;

            if (trace_func)
                trace_func(address, start, end, s_start, stop);

            if (s_start)
                TWCR |= (1 << TWSTA) | (1 << TWIE) | (1 << TWINT);
            else
                TWCR |= (1 << TWIE) | (1 << TWINT);

            while (sending);
        }

        uint8_t read(uint8_t address, bool s_start = true) {
            addressbyte = address;
            databyte = 0x00;
            receiving = true;
            send_stop = true;
            got_sla_ack = wrote_all = got_data_ack = false;

            if (s_start)
                TWCR |= (1 << TWSTA) | (1 << TWIE) | (1 << TWINT);
            else
                TWCR |= (1 << TWIE) | (1 << TWINT);

            while (receiving);

            return databyte;
        }

        template<typename T, bool s_start = true, bool stop = true, enable_if_t<!integer_type<T>, T>* = nullptr>
        void write(uint8_t addr, T&& val)
        {
            static_assert(!integer_type<T>, "Integer type not allowed here");
            autounion<T, true> tmp(val);
            uint8_t data[tmp.size] = { 0x00 };
            for (uint8_t i = 0; i < sizeof(data); ++i)
                data[i] = tmp[i];

            write<s_start, stop>(addr, data, data + sizeof(data));
        }

        template<typename T, bool s_start = true, bool stop = true, enable_if_t<!integer_type<T>, T>* = nullptr>
        void write(uint8_t addr, uint8_t reg, T&& val)
        {
            static_assert(!integer_type<T>, "Integer type not allowed here");
            autounion<T, true> tmp(val);
            uint8_t data[tmp.size + 1] = { reg, };
            for (uint8_t i = 1; i < sizeof(data); ++i)
                data[i] = tmp[i];

            write<s_start, stop>(addr, data, data + sizeof(data));
        }

        template<typename ...Ts, enable_if_t<integer_types<Ts...>, Ts...>* = nullptr, bool s_start = true, bool stop = true>
        void write(uint8_t addr, Ts... args)
        {
            uint8_t data[] = { static_cast<uint8_t>(args)... };
            static_assert(sizeof(data) == sizeof...(args), "write_multi_new static error");
            write<s_start, stop>(addr, data, data + sizeof(data));
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
                    break;
                case TW_MT_SLA_ACK:
                    got_sla_ack = true;
                    // Should send data byte.
                    if (data_start != data_end) {
                        TWDR = *data_start++;
                        TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
                    }
                    else {
                        // Send stop, as we had no data to send.
                        goto send_stop;
                    }
                    break;
                case TW_MR_DATA_NACK:
                    got_data_ack = true;
                    // Should get byte and then stop.
                    databyte = TWDR;
                    goto send_stop;
                case TW_MT_DATA_ACK:
                    got_data_ack = true;

                    if (data_start != data_end) {
                        TWDR = *data_start++;
                        TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
                        break;
                    }

                    wrote_all = true;

                    // All went well. Send stop or repeated start.
                    if (!send_stop) {
                        TWCR = (1 << TWEA) | (1 << TWSTA) | (1 << TWEN);
                        sending = false;
                        break;
                    }

                    // Intentional fall-through.
                case TW_MR_SLA_NACK:
                case TW_MT_SLA_NACK:
                case TW_MT_DATA_NACK:
send_stop:
                    // Send stop.
                    TWCR = (1 << TWEA) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE) | (1 << TWINT); 
                    sending = false;
                    receiving = false;
                    break;
                case TW_MR_SLA_ACK:
                    got_sla_ack = true;
                    // Should get data byte. Need to NACK.
                    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
                    break;
            }
        }
        
    };


    HWI2CBus I2c_HW;

#if 0
    template<typename T>
    void I2C_WRITE(uint8_t addr, uint8_t reg, T val)
    {
        static_assert(!integer_type<T>, "Integer type not allowed here");
        I2C_WRITE(addr, autounion<T, true>(val));
    }

    template<typename T, enable_if_t<integer_type<T>, T>* = nullptr>
    void I2C_WRITE(uint8_t addr, T val)
    {
        static_assert(integer_type<T>, "Integer type required here");
        I2c_HW.write(addr, static_cast<uint8_t>(val));
    }
#endif

}


SIGNAL(TWI_vect) {
    yaal::I2c_HW.isr();
}
#endif
#endif
