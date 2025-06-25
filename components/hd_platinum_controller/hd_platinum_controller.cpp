#include "esphome/core/log.h"
#include "hd_platinum_controller.h"

namespace esphome
{
  namespace hd_platinum_controller
  {
    static const char *const TAG = "hd_platinum_controller";

    void IRAM_ATTR static_isr() {
      // This function is required to be in IRAM, but doesn't need to do anything for this component.
    }


    void HDPlatinumController::setup()
    {
      this->radio = new RF24(this->ce_, this->cs_);
      setupRF24();
    }

    void HDPlatinumController::dump_config()
    {
      ESP_LOGCONFIG(TAG, "HD Platinum Controller:");
      ESP_LOGCONFIG(TAG, "  CS: %d", this->cs_);
      ESP_LOGCONFIG(TAG, "  CE: %d", this->ce_);
      ESP_LOGCONFIG(TAG, "  IRQ Pin: %d", this->irq_pin_);
      ESP_LOGCONFIG(TAG, "  RemoteID: %04x", this->remote_id_);
    }

    void HDPlatinumController::setupRF24()
    {
      ESP_LOGI(TAG, "Setting up RF24...");
      if (this->radio->begin())
      {
        this->radio->setChannel(RF_CHANNEL_0);
        this->radio->setPayloadSize(RF_PAYLOAD_SIZE);
        this->radio->setDataRate(RF_DATARATE);
        this->radio->stopListening();
        this->radio->openWritingPipe(RF_RESET_VALUE);
        this->radio->setPALevel(RF_POWER);
        this->radio->setAutoAck(false);
        this->radio->setAddressWidth(3);
        this->radio->setRetries(0, 0);
        this->radio->maskIRQ(false, true, true); // one way comms so only care about transmit
        attachInterrupt(
            digitalPinToInterrupt(this->irq_pin_), static_isr, FALLING);
        ESP_LOGD(TAG, "  RF24 setup complete");
      }
      else
      {
        ESP_LOGI(TAG, "  RF24 setup failed");
      }
    }

    void HDPlatinumController::set_up(SHADE_GROUP group)
    {
      ESP_LOGI(TAG, "Setting shade group %d to up", group);
      move_shades(group, SHADE_UP);
    }

    void HDPlatinumController::set_down(SHADE_GROUP group)
    {
      ESP_LOGI(TAG, "Setting shade group %d to down", group);
      move_shades(group, SHADE_DOWN);
    }

    void HDPlatinumController::move_shades(SHADE_GROUP group, SHADE_COMMAND command)
    {
      // Make sure the radio has a 5 byte payload and CRC is enabled
      this->radio->setPayloadSize(RF_PAYLOAD_SIZE);
      this->radio->setCRCLength(RF24_CRC_16);
      /**
       * Command payload is 5 bytes:
       *
       * 1 and 2: remote control ID
       * 3: whether a goup code was selected (0x10 for no, 0x20 for yes). we always send to specific shades so this is always 0x20
       * 4: group code (0x01, 0x02, 0x04, 0x08, or 0xff for all)
       * 5: command (0xa1 for up, 0xa2 for down)
       */
      uint8_t payload[RF_PAYLOAD_SIZE] = {0};
      payload[0] = this->remote_id_ >> 8;
      payload[1] = this->remote_id_ & 0xff;
      payload[2] = 0x20;
      payload[3] = group;
      payload[4] = command;
      ESP_LOGD("HDPlatinumController", "Sending payload: {%02x, %02x, %02x, %02x, %02x}", payload[0], payload[1], payload[2], payload[3], payload[4]);

      for (int j = 0; j <= 2; j++)
      {
        for (int i = 0; i < 250; i++)
        {
          this->radio->writeFast(payload, RF_PAYLOAD_SIZE, true);
          if (i % 3 == 0)
            this->radio->setChannel(RF_CHANNEL_0);
          if (i % 3 == 1)
            this->radio->setChannel(RF_CHANNEL_1);
          if (i % 3 == 2)
            this->radio->setChannel(RF_CHANNEL_2);
          delayMicroseconds(75);
        }
        this->radio->flush_tx();
        this->radio->txStandBy();
      }
    }

    HDPlatinumController::~HDPlatinumController()
    {
      delete this->radio;
    }
  }
}
