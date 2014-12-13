#!/usr/bin/env python

import os
import sys
import time
import RPi.GPIO as GPIO
import psutil
import subprocess
from subprocess import call
import signal
import re

def signal_handler_term(signal, frame):
    print "Caught SIGTERM signal"
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler_term)

def main():
    try:
        # tell the GPIO module that we want to use the
        # chip's pin numbering scheme
        GPIO.setmode(GPIO.BCM)

        # setup pin 23 as an input
        # setup pin 25 as status output - when autorig is running it's on
        GPIO.setup(23, GPIO.IN)
        GPIO.setup(25, GPIO.OUT, initial=GPIO.LOW)

        while True:
            if GPIO.input(23):
                # the button is being pressed, so run testrig, or idle if already running
                for proc in psutil.process_iter():
                    if "autorig" in proc.name():
                        #proc.kill()
                        os.remove("/var/run/pigpio.pid")
                        sys.exit(0)
                else:
                    #call (["/home/bojung1/dev/TestRig/autorig", "&"])
                    subprocess.Popen(["/home/bojung1/dev/TestRig/autorig"])
            # a small delay for the loop
            # also, update Status LED on GPIO 25
            for proc2 in psutil.process_iter():
                if "autorig" in proc2.name():
                    GPIO.output(25,GPIO.HIGH)
            time.sleep(0.25)
                    #if "autorig" in proc3.name():
                    #    GPIO.output(25,GPIO.LOW)
                    #   proc.kill()
                    #    os.remove("/var/run/pigpio.pid")
                    #    sysexit(0)


    except KeyboardInterrupt:
        print "Interrupted"
    except:
        print "Other error or exception occurred!"
    GPIO.cleanup()

if __name__=="__main__":
    main()










