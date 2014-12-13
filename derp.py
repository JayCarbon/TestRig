#!/usr/bin/env python

import RPi.GPIO as GPIO
import time

def blink(pin):
    GPIO.output(pin,GPIO.HIGH)
    time.sleep(1)
    GPIO.output(pin,GPIO.LOW)
    time.sleep(1)
    return

GPIO.setmode(GPIO.BCM)
GPIO.setup(25,GPIO.OUT)

for i in range(0,50):
    blink(25)

GPIO.cleanup()
