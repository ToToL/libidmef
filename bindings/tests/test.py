#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import idmef

idmef = idmef.IDMEF()

print("*** IDMEF->Set() ***")
idmef.set("alert.classification.text", "My Message")
idmef.set("alert.source(0).node.address(0).address", "s0a0")
idmef.set("alert.source(0).node.address(1).address", "s0a1")
idmef.set("alert.source(1).node.address(0).address", "s1a0")
idmef.set("alert.source(1).node.address(1).address", "s1a1")
idmef.set("alert.source(1).node.address(2).address", None)
idmef.set("alert.source(1).node.address(3).address", "s1a3")
print(idmef)

print("\n*** Value IDMEF->Get() ***")
print(idmef.get("alert.classification.text"))

print ("\n*** Listed Value IDMEF->Get() ***")
print (idmef.get("alert.source(*).node.address(*).address"))

print ("\n*** Object IDMEF->Get() ***")
print (idmef.get("alert.source(0).node.address(0)"))

print ("\n*** Listed Object IDMEF->Get() ***")
print (idmef.get("alert.source(*).node.address(*)"))


