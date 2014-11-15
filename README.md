TestRig
=======

This is an automated Test system to test individual motors via PWM. 

How to use:
1. Clone the code to the pi
2. Compile the code (make) 
3. Run the compiled binary (testrig) 

What does it do? 

The main function:
The testrig program takes a channel input between 0 and 3. (1st through 4th transposed.) 
It will then initialize everything, prep the motors, and then ask for a (M)anual or (A)utomatic test. 

An automatic test will sleep for 15 seconds, ramp up to 100% throttle for 10 seconds, then go back down to 10%
and work its way up back to 100% every 8 seconds, and then stop, chatting about what it's doing all the while.
Then it exits. 

A manual test will initialize at throttle zero, then ask for a throttle value. It will then set the throttle to
that value. It will continue to ask for values between 0-100. 255 quits.

NOTE: After the run the motor is still initialized. Unplugging the proper devices will prevent code from suprise
 spinning the motor if a test is restarted. 

Action items / improvements for the code: 
1. Some way of knowing if motors have been initialized already (lockfile?)
2. GPIO wrangling to allow compiled code to run with a switch instead of a laptop
3. A sweep for bugfixes

Hardware and rig action items: 
1. Confirm testrig setup with hardware folks
2. Dedicated hardware test set build out (location, mount, hotswap features)
3. Iterate on what else needs embiggening



