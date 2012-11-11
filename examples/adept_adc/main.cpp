#include "yaal/io.hh"
#include "yaal/adc.hh"

using namespace yaal;

PortB1 led;
adc_ adc;
PortF0 sensor;

int main(void) {

    led.mode = OUTPUT;
    adc.prescaler = AnalogDigitalConverter::Prescaler::FAST;
    adc.enable();
    sensor.mode = INPUT;

    uint16_t value = sensor.analog.get();

    if (value > 600)
        led = true;

    return 0;
}
