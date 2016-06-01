#!/usr/bin/python

import sys
sys.path.append('.')
sys.path.append('./.libs')

try:
	import LibIdmefEasy
except Exception,e:
	print "Import failed: ",e
	print "Try 'cd ./.libs && ln -s libidmef_python.so _LibIdmefEasy.so'"
	sys.exit(1)

idmef = LibIdmefEasy.IDMEF()
idmef.ReadFromFile("foo.bin")
idmef.PrintToStdout()
