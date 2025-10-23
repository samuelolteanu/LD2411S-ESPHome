import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_DISTANCE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CENTIMETER,
    UNIT_SECOND,
)
from . import LD2411SComponent, CONF_LD2411S_ID

CONF_MAX_MOTION_DISTANCE = "max_motion_distance"
CONF_MIN_MOTION_DISTANCE = "min_motion_distance"
CONF_MAX_PRESENCE_DISTANCE = "max_presence_distance"
CONF_MIN_PRESENCE_DISTANCE = "min_presence_distance"
CONF_UNOCCUPIED_TIME = "unoccupied_time"

DEPENDENCIES = ["ld2411s"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_LD2411S_ID): cv.use_id(LD2411SComponent),
        cv.Optional(CONF_DISTANCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CENTIMETER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MAX_MOTION_DISTANCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CENTIMETER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MIN_MOTION_DISTANCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CENTIMETER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MAX_PRESENCE_DISTANCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CENTIMETER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MIN_PRESENCE_DISTANCE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CENTIMETER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_UNOCCUPIED_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_SECOND,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_LD2411S_ID])
    
    if CONF_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_DISTANCE])
        cg.add(parent.set_distance_sensor(sens))
    
    if CONF_MAX_MOTION_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_MAX_MOTION_DISTANCE])
        cg.add(parent.set_max_motion_sensor(sens))
    
    if CONF_MIN_MOTION_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_MIN_MOTION_DISTANCE])
        cg.add(parent.set_min_motion_sensor(sens))
    
    if CONF_MAX_PRESENCE_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_MAX_PRESENCE_DISTANCE])
        cg.add(parent.set_max_presence_sensor(sens))
    
    if CONF_MIN_PRESENCE_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_MIN_PRESENCE_DISTANCE])
        cg.add(parent.set_min_presence_sensor(sens))
    
    if CONF_UNOCCUPIED_TIME in config:
        sens = await sensor.new_sensor(config[CONF_UNOCCUPIED_TIME])
        cg.add(parent.set_unocc_time_sensor(sens))