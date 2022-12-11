# Trash Bin Solar Charging Station
 A trashbin project which uses 3 kinds of sensors. Each kind of material inserted in the trashbin would equate to charge duration.

/***************************************************************************************************************************/

Kindly use the library included in the repository. Also, please download the readme file for the better readability of the truth table.

- New-LiquidCrystal-master 
library credits to: https://github.com/fmalpartida/New-LiquidCrystal 

- VarSpeedServo-master 
library credits to: https://github.com/netlabtoolkit/VarSpeedServo

Please refer to this tutorial in regard on how you can add library to your Arduino IDE. 

https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries

/***************************************************************************************************************************/

Please click here to see the project's truth table in detecting objects:

https://pastebin.com/7CMwEE6e

/***************************************************************************************************************************/

/*Charge durations. these units are automatically converted in minutes*/
const int plasticChargeDuration = 7;
const int paperChargeDuration = 3;
const int metalChargeDuration = 10;

/*Servo degrees. change the degree direction depending on where you want the servo to rotate depending on the object detected*/
const int plasticServoDegree = 60;
const int paperServoDegree = 120;
const int metalServoDegree = 180;



/***************************************************************************************************************************/
