#include <PRIZM.h> //PRIZM 라이브러리
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);
// 스캔 순서 파랑 1, 빨강 2, 초록 3, 노랑 4
// 그리퍼 잡은 각도 170
// 그리퍼 놓는 각도 20
PRIZM prizm;
EXPANSION exc;           //  prizm.PrizmEnd();
const int SPEED = 100;   //기본값을 500로 설정(상수로) ~720
const int irSensorPin4 = 4;
const int irSensorPin2 = 2; 
const int irSensorPin3 = 3; 
const int irSensorPin5 = 5;    

int robotX = 0;
int robotY = 0;
  
int YELLOW_BLOCK_X = 0;         // 노랑 기둥과 블록의 색상 좌표
int YELLOW_BLOCK_Y = 0;      

int GREEN_BLOCK_X = 0;         // 초록 기둥
int GREEN_BLOCK_Y = 0;

int BLUE_BLOCK_X = 0;          // 파랑 기둥
int BLUE_BLOCK_Y = 0;

int RED_BLOCK_X = 0;          // 빨강 기둥
int RED_BLOCK_Y = 0;
   
int GREEN_OBJECT_X = 0;        // 초록 오브젝트(1,1)
int GREEN_OBJECT_Y = 0;

int BLUE_OBJECT_X = 0;        //파랑(1,3)
int BLUE_OBJECT_Y = 0;

int RED_OBJECT_X =  0;          //빨강(1,2)
int RED_OBJECT_Y =  0;

void setup() {
  prizm.PrizmBegin();
  prizm.resetEncoder(1);
  Serial.begin(9600);
  //  huskylens.begin();
  prizm.setServoSpeed(1,100);
  prizm.setServoPosition(1,170);

  crose(400, 2);
  delay(1400);    
  first_line();   //처음 라인 교정
  scan_bo();      //스캔 완료
  o_b_m();          //오브젝트 옮기는 코드
  chY(0);     // 마무리 동작을 위해 1,0좌표로 이동 
  chX(1);
  move(100,3);
  delay(1000);
  crose(400,4);  
  delay(1800);

  prizm.PrizmEnd();
}

void chX(int x){    //  X좌표 위치 변경
  if(robotX !=x){
    if(robotX == 1 && robotY == 4){
      stay_r_turn5(2);
    }else{
      stay_r_turn(2);
    }
  }
}

