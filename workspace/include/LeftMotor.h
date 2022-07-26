#pragma once
#include"system.h"
#include"Motor.h"

class LeftMotor:public Motor
{
private:
    /* data */

    LeftMotor();
    ~LeftMotor();
    LeftMotor( const LeftMotor &x );
	LeftMotor&operator=( const LeftMotor & ) { return *this; };
public:

    static LeftMotor &getInstance( )
	{
		static LeftMotor LeftMotor_;
		return LeftMotor_;
	}
};