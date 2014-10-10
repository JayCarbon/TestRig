#ifndef MOTORI2C_HPP_
#define MOTORI2C_HPP_

#include <cstdio>
#include <cmath>
#include <stdint.h>
#include <unistd.h>
#include "../PCA9685/PCA9685.h"

#define MOTOR_STOP			(uint16_t)2000
#define MOTOR_MAX			(uint16_t)3000

enum {
	CHANNEL0 = 0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3
};

class MotorI2C
{

public:
	MotorI2C(uint32_t channel, PCA9685 *controller);
	void setSpeed(uint8_t speed);
	uint8_t getPercentage();
	//Set Motor to 0%
	void stop();
	//Shutdown Motor PWM Timer
	void shutdown();

private:
	uint8_t channel;
	uint8_t percentage;
	PCA9685 *controller;
};

#endif /* MOTORI2C_HPP_ */
