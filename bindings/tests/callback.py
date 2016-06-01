#!/usr/bin/python

import sys
sys.path.append('.')
sys.path.append('./.libs')

try:
	import LibIdmefEasy
except:
	print "Import failed"
	print "Try 'cd ./.libs && ln -s libidmef_python.so _LibIdmefEasy.so'"
	sys.exit(1)

def foo(id):
        print "callback: id = " + str(id)
	idmef = LibIdmefEasy._get_IDMEF(id)
        idmef.PrintToStdout()
        #print bar.Get("alert.classification.text") # XXX not yet implemented
        return 0

LibIdmefEasy.set_pymethod(foo)

LibIdmefEasy.test_fct()
