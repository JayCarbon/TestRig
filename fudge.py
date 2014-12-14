#!/usr/bin/env python

import psutil
import os
import time
import stat

def touch(path):
    with open(path, 'a'):
        os.utime(path, None)

def file_age_in_seconds(pathname):
        return time.time() - os.stat(pathname)[stat.ST_MTIME]


for proc in psutil.process_iter():
    print "%s %s" % (proc.name(), proc.status())

touch ("/tmp/fudge")
time.sleep(2)

print "%d" %file_age_in_seconds("/tmp/fudge");
