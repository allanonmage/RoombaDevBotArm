# RoombaDevBotArm
Development platform on a Roomba chasis

I built this to learn and explore arduino, robotics, and had hoped to move into Android app development.  The project stalled because of reasons, but if I pick it back up, I'll update the docs here.

The robot uses the following main components:
* Roomba 4000 series
* OWI robot arm
* Arduino ADK
* El cheapo USB Bluetooth adapter from eBay
* Clone of Adafruit motor controller
* PS3 controller
* Random old Android phone (It was old in 2012)
* This thing holds my phone on the controller so I can see an IP cam from the phone mounted on the robot: https://www.thingiverse.com/thing:45322

The PS3 controller controls the Roomba's movements and the arms movements.  My phone is attached to the controller and views a feed from the phone mounted on the robot so I can see what the robot sees.

I needed the following libraries, who knows how 7 years of Arduino development has affect any of this code, or if any of this is even available.
* USB_Host_Shield_2.0 from Circuits@home
* PS3 USB library - developed by Kristian Lauszus  http://blog.tkjelectronics.dk/

It looks like my guide is still available, which you can find here: https://forum.arduino.cc/index.php?topic=137747.0  Sorry to those that came behind me, I didn't know there were people commenting on that post!


Unfinished business
* Powering the robot's Android phone from the roomba
* Configuring the Androind phone for automatice stop/start of the IPCam software
* Get the pan/til mount operational.  The motor controller board has 2 free servo control slots, so that's where I'm planning to hook them up.
* Since the battery is now 7 years old, I'll need to replace the roomba's battery if I continue this project

Stretch goals that never happened
* Pair the PS3 controller to the phone its mounted to
* Establish network between the two phones to relay control and video
* Establish USB communications between robot's Android phone to relay commands to Arduino etc.
* Write a custom app for the phone mounted on the PS3 controller

Reflections and things I should have done
* When I wired up the main power switch, I thought about making it the main battery switch.  I decided against it.  In retrospect, that woul dhave been helpful to keep the roomba from draining the battery while the robot sat on my desk and later my shelf.
* It seems I was 3-5 years too early for USB libraries and enough Android support to do what I wanted.  Android support for USB and OTG relaly picked up in 2014, and became cheap a few years after than.
* Adafruit and some random mod on the Arduino were pretty dickish about the motor controller and offering any support for it.  Apparently, it was enough friction that I stopped fooling around with Arduno, because this was my last Arduino project for many years.  Not the only reason I faded out of this project, but it was enough of a sour taste in my mouth that I don't buy Adafruit parts unless I absolutely have to.  That's a story for a beer, not a readme file though.





