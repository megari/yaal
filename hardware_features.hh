#ifndef __YAAL_HARDWARE_FEATURES__
#define __YAAL_HARDWARE_FEATURES__ 1

// does hw support toggling PORT via writing 1 to PINx register?
// FIXME: add boards after checking their manual
#if defined(__AVR_ATmega32U4__) \
 || defined(__AVR_ATmega16U4__)
#     define AVR_WITH_PIN_TOGGLE 1
#endif


#endif
