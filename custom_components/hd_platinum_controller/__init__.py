import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CS_PIN

DEPENDENCIES = ["spi"]
MULTI_CONF = True

CONF_CE_PIN = "ce_pin"
CONF_REMOTE_ID = "remote_id"

hd_platinum_controller_ns = cg.esphome_ns.namespace("hd_platinum_controller")
HDPlatinumController = hd_platinum_controller_ns.class_(
    "HDPlatinumController", cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(HDPlatinumController),
        cv.Required(CONF_REMOTE_ID): cv.uint16_t,
        cv.Required(CONF_CE_PIN): cv.uint8_t,
        cv.Required(CONF_CS_PIN): cv.uint8_t,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_cs_pin(config[CONF_CS_PIN]))
    cg.add(var.set_ce_pin(config[CONF_CE_PIN]))
    cg.add(var.set_remote_id(config[CONF_REMOTE_ID]))

    cg.add_library("nrf24/RF24", None)
    cg.add_library("SPI", None)
