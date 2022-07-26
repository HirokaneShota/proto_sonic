#pragma once
#include"system.h"
#include "ev3api.h"

class Motor
{
protected:
	motor_port_t portNum;
public:
	Motor( );
	~Motor( );
	int8_t setPWM( int8_t );
	float getCounts();
	
private:
	
};