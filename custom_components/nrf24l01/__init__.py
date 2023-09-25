import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN

DEPENDENCIES = ["spi"]
MULTI_CONF = True

CONF_CE_PIN = "ce_pin"

nrf24lo1_ns = cg.esphome_ns.namespace("nRF24L01")

nRF24L01 = nrf24lo1_ns.class_("nRF24L01", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.declare_id(nRF24L01),
            cv.Required(CONF_CE_PIN): pins.gpio_output_pin_schema,
        }
    )
    .extend(spi.spi_device_schema())
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_cs_pin(config[CONF_CS_PIN]))
    cg.add(var.set_ce_pin(config[CONF_CE_PIN]))
    cg.add_library("nrf24/RF24", None)
    cg.add_library("SPI", None)
