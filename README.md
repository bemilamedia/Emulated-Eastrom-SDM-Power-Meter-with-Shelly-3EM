# Emulated Eastron SDM (Fork with balance 3phases of the Shelly 3EM - see the last point in this description)
 An ESP8266 project to emulate an Eastron SDM power meter

 ## Background

 I need to limit the power that my solar inverter exports to the grid.
 
 This is normally achieved by connecting an Eastron SDM230 power meter via modbus to the inverter's (Growatt MIN 3600TL-XE in my case) 2nd modbus port. Once installed the inverter acts as a master, polling the SDM230 slave device's input regisiters for data. If it detects that power is being exported to the grid, it limits the inverter's output power to maintain (approximately) zero export.

 I have a slightly more complex setup with a solar water heater diverter in the mix, this intercepts the unused power and uses it to heat my hot water tank. But once the talk is fully heated (usually around 2pm in the Summer) the power is exported to the grid - which I do not want. The real SDM230 power meter is not compatible with this process and cuts export before the solar diverter gets a chance to heat the water.

 My solution for this is to emulate the Eastron SDM230 and maintain full control of when the inverter limits is power output.

 ## Alpha software

 Heads up!
 - I am not a dev.
 - This is not yet tested as I'm away from home.
 - I started developing this project out of necesity and learned just enough C++ to get this working, my code is probably horrible!

 ## Required tools

 You will need:
-  ESP8266 device (I'm using a Wemos D1 mini clone 3.5 euros)
-  MAX485 TTL to RS-485 Interface Module (2 euros)
-  A calbe to connect the module to your inverter (I cut the ends of an Ethernet patch cable)
-  5 dupont cables

## Building the device

It's super easy. Connect the MAX485 module to your ESP8266 board:

D2	  ---> DI

D3	  ---> RO

D0	  ---> RE

D0	  ---> DE

Vcc	  ---> 3.3V

GND   ---> GND

Then connect your MAX485 module's A/B terminals to the A/B terminals on your inverter using two wires from your sacrificial ethernet patch cable - A links to A, B links to B. In my case, on the Growatt MIN 3600TL-XE I had to use pins 5 and 6 which is the power meter modbus.

## Building in Arduino IDE

Before building and writing to your ESP8266, rename the file "private-h.sample" to "private.h" and move it into the Emulated-Eastron-SDM foder. Then edit it to reflect your WiFi and MQTT server details.

## How it works

Once compiled and running the ESP8266 will:

- connect to your WiFi network
- connect to your MQTT server
- Listen for power values in Watts to on the MQTT topic you chose
- Update the 'Active power Watts' input register number 4 with the values it gets from the MQTT topic

My MQTT topic is the power value recorded by a 'Shelly EM' using a clamp meter connected to the main input power line. But you can use whatever source you like, or just manually publish the desired value to the MQTT server.


## Hints

Once installed you can open the serial monitor within the Arduino IDE to see debug info.
Experiment but setting the MQTT topic to something like test/power and publish the values that you want to test.
Don't forget to enable export control using your inverter's GUI!

## Development

I initially setup a USB Modbus 485 adaptor and connected it to my laptop, I then sniffed the bus to see what messages the inverter was sending. This was the first one RTU frame:

TX: 01 04 00 00 00 0E 71 CE

Part of Data Package |  Description | Value
----------------|-------------|-----------
01 | Slave address | 0x01 (1)
04 | Function code | 0x04 (4) - Read Input Registers
00 00 | Starting address | Physical: 0x0000 (0) Logical: 0x0001 (1)
00 0E | Quantity | 0x000E (14)
71 CE | CRC | 0x71CE (29134)

I then set out to build a device that could answer the request.


## Changes in this fork
The Schelly 3EM does not balance over the 3 phases. This is a known "problem", which is not addressed by Shelly.

I have adapted the code, for me, so that all 3 phases are read via MQTT and then balanced in the ESP8266. The balanced value is then output.

The code can certainly be optimized, also in terms of error / measurement error and so on. But for me it was first of all important to be able to output a balanced value via MQTT.

You have to update the private.h file with the 3 MQTT Topics of your shelly 3EM phases
