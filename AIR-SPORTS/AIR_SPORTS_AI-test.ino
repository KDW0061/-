#include <PRIZM.h>

#include <TELEOP.h>  //조작명령 들어있는 라이브러리 호출
#include <PRIZM.h>
#include "HUSKYLENS.h"

PRIZM prizm;
HUSKYLENS huskylens;
EXPANSION exc;
PS4 ps4;

int servo1Position = 90; // 초기 위치
int servo2Position = 90;   // 초기 위치
const int servoStep = 5;  // 서보모터가 한 번에 이동할 단계 크기
const int servo1MinPosition = 70;   //잡는 값 변경 가능 
const int servo1MaxPosition = 180;  //이건 고정
const int servo2MinPosition = 0;    //이건 고정
const int servo2MaxPosition = 110;   //잡는 값 변경 가능

void setup() {          //프리즘 프로그램 시작
  Serial.begin(9600);
  prizm.PrizmBegin();
  prizm.setServoSpeed(1,100); //서보모터 스피드 설정
  prizm.setServoSpeed(2,100);
  
  prizm.setServoPosition(1,70);  //서보모터 처음위치 설정
  
  prizm.setServoPosition(2,90);
  delay(500);
  
  prizm.setMotorInvert(2,1); // X번 포트를 변환시킴


  //여기부터 자율주행 코드

  exc.setMotorPower(1, 1, 120);
  delay(5000);
  
  prizm.setMotorPowers(-50,-50);
  delay(3800);
  prizm.setMotorPowers(125,125);

  prizm.setServoPosition(1,180);  
  prizm.setServoPosition(2,0);
  delay(1000);
  
  //여기까지 자율주행 코드 
  //일단됨

  /*
  prizm.setMotorPowers(-50,-50);
  delay(3800);
  prizm.setMotorPowers(125,125);

  prizm.setServoPosition(1,180);  
  prizm.setServoPosition(2,0);
  */

}

void loop() { //ps4 컨트롤러 버튼 입력값을 받음
  ps4.getPS4();
  Buttons();

}

void Buttons() {                                 //아래 값을 받아 로봇이동
  int lx = map(ps4.Stick(LX), 0, 255, -49, 50); //왼쪽 조이스틱의 x축값을 받음
  int ly = map(ps4.Stick(LY), 0, 255, -49, 50); //왼쪽 조이스틱의 y축값을 받음
  int r_motor = -(ly - lx); //  앞뒤 좌우 바꿈 -값 붙여
  int l_motor = -(ly + lx);  
  if (r_motor > 100){
    r_motor = 100;
  }
  if (l_motor > 100) {
    l_motor = 100;
  }
  prizm.setMotorPowers(l_motor, r_motor);


  // L2 버튼이 눌린 동안 서보모터 위치를 서서히 변경 (그리퍼 놓기)
  if (ps4.Button(L1)) {
    if (servo2Position > servo2MinPosition) {
      servo2Position -= servoStep; // 위치를 서서히 감소시켜 그리퍼 놓기
    }
  }

  // L2 버튼이 눌린 동안 서보모터 위치를 서서히 변경 (그리퍼 잡기)
  if (ps4.Button(L2)) {
    if (servo2Position < servo2MaxPosition) {
      servo2Position += servoStep; // 위치를 서서히 증가시켜 그리퍼 잡기
    }
  }

    // R2 버튼이 눌린 동안 서보모터 위치를 서서히 변경 (그리퍼 잡기)
  if (ps4.Button(R2)) {
    if (servo1Position > servo1MinPosition) {
      servo1Position -= servoStep; // 위치를 서서히 증감소시켜 그리퍼 잡기
    }
  }

  // R2 버튼이 눌린 동안 서보모터 위치를 서서히 변경 (그리퍼 놓기)
  if (ps4.Button(R1)) {
    if (servo1Position < servo1MaxPosition) {
      servo1Position += servoStep; // 위치를 서서히 증가시켜 그리퍼 놓기
    }
  }

  // 서보모터의 위치를 실제로 설정
  prizm.setServoPosition(1, servo1Position);
  prizm.setServoPosition(2, servo2Position);

  if (ps4.Button(SQUARE)) {
    exc.setMotorPower(1, 2, 125); // 125 브레이크값. 브레이크버튼.
  }
  while (ps4.Button(TRIANGLE)) { // 레일 감기, 올리기
    exc.setMotorPower(1, 1, 120); //0
    ps4.getPS4();
  }
  while (ps4.Button(CROSS)) { // 레일 풀기, 내리기
    exc.setMotorPower(1, 1, -80); //0
    ps4.getPS4();
  }
  exc.setMotorPower(1, 1, 125); //
}