void chY(int y){              // 해당 Y 좌표 이동
  while(robotY != y){
    if(robotY<y){                   // y 좌표가 로봇의 Y좌표보다 크면
      if(robotX==1){                // 로봇의 X 좌표가 1일 때
        stay_r_turn(2);
        move(130,3);
        delay(800);
        while(prizm.readLineSensor(irSensorPin5) != HIGH){        // 5번 ir센서가 1일때
          if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
        robotY+=1;
        Serial.print("robot Y : ");
        Serial.println(robotY);
      }else{              //로봇의 X 좌표가 0일때
        move(130,3);
        delay(800);
        while(prizm.readLineSensor(irSensorPin5) != HIGH){
          if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
        robotY+=1;
        Serial.print("robot Y : ");
        Serial.println(robotY);
      }
    }else{                          // y 좌표가 로봇의 Y 좌표보다 작을때 
      if(robotX==0){                // 로봇의 X 좌표가 0 일때
        stay_r_turn(2);
        move(130,3);
        delay(800);
        while(prizm.readLineSensor(irSensorPin5) != HIGH){
          if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
        robotY-=1;
        Serial.print("robot Y : ");
        Serial.println(robotY);
      }else{                        //  로봇의 X 좌표가 1일때
        move(130,3);
        delay(800);
        while(prizm.readLineSensor(irSensorPin5) != HIGH){
          if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
        robotY-=1;
        Serial.print("robot Y : ");
        Serial.println(robotY);
      }
    }
  }
}

void chY_m(int x, int n){              // 해당 좌표 이동
  for(int i=0; i<n+3; i++){
    if(robotY<n){
      if(robotX==1){
        stay_r_turn(2);
        move(100,3);
        delay(500);
        while(1){                                 //LOW = 흰색 , HIGH = 검정색
          if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
            robotY++;
            stop();
            break;
          }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
            exc.setMotorSpeed(3,1, 0);
            exc.setMotorSpeed(3,2, +50);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
            exc.setMotorSpeed(3,1, -50);
            exc.setMotorSpeed(3,2, 0);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
      }else{
        move(100,3);
        delay(500);
        while(1){                                 //LOW = 흰색 , HIGH = 검정색
          if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
            robotY++;
            stop();
            break;
          }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
            exc.setMotorSpeed(3,1, 0);
            exc.setMotorSpeed(3,2, +50);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
            exc.setMotorSpeed(3,1, -50);
            exc.setMotorSpeed(3,2, 0);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
      }
    }else if(robotY>n){
      if(robotX==0){
        stay_r_turn(2);
        move(100,3);
        delay(500);
        while(1){                                 //LOW = 흰색 , HIGH = 검정색
          if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
            robotY--;
            stop();
            break;
          }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
            exc.setMotorSpeed(3,1, 0);
            exc.setMotorSpeed(3,2, +50);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
            exc.setMotorSpeed(3,1, -50);
            exc.setMotorSpeed(3,2, 0);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
      }else{
        move(100,3);
        delay(500);
        while(1){                                 //LOW = 흰색 , HIGH = 검정색
          if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
            robotY--;
            stop();
            break;
          }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
            exc.setMotorSpeed(3,1, 0);
            exc.setMotorSpeed(3,2, +50);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
            exc.setMotorSpeed(3,1, -50);
            exc.setMotorSpeed(3,2, 0);
            exc.setMotorSpeed(2,1, 0);             
            exc.setMotorSpeed(2,2, 0);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
            exc.setMotorSpeed(3,1, -140);
            exc.setMotorSpeed(3,2, +100);
            exc.setMotorSpeed(2,1, +100);             
            exc.setMotorSpeed(2,2, -130);
          }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -100);
            exc.setMotorSpeed(3,2, +140);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -100);
          }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
            exc.setMotorSpeed(3,1, -130);
            exc.setMotorSpeed(3,2, +130);
            exc.setMotorSpeed(2,1, +130);             
            exc.setMotorSpeed(2,2, -130);
          }
        }
      }
    }else{
      if(robotX != x){
        if(robotX == 1 && robotY == 4){
          stay_r_turn5(2);
          stop();
        }else{
          stay_r_turn(2);
          stop();
        }
      }
      stop();
    }
  }
}

void o_b_m(){                 //오브젝트 옮기는 코드
  chY_m(GREEN_OBJECT_X, GREEN_OBJECT_Y);
  pickup();
  chY_m(YELLOW_BLOCK_X, YELLOW_BLOCK_Y);
  pickdown();
  if(GREEN_OBJECT_X == RED_BLOCK_X && GREEN_OBJECT_Y == RED_BLOCK_Y){
    chY_m(RED_OBJECT_X, RED_OBJECT_Y);
    pickup();
    chY_m(RED_BLOCK_X, RED_BLOCK_Y);
    pickdown();

    chY_m(BLUE_OBJECT_X, BLUE_OBJECT_Y);
    pickup();
    chY_m(BLUE_BLOCK_X, BLUE_BLOCK_Y);
    pickdown();
  }else if(GREEN_OBJECT_X == BLUE_BLOCK_X && GREEN_OBJECT_Y == BLUE_BLOCK_Y){
    chY_m(BLUE_OBJECT_X, BLUE_OBJECT_Y);
    pickup();
    chY_m(BLUE_BLOCK_X, BLUE_BLOCK_Y);
    pickdown();

    chY_m(RED_OBJECT_X, RED_OBJECT_Y);
    pickup();
    chY_m(RED_BLOCK_X, RED_BLOCK_Y);
    pickdown();
  }
  GREEN_OBJECT_X = YELLOW_BLOCK_X;
  GREEN_OBJECT_Y = YELLOW_BLOCK_Y;
  chY_m(GREEN_OBJECT_X, GREEN_OBJECT_Y);
  pickup();
  chY_m(GREEN_BLOCK_X, GREEN_BLOCK_Y);
  pickdown();
}

