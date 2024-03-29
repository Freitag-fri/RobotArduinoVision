#pragma once

//#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#include "Data.h"


class Robot
{
    private:    
        ///( 132-525) поворот   (345 - 90градусов)  516     310     115
        int serv0 = 325; 
        ///( 200-460) чемь меньше, тем сильнее расскрывается (можно и меньше наверное)      
        int serv2 = 475;  //450
        ///( 140-380) чемь меньше тем выше подымается        
        int serv4 = 390;    //370
        ///( 95-330..) чемь меньше тем выше подымается //схват вниз вверх        
        int serv12 = 230;   //230
        //( 140-330..) на 120 зажат схват      
        int serv5 = 150;       

        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
        ///обьект класса Data
        Data data;
        
        int angleNew = ConvertFromAngle(0);
        int lineNew = 0;


        int way1 = 463;
        int way4 = 390;
        int way12 = 230;

        bool work = false;

        static const int sizeArrAction = 18;
        /// 0 - ContronPosition() 
        /// 1 - MoveServo() 
        /// 2 - GetCoordinates()
        /// 3 - TakeItem()
        /// 4 - CoordinatesSetting()
        /// 5 - ReleaseItem()
        /// 6 - MoveAndle()
        /// 7 - MoveLine()
        /// 8 - CapturePreparation()
        const int arrAction[sizeArrAction] = {0, 8, 7, 6, 10, 2, 6, 7, 9, 7, 3, 0, 7, 6, 4, 6, 7, 5};
        int posAction = 0; 
        
    public:
        void ChangeWork();
        void MoveChangeWork();

        void SettingServo();
        ///вызывает GetData класса Data        
        void StartMove();
        void MoveServo();
        ///взять деталь
        void TakeItem();
        ///отпустить деталь
        void ReleaseItem(int value);
        ///преобразование значение учла в значение серво
        int ConvertFromAngle(int angle);
        ///опускаем и роскрываем схват
        void CapturePreparation();

        ///перевод робота в контрольную позицию
        void ControlPosition();
        ///перевод робота в контрольную позицию (линейный размер)
        void SetLineControlPosition();

        void MoveAngle();           //метод поворота
        void SetLine();             //метод для линейного перемещения

        void GetCoordinates();
        void CoordinatesSetting();

        void MoveLine();
        

        bool Moveservo1();
        bool Moveservo2();
        bool Moveservo3();
        unsigned long startTime = millis();

        static const int arrSetting = 6;
        const int arrLine[arrSetting] = {80, 83, 89, 10, 16, 22};       
        const int arrAngle[arrSetting] = {90, 80, 70, 90, 78, 68};        
        int posSetting = 0;

        void AddPosAction();
        void AddPosSetting();
        void ResetPosSetting();

        void SetCoordinatesGrab();
};