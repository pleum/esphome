import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import CONF_UPDATE_INTERVAL

DEPENDENCIES = ["uart"]

pms9103m_ns = cg.esphome_ns.namespace("pms9103m")
PMS9103MComponent = pms9103m_ns.class_(
    "PMS9103MComponent", uart.UARTDevice, cg.Component
)
PMS9103MSensor = pms9103m_ns.class_("PMS9103MSensor", sensor.Sensor)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PMS9103MComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


def final_validate(config):
    require_tx = config[CONF_UPDATE_INTERVAL] > cv.time_period("0s")
    schema = uart.final_validate_device_schema(
        "pms9103m", baud_rate=9600, require_rx=True, require_tx=require_tx
    )
    schema(config)


FINAL_VALIDATE_SCHEMA = final_validate
