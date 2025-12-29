#include <Arduino.h>

#define TRIG_L 2
#define ECHO_L 3
#define TRIG_C 4
#define ECHO_C 5
#define TRIG_R 6
#define ECHO_R 7
#define MOTOR_L 11
#define MOTOR_R 12
#define UMBRAL 100

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_L, OUTPUT); pinMode(ECHO_L, INPUT);
  pinMode(TRIG_C, OUTPUT); pinMode(ECHO_C, INPUT);
  pinMode(TRIG_R, OUTPUT); pinMode(ECHO_R, INPUT);
  pinMode(MOTOR_L, OUTPUT);
  pinMode(MOTOR_R, OUTPUT);
}

void loop() {
  int distL = leerDistancia(TRIG_L, ECHO_L);
  delay(50);
  int distC = leerDistancia(TRIG_C, ECHO_C);
  delay(50);
  int distR = leerDistancia(TRIG_R, ECHO_R);
  delay(50);

  Serial.print("L: "); Serial.print(distL); Serial.print(" cm | ");
  Serial.print("C: "); Serial.print(distC); Serial.print(" cm | ");
  Serial.print("R: "); Serial.print(distR); Serial.println(" cm");

  int vibL = 0, vibR = 0;
  if (distC > 0 && distC < UMBRAL) {
    vibL = map(distC, UMBRAL, 0, 0, 255);
    vibR = map(distC, UMBRAL, 0, 0, 255);
    
  } else {
    if (distL > 0 && distL < UMBRAL) {
      vibL = map(distL, UMBRAL, 0, 0, 255);
      
    }
    if (distR > 0 && distR < UMBRAL) {
      vibR = map(distR, UMBRAL, 0, 0, 255);
      
    }
  }

  analogWrite(MOTOR_L, vibL);
  analogWrite(MOTOR_R, vibR);
  delay(60);
}

int leerDistancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 25000);
  if (duration == 0) {
    Serial.print("No eco en pin Echo "); Serial.println(echo); 
    return 999;
  }
  int distance = duration / 58.2;
  return distance;
}