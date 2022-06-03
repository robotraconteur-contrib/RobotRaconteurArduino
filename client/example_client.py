from RobotRaconteur.Client import *
import time

sub = RRN.SubscribeServiceByType("arduinotest_interface.obj")

val = 0
val_dir = 10

while True:
    res, c = sub.TryGetDefaultClient()
    if not res:
        print("Could not find Arduino, retrying...")
        time.sleep(1)
        continue
    val = max(min(val + val_dir,255),0)
    if val >= 255: val_dir = -10
    elif val <= 0: val_dir = 10
    c.dimmer(val)
    time.sleep(0.1)


    