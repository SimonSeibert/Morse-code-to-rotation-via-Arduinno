# Morse code to rotation via Arduinno

<h2>What is the project</h2>

This is the source code for a translator, which essentially mimics the setup of the movie *"The Martian"* ([You can take a look at the setup here](https://www.youtube.com/watch?v=k-GH3mbvUro)). <br/>
It's a translator that receives a morse code input and converts it into hexadecimal numbers. A semicircle of hexadecimal numbers surrounds a servo motor and the pointer, which is placed on the servo motor, will then point to the corresponding hexadecimal numbers one after another.
You can also use a DIY Capacitive Sensor (e.g. aluminium) as input.
You can also use a LED as output. The output will be the morse code message blinked by the LED.

<h2>TL;DR</h2>

Input: 
- Button
- DIY capacitive sensor 
- Unity speech to text

Output: 
- Servo motor rotation
- Blinking LED 
- Unity Ouiji-Board

<h2>Hardware</h2>

- 1x Arduino Microcontroller (e.g. Arduino Uno)
- 1x Servo motor attachment for the Arduino
- 1x Button
- 1x LED (optional)
- 1x Breadboard
- Cables:
	- 1x Micro-USB Cable
	- 1x Servo motor - Microcontroller connection cable
	- 1x Power Cable
	- 2x Grounding Cables
	- 2x Communication Cables

<h2>Hardware Circuit</h2>

![Hardware Circuit](https://user-images.githubusercontent.com/35760266/124632943-13415f00-de85-11eb-847b-ab33e4d99759.png)
	
 <h2>Software</h2>
 
 - Unity 2020.3.8f1
 - Arduino IDE
	- <CapacitiveSensor.h> -> Capacitive Sensor 0.5.1 by Paul Stoffregen
	- <Servo.h>

<h2>Unity Integration</h2>

The project also contains a Unity implementation. Connect it to the same Port and Baud rate and you're ready to go. You can do the input on the Arduino and get an output in unity. The output shows a Ouiji-Board with hexadecimal numbers. A planchette will then traverse the message. You can also say a message using speech to text (with windows speech).

![Inside Unity](https://user-images.githubusercontent.com/35760266/124633213-569bcd80-de85-11eb-8536-eccb636a62fb.png)

<h2>Unity Arduino Communication</h2>

There is also a AtU.ino file included with which you can test the communication between Arduino and Unity and vis versa. You can send a message from Arduino which can be received in Unity. Additionally you can send a Message from Unity to the Arduino which will make the internal LED blink.
