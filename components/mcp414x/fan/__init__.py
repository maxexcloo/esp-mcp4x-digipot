import esphome.codegen as cg
from esphome.components import fan
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_SPEED_COUNT

from .. import mcp414x_ns, MCP414X

CONF_MCP414X_ID = "mcp414x_id"

MCP414XFan = mcp414x_ns.class_("MCP414XFan", fan.Fan, cg.Component)

CONFIG_SCHEMA = (
    fan.fan_schema(MCP414XFan)
    .extend(
        {
            cv.GenerateID(CONF_MCP414X_ID): cv.use_id(MCP414X),
            cv.Optional(CONF_SPEED_COUNT, default=100): cv.int_range(min=1, max=128),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await fan.new_fan(config, config[CONF_SPEED_COUNT])
    await cg.register_component(var, config)

    parent = await cg.get_variable(config[CONF_MCP414X_ID])
    cg.add(var.set_parent(parent))
