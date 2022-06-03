# Robot Raconteur Arduino Demo

This project is a demonstration of a Robot Raconteur service node implemented on an Arduino Uno (32 KB ROM, 2 KB RAM!) and a WizNet w5100 Ethernet Shield. The purpose of this project is to demonstrate that the Robot Raconteur protocol is simple enough to work with extremely limited devices.

The following features are implemented:

* Simple service with a single function `dimmer(uint16 val)`, which will set the intensity PWM output 9. This pin can be used with a normal LED PWM controlled light.
* TCP server that can accept Robot Raconteur TCP transport connections
* WebSocket server capabilities, meaning that the TCP server can accept connections from web browsers using the built in WebSocket client.
* Auto-discovery, which allows Robot Raconteur clients to automatically find the service on the network and control the light

This demonstration takes up most of the ROM on the Arduino Uno, but it is not highly optimized. It is estimated that the ROM usage can be reduced by about half with careful optimization.

## Example Client

The following client will search for the Arduino on the network, and adjust the pulsate the light intensity:

```python
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
```

## Hardware

The original Ethernet w5100 shield is no longer manufactured by Arduino, but there are clones still available:

https://www.sunfounder.com/products/w5100-ethernet-shield

https://www.sunfounder.com/collections/arduino-boards/products/arduino-unor3-control-board

## Building

This project can be built using the normal Arduino IDE, or using the VS Code Arduino extension. It has been tested using an Arduino Uno, but should work on any board.

The libraries "CrytoLegacy" and "Base64" are required. "Base64" can be installed using the Arduino library manager, but the "CrytoLegacy" must be cloned from GitHub from: https://github.com/rweather/arduinolibs . Copy the `CryptoLegacy` folder under `libraries` in `arduinolibs` to `C:\<user>\Documents\Arduino\libraries` on Windows, or `/home/<user>/Arduino/libraries` on Linux.
