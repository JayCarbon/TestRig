#!/usr/bin/env python

import os
import sys
import time
import RPi.GPIO as GPIO
import psutil
from subprocess import call

def main():
    rigrun = 0
    # tell the GPIO module that we want to use the
    # chip's pin numbering scheme
    GPIO.setmode(GPIO.BCM)

    # setup pin 23 as an input
    GPIO.setup(23,GPIO.IN)

    while True:
        if GPIO.input(23):
            # the button is being pressed, so run testrig, or idle if already running
            for proc in psutil.process_iter():
                if "derp.py" in proc.name():
                    rigrun = 1
            if rigrun == 1:
                rigrun = 0
                continue
            else:
                call (["/home/bojung1/dev/TestRig/derp.py","&"])
        else:
            # the button isn't being pressed, so turn off the green LED
            #a small delay for the loop
            print "idle"
            time.sleep(0.2)

    GPIO.cleanup()

if __name__=="__main__":
    main()

