/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

/**
 * JellibiAGV 보드용 샘플 
 *   D2 : RFID Reader control : SPI SS(Slave Select)
 *   D3 : Buzzer (Piezo Speaker)
 *   D4 : RFID Reader control : Module Reset
 *   D5 : Left side DC MOTOR : PWM  : 회전속도제어
 *   D6 : Right side DC MOTOR : PWM : 회전속도제어
 *   D7 : Left side DC MOTOR : GPO : 회전방향제어
 *   D8 : Right side DC MOTOR : GPO : 회전방향제어
 *   D9 : Servo 1  : PWM
 *   D10 : Servo 2 : PWM
 *   D11 : RFID Reader control : SPI MOSI 
 *   D12 : RFID Reader control : SPI MISO 
 *   D13 : RFID Reader control : SPI SCL
 *   A0 : 전면 센서보드 가운데 IR 센서 : ADC
 *   A1 : 전면 센서보드 왼쪽 IR 센서 : ADC
 *   A2 : 전면 센서보드 오른쪽 IR 센서 : ADC 
 *   A3 : 측면 사용자 버튼 : GPI
 *   A6 : 바닥면 센서보드 왼쪽 IR 센서 : ADC
 *   A7 : 바닥면 센서보드 오른쪽 IR 센서 : ADC
 */

#include "Application.h"

Application _app;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    _app.Init();
    _app.AppRFIDReader();
}

void loop() {
    // put your main code here, to run repeatedly:
    _app.RunOnce();
}
