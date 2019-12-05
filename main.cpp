#pragma once
#include "Robot.h"
#include <Adafruit_PWMServoDriver.h>

void Foo();
void StartPos();

Robot robot;

void setup()
{
  Serial.begin(9600);
  while (Serial.available()) Serial.read();         // очистка ComPort
  delay(500);

  robot.SettingServo();
  delay(500);
}

void loop()
{
  static bool t = false;
  if(!t)
  {
    robot.ControlPosition();
    t = !t;
  }

  if(millis() - robot.startTime > 60)
  {
    robot.MoveLine();
    robot.startTime = millis();
  }

  //robot.GetData();      //получение данных
  //robot.StartMove();    //если есть данные начинается движение
  
/*
robot.pos = 0;
  for(int i = 0; i < 3; i++)
  {
    robot.ControlPosition();
    robot.TakeItem();
    delay(500);           //приезжаем к месту выгрузки
    robot.SetAngle(90);
    robot.SetLine(robot.arrLine[robot.pos++]);


    delay(500);
    robot.ReleaseItem();
    
  }
  robot.ControlPosition();
  while (Serial.available()) Serial.read();         // очистка ComPort
  */
}