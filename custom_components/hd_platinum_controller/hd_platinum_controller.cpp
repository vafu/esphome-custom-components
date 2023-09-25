#include <SPI.h>
#include "esphome/core/log.h"
#include "hd_platinum_controller.h"

namespace esphome
{
  namespace hd_platinum_controller
  {

    void HDPlatinumController::setup()
    {
      tx = RF24(RF_CE_PIN, RF_CS_PIN); // (CE, CS)
      // NRF24 setup
      setupRF24();
    }

    void HDPlatinumController::loop()
    {
      // This will be called every "loop" by esphome
    }

    void HDPlatinumController::dump_config()
    {
      ESP_LOGCONFIG("HD Platinum Controller");
    }

    void HDPlatinumController::setupRF24()
    {
      tx.begin();
      tx.setChannel(RF_CHANNEL_0);
      tx.setPayloadSize(5);
      tx.setDataRate(RF_DATARATE);        // HD Remote uses 2Mbs
      tx.openWritingPipe(RF_RESET_VALUE); // "Reset Value" for nRF24 Tx address
      tx.stopListening();
      tx.setPALevel(RF_POWER);
      tx.setAutoAck(false);
      tx.setAddressWidth(3);
      tx.setRetries(0, 0);
    }

    void HDPlatinumController::write_state(bool state)
    {
    }
  }
}
