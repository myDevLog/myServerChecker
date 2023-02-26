# myServerChecker

A WiFi-Device which checks if our Backend on the College-Server is still up and running via LED.\
The **ESP8266** first tries to connect to *Eduroam*, or the College-Network.\
After a successfull connection it tries to connect to the Mqtt-Broker on the Server.

On startup, while attempting to connect to the WiFi, the LED will blink yellow at a regualr interval.\
If the connection fails, the Server is considered down, which colors the LED red.\
If the connection is successful, the Server is considered running, which colors the LED green.

### **Important: This Sketch is only made for WPA2 Enterprise Networks in PEAP-Mode! Meaning a Wireless Network, where each user has their own unique username and password.**

<br>

## Libraries used:
From the Arduino **Boards**-Manager:

For the needed Library to show up you need to have the following URL's under "File>Preferences>Additional Boards Manager URLs":
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://dl.espressif.com/dl/package_esp32_index.json
```

- "esp8266" by ESP8266 Community

<br>

From the Arduino **Library**-Manager:
- "PubSubClient" by Nick O'Leary
- "WiFi101" by Arduino

<br>

## Parts used:
- 1x Esp8266 01
- 1x Arduino Power Modules (As energysupply)
- 1x RGB-LED
- 2x 220 Ohm Resistors
- 1x Battery-Holder
- 1x USB to ESP8266 01 Serial Wireless WiFi Module (for programming the ESP-Device)
- Batteries
- Wires

**!** Fill out the [mqttSetup.h](ServerChecker/mqttSetup.h) as well as the [wifiSetup.h](ServerChecker/wifiSetup.h) file with the appropriate Data **!**

<br>

## Programming the ESP 8266 01:
1. Stick the ESP into the USB-to-ESP Writer (with the ESP facing the USB-Plug)
2. Make a connection on the USB-to-ESP Writer between GND and the GPIO-Pin
3. Plug the USB-to-ESP Writer in
4. Wait about 3 Seconds
5. Disconnect the GND and the GPIO-Pin
6. Select a Port
7. Upload the Sketch
