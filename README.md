TestRig
=======

This is an automated Test system to test individual motors via PWM. 

How to use:

1. Clone the code to the pi
2. Compile the code (make) 
3. Run the compiled binary (autorig) by pushing the button 
4. If necessary, add the init scripts as symlinks to /etc/init.d/

What does it do? 

The Push Button Autotest:

Push the button on the prewired GPIO 23 and autotest will trigger and light a yellow light. Then, it will trigger a test run of the autotest. 
Autotest assumes channel 0. Be sure to wire the GPIO to ensure that can be tested.

Push the button during operation to interrupt and stop the test at any time. 


The Manual Test (Work In Progress) 
The testrig program will first take a channel input between 0 and 3. (1st through 4th transposed.) It will then initialize everything, prep the motors, and then ask for a (M)anual or (A)utomatic test. 


An automatic test will sleep for 15 seconds, ramp up to 100% throttle for 10 seconds, then go back down to 10% and work its way up back to 100% every 8 seconds, and then stop, chatting about what it's doing all the while. Then it exits. 

A manual test will initialize at throttle zero, then ask for a throttle value. It will then set the throttle to that value. It will continue to ask for values between 0-100. 255 quits.

NOTE: After the run the motor is still initialized. Unplugging and restarting the proper devices (pi, motors, PWM) will prevent the motor code from SURPRISE SPINNING the motor if a test is restarted. 

Action items / improvements for the code: 

1. Some way of knowing if motors have been initialized already (lockfile?)
2. A schematic that Don can reference
3. A sweep for bugfixes


Hardware and rig action items: 

1. Confirm testrig setup with hardware folks
2. Dedicated hardware test set build out (location, mount, hotswap features)
3. Iterate on what else needs embiggening
