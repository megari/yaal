#ifndef __YAAL_DEVICE__TOUCHSCREEN4D__
#define __YAAL_DEVICE__TOUCHSCREEN4D__ 1
#include "../requirements.hh"
#ifdef __YAAL__

namespace yaal {

    namespace internal {
        static constexpr uint8_t ACK = 0x06;
        static constexpr uint8_t NAK = 0x15;

        static constexpr uint8_t AUTOBAUD = 0x55;
        static constexpr uint8_t SETBAUD = 0x51;

        static constexpr uint8_t DISPCONTROL = 0x59;
        static constexpr uint8_t DISPCONTROL_TOUCH = 0x05;
        static constexpr uint8_t DISPCONTROL_TOUCH_ENABLE = 0x00;
        static constexpr uint8_t DISPCONTROL_TOUCH_DISABLE = 0x01;
        static constexpr uint8_t DISPCONTROL_TOUCH_RESET_ACTIVE = 0x02;

        static constexpr uint8_t CLEARSCREEN = 0x45;
        static constexpr uint8_t DRAWCHAR_TEXT = 0x54;
        static constexpr uint8_t DRAWELLIPSE = 0x65;
        static constexpr uint8_t SETPENSIZE = 0x70;
        static constexpr uint8_t PEN_SOLID = 0x00;
        static constexpr uint8_t PEN_WIREFRAME = 0x01;

        static constexpr uint8_t TOUCHCOORDS = 0x6f;
        static constexpr uint8_t TOUCHCOORDS_WAIT_ANY = 0x00;
        static constexpr uint8_t TOUCHCOORDS_WAIT_PRESS = 0x01;
        static constexpr uint8_t TOUCHCOORDS_WAIT_RELEASE = 0x02;
        static constexpr uint8_t TOUCHCOORDS_WAIT_MOVING = 0x03;
        static constexpr uint8_t TOUCHCOORDS_STATUS = 0x04; // FIXME -> enum
        static constexpr uint8_t TOUCHCOORDS_GETCOORDINATES = 0x05;
    }

    template <typename T>
    class Touchscreen4D {
    private:
        T serial;

    public:

        YAAL_INLINE("4D touchscreen init")
        bool init(uint32_t baud = 9600) {
            serial.setBaud(baud);
            serial.setFrameFormat();
            serial.transmit(internal::AUTOBAUD);
            return serial.receive() == internal::ACK;
        }

        YAAL_INLINE("4D touchscreen set baud")
        bool set_baud(uint32_t baud) {
            uint8_t rate;
            switch (baud) {
                case 110:
                    rate = 0x00;
                    break;
                case 300:
                    rate = 0x01;
                    break;
                case 600:
                    rate = 0x02;
                    break;
                case 1200:
                    rate = 0x03;
                    break;
                case 2400:
                    rate = 0x04;
                    break;
                case 4800:
                    rate = 0x05;
                    break;
                case 9600:
                    rate = 0x06;
                    break;
                case 14400:
                    rate = 0x07;
                    break;
                case 19200:
                    rate = 0x08;
                    break;
                case 31250:
                    rate = 0x09;
                    break;
                case 38400:
                    rate = 0x0a;
                    break;
                case 56000:
                    rate = 0x0b;
                    break;
                case 57600:
                    rate = 0x0c;
                    break;
                case 115200:
                    rate = 0x0d;
                    break;
                case 129032:
                    rate = 0x0e;
                    break;
                case 282353:
                    rate = 0x0f;
                    break;
                case 128000:
                    rate = 0x10;
                    break;
                case 256000:
                    rate = 0x11;
                    break;
                default:
                    rate = 0xff;
                    return false;
            }

            serial.transmit(internal::SETBAUD);
            serial.transmit(rate);
            if (serial.receive() != internal::ACK)
                return false;

            serial.setBaud(baud);
            return true;
        }

