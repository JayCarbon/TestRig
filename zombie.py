#!/usr/bin/env python

import os
import psutil
import subprocess
import time

while True:
    for proc in psutil.process_iter():
        if "autorig" in proc.name():
            if proc.status() == "zombie":
                subprocess.Popen(["/etc/init.d/buttonmon", "stop"])
                time.sleep(.05)
                subprocess.Popen(["/etc/init.d/buttonmon", "start"])


