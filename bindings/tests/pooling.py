#!/usr/bin/python

import LibIdmefEasy

client = LibIdmefEasy.ClientEasy("PoolingTest", LibIdmefEasy.Client.IDMEF_READ)
client.Start()

while True:
    idmef = LibIdmefEasy.IDMEF()

    ret = client.RecvIDMEF(idmef)
    if ret:
	print idmef
