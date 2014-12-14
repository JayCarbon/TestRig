#!/usr/bin/env python

import os
import sys
import time
import RPi.GPIO as GPIO
import psutil
import subprocess
from subprocess import call
import signal
import stat
import os.path

def signal_handler_term(signal, frame):
    print "Caught SIGTERM signal"
    sys.exit(0)

def touch(path):
    with open(path, 'a'):
        os.utime(path, None)

def file_age_in_seconds(pathname):
    return time.time() - os.stat(pathname)[stat.ST_MTIME]

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
            # the button is being pressed, so run autorig, or kill() if already running
            # based on "clever" logic
            if GPIO.input(23):

                if os.path.exists("/tmp/autorig"):
                    for proc in psutil.process_iter():
                        if "autorig" in proc.name():
                            if file_age_in_seconds("/tmp/autorig") > 3:
                                proc.kill()
                                os.remove("/var/run/pigpio.pid")
                                os.remove("/tmp/autorig")
                                time.sleep(2)
                                break

                else:
                    subprocess.Popen(["/home/bojung1/dev/TestRig/autorig"])
                    touch ("/tmp/autorig")
                    time.sleep(2)
            # a small delay for the loop
            # also, update Status LED on GPIO 25

            for proc2 in psutil.process_iter():
                if "autorig" in proc2.name():
                    GPIO.output(25,GPIO.HIGH)
            time.sleep(0.1)

    except KeyboardInterrupt:
        print "Interrupted"
    except:
        print "Other error or exception occurred!"
    GPIO.cleanup()
    os.remove("/tmp/autorig")

if __name__=="__main__":
    main()










