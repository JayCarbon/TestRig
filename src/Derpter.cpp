#include "MotorI2C/MotorI2C.h"
#include "PCA9685/PCA9685.h"
#include "RcChannel/RcChannel.h"
#include "IMU.h"
#include "PID.h"
#include "Copter.h"

PCA9685 *motorController;

bool MotorsStartup = false;
bool MotorsArmed = false;
bool MotorsArming = false;

MotorI2C *motor;

void motor_test();

int main(void)
{
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
	motor = new MotorI2C(0, motorController);

	if(!MotorsStartup)
	{
		StartupMotors();
		MotorsStartup = true;
	}

    motor_test();

    gpioTerminate();

	return EXIT_SUCCESS;
}

// motor_test replaced the loop function. 
// go up by 10 increments of throttle, every 30 seconds, after reset and a 10 second 
// 30 seconds after 100% it will go back to 0. 
void motor_test() 
{
    printf("Starting Test\n");

    printf("Setting throttle to zero\n");
    motorController->setSpeed(0, PWM_ZERO);

    /*
    int mocount; 
    for (mocount = 2100; mocount = 3000; mocunt = mocount + 100)
    {*/

    printf("Sleeping for 10 seconds. Check status.\n");
    usleep(10000000);

    for(int i = 1; i <= 10; i++)
    {
    	int speed = i *10;
    	printf("Setting throttle to [%i%%] for 20 seconds\n", speed);
		motor->setSpeed(speed);
		usleep(20000000);
    }
/*

        //sleep for 10 seconds
        printf("Sleeping for 10 seconds. Check status.\n");
        usleep(10000000);

        printf("Setting throttle to 10%% for 20 seconds\n");
        motor->setSpeed(10);
        usleep(20000000);

        printf("Setting throttle for 20%% for 20 seconds\n");
        motor->setSpeed(20);
        usleep(20000000);

        printf("Setting throttle for 30%% for 20 seconds\n");
        motor->setSpeed(30);
        usleep(20000000);

    printf("Setting throttle for 40%% for 20 seconds\n");
    motor->setSpeed(40);
    usleep(20000000);

    printf("Setting throttle for 50%% for 20 seconds\n");
    motor->setSpeed(50);
    usleep(20000000);

    printf("Setting throttle for 60%% for 20 seconds\n");
    motor->setSpeed(60);
    usleep(20000000);

    printf("Setting throttle for 70%% for 20 seconds\n");
    motor->setSpeed(70);
    usleep(20000000);

    printf("Setting throttle for 80%% for 20 seconds\n");
    motor->setSpeed(80);
    usleep(20000000);

    printf("Setting throttle for 90%% for 20 seconds\n");
    motor->setSpeed(90);
    usleep(20000000);

    printf("Setting throttle to max\n");
    motor->setSpeed(100);
*/

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
