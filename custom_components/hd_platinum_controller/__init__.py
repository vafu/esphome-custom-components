import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import switch

hd_platinum_controller_ns = cg.esphome_ns.namespace("hd_platinum_controller")
HDPlatinumController = hd_platinum_controller_ns.class_(
    "HDPlatinumController", cg.Component
)

CONF_REMOTE_ID = "remote_id"
CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(HDPlatinumController),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
