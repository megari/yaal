#include <yaal/arduino.hh>
#include <yaal/devices/rgbled.hh>
#include <util/delay.h>

BasicRGBLed<D1, D2, D0> rgb;

void setup() {
    rgb.setup();
}

void loop() {
    rgb.off();
    _delay_ms(800);
    rgb.red();
    _delay_ms(800);
    rgb.yellow();
    _delay_ms(800);
    rgb.green();
    _delay_ms(800);
    rgb.cyan();
    _delay_ms(800);
    rgb.blue();
    _delay_ms(800);
    rgb.magenta();
    _delay_ms(800);
    rgb.white();
    _delay_ms(800);
}
