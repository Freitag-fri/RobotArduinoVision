
#include  <Data.h>


void Data::GetCoordinates()
{
  checkData = false;
  //delay(100);                               //без этого не работае :)
  pos = 0;
  bufData[pos++] = c;
  while (Serial.available())
  {
    c = Serial.read();
    if (pos < 12)
    {
      bufData[pos++] = c;

      if (pos == 12)                //заполнили массив
      {
        checkRead = true;
        pos = 0;
        CheckCoordinates();                //преобразуем массив в данные             
      }
    }
  }
}

void Data::GetSignal()
{
  pos = 0;
  bufData2[pos++] = c;

  while (Serial.available())
  {
    c = Serial.read();

    if(bufData2[0] == 's' && pos < 4)
    {
      bufData2[pos++] = c;
      if (pos == 4)                //заполнили массив
      {
        checkRead = true;
        pos = 0;
        CheckData();                //преобразуем массив в данные             
      }
    } 
  }
}

void Data::GetData()
{
  if(Serial.available())
  {
    c = Serial.read();
    if(c == 's')
    {
      GetSignal();
    }
    else if (c == 'a')
    {
      GetCoordinates();
    }
  }
  
}

void Data::CheckData()
{
  
  int test = atoi(&bufData2[1]);
  if(checkRead)
  {
    if(test == 111)
    {
      workData = true;
    }
    else if(test == 100)
    {
      workData = false;
    }
    else if(test == 200)
    {
      resetPos = true;
    }
    delay(300);
  }
  checkRead = false;
}

void Data::CheckCoordinates()
{
  if (checkRead && bufData[0] == 'a' && bufData[4] == 'b' && bufData[8] == 'c')
  {
    bufData[4] = 0;                                    //обнуляем ключи данный для отработки atoi(прообразование в int)
    bufData[8] = 0;
    bufData[12] = 0;

    angle = atoi(&bufData[1]); //str.toInt();
    line = atoi(&bufData[5]); //str.toInt();
    checkSum = atoi(&bufData[9]); //str.toInt();

    if (checkSum == angle + line)                         //проверка на корректность введенных значений
    {
      //Serial.print("корректные даные \n");
      checkData = true;
    }
    else
    {
      //Serial.print("не корректные даные сумма не совподает  \n");
      checkData = false;
    }
  }
  else
  {
    //Serial.print("не корректные даные неправильный формат  \n");
    checkData = false;
  }
  checkRead = false;
}

void Data::PrintData()
{
  if (checkData)
  {
    Serial.print( "Данные корректны");
  }
  else
  {
    Serial.print( "Данные не корректны");
  }
  Serial.print( "angle =  ");     Serial.println(angle);
  Serial.print( "line =  ");      Serial.println(line);
  Serial.print( "checkSum =  ");  Serial.println(checkSum);
}

int Data::GetAngle()
{
  return angle;
}

int Data::GetLine()
{
  return line;
}

bool Data::GetCheckData()
{
  return checkData;
}

void Data::SetCheckDataFalse()  ///надо ли?
{
  checkData = false;
}

bool Data::GetWorkData()
{
  return workData;
}

void Data::SetResetPosFalse()
{
  resetPos = false;
}

bool Data::GetResetPos()
{
  return resetPos;
}
