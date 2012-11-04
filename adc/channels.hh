#ifndef __YAAL_ADC__INPUTS__
#define __YAAL_ADC__INPUTS__ 1

#include "types.hh"
#include "defines.hh"

namespace yaal {

# if defined(YAAL_ADC0)
    typedef AdcSingleChannel<YAAL_ADC0, adc_> Adc0;
# endif
# if defined(YAAL_ADC1)
    typedef AdcSingleChannel<YAAL_ADC1, adc_> Adc1;
# endif
# if defined(YAAL_ADC2)
    typedef AdcSingleChannel<YAAL_ADC2, adc_> Adc2;
# endif
# if defined(YAAL_ADC3)
    typedef AdcSingleChannel<YAAL_ADC3, adc_> Adc3;
# endif
# if defined(YAAL_ADC4)
    typedef AdcSingleChannel<YAAL_ADC4, adc_> Adc4;
# endif
# if defined(YAAL_ADC5)
    typedef AdcSingleChannel<YAAL_ADC5, adc_> Adc5;
# endif
# if defined(YAAL_ADC6)
    typedef AdcSingleChannel<YAAL_ADC6, adc_> Adc6;
# endif
# if defined(YAAL_ADC7)
    typedef AdcSingleChannel<YAAL_ADC7, adc_> Adc7;
# endif
# if defined(YAAL_ADC8)
    typedef AdcSingleChannel<YAAL_ADC8, adc_> Adc8;
# endif
# if defined(YAAL_ADC9)
    typedef AdcSingleChannel<YAAL_ADC9, adc_> Adc9;
# endif
# if defined(YAAL_ADC10)
    typedef AdcSingleChannel<YAAL_ADC10, adc_> Adc10;
# endif
# if defined(YAAL_ADC11)
    typedef AdcSingleChannel<YAAL_ADC11, adc_> Adc11;
# endif
# if defined(YAAL_ADC12)
    typedef AdcSingleChannel<YAAL_ADC12, adc_> Adc12;
# endif
# if defined(YAAL_ADC13)
    typedef AdcSingleChannel<YAAL_ADC13, adc_> Adc13;
# endif
# if defined(YAAL_ADC14)
    typedef AdcSingleChannel<YAAL_ADC14, adc_> Adc14;
# endif
# if defined(YAAL_ADC15)
    typedef AdcSingleChannel<YAAL_ADC15, adc_> Adc15;
# endif
# if defined(YAAL_ADC16)
    typedef AdcSingleChannel<YAAL_ADC16, adc_> Adc16;
# endif
# if defined(YAAL_ADC17)
    typedef AdcSingleChannel<YAAL_ADC17, adc_> Adc17;
# endif
# if defined(YAAL_ADC18)
    typedef AdcSingleChannel<YAAL_ADC18, adc_> Adc18;
# endif
# if defined(YAAL_ADC19)
    typedef AdcSingleChannel<YAAL_ADC19, adc_> Adc19;
# endif
# if defined(YAAL_ADC20)
    typedef AdcSingleChannel<YAAL_ADC20, adc_> Adc20;
# endif

# if defined(YAAL_ADC_GND)
    typedef AdcSingleChannel<YAAL_ADC_GND, adc_> AdcGnd;
# endif
# if defined(YAAL_ADC_TEMP)
    typedef AdcSingleChannel<YAAL_ADC_TEMP, adc_> AdcTemp;
# endif

}

#endif
