/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

//리프트 함수 코드

#include "LiftControl.h"
#include "Define.h"

LiftControl::LiftControl(uint8_t servo1Pin, uint8_t servo2Pin)
: _liftState(false)
, _servo1Pin(servo1Pin)
, _servo2Pin(servo2Pin)
{
}

void LiftControl::Init()
{
    _servo1.attach(_servo1Pin);
    _servo2.attach(_servo2Pin);
    // default to Lift down state
    _servo1.write(SERVO1_PUTDOWN_ANGLE);
    _servo2.write(SERVO2_PUTDOWN_ANGLE);
    delay(300);
    _servo1.detach(); //추가 - 서보 소리 나는 문제 수정
    _servo2.detach();
}

void LiftControl::LiftUP()
{
    _servo1.attach(_servo1Pin);
    _servo2.attach(_servo2Pin);
    if (_liftState) { 
        return;
    }

    for ( int i =0; i <= MOVE_STEP; i++) {
        int angle1 = map(i, 0, MOVE_STEP, SERVO1_PUTDOWN_ANGLE, SERVO1_LIFTUP_ANGLE);
        int angle2 = map(i, 0, MOVE_STEP, SERVO2_PUTDOWN_ANGLE, SERVO2_LIFTUP_ANGLE);
        _servo1.write(angle1);
        _servo2.write(angle2);
        delay(20 + (MOVE_STEP - i)*2);  
    }  
    _liftState = true;
}

void LiftControl::LiftDown()
{
  if (!_liftState) {
    return;
  }
  for ( int i =0; i <= MOVE_STEP; i++) {
    int angle1 = map(i, 0, MOVE_STEP, SERVO1_LIFTUP_ANGLE, SERVO1_PUTDOWN_ANGLE);
    int angle2 = map(i, 0, MOVE_STEP, SERVO2_LIFTUP_ANGLE, SERVO2_PUTDOWN_ANGLE);
    _servo1.write(angle1);
    _servo2.write(angle2);
    delay(20 + (MOVE_STEP - i)*2);
  }
  _liftState = false;
  _servo1.detach(); //추가 - 서보 소리 나는 문제 수정
  _servo2.detach();
}
