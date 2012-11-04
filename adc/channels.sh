#!/bin/sh

cat <<EOF
#ifndef __YAAL_ADC__INPUTS__
#define __YAAL_ADC__INPUTS__ 1

#include "types.hh"
#include "defines.hh"

namespace yaal {

EOF

capitalize() {
    echo "$1" | tr '[A-Z]' '[a-z]' | sed 's/^./\U&/g'
}

for i in $(seq 0 20); do
    cat <<EOF
# if defined(YAAL_ADC${i})
    typedef AdcSingleChannel<YAAL_ADC${i}, adc_> Adc${i};
# endif
EOF
done

echo

for n in GND TEMP; do
    cat <<EOF
# if defined(YAAL_ADC_${n})
    typedef AdcSingleChannel<YAAL_ADC_${n}, adc_> Adc$(capitalize ${n});
# endif
EOF
done

cat <<EOF

}

#endif
EOF
