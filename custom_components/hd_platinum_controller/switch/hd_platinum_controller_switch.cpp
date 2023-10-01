#include "hd_platinum_controller_switch.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace hd_platinum_controller
  {
    static const char *const TAG = "hd_platinum_controller.switch";

    void HDPlatinumControllerSwitch::dump_config()
    {
      ESP_LOGCONFIG("HDPlatinumControllerSwitch", "HDPlatinumControllerSwitch");
      LOG_SWITCH("", "HD Platinum Controller Switch", this);
    }

    void HDPlatinumControllerSwitch::write_state(bool state)
    {
      if (state)
      {
        this->controller_->set_down(this->group_);
      }
      else
      {
        this->controller_->set_up(this->group_);
      }

      publish_state(state);
    }
  }
}
