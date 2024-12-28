/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Arduino.h>
#include "Define.h"
#include "Drive.h"
#include "RFIDReader.h"
#include "LiftControl.h"
#include "CommandBuilder.h"


class Application
{
public:
/**
 * JellibiAGV 보드용 샘플 
 *   D2 : RFID Reader control : SPI SS(Slave Select)
 *   D3 : Buzzer (Piezo Speaker)
 *   D4 : RFID Reader control : Module Reset
 *   D5 : Left side DC MOTOR : PWM  : 회전속도제어
 *   D6 : Right side DC MOTOR : PWM : 회전속도제어
 *   D7 : Left side DC MOTOR : GPIO : 회전방향제어
 *   D8 : Right side DC MOTOR : GPIO : 회전방향제어
 *   D9 : Servo 1  : PWM
 *   D10 : Servo 2 : PWM
 *   D11 : RFID Reader control : SPI MOSI 
 *   D12 : RFID Reader control : SPI MISO 
 *   D13 : RFID Reader control : SPI SCL
 *   A0 : 전면 센서보드 가운데 IR 센서 : ADC
 *   A1 : 전면 센서보드 왼쪽 IR 센서 : ADC
 *   A2 : 전면 센서보드 오른쪽 IR 센서 : ADC
 *   A3 : 기구 측면 사용자용 버튼 : GPI
 *   A6 : 바닥면 센서보드 왼쪽 IR 센서 : ADC
 *   A7 : 바닥면 센서보드 오른쪽 IR 센서 : ADC
 */
    static const uint8_t s_RFIDReaderSlaveSelect = 2;
    static const uint8_t s_Buzzer = 3;
    static const uint8_t s_RFIDReaderReset = 4;
    static const uint8_t s_RightWheelPWM = 5;
    static const uint8_t s_LeftWheelPWM = 6;
    static const uint8_t s_RightWheelDir = 7;
    static const uint8_t s_LeftWheelDir = 8;
    static const uint8_t s_LiftServo1 = 9;
    static const uint8_t s_LiftServo2 = 10;
    static const uint8_t s_UserButton = A3;
    
    static const uint8_t s_SensorFrontRight = A2;
    static const uint8_t s_SensorFrontLeft = A6;
    static const uint8_t s_SensorFrontCenter = A7;
    static const uint8_t s_SensorBottomRight = A0;
    static const uint8_t s_SensorBottomLeft = A1;

private:
    enum APP_STATE{
        STATE_NONE=0,
        STATE_RFIDREAD,
        STATE_CMDLIST,
        STATE_LINECOUNTER,
        STATE_LINETRACER,
        STATE_TURNRIGHT,
        STATE_TURNLEFT 
    } _state;
        
    Drive _drive;
    RFIDReader _reader;
    LiftControl _lifter;
    CommandBuilder _builder;

    void ResetState(APP_STATE newstate);
    void ProcessCmdList(CMD cmd);
    void ProcessRFIDRead();

    void TestLineCounter();
    bool LineTracer(uint16_t nTargetLineCounter);
    
    void AlarmBeep();
    void AlarmBeep1();
    void AlarmBeep2();

public: 
    Application();
    virtual ~Application();
    void Init(); // called at arduino's setup() function
    
    // {{{ Test Application
    void AppLineCounter();
    void AppLineTracer();
    void AppTurnRight();
    void AppTurnLeft();
    // }}}

    void AppCommandList();
    void AppRFIDReader();
    
    void RunOnce(); // called at arduino's loop() function
};

#endif
