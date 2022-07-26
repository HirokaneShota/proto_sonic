#include "../include/system.h"
#include "../include/Motor.h"

Motor::Motor( )
{
	//ev3_motor_config( static_cast<motor_port_t>(port), type );
}

Motor::~Motor( )
{
}

int8_t Motor::setPWM(int8_t motorPower)
{
	if ( motorPower < -100 || motorPower > 100 )
	{
		return SYS_PARAM;
	}

	ev3_motor_set_power( static_cast<motor_port_t>(portNum), motorPower );

	return SYS_OK;
}


float Motor::getCounts(void)
{
	float motorAngle = 0.0f;

	motorAngle = ev3_motor_get_counts( static_cast<motor_port_t>(portNum) );

	return motorAngle;
}