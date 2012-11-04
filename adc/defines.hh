#ifndef __YAAL_ADC__DEFINES__
#define __YAAL_ADC__DEFINES__ 1

// atmega16u4 and atmega32u4
#if defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
#  define YAAL_ADC_GND 0x1f
#  define YAAL_ADC_TEMP 0x27
#  define YAAL_ADC0 0x0
#  define YAAL_PORTF0_ADC Adc0
#  define YAAL_ADC1 0x1
#  define YAAL_PORTF1_ADC Adc1
#  define YAAL_ADC4 0x4
#  define YAAL_PORTF4_ADC Adc4
#  define YAAL_ADC5 0x5
#  define YAAL_PORTF5_ADC Adc5
#  define YAAL_ADC6 0x6
#  define YAAL_PORTF6_ADC Adc6
#  define YAAL_ADC7 0x7
#  define YAAL_PORTF7_ADC Adc7
#  define YAAL_ADC8 0x20
#  define YAAL_PORTD4_ADC Adc8
#  define YAAL_ADC9 0x21
#  define YAAL_PORTD6_ADC Adc9
#  define YAAL_ADC10 0x22
#  define YAAL_PORTD7_ADC Adc10
#  define YAAL_ADC11 0x23
#  define YAAL_PORTB4_ADC Adc11
#  define YAAL_ADC12 0x24
#  define YAAL_PORTB5_ADC Adc12
#  define YAAL_ADC13 0x25
#  define YAAL_PORTB6_ADC Adc13
#else
#  error "Your MCU do not has ADC definitions. Update yaal/adc/defines.hh."
#endif

#endif
