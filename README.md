# Trash Bin Solar Charging Station
 A trashbin project which uses 3 kinds of sensors. Each kind of material inserted in the trashbin would equate to charge duration.

Kindly use the library included in the repository. Also, please download the readme file for the better readability of the truth table.

- New-LiquidCrystal-master 
library credits to: https://github.com/fmalpartida/New-LiquidCrystal 

- VarSpeedServo-master 
library credits to: https://github.com/netlabtoolkit/VarSpeedServo

Please refer to this tutorial in regard on how you can add library to your Arduino IDE. 

https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries

/*
  infraredSensor LOW = detection
  metalSensor HIGH = detection
  plasticSensor LOW = detection
  /------------------------------------------------------------------------/
  Truth Table
  1 = DETECT 0 = NO_DETECT
  Please don't get this confused with the actual sensor input

                  M   Pl  M  Pa   n
  IR SENSOR      |1| |1| |1| |1| |0|
  PLASTIC SENSOR |1| |1| |0| |0| |0|
  METAL SENSOR   |1| |0| |1| |0| |0|

  M = Metal       - 1 1 1
  Pl = Plastic    - 1 1 0
  Metal           - 1 0 1
  Pa = Paper      - 1 0 0
  null            - 0 0 0
  /------------------------------------------------------------------------/

*/

/*Charge durations. these units are automatically converted in minutes*/
const int plasticChargeDuration = 7;
const int paperChargeDuration = 3;
const int metalChargeDuration = 10;

/*Servo degrees. change na lang direction what direction the servo would go depending on the material detected*/
const int plasticServoDegree = 60;
const int paperServoDegree = 120;
const int metalServoDegree = 180;
