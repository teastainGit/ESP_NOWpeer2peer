# ESP_NOWpeer2peer
 Very simple example of using ESP-NOW for peer to peer communications
 
 I was interested In ESP peer to peer with no client/server, no WiFi router login, not IoT (!!!)
I ran across a tutorial for "esp_now" and with some difficulty and learning curve I got two M5Stack
 devices talking peer to peer, perfectly!
I have created a dozen projects from the simple example above to a JoyC joystick controlling a 
RoverC and many other applications.
I made a HVAC controller with wireless reading of duct temperature, transmitted to the Core Basic and
 in turn the Core transmitting the RC Servo angle for vent damper control...well, this Is how!
Copied below Is the most simplified esp_now example that I could think of. 
This example Is ONE sketch for TWO M5StickCs. 
Only one sketch because the two programs are IDENTICAL except for MAC address

