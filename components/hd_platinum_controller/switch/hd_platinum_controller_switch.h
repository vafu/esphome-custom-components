#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../hd_platinum_controller.h"

namespace esphome
{
  namespace hd_platinum_controller
  {
    class HDPlatinumControllerSwitch : public switch_::Switch, public Component
    {
    public:
      void dump_config() override;
      void set_group(uint8_t group) { this->group_ = static_cast<SHADE_GROUP>(group); }
      void set_controller(HDPlatinumController *controller) { this->controller_ = controller; }

    protected:
      void write_state(bool state) override;

    private:
      SHADE_GROUP group_;
      HDPlatinumController *controller_;
    };
  };
};
