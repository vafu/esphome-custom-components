#pragma once

#include "esphome/core/component.h"
#include <RF24.h>

namespace esphome
{
  namespace nRF24L01
  {
    class nRF24L01 : public Component
    {
    public:
      void setup() override;
      void loop() override;
      void dump_config() override;

    protected:
      void set_cs_pin(rf24_gpio_pin_t cs) { this->cs_ = cs; }};
      void set_ce_pin(rf24_gpio_pin_t ce) { this->ce_ = ce; }};

    private:
      rf24_gpio_pin_t cs_;
      rf24_gpio_pin_t ce_;
    }
  }
}
