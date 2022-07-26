#include"../include/Steering.h"

Steering::Steering( )
{
	motor_angle.left = 0;
	motor_angle.right = 0;
}

Steering::~Steering( ) {}

int8 Steering::run( MOTOR_POWER motor_power )
{
	if ( motor_power.left < -100 || motor_power.left > 100 ||
		motor_power.right < -100 || motor_power.right > 100 )
	{
		return SYS_PARAM;
	}

	int8 retChk = SYS_NG;

	retChk = rightMotor.setPWM( motor_power.right );
	if ( retChk != SYS_OK ) {
		return retChk;
	}

	retChk = leftMotor.setPWM( motor_power.left );
	if ( retChk != SYS_OK ) {
		return retChk;
	}

	return SYS_OK;
}

MOTOR_ANGLE Steering::getMotorAngle( void )
{
	return motor_angle;
}

int8 Steering::update( )
{
	int8 retChk = SYS_NG;                       

	motor_angle.left = leftMotor.getCounts( );

	motor_angle.right = rightMotor.getCounts( );
	
	if ( motor_angle.right - motor_angle.left < 3 &&
		motor_angle.right - motor_angle.left>0 ) {

		motor_angle.left = motor_angle.right;
	}
	else if ( motor_angle.left - motor_angle.right < 3 &&
		motor_angle.left - motor_angle.right>0 ) {

		motor_angle.right = motor_angle.left;
	}

	return SYS_OK;
}

int8 Steering::deletePort( ) {
	//delete (&leftMotor);
	//delete (&rightMotor);
	return SYS_OK;
}