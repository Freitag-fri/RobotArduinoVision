#pragma once
#include "Robot.h"

void Robot::SettingServo()
{
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(10);
  pwm.setPWM(0, 0, serv0);        //( 125-527)
  pwm.setPWM(2, 0, serv2);        //4 ( 200-460)        //чемь меньше, тем сильнее расскрывается (можно и меньше наверное)
  pwm.setPWM(4, 0, serv4);        //4 ( 140-380)        //чемь меньше тем выше подымается 
  pwm.setPWM(12, 0, serv12);        //4 ( 95-330..)        //чемь меньше тем выше подымается //схват вниз вверх
  pwm.setPWM(5, 0, serv5);        //4 ( 140-330..)        //на 120 зажат //схват
}

 void Robot::GetData()
 {
   data.GetCoordinates();
 }

 void Robot::StartMove()
 {
    data.GetData();
    ChangeWork();

    /*  
    if(work)
    {
      if(arrAction[posAction] == 0)
        {ControlPosition(); }      //устанавливает координаты для контрольной позиции
    
    //else if(arrAction[posAction] == 1)
    //  {MoveServo(); }
    
      else if(arrAction[posAction] == 2)
        {GetCoordinates();}

      else if(arrAction[posAction] == 3)
        {TakeItem();}

      else if(arrAction[posAction] == 4)
        {CoordinatesSetting(); }

      else if(arrAction[posAction] == 5)
        {ReleaseItem(); }

      else if(arrAction[posAction] == 6)
      {
        MoveAngle(); 
      }

      else if(arrAction[posAction] == 7)
      {
       MoveLine(); 
      }
    }
    */
 }

 void Robot::ChangeWork()
 {
    //if(work != data.workData)
    //{
        work = data.workData;
        MoveChangeWork();
    //}
 }
  void Robot::MoveChangeWork()
  {
    if(work)
    {
      angleNew = ConvertFromAngle(10);
      MoveAngle(); 
    }
    else
    {
      angleNew = ConvertFromAngle(-10);
      MoveAngle(); 
    }
  }

void Robot::TakeItem()
{
    if(serv5 > 130)
    {
      pwm.setPWM(5, 0, --serv5); 
    }

    else if (serv5 == 130)
    {
      AddPosAction();
    }
    
}

void Robot::ReleaseItem()
{
  if(serv5 < 220)
  {
    pwm.setPWM(5, 0, ++serv5); 
  }

  else if(serv5 == 220)
  {
    AddPosAction();
  }
}


void Robot::MoveServo()
{
  /*
  if(serv0 != angleNew || serv2 != way1 || serv4 != way4 || serv12 != way12)
  {
    MoveAngle();        
    MoveLine();
  }
  else
  {
    AddPosAction();
  }
  */
}

void Robot::GetCoordinates()
{
  GetData();
  if (data.GetCheckData())
  {
    angleNew = ConvertFromAngle(data.GetAngle());
    lineNew = data.GetLine();
    SetLine();
    AddPosAction();

    data.SetCheckDataFalse();
  }
}

void Robot::CoordinatesSetting()
{
  angleNew = ConvertFromAngle(arrAngle[posSetting]);
  lineNew = arrLine[posSetting++];

  way1 = 310 - (lineNew * 0.35) + 9;    //коррекция что б поднять на подставку
  way4 = 380 - lineNew;
  way12 = 95 + lineNew * 0.38;

  AddPosAction();
}

void Robot::MoveAngle()      
{
  if (serv0 < angleNew)
  {
      pwm.setPWM(0, 0, ++serv0);
  }

  else if (serv0 > angleNew)
  {
      pwm.setPWM(0, 0, --serv0);
  }
  else
  {
    AddPosAction();
  }
}

void Robot::ControlPosition()  
{
  way1 =  410;
  way4 =  340;
  way12 = 190;
  angleNew = ConvertFromAngle(0);

  AddPosAction();
}

void Robot::SetLine()
{
  way1 = 310 - lineNew * 0.35;
  way4 = 380 - lineNew;
  way12 = 95 + lineNew * 0.38; 
}

void Robot::MoveLine()
{
  bool serv1 = Moveservo1();
  bool serv2 = Moveservo2();
  bool serv3 = Moveservo3();
  if(serv1 && serv2 && serv3)
  {
    AddPosAction();
  }
}

bool Robot::Moveservo1()
{
  if(serv2 < way1)
  {
    pwm.setPWM(2, 0, ++serv2);
  }
  else if(serv2 > way1)
  {
    pwm.setPWM(2, 0, --serv2);
  }
  else 
  {
    return true;
  }
  return false;
}

bool Robot::Moveservo2()
{
  if(serv4 < way4)
  {
    pwm.setPWM(4, 0, ++serv4);
  }
  else if(serv4 > way4)
  {
    pwm.setPWM(4, 0, --serv4);
  }
  else 
  {
    return true;
  }
  return false;
}

bool Robot::Moveservo3()
{
  if(serv12 < way12)
  {
    pwm.setPWM(12, 0, ++serv12);
  }
  else if(serv12 > way12)
  {
    pwm.setPWM(12, 0, --serv12);
  } 

  else 
  {
    return true;
  }
  return false; 
}

int Robot::ConvertFromAngle(int angle)
{
  return map(angle, -90, 90, 140, 533);
}

void Robot::AddPosAction()
{ 
  if(posAction < sizeArrAction - 1)
  {
    posAction++;
  }
  else
  {
    posAction = 0;
  }
}

void Robot::AddPosSetting()
{ 
  if(posSetting < arrSetting - 1)
  {
    posSetting++;
  }
  else
  {
    posSetting = 0;
  }
}