#include "MotorI2C/MotorI2C.h"
#include "PCA9685/PCA9685.h"
#include "RcChannel/RcChannel.h"
#include "IMU.h"
#include "PID.h"
#include "Copter.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

PCA9685 *motorController;

bool MotorsStartup = false;
bool MotorsArmed = false;
bool MotorsArming = false;

MotorI2C *motor;

void motor_test();

void manual_test();

int main(void)
{
	while (true)
	{
	string inputchan;
	int realchan=0;
	printf("Input the channel that the test motor is on:\n");
	getline (cin, inputchan);
	stringstream(inputchan) >> realchan;
	if (realchan > 3 || realchan < 0)
		{
		printf("Enter a channel between 0 and 3 ya fucking dumbass\n");
		continue;
		}
	else 
		{
		printf("Ok, channel set is %i.\n", realchan);
		break;
		}
	}

	printf("Initializing PIGPIO\n");
	if (gpioInitialise() < 0)
	{
		printf("FAILED\n");
		return EXIT_FAILURE;
	}

	printf("Initializing MotorController\n");
	motorController = new PCA9685();
	motorController->reset();
	motorController->setFrequency(PWM_DEFAULT_FREQUENCY);

	printf("Initializing Motor\n");
	motor = new MotorI2C(realchan, motorController);

	if(!MotorsStartup)
	{
		StartupMotors();
		MotorsStartup = true;
	}

	motor_test();

	gpioTerminate();

	return EXIT_SUCCESS;
}

//manual_test will be an option to manually set the throttle via the instantiated motor settings. 
//go through same initialization, then manually be able to set up throttle to whatever we need to test at the time. 

void manual_test()
{






} 



// motor_test replaced the loop function. 
// go up by 10 increments of throttle, every 8 seconds, after reset and a 15 second interval.
// 8 seconds after 100% it will go back to 0. 
void motor_test() 
{
	printf("Starting Test\n");
	printf("Setting throttle to zero\n");
	motor->setSpeed(0);

	////////
	//leaving this in for future debugging. 
	//motorController->setSpeed(0, PWM_ZERO);
	////////

	printf("Sleeping for 15 seconds. Check status.\n");
	usleep(5000000);

	//count down from 10
	for(int countdown=10; countdown > 0; countdown--)
	{
	printf("%i.\n", countdown);
	usleep(1000000);
	}

	//go up to 100% for initial testing 100%, 2 second increments
	for (int goup=20; goup < 100; goup = goup + 20)
	{
	printf("Setting to [%i%%] for 2 seconds.\n", goup);
 	motor->setSpeed(goup);
 	usleep(2000000);
	}

	printf("Setting to [100%%] for 10 seconds.\n");
	motor->setSpeed(100);
        //count down from 10
        for(int countdown=10; countdown > 0; countdown--)
        {
        printf("%i.\n", countdown);
        usleep(1000000);
        }

	for(int i = 1; i <= 10; i++)
	{
    	int speed = i *10;
    	printf("Setting throttle to [%i%%] for 8 seconds\n", speed);
		motor->setSpeed(speed);
		usleep(8000000);
	}
	
	printf("Setting throttle back to zero\n");
	motor->stop();
}

void StartupMotors()
{
	printf("Arming motor\n");

	motorController->reset();
	motorController->setFrequency(PWM_DEFAULT_FREQUENCY);

	printf("Setting throttle to zero\n");
	motorController->setSpeedAll(PWM_ZERO);

	//sleep for 5 second
	printf("Sleeping for 2 seconds\n");
	usleep(2000000);

	printf("Setting throttle to max\n");
	motorController->setSpeedAll(MOTOR_MAX);

	//sleep for 1 second
	printf("Sleeping for 1 second\n");
	usleep(1000000);

	printf("Setting throttle back to zero\n");
	motorController->setSpeedAll(MOTOR_STOP);

	printf("Waiting for 1 second.\n");
	usleep(1000000);
}
