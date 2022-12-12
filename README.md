# Trash Bin Solar Charging Station
 A trashbin project which uses 3 kinds of sensors. Each kind of material inserted in the trashbin would equate to charge duration.

/**************************************************************************************************************************/

Kindly use the library included in the repository. Also, please download the readme file for the better readability of the truth table.

- New-LiquidCrystal-master 
library credits to: https://github.com/fmalpartida/New-LiquidCrystal 

- VarSpeedServo-master 
library credits to: https://github.com/netlabtoolkit/VarSpeedServo

Please refer to this tutorial in regard on how you can add library to your Arduino IDE. 

https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries

/**************************************************************************************************************************/

PROJECT PIN OUTS 

LCD i2c 0x27 
GND - GND
VCC - 5V 
SDA - A4 (SDA)
SCL - A5 (SCL)

Servo Bottom 
Brown - GND
Red - 5V
Orange - D9 (PWM)

Servo Top
Brown - GND
Red - 5V
Orange - D10 (PWM)

Plastic Sensor 
D2 

Metal Sensor 
D3

IR Sensor
GND - GND
VCC - 5V
OUT - D5

Relay Module (LOW TRIGGER) 
VCC - 5V
GND - 5V 
Out - D6 

/**************************************************************************************************************************/

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

/**************************************************************************************************************************/

/*Charge durations. these units are automatically converted in minutes*/
const int plasticChargeDuration = 7;
const int paperChargeDuration = 3;
const int metalChargeDuration = 10;

/*Servo degrees. change na lang direction what direction the servo would go depending on the material detected*/
const int plasticServoDegree = 60;
const int paperServoDegree = 120;
const int metalServoDegree = 180;

/*Servo top degree for opening the lid*/
const int servoLidDegree = 180;

/*Set the default servo degree bottom. this degree should be the "closed" state of the project*/
const int defaultServoDegreeBottom = 0;

/*Set the default servo degree topm. this degree should be the "closed" state of the project*/
const int defaultServoDegreeTop = 0;



/**************************************************************************************************************************/
