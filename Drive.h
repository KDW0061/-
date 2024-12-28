/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 *
 *  함수 선언
 */

#ifndef __DRIVE_H__
#define __DRIVE_H__
#include <Arduino.h>
#include "Define.h"

class Drive
{
private: 
    uint8_t _rightWheelPwm;
    uint8_t _rightWheelDir;
    uint8_t _leftWheelPwm;
    uint8_t _leftWheelDir;
    
    uint8_t _pinFrontRight;
    uint8_t _pinFrontCenter;
    uint8_t _pinFrontLeft;
    uint8_t _pinBottomRight;
    uint8_t _pinBottomLeft;

private:
    const int _speed = NORMAL_DRIVE_SPEED;
    const int _turnLowSpeed = TURN_INSIDE_WHEEL_SPEED;
    const int _turnSpeed = TURN_OUTSIDE_WHEEL_SPEED;
    const int _turnHighSpeed = TURN_INITIAL_WHEEL_SPEED;
    int16_t  _initRightValue; // Default sampling right ir value
    int16_t  _initLeftValue;  // Default sampling left ir value
    int16_t  _centerValue;   // for line trace
    int16_t  _rightValue;    // 
    int16_t  _leftValue;

    uint16_t _nLineCounter;

    int16_t GetLeft();
    int16_t GetRight();
    
    int16_t GetFrontLeft();
    int16_t GetFrontRight();
    int16_t GetFrontCenter();

public:
    Drive(uint8_t rightWheelPwm, 
          uint8_t rightWheelDir, 
          uint8_t leftWheelPwm, 
          uint8_t leftWheelDir,
          uint8_t pinFrontRight, 
          uint8_t pinFrontCenter, 
          uint8_t pinFrontLeft, 
          uint8_t pinBottomRight, 
          uint8_t pinBottomLeft);

    void Init();
    void InitSensor();
    void Sensing();

    void LineTrace();  
    void PivotTurnLeft();
    void PivotTurnRight();
    void jajturnleft();
    void jajturnright();
    void UTurnLeft();
    

    uint16_t LineCounter();
    
    void Stop();
    void Forward();
    void Backward();
    void StepForward(uint32_t timeInMs);
    void StepBackward(uint32_t timeInMs);
    void ResetLineCounter();

    

    
};

#endif//__DRIVE_H__
