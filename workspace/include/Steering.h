#pragma once
#include"system.h"
#include"LeftMotor.h"
#include"RightMotor.h"

class Steering
{
private:
	Steering( );
	~Steering( );

	MOTOR_ANGLE motor_angle;
	LeftMotor &leftMotor = LeftMotor::getInstance();
	RightMotor &rightMotor = RightMotor::getInstance();;

	Steering( const Steering &x );
	Steering&operator=( const Steering & ) { return *this; };

public:
	int8 run( MOTOR_POWER motorPower );
	MOTOR_ANGLE getMotorAngle( void );
	int8 update( );
	int8 deletePort( );

	static Steering &getInstance( )
	{
		static Steering Steering_;
		return Steering_;
	}
};