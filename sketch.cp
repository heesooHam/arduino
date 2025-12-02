// 서보 모터를 사용하기 위한 라이브러리 include
#include <Servo.h> 

/** 손 거리 인식하는 초음파 센서 설정**/
#define TRIG_HAND 1 // 초음파 센서 보내는 핀
#define ECHO_HAND 2 // 받는 핀

/** 쓰레기 용량 확인하는 초음하 센서 설정**/
#define TRIG_TRASH 3 // 초음파 센서 보내는 핀
#define ECHO_TRASH 4 // 받는 핀

/** LED 3개 핀 설정 **/
#define LED_GREEN 5 // 초록 : 용량 넉넉
#define LED_YELLOW 6 // 노랑색 : 용량 조금 차있음
#define LED_RED 7 // 빨간색 : 용량 거의 없음

/** 서보 모터 핀 **/
#define MOTOR 8 
#define OPEN_ANGLE 120 // 열리는 각도
#define CLOSE_ANGLE 0 // 닫히는 각도

Servo servo;

enum COLOR {GREEN, YELLOW, RED};

void setup() 
{
  // 손 거리 인식
  pinMode(TRIG_HAND, OUTPUT);
  pinMode(ECHO_HAND, INPUT);

  // 쓰레기 용량 확인
  pinMode(TRIG_TRASH, OUTPUT);
  pinMode(ECHO_TRASH, INPUT);

  // LED 3개
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // 서보 모터
  servo.attach(MOTOR);
}

void loop()
{
  long detection_duration_hand = 10; // 인식 거리 (단위 : cm)
  long detection_duration_trash = 10; // 인식 거리 (cm)

  // 손 거리 측정
  long to_cm_hand = measureHandDistance();

  // 손 위치가 가까워지면 서보 모터를 움직임
  if (to_cm_hand < detection_duration_hand) {
    /*
      서보 모터를 움직임 controlLid()
    */
  }

  // 쓰레기 용량 측정
  long to_cm_trash = measureTrashDistance();

  // 쓰레기가 일정 용량 이상 차면 LED 불빛이 변함
  if (to_cm_trash < detection_duration_trash) {
    /*
      LED 색깔 변환 changeLEDColor()
    */
  }
}

// 손 거리 측정 함수
long measureHandDistance() {
  long duration, to_cm;
  
  digitalWrite(TRIG_HAND, HIGH);
  delay(10);
  digitalWrite(TRIG_HAND, LOW);
  
  duration = pulseIn(ECHO_HAND, HIGH);
  to_cm = duration * 17 / 1000;
  
  return to_cm;
}

// 쓰레기 용량 측정 함수
long measureTrashDistance() {
  long duration, to_cm;
  
  digitalWrite(TRIG_TRASH, HIGH);
  delay(10);
  digitalWrite(TRIG_TRASH, LOW);
  
  duration = pulseIn(ECHO_TRASH, HIGH);
  to_cm = duration * 17 / 1000;
  
  return to_cm;
}

