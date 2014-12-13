#!/usr/bin/env python

import psutil

for proc in psutil.process_iter():
    print "%s %s" % (proc.name(), proc.status())

