#!/usr/bin/env python

import os
import sys
import time
import RPi.GPIO as GPIO
import psutil
from subprocess import call
import signal

def signal_handler_term(signal, frame):
    print "Caught SIGTERM signal"
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler_term)

def main():
    try:
        rigrun = 0
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
                        rigrun = 1
                if rigrun == 1:
                    rigrun = 0
                    continue
                else:
                    #call (["/home/bojung1/dev/TestRig/derp.py","&"])
                    call (["/home/bojung1/dev/TestRig/autorig", "&"])
            else:
                # the button isn't being pressed, so idle
                # a small delay for the loop
                # also, update Status LED on GPIO 25
                for proc2 in psutil.process_iter():
                    if "autorig" in proc2.name():
                        GPIO.output(25,GPIO.HIGH)
                    else:
                        GPIO.output(25,GPIO.LOW)
            time.sleep(0.02)

    except KeyboardInterrupt:
        print "Interrupted"
    except:
        print "Other error or exception occurred!"

    GPIO.cleanup()

if __name__=="__main__":
    main()










