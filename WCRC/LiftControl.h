/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

//리프트 함수 선언

#ifndef __LIFTCONTROL_H__
#define __LIFTCONTROL_H__
#include <Arduino.h>
#include <Servo.h>

class LiftControl
{
private:
    const int MOVE_STEP = 30;
protected:
    uint8_t _servo1Pin;
    uint8_t _servo2Pin;
    Servo _servo1;
    Servo _servo2;
    bool  _liftState;
public:
    LiftControl(uint8_t servo1Pin, uint8_t servo2Pin);
    void Init();
    void LiftUP();
    void LiftDown();
};

#endif//__LIFTCONTROL_H__