void scan_bo(){   //오브젝트, 기둥 스캔 
  for(int i = 1; i<5; i++){
    chY(i);
    stop();
    scan();         // 3 
  }
  while(RED_BLOCK_Y == 0 || GREEN_BLOCK_Y == 0 || BLUE_BLOCK_Y == 0 || YELLOW_BLOCK_Y == 0){
    chX(1);
    for(int j =4; j>=1; j--){
      if(RED_BLOCK_Y != 0 && GREEN_BLOCK_Y != 0 && BLUE_BLOCK_Y != 0 && YELLOW_BLOCK_Y != 0){
        break;
      }
      chY(j);    // 2 
      stop();
      scan();
    }
  }
}

/*
void scan_bo(){   //오브젝트, 기둥 스캔 
  chY(1);    // 0
  stop();
  delay(100);
  scan();
  chY(2);    // 1
  stop();
  delay(100);
  scan();
  chY(3);    // 2
  stop();
  delay(100);
  scan();
  chY(4);    // 3
  stop();
  delay(100);
  scan();
  chX(1);
  stop();
  stop();
  delay(50);
  scan();         // 3 
  chY(3);    // 2 
  stop();
  delay(100);   
  scan();
  chY(2);    // 1
  stop();
  delay(100);
  scan();
  chY(1);    // 0
  stop();
  delay(100);
  scan();
}
*/
void scan(){            //스캔 및 값 저장 
  Wire.begin();         //I2C 통신 시작
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    delay(100);
  }
  if (huskylens.request())
    {
    Serial.println(F("스캔 시작"));
    while (huskylens.available())
    {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
    }    
  }
}

void printResult(HUSKYLENSResult result){           //허스키 렌즈로 읽은 값 처리
  if (result.command == COMMAND_RETURN_BLOCK){
    Serial.println(String()+F("xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",height=")+result.height+F(",ID=")+result.ID);
    if(result.ID==1){
      if(result.yCenter>100){
        Serial.println("파랑 기둥");      
        BLUE_BLOCK_X = robotX;              //좌표 저장
        BLUE_BLOCK_Y = robotY;
      }
      else{
        Serial.println("파랑 오브젝트");
        BLUE_OBJECT_X = robotX;         
        BLUE_OBJECT_Y = robotY;
      }
    }
    else if(result.ID==2){
      if(result.yCenter>100){
        Serial.println("빨강 기둥");
        RED_BLOCK_X = robotX;         
        RED_BLOCK_Y = robotY;
      }
      else{
        Serial.println("빨강 오브젝트");
        RED_OBJECT_X = robotX;         
        RED_OBJECT_Y = robotY; 
      }
    }
    else if(result.ID==3){
      if(result.yCenter>100){
        Serial.println("초록 기둥");
        GREEN_BLOCK_X = robotX;         
        GREEN_BLOCK_Y = robotY;
      }
      else{
        Serial.println("초록 오브젝트");
        GREEN_OBJECT_X = robotX;         
        GREEN_OBJECT_Y = robotY;
      }
    }
    else if(result.ID==4){
      if(result.yCenter>100){
        Serial.println("노랑 기둥");
        YELLOW_BLOCK_X = robotX;         
        YELLOW_BLOCK_Y = robotY; 
      }
    }
    else{
      Serial.println("no object");
    }
  }
}

void line_r_t(int n){              // 오른쪽 움직임 라인 트레이서  n칸 수
  for(int i=0; i<n; i++){
    if(robotX==0){
      robotY++;
    }else if (robotX == 1){
      robotY--;
    }
    move(100,3);
    delay(800);
    while(1){                                 //LOW = 흰색 , HIGH = 검정색
      if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
        stop();
        delay(100);
        break;
      }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
        exc.setMotorSpeed(3,1, 0);
        exc.setMotorSpeed(3,2, +50);
        exc.setMotorSpeed(2,1, 0);             
        exc.setMotorSpeed(2,2, 0);
      }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
        exc.setMotorSpeed(3,1, -50);
        exc.setMotorSpeed(3,2, 0);
        exc.setMotorSpeed(2,1, 0);             
        exc.setMotorSpeed(2,2, 0);
      }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == HIGH)){
        exc.setMotorSpeed(3,1, -140);
        exc.setMotorSpeed(3,2, +100);
        exc.setMotorSpeed(2,1, +100);             
        exc.setMotorSpeed(2,2, -130);
      }else if(prizm.readLineSensor(irSensorPin2) == HIGH && (prizm.readLineSensor(irSensorPin3) == LOW)){
        exc.setMotorSpeed(3,1, -100);
        exc.setMotorSpeed(3,2, +140);
        exc.setMotorSpeed(2,1, +130);             
        exc.setMotorSpeed(2,2, -100);
      }else if(prizm.readLineSensor(irSensorPin2) == LOW && (prizm.readLineSensor(irSensorPin3) == LOW)){
        exc.setMotorSpeed(3,1, -130);
        exc.setMotorSpeed(3,2, +130);
        exc.setMotorSpeed(2,1, +130);             
        exc.setMotorSpeed(2,2, -130);
      }
    }
  }
}

