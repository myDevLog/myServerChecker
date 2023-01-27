# myServerChecker

A WiFi-Device which checks if our Backend on the Colledge-Server is still up and running via LED.\
The **ESP8266** first tries to connect to *Eduroam*, or the Colledge-Network.\
After a successfull connection it tries to connect to the Mqtt-Broker on the Server.

On startup, while attempting to connect to the WiFi, the LED will blink yellow at a regualr interval.\
If the connection fails, the Server is considered down, which colors the LED red.\
If the connection is successful, the Server is considered running, which colors the LED green.

Parts used:
- 1x Esp8266 01s
- 1x Arduino Power Modules (As energysupply)
- 1x RGB-LED
- 2x 220 Ohm Resistors
- 1x Battery-Holder
- Batteries
- Wires
