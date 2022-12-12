/*LCD Library*/
#include <LiquidCrystal_I2C.h> //library
#include <Wire.h>
#define BACKLIGHT_PIN 13 // backlight pin
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

/*watchdog library. anti millis-overflow*/
#include <avr/wdt.h>

/*Servo library*/
#include <VarSpeedServo.h>
VarSpeedServo myServoBottom;
VarSpeedServo myServoTop;

const int servoPinBottom = 9; // bottom servo
const int servoPinTop = 10; // top servo

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

/*Set the default servo degree top. this degree should be the "closed" state of the project*/
const int defaultServoDegreeTop = 0;

/*orange sensor*/
const int plasticSensorPin = 2;
int plasticSensorValue;

/*blue sensor*/
const int metalSensorPin = 3;
int metalSensorValue;

/*infrared sensor for default*/
const int infraredSensorPin = 5;
int infraredSensorValue;

/*relay module*/
const int relayModule = 6;

/*Conditions. please don't touch. since majority of detections are different. example: relay on = low, plastic detect = high, etc.*/
uint8_t IR_DETECT = LOW;
uint8_t IR_NO_DETECT = HIGH;

uint8_t P_DETECT = HIGH;
uint8_t P_NO_DETECT = LOW;

uint8_t M_DETECT = LOW;
uint8_t M_NO_DETECT = HIGH;

uint8_t RELAY_ON = LOW;
uint8_t RELAY_OFF = HIGH;

/**/
unsigned long previousMillis = 0;
unsigned long lastPrint;

/*global variable for charge time*/
unsigned long chargeTime;

void setup()
{
  Serial.begin(115200);
  pinMode(plasticSensorPin, INPUT_PULLUP);
  pinMode(metalSensorPin, INPUT);
  pinMode(infraredSensorPin, INPUT);
  pinMode(relayModule, OUTPUT);
  digitalWrite(relayModule, RELAY_OFF);
  lcd.begin(16, 2);
  while (!Serial)
  {
    ; // Wait for serial to connect
  }

  myServoTop.attach(servoPinTop);
  myServoTop.write(0, defaultServoDegreeTop, true);
  myServoBottom.attach(servoPinBottom);
  myServoBottom.write(0, defaultServoDegreeBottom, true);
}

void loop()
{
  detectObjects();
  defaultDisplay();
}

void detectObjects()
{
  String materialKind;
  int servoBottomDegree;
  
  plasticSensorValue = digitalRead(plasticSensorPin);
  metalSensorValue = digitalRead(metalSensorPin);
  infraredSensorValue = digitalRead(infraredSensorPin);

  if (infraredSensorValue == IR_DETECT)
  {
    if ((plasticSensorValue == P_DETECT && metalSensorValue == M_DETECT) || (plasticSensorValue == P_NO_DETECT && metalSensorValue == M_DETECT))
    {
      chargeTime += (metalChargeDuration * 60000);
      servoBottomDegree = metalServoDegree; // change the servo degree
      materialKind = "metal";
    }

    else if (plasticSensorValue == P_NO_DETECT && metalSensorValue == M_NO_DETECT)
    {

      chargeTime += (paperChargeDuration * 60000);
      servoBottomDegree = paperServoDegree; // change the servo degree
      materialKind = "paper";
    }

    else if (plasticSensorValue == P_DETECT && metalSensorValue == M_NO_DETECT)
    {
      chargeTime += (plasticChargeDuration * 60000);
      servoBottomDegree = plasticServoDegree; // change the servo degree
      materialKind = "plastic";
    }

    
    myServoBottom.write(servoBottomDegree, 255, true); // rotate servo to desired degree
    myServoTop.write(servoLidDegree, 255, true);
    myServoTop.write(defaultServoDegreeTop, 255, true);
    myServoBottom.write(defaultServoDegreeBottom, 100, true);
    
    checkMaterial(materialKind, chargeTime, servoBottomDegree);

  }
}

void checkMaterial(String &material, long longVariable, int servoBottomDegree)
{
  while (longVariable >= 1000)
  {
    detectObjects();
    if (millis() - lastPrint >= 1000)
    {
      lastPrint = millis();
      longVariable = longVariable - 1000;
      chargeTime = chargeTime - 1000;
      chargingDisplay(material, longVariable);
      digitalWrite(relayModule, RELAY_ON);
    }
    /*exit condition*/
    if (longVariable == 0 && chargeTime == 0)
    {
      digitalWrite(relayModule, RELAY_OFF);
      thankYouMessage();
    }
  }
}

void storeValue(char *to, int val, char behind)
{
  *to++ = '0' + val / 10;
  *to++ = '0' + val % 10;
  *to++ = behind;
}
char *timeSort(unsigned long num)
{
  static char Buffer[10];
  int totalsec = num / 1000; // gives the total number of seconds
  int totalmin = totalsec / 60;
  int totalhour = totalmin / 60;
  storeValue(Buffer, totalhour, ':');
  storeValue(Buffer + 3, totalmin % 60, ':');
  storeValue(Buffer + 6, totalsec % 60, 0);
  return Buffer;
}

void chargingDisplay(String &material, unsigned long longVariable)
{
  lcd.setCursor(0, 0);
  lcd.print(material + " detected");
  lcd.setCursor(0, 1);
  lcd.print(timeSort(longVariable));
  lcd.print(F("       "));
}

void defaultDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print(F("Insert trash    "));
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
}

void thankYouMessage()
{
  lcd.setCursor(0, 0);
  lcd.print(F("Thank you for"));
  lcd.setCursor(0, 1);
  lcd.print(F("recycling"));
  delay(300);
  wdt_enable(WDTO_15MS);
}
