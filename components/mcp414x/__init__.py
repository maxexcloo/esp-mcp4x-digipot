import esphome.codegen as cg
from esphome.components import spi, number
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_MIN_VALUE, CONF_MAX_VALUE, CONF_STEP

CODEOWNERS = ["@ellsclytn"]
DEPENDENCIES = ["spi"]
AUTO_LOAD = ["number", "fan"]
MULTI_CONF = True

CONF_INITIAL_VALUE = "initial_value"

mcp414x_ns = cg.esphome_ns.namespace("mcp414x")
MCP414X = mcp414x_ns.class_("MCP414X", number.Number, cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = (
    number.number_schema(MCP414X)
    .extend(
        {
            cv.Optional(CONF_INITIAL_VALUE, default=0): cv.int_range(min=0, max=128),
            cv.Optional(CONF_MIN_VALUE, default=0): cv.int_range(min=0, max=128),
            cv.Optional(CONF_MAX_VALUE, default=128): cv.int_range(min=0, max=128),
            cv.Optional(CONF_STEP, default=1): cv.positive_int,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True))
)


async def to_code(config):
    var = await number.new_number(
        config,
        min_value=config[CONF_MIN_VALUE],
        max_value=config[CONF_MAX_VALUE],
        step=config[CONF_STEP],
    )
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
