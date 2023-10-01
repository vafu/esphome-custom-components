#pragma once

#include "esphome/core/component.h"
#include <RF24.h>

namespace esphome
{
  namespace hd_platinum_controller
  {
    // Hunter Douglas shades use channels 33, 52, and 71
    const uint8_t RF_CHANNEL_0 = 33;
    const uint8_t RF_CHANNEL_1 = 52;
    const uint8_t RF_CHANNEL_2 = 71;

    // Hunter Douglas uses a 2 Mb/s rate
    const rf24_datarate_e RF_DATARATE = RF24_2MBPS;

    // Max transmit power
    const rf24_pa_dbm_e RF_POWER = RF24_PA_MAX;

    // Default TX reset address
    const uint64_t RF_RESET_VALUE = 0xe7e7e7;

    const uint8_t RF_PAYLOAD_SIZE = 5;

    // Shade commands
    enum SHADE_COMMAND : uint8_t
    {
      SHADE_UP = 0xa1,
      SHADE_DOWN = 0xa2
    };

    // Groups in the Platinum protocol are specified by a 1 in the bit position
    // The group is 1 byte in length with all groups specificed by 0x11111111 or 0xff
    enum SHADE_GROUP : u_int8_t
    {
      SHADE_GROUP_1 = 1,
      SHADE_GROUP_2 = 1 << 1,
      SHADE_GROUP_3 = 1 << 2,
      SHADE_GROUP_4 = 1 << 3,
      // there are only 4 buttons on controllers but the protocol supports 8 groups
      SHADE_GROUP_5 = 1 << 4,
      SHADE_GROUP_6 = 1 << 5,
      SHADE_GROUP_7 = 1 << 6,
      SHADE_GROUP_8 = 1 << 7,
      SHADE_GROUP_ALL = 0xff
    };

    class HDPlatinumController : public Component
    {

    public:
      ~HDPlatinumController();

      void setup() override;
      void dump_config() override;

      void set_cs_pin(rf24_gpio_pin_t cs) { this->cs_ = cs; }
      void set_ce_pin(rf24_gpio_pin_t ce) { this->ce_ = ce; }
      void set_remote_id(uint32_t remote_id) { this->remote_id_ = remote_id; }

      void set_up(SHADE_GROUP group);
      void set_down(SHADE_GROUP group);

    private:
      rf24_gpio_pin_t cs_;
      rf24_gpio_pin_t ce_;
      uint16_t remote_id_;
      RF24 *radio;

      void setupRF24();
      void move_shades(SHADE_GROUP group, SHADE_COMMAND command);
    };
  }; // namespace hd_platinum_controller
} // namespace esphome
