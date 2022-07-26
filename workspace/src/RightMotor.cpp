#include "../include/system.h"
#include "../include/RightMotor.h"
#include "../include/Motor.h"

RightMotor::RightMotor()
{
    portNum = EV3_PORT_B;
    ev3_motor_config( static_cast<motor_port_t>(portNum), LARGE_MOTOR);
}

RightMotor::~RightMotor()
{
}