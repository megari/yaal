#ifndef __YAAL_ADC__TYPES__
#define __YAAL_ADC__TYPES__ 1

/* yaal/adc/adctypes.hh
 * types for adc subsystem
 */

#include "../requirements.hh"
#include "../atomic.hh"
#include "../bitmask.hh"
#include "../qualifiers.hh"


namespace yaal {
    // FIXME: relocate
    // FIXME: implement
    namespace internal {
        void sleep() {
            asm ("nop");
        }
    }

    // 10-bits: read 16 bit word read ADCL then ADCH
    //  8-bits: ident to left and read only ADCH

    // adc analog input path error correction: 24.7.3.

    // ADIF is high on complete

    // single channel, result is: adc = (v_in / V_ref) * 1023
    // diff channel, result is: adc = ((V_pos - V_neg) / V_ref) * Gain * 512
    // diff result is 2's complement, 0x200 (-512d) to 0x1ff (+511d)
    // to check positive/negatie, read only polarity bit

    // ADMUX:
    // REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0
    // REFSn: 0,0 - AREF, 0,1 - AVcc, 1,0 - reserved, 1,1 - Internal 2.56V
    //  - put external capacitor on AREF pin (atleast when using internal or AVcc)
    // ADLAR: Left adjust result will effect ADC valua immediately
    // MUXn: Channel selection

    // ADCSRA
    // ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0
    // ADEN: ADC enabled
    // ADSC: start conversion
    // ADATE: auto trigger enable
    // ADIF: interrupt flag
    // ADIE: interrupt enable
    // ADPSn: adc prescaler select
    //  - 000 clk/2 (I ques this is really 1)
    //  - 001 clk/2
    //  - 010 clk/4
    //  - 011 clk/8
    //  - 100 clk/16
    //  - 101 clk/32
    //  - 110 clk/64
    //  - 111 clk/128

    // ADCSRB
    // ADHSM, ACME, MUX5, -, ADTS3, ADTS2, ADTS1, ADTS0
    // ADHSM: high speed mode
    // MUX5: mux bit
    // ADTSn: Autotrigger source

    // DIDR0
    // digital input disable, ADC7D ... ADC4D, ADC1D ... ADC0D

    // DIDR2
    // digital input disable, ADC13D ... ADC8D

    class AnalogDigitalConverter {
        friend void ::yaal::sleep();

        typedef bool sleep_memory;

        YAAL_INLINE("AnalogDigitalConverter::pre_sleep")
        sleep_memory pre_sleep() {
            bool is_on = on();
            disable();
            return is_on;
        }

        YAAL_INLINE("AnalogDigitalConverter::post_sleep")
        void post_sleep(sleep_memory was_on) {
            if (was_on)
                enable();
        }

    public:

        class Reference {
        public:
            enum Source {
                EXTERNAL = 0 << REFS0, // AREF
                POWER    = 1 << REFS0, // AVcc
                RESERVED = 2 << REFS0,
                INTERNAL = 3 << REFS0, // Internal 2.56V
            };

            YAAL_INLINE("AnalogDigitalConverter::Reference::set")
            void set(Source reference_source) {
                Atomic block;
                ADMUX = reference_source | (ADMUX & ~BitMask<2, REFS0>::right);
            }

            YAAL_INLINE("AnalogDigitalConverter::Reference::operator=")
            Reference& operator=(Source reference_source) {
                set(reference_source);
                return *this;
            }
        } reference;

        class Prescaler {
        public:
            enum Values {
                // Include enumeration from file
                // file is created vua script
                // it will define following variables if possible
                // SLOW   50-125 kHz
                // FAST  125-200 kHz
                // SUPER 200-300 kHz
#               define __INTERNAL_INCLUDE_ENUM__ 1
#               include "prescaler_constants.hh"
#               undef __INTERNAL_INCLUDE_ENUM__
                // normally FAST should be ok
                // with SUPER you should enable high speed mode
            };

            YAAL_INLINE("AnalogDigitalConverter::Prescaler::set")
            void set(Values value) {
                Atomic block;
                ADCSRA = (ADCSRA & ~BitMask<3>::right) | (value & BitMask<3>::right);
            }

            YAAL_INLINE("AnalogDigitalConverter::Prescaler::operator=")
            Prescaler& operator= (Values value) {
                set(value);
                return *this;
            }
        } prescaler;

        class Channel {
        public:
            YAAL_INLINE("AnalogDigitalConverter::Channel::set")
            void set(uint8_t mux) {
                Atomic block;
                if (mux & (1 << 5))
                    ADCSRB |= (1 << MUX5);
                else
                    ADCSRB &= ~(1 << MUX5);
                ADMUX = (ADMUX & ~BitMask<5>::right) | (mux & BitMask<5>::right);
            }

            template<typename AdcSingleChannelClass>
            YAAL_INLINE("AnalogDigitalConverter::Channel::operator= template")
            Channel& operator= (AdcSingleChannelClass adc) {
                set(adc.mux);
                return *this;
            }

            YAAL_INLINE("AnalogDigitalConverter::Channel::operator=")
            Channel& operator= (uint8_t mux) {
                set(mux);
                return *this;
            }
        } channel;

        YAAL_INLINE("AnalogDigitalConverter::enable")
        void enable() {
            if (!on()) {
                Atomic block;
                ADCSRA |= (1 << ADEN);
            }
        }

        YAAL_INLINE("AnalogDigitalConverter::disable")
        void disable() {
            if (on()) {
                Atomic block;
                ADCSRA &= ~(1 << ADEN);
            }
        }

        YAAL_INLINE("AnalogDigitalConverter::on")
        bool on() const {
            return ADCSRA & (1 << ADEN);
        }

        YAAL_INLINE("AnalogDigitalConverter::start_conversion")
        void start_conversion() {
            Atomic block;
            ADCSRA |= (1 << ADSC);
        }

        YAAL_INLINE("AnalogDigitalConverter::converting")
        bool converting() const {
            return ADCSRA & (1 << ADSC);
        }

        YAAL_INLINE("AnalogDigitalConverter::single_conversion")
        uint16_t single_conversion() {
            // should we instead use concept:
            // adc.enable();
            // adc.request_single_conversion(0);
            // while(adc.converting();
            // utin16_t value = adc.get();
            //enable(); // FIXME: should this be done only in safe mode?
            while (converting());
            start_conversion();
            // FIXME: this will never return if adc is not enabled.
            while (converting());
            {
                // FIXME: is this useless?
                Atomic block;
                return ADC;
            }
        }

        YAAL_INLINE("AnalogDigitalConverter::single_conversion with mux")
        uint16_t single_conversion(uint8_t mux) {
            channel = mux;
            return single_conversion();
        }

    };

    typedef AnalogDigitalConverter adc_;

    void sleep() {
        adc_ adc;
        typename AnalogDigitalConverter::sleep_memory adc_memory = adc.pre_sleep();
        internal::sleep();
        adc.post_sleep(adc_memory);
    }

    template<uint8_t adc_mask, typename ADCClass>
    class AdcSingleChannel {
    public:
        static const uint8_t mux = adc_mask;

        YAAL_INLINE("AdcSingleChannel::get")
        uint16_t get() {
            ADCClass adc;
            return adc.single_conversion(adc_mask);
        }

        YAAL_INLINE("AdcSingleChannel::operator=")
        operator uint16_t () {
            return get();
        }
    };
}

#endif
