
#include  <Data.h>


void Data::GetData()
{
  delay(100);                               //без этого не работае :)
  while (Serial.available())
  {
    c = Serial.read();
    // Serial.println(c);
    if (c == 'a')               //начали считывать данные
    {
      pos = 0;
      bufData[pos++] = c;
    }
    else if (pos < 12)
    {
      bufData[pos++] = c;

      if (pos == 12)                //заполнили массив
      {
        checkRead = true;
        pos = 0;
      }
    }
  }
}

void Data::CheckData()
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
      Serial.print("корректные даные \n");
      checkData = true;
    }
    else
    {
      Serial.print("не корректные даные сумма не совподает  \n");
      checkData = false;
    }
  }
  else
  {
    Serial.print("не корректные даные неправильный формат  \n");
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

int Data::GetCheckSum()
{
  return checkSum;
}

bool Data::GetCheckData()
{
  return checkData;
}