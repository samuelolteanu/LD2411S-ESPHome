import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
    DEVICE_CLASS_OCCUPANCY,
    DEVICE_CLASS_MOTION,
)
from . import LD2411SComponent, CONF_LD2411S_ID

CONF_PRESENCE = "presence"
CONF_MOTION = "motion"

DEPENDENCIES = ["ld2411s"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_LD2411S_ID): cv.use_id(LD2411SComponent),
        cv.Optional(CONF_PRESENCE): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_OCCUPANCY
        ),
        cv.Optional(CONF_MOTION): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_MOTION
        ),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_LD2411S_ID])
    
    if CONF_PRESENCE in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_PRESENCE])
        cg.add(parent.set_presence_binary_sensor(sens))
    
    if CONF_MOTION in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_MOTION])
        cg.add(parent.set_motion_binary_sensor(sens))