#include "../include/system.h"
#include "../include/LeftMotor.h"
#include "../include/Motor.h"

LeftMotor::LeftMotor()
{
	portNum = EV3_PORT_C;
	ev3_motor_config( static_cast<motor_port_t>(portNum), LARGE_MOTOR );
}

LeftMotor::~LeftMotor()
{
}