#include "MotorI2C.h"

MotorI2C::MotorI2C(uint32_t channel, PCA9685 *controller)
{
	this->controller = controller;
	this->channel = channel;
	percentage = 0;
}

void MotorI2C::setSpeed(uint8_t speed)
{
#ifdef TRACE
	printf("MotorI2C::setSpeed: speed [%zu]\n", speed);
#endif

//	if(speed > 100)
//		speed = 100;
//
//	uint32_t stepEnd = 0;
//
//	if(speed > 0)
//		stepEnd = (uint32_t)round(PWM_STEPS * ((float)speed/100));

	uint32_t stepEnd = (speed * 10) + 2000;

	controller->setSpeed(channel, stepEnd);
	percentage = speed;
}

uint8_t MotorI2C::getPercentage()
{
	return percentage;
}

void MotorI2C::stop()
{
	controller->setSpeed(channel,MOTOR_STOP);
}

void MotorI2C::shutdown()
{
	percentage = 0;
	controller->shutdown(channel);
}