void first_line(){          //처음 라인 맞추기
  while (1){
    if (prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == HIGH){
      stop();
      delay(1000);
    }else if(prizm.readLineSensor(irSensorPin4) == HIGH && prizm.readLineSensor(irSensorPin5) == LOW){
      exc.setMotorSpeed(3,1, 0);
      exc.setMotorSpeed(3,2, +50);
      exc.setMotorSpeed(2,1, 0);             
      exc.setMotorSpeed(2,2, 0);
    }else if(prizm.readLineSensor(irSensorPin4) == LOW && prizm.readLineSensor(irSensorPin5) == HIGH){
      exc.setMotorSpeed(3,1, -100);
      exc.setMotorSpeed(3,2, +100);
      exc.setMotorSpeed(2,1, +100);             
      exc.setMotorSpeed(2,2, -100);
    }else{
      while(1){
        if(prizm.readLineSensor(irSensorPin4) == LOW)
          move(100, 3);
        else
          break;
      }
    }
    if(prizm.readLineSensor(irSensorPin3) == HIGH){
      stop();
      delay(1000);
    }else{
      while(1){
        if(prizm.readLineSensor(irSensorPin3) == LOW)
          move(100, 2);
        else
          break;
      }
    }
    break;
  }
}
/*
void stay_r_turn(){
  wheel(0,0,30);
  delay(2250);
  while(1){
    if(prizm.readLineSensor(irSensorPin4) == HIGH){
      exe.setMotorSpeed(2,1, 125);
      exe.setMotorSpeed(2,2, 125);
      exe.setMotorSpeed(3,1, 125);
      exe.setMotorSpeed(3,2, 125);
      break;
    }
    else{
      wheel(0,0,25);      //검정선을 만날때 까지 더 천천히 회전
    }
  }
}
*/

void stay_r_turn(int n){      //n=1 : 90도 , n=2 : 180도    4번 ir센서 사용
  if(robotX == 0){
    robotX = 1;
  }else if(robotX == 1){
    robotX = 0;
  }
  for(int i=0; i<n; i++){
    turn_s(180,2); 
    delay(1400); 
    while(1){
      if(prizm.readLineSensor(irSensorPin4) == HIGH){
        break;
      }else{
        turn_s(120,2);
      }
    }
  }

}


