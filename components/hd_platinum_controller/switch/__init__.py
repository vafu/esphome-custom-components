import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_SWITCHES
from esphome.components import switch
from .. import hd_platinum_controller_ns, HDPlatinumController

# MULTI_CONF = True

CONF_GROUP_NUMBER = "group"
CONF_CONTROLLER_ID = "controller_id"

HDPlatinumControllerSwitch = hd_platinum_controller_ns.class_(
    "HDPlatinumControllerSwitch", switch.Switch
)

SWITCH_CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_GROUP_NUMBER): cv.uint8_t,
    }
).extend(switch.switch_schema(HDPlatinumControllerSwitch))

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(HDPlatinumControllerSwitch),
        cv.GenerateID(CONF_CONTROLLER_ID): cv.use_id(HDPlatinumController),
        cv.Required(CONF_SWITCHES): cv.ensure_list(SWITCH_CONFIG_SCHEMA),
    }
)


async def to_code(config):
    controller = await cg.get_variable(config[CONF_CONTROLLER_ID])

    for i, conf in enumerate(config[CONF_SWITCHES]):
        switch_ = cg.new_Pvariable(conf[CONF_ID])
        cg.add(switch_.set_group(cg.uint8(conf[CONF_GROUP_NUMBER])))
        cg.add(switch_.set_controller(controller))
        await switch.register_switch(switch_, conf)
