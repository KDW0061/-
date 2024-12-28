/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 *
 *  함수가 있는 코드
 */

#include "Drive.h"

Drive::Drive(uint8_t rightWheelPwm,
             uint8_t rightWheelDir,
             uint8_t leftWheelPwm,
             uint8_t leftWheelDir,
             uint8_t pinFrontRight,
             uint8_t pinFrontCenter,
             uint8_t pinFrontLeft,
             uint8_t pinBottomRight,
             uint8_t pinBottomLeft)
: _initRightValue(0)
, _initLeftValue(0)
, _centerValue(0)
, _rightValue(0)
, _leftValue(0)
, _nLineCounter(0)
, _rightWheelPwm(rightWheelPwm)
, _rightWheelDir(rightWheelDir)
, _leftWheelPwm(leftWheelPwm)
, _leftWheelDir(leftWheelDir)
, _pinFrontRight(pinFrontRight)
, _pinFrontCenter(pinFrontCenter)
, _pinFrontLeft(pinFrontLeft)
, _pinBottomRight(pinBottomRight)
, _pinBottomLeft(pinBottomLeft)
{
}

void Drive::Init()
{
    pinMode(_rightWheelDir, OUTPUT);
    pinMode(_leftWheelDir, OUTPUT);
    pinMode(_rightWheelPwm, OUTPUT);
    pinMode(_leftWheelPwm, OUTPUT);
    pinMode(_pinFrontRight, INPUT);
    pinMode(_pinFrontCenter, INPUT);
    pinMode(_pinFrontLeft, INPUT);
    pinMode(_pinBottomRight, INPUT);
    pinMode(_pinBottomLeft, INPUT);
}

void Drive::InitSensor() 
{
    Stop();
    _initLeftValue = GetLeft();
    _initRightValue = GetRight();
    _centerValue = GetRight() - GetLeft();
    ResetLineCounter();
}

void Drive::Sensing()
{
    _rightValue = GetRight();
    _leftValue = GetLeft();
}

void Drive::Forward() // Forward를 사용해서 직진 값을 맞추려면 _speed에 값을 빼주거나 더해주면 된다. ex)_speed-2
{
    delay(10);
    digitalWrite(_leftWheelDir, 1);
    digitalWrite(_rightWheelDir, 0);
    delay(10);
    analogWrite( _leftWheelPwm, _speed);
    analogWrite( _rightWheelPwm, _speed-7);
}

void Drive::Backward() // 후진
{
    delay(10);
    digitalWrite(_leftWheelDir, 0);
    digitalWrite(_rightWheelDir, 1);
    delay(10);
    analogWrite( _leftWheelPwm, _speed-88);
    analogWrite( _rightWheelPwm, _speed-90);
}

// Half Pivot Turn for JellibiAGV
void Drive::PivotTurnLeft() // 왼쪽 회전 시간
{
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1); // 왼바퀴 방향 앞으로 지정
    digitalWrite(_rightWheelDir, 0); // 오른바퀴 방향 앞으로 지정
    delay(10);
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 90);
    delay(200);
    while(!(_leftValue >= 480 && _rightValue <= 200))
    {
      analogWrite( _rightWheelPwm, 85);
      Sensing();
    }
    while(!(_leftValue <= BLANKDETECT_THERSHOLD_MAX && _rightValue <=BLANKDETECT_THERSHOLD_MAX))
    {
      analogWrite( _rightWheelPwm, 85);
      Sensing();
    }
    analogWrite( _leftWheelPwm, 75);
    delay(100);
    analogWrite( _leftWheelPwm, 0);
}

// Half Pivot Turn for JellibiAGV
void Drive::PivotTurnRight() // 오른쪽 회전 시간
{
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1); // 왼바퀴 방향 앞으로 지정, 코드 리뷰 블로그 보면 잘 나와있으니까 헷갈리면 보고오면 좋아
    digitalWrite(_rightWheelDir, 0); // 오른바퀴 방향 앞으로 지정
    delay(10);
    analogWrite( _leftWheelPwm, 90);
    analogWrite( _rightWheelPwm, 0);
    delay(300);
    while(!(_rightValue >= 480 && _leftValue <= 200))
    {
      analogWrite( _leftWheelPwm, 85);
      Sensing();
    }
    while(!(_leftValue <= BLANKDETECT_THERSHOLD_MAX && _rightValue <=BLANKDETECT_THERSHOLD_MAX))
    {
      analogWrite( _leftWheelPwm, 85);
      Sensing();
    }
    analogWrite( _rightWheelPwm, 60);
    delay(200);
    analogWrite( _rightWheelPwm, 0);
}

