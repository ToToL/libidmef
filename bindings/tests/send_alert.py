#!/usr/bin/python

import sys
import LibIdmefEasy

idmef = LibIdmefEasy.IDMEF()
idmef.Set("alert.classification.text", "Bar")

client = LibIdmefEasy.ClientEasy("MyTest")
client << idmef

