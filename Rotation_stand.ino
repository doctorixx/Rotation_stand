#include <GyverStepper.h>
/*
Прошивка и схема разработаты Doctor(Изумруд Тв,Windows-up)
Приятного использования

*/
#define REVERSE_PIN 10 // Светодиод реверса
#define ALLOW_PIN 11 // Светодиод вкл/выкл
#define POWER_BUTTON 7 // Кнопка вкл/выкл
#define REVERSE_BUTTON 8 // Кнопка реверса
#define SPEED_CONTROL A0 // Потенциометр

#define MOTOR_IN1 5 // Пин IN1 на драйвере мотора
#define MOTOR_IN2 4 // Пин IN2 на драйвере мотора
#define MOTOR_IN3 3 // Пин IN3 на драйвере мотора
#define MOTOR_IN4 2 // Пин I41 на драйвере мотора


bool is_reverse;
bool allow = true;
uint32_t tmr;

GStepper<STEPPER4WIRE> stepper(2048, MOTOR_IN1, MOTOR_IN3, MOTOR_IN2, MOTOR_IN4);

void setup() {
  stepper.setRunMode(KEEP_SPEED); 
  stepper.setSpeedDeg(10);        

  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  pinMode(ALLOW_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);

  digitalWrite(11, ALLOW_PIN);
}

void loop() {
  stepper.tick();

  
  if (millis() - tmr > 15) {
    tmr = millis();

    stepper.setSpeed(analogRead(SPEED_CONTROL) / 2);
  }

  if (digitalRead(REVERSE_BUTTON) == LOW) {
    is_reverse = ! is_reverse;
    stepper.reverse(is_reverse);
    delay(500);
    digitalWrite(REVERSE_PIN, is_reverse);
  }


  if (digitalRead(POWER_BUTTON) == LOW) {
    allow = !allow;
    digitalWrite(ALLOW_PIN, allow);
    delay(500);
  }

  if (allow == LOW) {
    stepper.setSpeed(0);
  }


}
