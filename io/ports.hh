#ifndef __YAAL_IO__PORTS__
#define __YAAL_IO__PORTS__ 1
/* Generated using ports.sh */

#include "register.hh"
#include "port.hh"
#include "../adc/null.hh"
#include "../adc/channels.hh"
#include <avr/io.h>

namespace yaal {

    namespace internal {
#       ifdef PINA
            typedef ReadonlyRegister<YAAL_ADDR(PINA)> PinA;
#       endif
#       ifdef DDRA
            typedef Register<YAAL_ADDR(DDRA)> DdrA;
#       endif
#       ifdef PORTA
            typedef Register<YAAL_ADDR(PORTA)> PortA;
#       endif
#       ifdef PINB
            typedef ReadonlyRegister<YAAL_ADDR(PINB)> PinB;
#       endif
#       ifdef DDRB
            typedef Register<YAAL_ADDR(DDRB)> DdrB;
#       endif
#       ifdef PORTB
            typedef Register<YAAL_ADDR(PORTB)> PortB;
#       endif
#       ifdef PINC
            typedef ReadonlyRegister<YAAL_ADDR(PINC)> PinC;
#       endif
#       ifdef DDRC
            typedef Register<YAAL_ADDR(DDRC)> DdrC;
#       endif
#       ifdef PORTC
            typedef Register<YAAL_ADDR(PORTC)> PortC;
#       endif
#       ifdef PIND
            typedef ReadonlyRegister<YAAL_ADDR(PIND)> PinD;
#       endif
#       ifdef DDRD
            typedef Register<YAAL_ADDR(DDRD)> DdrD;
#       endif
#       ifdef PORTD
            typedef Register<YAAL_ADDR(PORTD)> PortD;
#       endif
#       ifdef PINE
            typedef ReadonlyRegister<YAAL_ADDR(PINE)> PinE;
#       endif
#       ifdef DDRE
            typedef Register<YAAL_ADDR(DDRE)> DdrE;
#       endif
#       ifdef PORTE
            typedef Register<YAAL_ADDR(PORTE)> PortE;
#       endif
#       ifdef PINF
            typedef ReadonlyRegister<YAAL_ADDR(PINF)> PinF;
#       endif
#       ifdef DDRF
            typedef Register<YAAL_ADDR(DDRF)> DdrF;
#       endif
#       ifdef PORTF
            typedef Register<YAAL_ADDR(PORTF)> PortF;
#       endif
#       ifdef PING
            typedef ReadonlyRegister<YAAL_ADDR(PING)> PinG;
#       endif
#       ifdef DDRG
            typedef Register<YAAL_ADDR(DDRG)> DdrG;
#       endif
#       ifdef PORTG
            typedef Register<YAAL_ADDR(PORTG)> PortG;
#       endif
    }


#   if defined(PORTA) && defined(DDRA) && defined(PINA)
        typedef Port<internal::PortA, internal::DdrA, internal::PinA> PortA;
#       ifdef PORTA0
#         if defined(YAAL_PORTA0_ADC)
            typedef Pin<PortA, 0, YAAL_PORTA0_ADC> PortA0;
#         else
            typedef Pin<PortA, 0, NullAdc> PortA0;
#         endif
#       endif
#       ifdef PORTA1
#         if defined(YAAL_PORTA1_ADC)
            typedef Pin<PortA, 1, YAAL_PORTA1_ADC> PortA1;
#         else
            typedef Pin<PortA, 1, NullAdc> PortA1;
#         endif
#       endif
#       ifdef PORTA2
#         if defined(YAAL_PORTA2_ADC)
            typedef Pin<PortA, 2, YAAL_PORTA2_ADC> PortA2;
#         else
            typedef Pin<PortA, 2, NullAdc> PortA2;
#         endif
#       endif
#       ifdef PORTA3
#         if defined(YAAL_PORTA3_ADC)
            typedef Pin<PortA, 3, YAAL_PORTA3_ADC> PortA3;
#         else
            typedef Pin<PortA, 3, NullAdc> PortA3;
#         endif
#       endif
#       ifdef PORTA4
#         if defined(YAAL_PORTA4_ADC)
            typedef Pin<PortA, 4, YAAL_PORTA4_ADC> PortA4;
#         else
            typedef Pin<PortA, 4, NullAdc> PortA4;
#         endif
#       endif
#       ifdef PORTA5
#         if defined(YAAL_PORTA5_ADC)
            typedef Pin<PortA, 5, YAAL_PORTA5_ADC> PortA5;
#         else
            typedef Pin<PortA, 5, NullAdc> PortA5;
#         endif
#       endif
#       ifdef PORTA6
#         if defined(YAAL_PORTA6_ADC)
            typedef Pin<PortA, 6, YAAL_PORTA6_ADC> PortA6;
#         else
            typedef Pin<PortA, 6, NullAdc> PortA6;
#         endif
#       endif
#       ifdef PORTA7
#         if defined(YAAL_PORTA7_ADC)
            typedef Pin<PortA, 7, YAAL_PORTA7_ADC> PortA7;
#         else
            typedef Pin<PortA, 7, NullAdc> PortA7;
#         endif
#       endif
#   endif

#   if defined(PORTB) && defined(DDRB) && defined(PINB)
        typedef Port<internal::PortB, internal::DdrB, internal::PinB> PortB;
#       ifdef PORTB0
#         if defined(YAAL_PORTB0_ADC)
            typedef Pin<PortB, 0, YAAL_PORTB0_ADC> PortB0;
#         else
            typedef Pin<PortB, 0, NullAdc> PortB0;
#         endif
#       endif
#       ifdef PORTB1
#         if defined(YAAL_PORTB1_ADC)
            typedef Pin<PortB, 1, YAAL_PORTB1_ADC> PortB1;
#         else
            typedef Pin<PortB, 1, NullAdc> PortB1;
#         endif
#       endif
#       ifdef PORTB2
#         if defined(YAAL_PORTB2_ADC)
            typedef Pin<PortB, 2, YAAL_PORTB2_ADC> PortB2;
#         else
            typedef Pin<PortB, 2, NullAdc> PortB2;
#         endif
#       endif
#       ifdef PORTB3
#         if defined(YAAL_PORTB3_ADC)
            typedef Pin<PortB, 3, YAAL_PORTB3_ADC> PortB3;
#         else
            typedef Pin<PortB, 3, NullAdc> PortB3;
#         endif
#       endif
#       ifdef PORTB4
#         if defined(YAAL_PORTB4_ADC)
            typedef Pin<PortB, 4, YAAL_PORTB4_ADC> PortB4;
#         else
            typedef Pin<PortB, 4, NullAdc> PortB4;
#         endif
#       endif
#       ifdef PORTB5
#         if defined(YAAL_PORTB5_ADC)
            typedef Pin<PortB, 5, YAAL_PORTB5_ADC> PortB5;
#         else
            typedef Pin<PortB, 5, NullAdc> PortB5;
#         endif
#       endif
#       ifdef PORTB6
#         if defined(YAAL_PORTB6_ADC)
            typedef Pin<PortB, 6, YAAL_PORTB6_ADC> PortB6;
#         else
            typedef Pin<PortB, 6, NullAdc> PortB6;
#         endif
#       endif
#       ifdef PORTB7
#         if defined(YAAL_PORTB7_ADC)
            typedef Pin<PortB, 7, YAAL_PORTB7_ADC> PortB7;
#         else
            typedef Pin<PortB, 7, NullAdc> PortB7;
#         endif
#       endif
#   endif

#   if defined(PORTC) && defined(DDRC) && defined(PINC)
        typedef Port<internal::PortC, internal::DdrC, internal::PinC> PortC;
#       ifdef PORTC0
#         if defined(YAAL_PORTC0_ADC)
            typedef Pin<PortC, 0, YAAL_PORTC0_ADC> PortC0;
#         else
            typedef Pin<PortC, 0, NullAdc> PortC0;
#         endif
#       endif
#       ifdef PORTC1
#         if defined(YAAL_PORTC1_ADC)
            typedef Pin<PortC, 1, YAAL_PORTC1_ADC> PortC1;
#         else
            typedef Pin<PortC, 1, NullAdc> PortC1;
#         endif
#       endif
#       ifdef PORTC2
#         if defined(YAAL_PORTC2_ADC)
            typedef Pin<PortC, 2, YAAL_PORTC2_ADC> PortC2;
#         else
            typedef Pin<PortC, 2, NullAdc> PortC2;
#         endif
#       endif
#       ifdef PORTC3
#         if defined(YAAL_PORTC3_ADC)
            typedef Pin<PortC, 3, YAAL_PORTC3_ADC> PortC3;
#         else
            typedef Pin<PortC, 3, NullAdc> PortC3;
#         endif
#       endif
#       ifdef PORTC4
#         if defined(YAAL_PORTC4_ADC)
            typedef Pin<PortC, 4, YAAL_PORTC4_ADC> PortC4;
#         else
            typedef Pin<PortC, 4, NullAdc> PortC4;
#         endif
#       endif
#       ifdef PORTC5
#         if defined(YAAL_PORTC5_ADC)
            typedef Pin<PortC, 5, YAAL_PORTC5_ADC> PortC5;
#         else
            typedef Pin<PortC, 5, NullAdc> PortC5;
#         endif
#       endif
#       ifdef PORTC6
#         if defined(YAAL_PORTC6_ADC)
            typedef Pin<PortC, 6, YAAL_PORTC6_ADC> PortC6;
#         else
            typedef Pin<PortC, 6, NullAdc> PortC6;
#         endif
#       endif
#       ifdef PORTC7
#         if defined(YAAL_PORTC7_ADC)
            typedef Pin<PortC, 7, YAAL_PORTC7_ADC> PortC7;
#         else
            typedef Pin<PortC, 7, NullAdc> PortC7;
#         endif
#       endif
#   endif

#   if defined(PORTD) && defined(DDRD) && defined(PIND)
        typedef Port<internal::PortD, internal::DdrD, internal::PinD> PortD;
#       ifdef PORTD0
#         if defined(YAAL_PORTD0_ADC)
            typedef Pin<PortD, 0, YAAL_PORTD0_ADC> PortD0;
#         else
            typedef Pin<PortD, 0, NullAdc> PortD0;
#         endif
#       endif
#       ifdef PORTD1
#         if defined(YAAL_PORTD1_ADC)
            typedef Pin<PortD, 1, YAAL_PORTD1_ADC> PortD1;
#         else
            typedef Pin<PortD, 1, NullAdc> PortD1;
#         endif
#       endif
#       ifdef PORTD2
#         if defined(YAAL_PORTD2_ADC)
            typedef Pin<PortD, 2, YAAL_PORTD2_ADC> PortD2;
#         else
            typedef Pin<PortD, 2, NullAdc> PortD2;
#         endif
#       endif
#       ifdef PORTD3
#         if defined(YAAL_PORTD3_ADC)
            typedef Pin<PortD, 3, YAAL_PORTD3_ADC> PortD3;
#         else
            typedef Pin<PortD, 3, NullAdc> PortD3;
#         endif
#       endif
#       ifdef PORTD4
#         if defined(YAAL_PORTD4_ADC)
            typedef Pin<PortD, 4, YAAL_PORTD4_ADC> PortD4;
#         else
            typedef Pin<PortD, 4, NullAdc> PortD4;
#         endif
#       endif
#       ifdef PORTD5
#         if defined(YAAL_PORTD5_ADC)
            typedef Pin<PortD, 5, YAAL_PORTD5_ADC> PortD5;
#         else
            typedef Pin<PortD, 5, NullAdc> PortD5;
#         endif
#       endif
#       ifdef PORTD6
#         if defined(YAAL_PORTD6_ADC)
            typedef Pin<PortD, 6, YAAL_PORTD6_ADC> PortD6;
#         else
            typedef Pin<PortD, 6, NullAdc> PortD6;
#         endif
#       endif
#       ifdef PORTD7
#         if defined(YAAL_PORTD7_ADC)
            typedef Pin<PortD, 7, YAAL_PORTD7_ADC> PortD7;
#         else
            typedef Pin<PortD, 7, NullAdc> PortD7;
#         endif
#       endif
#   endif

#   if defined(PORTE) && defined(DDRE) && defined(PINE)
        typedef Port<internal::PortE, internal::DdrE, internal::PinE> PortE;
#       ifdef PORTE0
#         if defined(YAAL_PORTE0_ADC)
            typedef Pin<PortE, 0, YAAL_PORTE0_ADC> PortE0;
#         else
            typedef Pin<PortE, 0, NullAdc> PortE0;
#         endif
#       endif
#       ifdef PORTE1
#         if defined(YAAL_PORTE1_ADC)
            typedef Pin<PortE, 1, YAAL_PORTE1_ADC> PortE1;
#         else
            typedef Pin<PortE, 1, NullAdc> PortE1;
#         endif
#       endif
#       ifdef PORTE2
#         if defined(YAAL_PORTE2_ADC)
            typedef Pin<PortE, 2, YAAL_PORTE2_ADC> PortE2;
#         else
            typedef Pin<PortE, 2, NullAdc> PortE2;
#         endif
#       endif
#       ifdef PORTE3
#         if defined(YAAL_PORTE3_ADC)
            typedef Pin<PortE, 3, YAAL_PORTE3_ADC> PortE3;
#         else
            typedef Pin<PortE, 3, NullAdc> PortE3;
#         endif
#       endif
#       ifdef PORTE4
#         if defined(YAAL_PORTE4_ADC)
            typedef Pin<PortE, 4, YAAL_PORTE4_ADC> PortE4;
#         else
            typedef Pin<PortE, 4, NullAdc> PortE4;
#         endif
#       endif
#       ifdef PORTE5
#         if defined(YAAL_PORTE5_ADC)
            typedef Pin<PortE, 5, YAAL_PORTE5_ADC> PortE5;
#         else
            typedef Pin<PortE, 5, NullAdc> PortE5;
#         endif
#       endif
#       ifdef PORTE6
#         if defined(YAAL_PORTE6_ADC)
            typedef Pin<PortE, 6, YAAL_PORTE6_ADC> PortE6;
#         else
            typedef Pin<PortE, 6, NullAdc> PortE6;
#         endif
#       endif
#       ifdef PORTE7
#         if defined(YAAL_PORTE7_ADC)
            typedef Pin<PortE, 7, YAAL_PORTE7_ADC> PortE7;
#         else
            typedef Pin<PortE, 7, NullAdc> PortE7;
#         endif
#       endif
#   endif

#   if defined(PORTF) && defined(DDRF) && defined(PINF)
        typedef Port<internal::PortF, internal::DdrF, internal::PinF> PortF;
#       ifdef PORTF0
#         if defined(YAAL_PORTF0_ADC)
            typedef Pin<PortF, 0, YAAL_PORTF0_ADC> PortF0;
#         else
            typedef Pin<PortF, 0, NullAdc> PortF0;
#         endif
#       endif
#       ifdef PORTF1
#         if defined(YAAL_PORTF1_ADC)
            typedef Pin<PortF, 1, YAAL_PORTF1_ADC> PortF1;
#         else
            typedef Pin<PortF, 1, NullAdc> PortF1;
#         endif
#       endif
#       ifdef PORTF2
#         if defined(YAAL_PORTF2_ADC)
            typedef Pin<PortF, 2, YAAL_PORTF2_ADC> PortF2;
#         else
            typedef Pin<PortF, 2, NullAdc> PortF2;
#         endif
#       endif
#       ifdef PORTF3
#         if defined(YAAL_PORTF3_ADC)
            typedef Pin<PortF, 3, YAAL_PORTF3_ADC> PortF3;
#         else
            typedef Pin<PortF, 3, NullAdc> PortF3;
#         endif
#       endif
#       ifdef PORTF4
#         if defined(YAAL_PORTF4_ADC)
            typedef Pin<PortF, 4, YAAL_PORTF4_ADC> PortF4;
#         else
            typedef Pin<PortF, 4, NullAdc> PortF4;
#         endif
#       endif
#       ifdef PORTF5
#         if defined(YAAL_PORTF5_ADC)
            typedef Pin<PortF, 5, YAAL_PORTF5_ADC> PortF5;
#         else
            typedef Pin<PortF, 5, NullAdc> PortF5;
#         endif
#       endif
#       ifdef PORTF6
#         if defined(YAAL_PORTF6_ADC)
            typedef Pin<PortF, 6, YAAL_PORTF6_ADC> PortF6;
#         else
            typedef Pin<PortF, 6, NullAdc> PortF6;
#         endif
#       endif
#       ifdef PORTF7
#         if defined(YAAL_PORTF7_ADC)
            typedef Pin<PortF, 7, YAAL_PORTF7_ADC> PortF7;
#         else
            typedef Pin<PortF, 7, NullAdc> PortF7;
#         endif
#       endif
#   endif

#   if defined(PORTG) && defined(DDRG) && defined(PING)
        typedef Port<internal::PortG, internal::DdrG, internal::PinG> PortG;
#       ifdef PORTG0
#         if defined(YAAL_PORTG0_ADC)
            typedef Pin<PortG, 0, YAAL_PORTG0_ADC> PortG0;
#         else
            typedef Pin<PortG, 0, NullAdc> PortG0;
#         endif
#       endif
#       ifdef PORTG1
#         if defined(YAAL_PORTG1_ADC)
            typedef Pin<PortG, 1, YAAL_PORTG1_ADC> PortG1;
#         else
            typedef Pin<PortG, 1, NullAdc> PortG1;
#         endif
#       endif
#       ifdef PORTG2
#         if defined(YAAL_PORTG2_ADC)
            typedef Pin<PortG, 2, YAAL_PORTG2_ADC> PortG2;
#         else
            typedef Pin<PortG, 2, NullAdc> PortG2;
#         endif
#       endif
#       ifdef PORTG3
#         if defined(YAAL_PORTG3_ADC)
            typedef Pin<PortG, 3, YAAL_PORTG3_ADC> PortG3;
#         else
            typedef Pin<PortG, 3, NullAdc> PortG3;
#         endif
#       endif
#       ifdef PORTG4
#         if defined(YAAL_PORTG4_ADC)
            typedef Pin<PortG, 4, YAAL_PORTG4_ADC> PortG4;
#         else
            typedef Pin<PortG, 4, NullAdc> PortG4;
#         endif
#       endif
#       ifdef PORTG5
#         if defined(YAAL_PORTG5_ADC)
            typedef Pin<PortG, 5, YAAL_PORTG5_ADC> PortG5;
#         else
            typedef Pin<PortG, 5, NullAdc> PortG5;
#         endif
#       endif
#       ifdef PORTG6
#         if defined(YAAL_PORTG6_ADC)
            typedef Pin<PortG, 6, YAAL_PORTG6_ADC> PortG6;
#         else
            typedef Pin<PortG, 6, NullAdc> PortG6;
#         endif
#       endif
#       ifdef PORTG7
#         if defined(YAAL_PORTG7_ADC)
            typedef Pin<PortG, 7, YAAL_PORTG7_ADC> PortG7;
#         else
            typedef Pin<PortG, 7, NullAdc> PortG7;
#         endif
#       endif
#   endif

}

#endif