void stay_r_turn5(int n){      //n=1 : 90도 , n=2 : 180도  5번 ir센서 사용
  if(robotX == 0){
    robotX = 1;
  }else if(robotX == 1){
    robotX = 0;
  }
  for(int i=0; i<n; i++){
    turn_s(180,2); 
    delay(1400); 
    while(1){
      if(prizm.readLineSensor(irSensorPin5) == HIGH){
        break;
      }else{
        turn_s(120,2);
      }
    }
  }
  while(1){
    if(prizm.readLineSensor(irSensorPin4) == HIGH){
      break;
    }else{
      turn_s(50,1);
    }
  }
}

void pickup(){      // object 들기
  exc.setMotorSpeed(3,1, 0);
  exc.setMotorSpeed(3,2, 0);
  exc.setMotorSpeed(2,1, -100);
  exc.setMotorSpeed(2,2, 0);
  delay(800);
  while(1){
    if(prizm.readLineSensor(irSensorPin5) == HIGH){
      move(80, 2);
      delay(1000);
      stop();
      prizm.setServoPosition(1,20);
      delay(1100);
      stop();
      prizm.setMotorSpeed(1, -70);      //모터 올리기
      delay(1000);
      prizm.setMotorSpeed(1, 0);
      stop();
      break;
    }else{
      exc.setMotorSpeed(3,1, 0);
      exc.setMotorSpeed(3,2, +60);
      exc.setMotorSpeed(2,1, 0);
      exc.setMotorSpeed(2,2, 0);
    }
  }
  while(1){
    if (prizm.readLineSensor(irSensorPin2) == HIGH){
      break;
    }else{
      if(robotX == 0 && robotY ==4){
        move(80, 1);
        delay(1150);
        break;
      }else{
        move(80, 1);
      }
    }
  }
}

void pickdown(){      // object 놓기
  exc.setMotorSpeed(3,1, 0);
  exc.setMotorSpeed(3,2, 0);
  exc.setMotorSpeed(2,1, -100);
  exc.setMotorSpeed(2,2, 0);
  delay(800);
  while(1){
    if(prizm.readLineSensor(irSensorPin5) == HIGH){
      move(80, 2);
      delay(1000);
      stop();
      prizm.setMotorSpeed(1, 70);      //모터 올리기
      delay(1000);
      prizm.setMotorSpeed(1, 0);
      stop();
      prizm.setServoPosition(1,170);
      delay(1000);
      stop();
      break;
    }else{
      exc.setMotorSpeed(3,1, 0);
      exc.setMotorSpeed(3,2, +60);
      exc.setMotorSpeed(2,1, 0);
      exc.setMotorSpeed(2,2, 0);
    }
  }
  while(1){
    if (prizm.readLineSensor(irSensorPin2) == HIGH){
      break;
    }else{
      if(robotX == 0 && robotY ==4){
        move(80, 1);
        delay(1150);
        stop();
        break;
      }else{
        move(80, 1);
      }
    }
  }
}

void turn_s(int speed, int n){          // 1: 왼쪽 회전  , 2: 오른쪽 회전
  if(n == 1){
    exc.setMotorSpeed(3,1, -speed);
    exc.setMotorSpeed(3,2, -speed);
    exc.setMotorSpeed(2,1, -speed);
    exc.setMotorSpeed(2,2, -speed);
  }
  else if(n == 2){
    exc.setMotorSpeed(3,1, +speed);
    exc.setMotorSpeed(3,2, +speed);
    exc.setMotorSpeed(2,1, +speed);
    exc.setMotorSpeed(2,2, +speed);
  }
}

