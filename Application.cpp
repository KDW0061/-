/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#include <Arduino.h>
#include "Application.h"
#include "Tone_note.h"


Application::Application()
: _state(STATE_NONE)
, _reader(s_RFIDReaderSlaveSelect, s_RFIDReaderReset)
, _lifter(s_LiftServo1, s_LiftServo2)
, _drive(s_RightWheelPWM, 
         s_RightWheelDir, 
         s_LeftWheelPWM, 
         s_LeftWheelDir,
         s_SensorFrontRight, 
         s_SensorFrontCenter, 
         s_SensorFrontLeft, 
         s_SensorBottomRight, 
         s_SensorBottomLeft)
{
}

void Application::Init()
{
    _drive.Init();
    _lifter.Init();
    _reader.Init();
    _builder.Init();
    pinMode(s_Buzzer, OUTPUT);
    pinMode(s_UserButton, INPUT);
    Serial.println("Application Initialized");
}

void Application::ResetState(APP_STATE newstate)
{
    if (_state != newstate) {
        if (Serial) {
            switch (newstate) {
            case STATE_NONE:
                Serial.println("ENTER Application STATE_NONE");
                break;
            case STATE_RFIDREAD:
                Serial.println("ENTER Application STATE_RFIDREAD");
                break;
            case STATE_CMDLIST:
                Serial.println("ENTER Application STATE_CMDLIST");
                break;
            case STATE_LINECOUNTER:
                Serial.println("ENTER Application STATE_LINECOUNTER");

                break;
            case STATE_LINETRACER:
                Serial.println("ENTER Application STATE_LINETRACER");
                break;
            case STATE_TURNRIGHT:
                Serial.println("ENTER Application STATE_TURNRIGHT");
                break;
            case STATE_TURNLEFT:
                Serial.println("ENTER Application STATE_TURNLEFT");
                break;
            }
        }
    }
    _state = newstate;
}

Application::~Application()
{
    ResetState(STATE_NONE);
}

void Application::AppLineCounter()
{
    ResetState(STATE_LINECOUNTER);
    _drive.InitSensor();
    _drive.ResetLineCounter();
    _drive.Forward();
}

void Application::AppLineTracer()
{
    ResetState(STATE_LINETRACER);


    _drive.InitSensor();
}

void Application::AppTurnRight()
{
    ResetState(STATE_TURNRIGHT);
    _drive.PivotTurnRight();
    ResetState(STATE_NONE);
}

void Application::AppTurnLeft()
{
    ResetState(STATE_TURNRIGHT);
    _drive.PivotTurnLeft();
    ResetState(STATE_NONE);
}

void Application::AppCommandList()
{
    ResetState(STATE_CMDLIST);
}

void Application::AppRFIDReader()
{
    ResetState(STATE_RFIDREAD);
}

void Application::RunOnce() 
{
    _drive.Sensing();
    if (_state == STATE_NONE) {
    } else if (_state == STATE_LINECOUNTER) {
        TestLineCounter();
    } else if (_state == STATE_LINETRACER) {
        _drive.LineTrace();
    } else if (_state == STATE_TURNRIGHT) {
        _drive.PivotTurnRight();
    } else if (_state == STATE_TURNLEFT) {
        _drive.PivotTurnLeft();
    } else if (_state == STATE_CMDLIST) {
        ProcessCmdList(_builder.GetCommand());
    } else if (_state == STATE_RFIDREAD) {
        ProcessRFIDRead();
    }
}

void Application::ProcessCmdList(CMD cmd)
{
    if (cmd !=  eNONE) {
        bool bProcessFinished = true;
        switch (cmd) {
            case eInit:         _drive.InitSensor();        break;
            case eTurnRight:    _drive.PivotTurnRight();    break;
            case eTurnLeft:     _drive.PivotTurnLeft();     break;
            case eStepForward:  _drive.StepForward(STEP_FORWARD_DURATION);  break;
            case eStepBackward: _drive.StepBackward(STEP_BACKWARD_DURATION);break;
            case eStop:         _drive.Stop();              break;
            case eSVLiftUp:     _lifter.LiftUP();           break;
            case eSVLiftDown:   _lifter.LiftDown();         break;
            case eSleep:        delay(SLEEP_DURATION);      break;
            case eBeep:         AlarmBeep();                break;
            case jajturnright:         _drive.jajturnright();                break;
            case jajturnleft:          _drive.jajturnleft();                 break;
            case UTurnLeft:            _drive.UTurnLeft();                   break;
            default: 
                bProcessFinished = LineTracer((uint16_t)cmd);
                break;
        }
        if (bProcessFinished) {
            _builder.Next();
        }
    } else {
        AppRFIDReader();
    }
}

void Application::AlarmBeep()
{
    tone(s_Buzzer, NOTE_C4,150);
    delay(150);
    tone(s_Buzzer, NOTE_E4, 150);
    delay(150);
    tone(s_Buzzer, NOTE_G4, 150);
    delay(150);
}

void Application::AlarmBeep1()
{
    uint8_t i = 2;
    do {
        for(int note = 200; note< 2000; note+= 1 ) {
            tone(s_Buzzer, note, 15);
        }
        for (int note = 2000; note > 200; note-= 1) {
            tone(s_Buzzer, note, 15);
        }
    }while ( i--);
}


void Application::AlarmBeep2()
{
    uint8_t i = 2;
    do {
        for(int note = 200; note< 3000; note+= 4 ) {
            tone(s_Buzzer, note, 10);
        }
        for (int note = 3000; note > 200; note-= 4) {
            tone(s_Buzzer, note, 10);
        }
    }while ( i--);
}

bool Application::LineTracer(uint16_t nTargetLineCounter)
{

    _drive.LineTrace();
    uint16_t nLineCount = _drive.LineCounter();
    if (nTargetLineCounter == nLineCount) {
        if (Serial) {
            Serial.println("LineCount Finished");
        }
        _drive.Stop();
        _drive.ResetLineCounter();
        return true;
    }
    return false;
}

void Application::TestLineCounter() 
{
    _drive.LineTrace();
    int16_t nLine = _drive.LineCounter();
    if(Serial) {
        Serial.println(String("Line :")+ String(nLine));
    }
}

void Application::ProcessRFIDRead()
{
    if (_reader.Read()) {
        if (_builder.BuildCmdList(_reader.getUid())) {
            AppCommandList();
        } else {
            if (Serial) {
                Serial.println("Unknown Card UID");
            }
        }
    }
}