void Drive::jajturnleft()   // 왼쪽 회전
{
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1); // 왼바퀴 방향 앞으로 지정
    digitalWrite(_rightWheelDir, 0); // 오른바퀴 방향 앞으로 지정
    delay(10);
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 90);
    delay(200);
    while(!(_leftValue >= 510 && _rightValue <= 200))
    {
      analogWrite( _rightWheelPwm, 75);
      Sensing();
    }
    while(!(_leftValue <= BLANKDETECT_THERSHOLD_MAX && _rightValue <=BLANKDETECT_THERSHOLD_MAX))
    {
      analogWrite( _rightWheelPwm, 75);
      Sensing();
    }
    analogWrite( _leftWheelPwm, 75);
    delay(100);
    analogWrite( _leftWheelPwm, 0);
}

void Drive::jajturnright()  //오른쪽 회전
{
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1); // 왼바퀴 방향 앞으로 지정, 코드 리뷰 블로그 보면 잘 나와있으니까 헷갈리면 보고오면 좋아
    digitalWrite(_rightWheelDir, 0); // 오른바퀴 방향 앞으로 지정
    delay(10);
    analogWrite( _leftWheelPwm, 90);
    analogWrite( _rightWheelPwm, 0);
    delay(300);
    while(!(_rightValue >= 510 && _leftValue <= 200))
    {
      analogWrite( _leftWheelPwm, 75);
      Sensing();
    }
    while(!(_leftValue <= BLANKDETECT_THERSHOLD_MAX && _rightValue <=BLANKDETECT_THERSHOLD_MAX))
    {
      analogWrite( _leftWheelPwm, 75);
      Sensing();
    }
    analogWrite( _rightWheelPwm, 60);
    delay(200);
    analogWrite( _rightWheelPwm, 0);
}

void Drive::UTurnLeft()     // 왼쪽 회전 유턴
{
     analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1);
    digitalWrite(_rightWheelDir, 0);
    delay(10);
    analogWrite( _rightWheelPwm, _turnHighSpeed); // outside speed
    analogWrite( _leftWheelPwm, _turnHighSpeed);
    delay(100);
    digitalWrite(_leftWheelDir, 0);
    digitalWrite(_rightWheelDir, 0);
    delay(10);
    analogWrite( _leftWheelPwm, _turnLowSpeed);
    analogWrite( _rightWheelPwm, _turnLowSpeed);
    delay(1660);
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
}

void Drive::LineTrace() // turnspeed가 0보다 크면 오른쪽으로 회전, 0보다 작으면 왼쪽으로 회전           라인 트레이서(선 따라가기)
{
    int16_t turnSpeed = ((_rightValue-_leftValue) - _centerValue)/16; // 나누는 값은 회전반경, 회전 속도를 결정
    int16_t leftSpeed = (_speed+15) + turnSpeed; //_speed는 초기 스피드로 Define.h에 Normal_Drive_speed로 정의
    int16_t rightSpeed = (_speed+7) - turnSpeed;

    digitalWrite( _leftWheelDir, (leftSpeed > 0)?1:0);
    digitalWrite( _rightWheelDir, (rightSpeed > 0)?0:1);
    analogWrite( _leftWheelPwm, round(abs(leftSpeed)));
    analogWrite( _rightWheelPwm, round(abs(rightSpeed)));
}

uint16_t Drive::LineCounter()         //라인 카운터 
{
    static uint8_t bSignalHigh = 0;
    if (_rightValue > LINEDETECT_THRESHOLD_MIN && _leftValue > LINEDETECT_THRESHOLD_MIN) {
        if (bSignalHigh==0) {
            _nLineCounter++;
            if (Serial) {
                Serial.println(String("LINE!!! :")+ String(_nLineCounter));
            }
            bSignalHigh = 1;
        }
    } else if (_rightValue < BLANKDETECT_THERSHOLD_MAX && _leftValue < BLANKDETECT_THERSHOLD_MAX) {
        if (bSignalHigh) {
            bSignalHigh = 0;
        }
    }
    return _nLineCounter;
}

void Drive::ResetLineCounter()
{
    _nLineCounter = 0;
}

void Drive::Stop() 
{
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
}

void Drive::StepForward(uint32_t timeInMs)
{
    Forward();
    delay(timeInMs);
    Stop();
}


void Drive::StepBackward(uint32_t timeInMs)
{
    Backward();
    delay(timeInMs);
    Stop();
}


int16_t Drive::GetLeft() 
{
    return analogRead(_pinBottomLeft);
}

int16_t Drive::GetRight() 
{
    return analogRead(_pinBottomRight);
}


int16_t Drive::GetFrontLeft()
{
    return analogRead(_pinFrontLeft);
}

int16_t Drive::GetFrontRight()
{
    return analogRead(_pinFrontRight);
}

int16_t Drive::GetFrontCenter()
{
    return analogRead(_pinFrontCenter);  
}
