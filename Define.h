/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#ifndef __DEFINE_H__
#define __DEFINE_H__
#include <Arduino.h>

/* 
     Playground 


       1       2       3       4       5       6       7       8
       ┬       ┬      ┬       ┬      ┬      ┬      ┬      ┬
 A   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 B   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 C   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 D   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 E   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 F   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 G   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       │       │      │       │      │      │      │      │    │
       │       │      │       │      │      │      │      │    │
 H   ├―┼―――――――┼――――――┼―――――――┼――――――┼――――――┼――――――┼――――――┼――――┤
       ┴       ┴      ┴       ┴      ┴      ┴      ┴      ┴    ┴
     Seoul  InCheon  SeJong  Daejeon  Daegu  KwangJu ChunCeon  Jeju


*/

#define MAX_CMD 32

enum CMD {
    eNONE = 0,          // None, 명령목록의 끝을 구분하는데 사용
    eTr1 = 1,           // {{{ LineTrace 
    eTr2 = 2,
    eTr3 = 3, 
    eTr4 = 4,
    eTr5 = 5, 
    eTr6 = 6, 
    eTr7 = 7, 
    eTr8 = 8,
    eTr9 = 9, 
    eTr10 = 10, 
    eTr11 = 11, 
    eTr12 = 12, 
    eTr13 = 13, 
    eTr14 = 14, 
    eTr15 = 15,         // }}} 
    eInit = 100,    // INIT LineTracer, 라인트레이서 동작을 위한 기준값을 센서에 읽어들여서 라인트레이서 동작 전에 반드시 사용
    eTurnRight,     // Turn Right 
    eTurnLeft,      // Turn Left
    jajturnleft,
    jajturnright,
    UTurnLeft,
    eStepForward,   // STEP, 빠레트를 들으러 갈 때 사용, 빠레트와 젤리비의 중심점 맞추기
    eStepBackward, // eStepForward를 사용하고 라인트레이싱으로 이동 가능한 위치로 후진
    eStop,            // STOP
    eSVLiftUp,      // Servo Lift
    eSVLiftDown,    // Servo Down
    eRFID,          // Start Card detect
    eSleep,         // Sleep 1sec 
    eBeep           // Beep
};

/*
static const String s_strRFIDUidForDaegu;
static const String s_strRFIDUidForGwangju;
static const String s_strRFIDUidForChuncheon;
static const String s_strRFIDUidForJeju;
*/

#define STEP_FORWARD_DURATION       450 // 수가 낮으면 덜 움직인다, 이걸로 eStepForward 동작
#define STEP_BACKWARD_DURATION      250 // eStepBackward 동작
#define SLEEP_DURATION             300

//#define MAX_DRIVE_SPEED       150
#define NORMAL_DRIVE_SPEED    150

#define TURN_INITIAL_WHEEL_SPEED 80 // 수가 낮으면 속도가 느려진다, highspeed
#define TURN_INSIDE_WHEEL_SPEED  60 // lowspeed
#define TURN_OUTSIDE_WHEEL_SPEED 68 //_turnSpeed

#define LINEDETECT_THRESHOLD_MIN 500
#define BLANKDETECT_THERSHOLD_MAX 200

#define SERVO1_PUTDOWN_ANGLE 180 // MinDown
#define SERVO1_LIFTUP_ANGLE 90+20  // MaxUp+10
#define SERVO2_PUTDOWN_ANGLE  0   // MinDown
#define SERVO2_LIFTUP_ANGLE 90-20 // MaxUp-10


#endif//__DEFINE_H__
