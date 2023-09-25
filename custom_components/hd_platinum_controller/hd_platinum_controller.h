#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include <RF24.h>

namespace esphome
{
  namespace hd_platinum_controller
  {

    // Hunter Douglas shades use channels 33, 52, and 71
    const uint8_t RF_CHANNEL_0 = 33;
    const uint8_t RF_CHANNEL_1 = 52;
    const uint8_t RF_CHANNEL_2 = 71;

    // Radio settings. Hunter Douglas uses a 2 Mb/s rate
    const rf24_datarate_e RF_DATARATE = RF24_2MBPS;
    const rf24_pa_dbm_e RF_POWER = RF24_PA_MAX;
    const uint64_t RF_RESET_VALUE = 0xe7e7e7;

    // Pin D1 on the ESP32 is connected to RST on the MikroBus
    // See https://learn.sparkfun.com/tutorials/micromod-mikrobus-carrier-board-hookup-guide/hardware-overview
    // and https://learn.sparkfun.com/tutorials/micromod-esp32-processor-board-hookup-guide/hardware-overview
    // TODO: move this to config
    const uint8_t RF_CE_PIN = 27; // This is D1 (ESP32 Pin 27) for Chip Enable
    const uint8_t RF_CS_PIN = 5;  // This is GPIO5 (ESP32 Pin 5) for Chip Select

    class HDPlatinumController : public Component, public switch ::Switch
    {
      RF24 tx;
      void setupRF24();

    public:
      void setup() override;
      void loop() override;
      void dump_config() override;
      void write_state(bool state) override;
    };

  } // namespace empty_component
} // namespace esphome
