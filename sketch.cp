// 서보 모터를 사용하기 위한 라이브러리 include
#include <Servo.h> 

/** 손 거리 인식하는 초음파 센서 설정**/
#define TRIG_HAND 3 // 초음파 센서 보내는 핀
#define ECHO_HAND 4 // 받는 핀

/** 쓰레기 용량 확인하는 초음하 센서 설정**/
#define TRIG_TRASH 5 // 초음파 센서 보내는 핀
#define ECHO_TRASH 6 // 받는 핀

/** LED 3개 핀 설정 **/
#define LED_GREEN 8 // 초록 : 용량 넉넉
#define LED_YELLOW 9 // 노랑색 : 용량 조금 차있음
#define LED_RED 10 // 빨간색 : 용량 거의 없음

/** 서보 모터 핀 **/
#define MOTOR 11
#define OPEN_ANGLE 90 // 열리는 각도
#define CLOSE_ANGLE 0 // 닫히는 각도

Servo servo;

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
  servo.write(CLOSE_ANGLE); // 초기 상태는 닫힌 상태
}

void loop()
{
  long detection_duration_hand = 25; // 인식 거리 (단위 : cm)
  long detection_duration_trash = 10; // 인식 거리 (cm)

  // 손 거리 측정
  long to_cm_hand = measureHandDistance();

  // 손 위치가 가까워지면 서보 모터를 움직임
  if (to_cm_hand < detection_duration_hand) {
    controlLid();
  }

  // 쓰레기 용량 측정
  long to_cm_trash = measureTrashDistance();

  // 쓰레기가 일정 용량 이상 차면 LED 불빛이 변함
  changeLEDColor(to_cm_trash);
  
  delay(100); // 센서 안정화를 위한 짧은 딜레이
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

// 서보 모터 제어 함수 (뚜껑 열고 닫기)
void controlLid() {
  servo.write(OPEN_ANGLE);  // 뚜껑 열기
  delay(3000);               // 3초 대기 (쓰레기 버릴 시간)
  servo.write(CLOSE_ANGLE);  // 뚜껑 닫기
  delay(1000);               // 1초 대기 (완전히 닫힐 때까지)
}

// LED 색깔 변경 함수 (거리에 따라)
void changeLEDColor(long distance) {
  // 모든 LED 끄기
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  
  // 거리에 따라 LED 켜기
  // 거리가 가까울수록 (쓰레기가 많을수록) 빨간색
  if (distance < 5) {
    // 쓰레기가 거의 가득 참 (5cm 미만)
    digitalWrite(LED_RED, HIGH);
  } else if (distance < 15) {
    // 쓰레기가 반 정도 참 (5~15cm)
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    // 쓰레기가 별로 안 참 (15cm 이상)
    digitalWrite(LED_GREEN, HIGH);
  }