void crose(int speed, int n){ // 좌측 아래 이동 
  if(n==1){                   //좌측아래
    exc.setMotorSpeed(3,1, -0);
    exc.setMotorSpeed(3,2, -speed);
    exc.setMotorSpeed(2,1, +0);
    exc.setMotorSpeed(2,2, +speed);
  }else if(n==2){             //우측 위
    exc.setMotorSpeed(3,1, 0);
    exc.setMotorSpeed(3,2, +speed);
    exc.setMotorSpeed(2,1, 0);
    exc.setMotorSpeed(2,2, -speed);
  }else if(n==3){             //좌측 위
    exc.setMotorSpeed(3,1, +speed);
    exc.setMotorSpeed(3,2, 0);
    exc.setMotorSpeed(2,1, -speed);
    exc.setMotorSpeed(2,2, 0);
  }else if(n==4){             // 우측 아래
    exc.setMotorSpeed(3,1, -speed);
    exc.setMotorSpeed(3,2, 0);
    exc.setMotorSpeed(2,1, +speed);
    exc.setMotorSpeed(2,2, 0);
  }
}

void move(int speed, int n){ // 좌측 아래 이동 
  if(n==1){                   //뒤로
    exc.setMotorSpeed(3,1, -speed);
    exc.setMotorSpeed(3,2, -speed);
    exc.setMotorSpeed(2,1, +speed);
    exc.setMotorSpeed(2,2, +speed);
  }else if(n==2){             //앞으로
    exc.setMotorSpeed(3,1, +speed);
    exc.setMotorSpeed(3,2, +speed);
    exc.setMotorSpeed(2,1, -speed);
    exc.setMotorSpeed(2,2, -speed);
  }else if(n==3){             //오른쪽
    exc.setMotorSpeed(3,1, -speed);
    exc.setMotorSpeed(3,2, +speed);
    exc.setMotorSpeed(2,1, +speed);
    exc.setMotorSpeed(2,2, -speed);
  }else if(n==4){             //왼쪽
    exc.setMotorSpeed(3,1, +speed);
    exc.setMotorSpeed(3,2, -speed);
    exc.setMotorSpeed(2,1, -speed);
    exc.setMotorSpeed(2,2, +speed);
  }
}

void stop() {  // Moter stop
  exc.setMotorSpeed(3,1, 0); //exc.setMotorPower(ID, port, power)// power -100 ~ 100;
  exc.setMotorSpeed(3,2, 0);
  exc.setMotorSpeed(2,1, 0);
  exc.setMotorSpeed(2,2, 0);
  delay(1000);
}

void Serialprint(){     //확인 코드
  Serial.print("YELLOW_BLOCK_X =");
  Serial.println(YELLOW_BLOCK_X);
  Serial.print("YELLOW_BLOCK_Y =");
  Serial.println(YELLOW_BLOCK_Y);

  Serial.print("GREEN_BLOCK_X =");
  Serial.println(GREEN_BLOCK_X);
  Serial.print("GREEN_BLOCK_Y =");
  Serial.println(GREEN_BLOCK_Y);
  Serial.print("GREEN_OBJECT_X =");
  Serial.println(GREEN_OBJECT_X);
  Serial.print("GREEN_OBJECT_Y =");
  Serial.println(GREEN_OBJECT_Y);
  
  Serial.print("BLUE_BLOCK_X =");
  Serial.println(BLUE_BLOCK_X);
  Serial.print("BLUE_BLOCK_Y =");
  Serial.println(BLUE_BLOCK_Y);
  Serial.print("BLUE_OBJECT_X =");
  Serial.println(BLUE_OBJECT_X);
  Serial.print("BLUE_OBJECT_Y =");
  Serial.println(BLUE_OBJECT_Y);
  
  Serial.print("RED_BLOCK_X =");
  Serial.println(RED_BLOCK_X);
  Serial.print("RED_BLOCK_Y =");
  Serial.println(RED_BLOCK_Y);
  Serial.print("RED_OBJECT_X =");
  Serial.println(RED_OBJECT_X);
  Serial.print("RED_OBJECT_Y =");
  Serial.println(RED_OBJECT_Y);

  Serial.print("robotX =");
  Serial.println(robotX);
  Serial.print("robotY =");
  Serial.println(robotY);
}

void loop(){
}