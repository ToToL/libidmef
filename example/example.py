import idmef
import json

msg = idmef.IDMEF()

msg.set("alert.classification.text", "Test alert")
msg.set("alert.source(0).node.address(0).address", "10.0.0.1")


print(msg)
print(msg.toJSON())
print(msg.toBinary())

msg2 = idmef.IDMEF(msg.toJSON())
print(msg2)