        // Draw ASCII character in the given color.
        // The color format is R5G6B5.
        bool draw_char(uint8_t c, uint8_t x, uint8_t y, uint16_t color = 0xffff) {
            serial.transmit(internal::DRAWCHAR_TEXT);
            serial.transmit(c);
            serial.transmit(x);
            serial.transmit(y);
            serial.transmit(color);
            return serial.receive() == internal::ACK;
        }

        // Draw an ellipse in the given color.
        // The color format is R5G6B5.
        bool draw_ellipse(uint16_t x, uint16_t y, uint16_t rx, uint16_t ry, uint16_t color) {
            serial.transmit(internal::DRAWELLIPSE);
            serial.transmit(x); // X coordinate of center
            serial.transmit(y); // Y coordinate of center
            serial.transmit(rx); // Radius in the X axis
            serial.transmit(ry); // Radius in the Y axis
            serial.transmit(color); // Color
            return serial.receive() == internal::ACK;
        }

        bool set_pen_size(bool solid) {
            serial.transmit(internal::SETPENSIZE);
            serial.transmit(solid ? internal::PEN_SOLID : internal::PEN_WIREFRAME);
            return serial.receive() == internal::ACK;
        }

        bool clear_screen() {
            serial.transmit(internal::CLEARSCREEN);
            return serial.receive() == internal::ACK;
        }

        bool toggle_touchscreen(bool enabled) {
            serial.transmit(internal::DISPCONTROL);
            serial.transmit(internal::DISPCONTROL_TOUCH);
            serial.transmit(enabled ? internal::DISPCONTROL_TOUCH_ENABLE
                                    : internal::DISPCONTROL_TOUCH_DISABLE);
            return serial.receive() == internal::ACK;
        }

        bool reset_active_touch_region() {
            serial.transmit(internal::DISPCONTROL);
            serial.transmit(internal::DISPCONTROL_TOUCH);
            serial.transmit(internal::DISPCONTROL_TOUCH_RESET_ACTIVE);
            return serial.receive() == internal::ACK;
        }

        enum TouchActType : uint8_t {
            ACT_NONE = 0,
            ACT_PRESS = 1,
            ACT_RELEASE = 2,
            ACT_MOVING = 3
        };

        enum TouchActType get_touch_status() {
            serial.transmit(internal::TOUCHCOORDS);
            serial.transmit(internal::TOUCHCOORDS_STATUS);

            uint8_t response[4];
            for (int i = 0; i < 4; ++i)
                response[i] = serial.receive();

            return static_cast<TouchActType>(response[1]);
        }

        struct TouchCoords {
            uint16_t x;
            uint16_t y;
        };

        TouchCoords get_touch_coordinates() {
            serial.transmit(internal::TOUCHCOORDS);
            serial.transmit(internal::TOUCHCOORDS_GETCOORDINATES);

            uint8_t response[4];
            for (int i = 0; i < 4; ++i)
                    response[i] = serial.receive();

            TouchCoords ret = { (uint16_t)(response[0] << 8 | response[1]),
                                (uint16_t)(response[2] << 8 | response[3]) };
            return ret;
        }

        enum TouchKind : uint8_t {
            WAIT_ANY = internal::TOUCHCOORDS_WAIT_ANY,
            WAIT_PRESS = internal::TOUCHCOORDS_WAIT_PRESS,
            WAIT_RELEASE = internal::TOUCHCOORDS_WAIT_RELEASE,
            WAIT_MOVING = internal::TOUCHCOORDS_WAIT_MOVING
        };

        TouchCoords wait_until_touch(TouchKind kind = WAIT_ANY) {
            serial.transmit(internal::TOUCHCOORDS);
            serial.transmit(static_cast<uint8_t>(kind));

            uint8_t response[4];
            for (int i = 0; i < 4; ++i)
                    response[i] = serial.receive();

            TouchCoords ret = { (uint16_t)(response[0] << 8 | response[1]),
                                (uint16_t)(response[2] << 8 | response[3]) };
            return ret;
        }

    };

}

#endif
#endif
