#include <Servo.h>
#include <Ultrasonic.h>

int E1 = 6;
int M1 = 7;
int E2 = 5;                         
int M2 = 4;

long bt = 0; //Ultimo botao precionado

Servo headServo;
Servo neckServo;

#define headServoCenter 12
#define neckServoCenter 90


#define TRIGGER_PIN 12
#define ECHO_PIN    13

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);


void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  //Serial.begin(9600);
  
  headServo.attach(10);
  neckServo.attach(9);
  
  headServo.write(headServoCenter);
  neckServo.write(neckServoCenter);
}

void loop()
{ 
//  if (Serial.available() > 0) {
//    
//    int valor = Serial.parseInt();
//    Serial.println(valor, DEC);
//  }
  
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  andarFrente(0,0);
}

void andarFrente(int speedA, int speedB)
{
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);
  analogWrite(E1, 1023);   //PWM Speed Control
  analogWrite(E2, 1023);   //PWM Speed Control
}

void andarRe(int speedA, int speedB)
{
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 1023);   //PWM Speed Control
  analogWrite(E2, 1023);   //PWM Speed Control
}

void andarEsquerda(int speedA, int speedB)
{
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  analogWrite(E1, 1023);   //PWM Speed Control
  analogWrite(E2, 1023);   //PWM Speed Control
}

void andarDireita(int speedA, int speedB)
{
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 1023);   //PWM Speed Control
  analogWrite(E2, 1023);   //PWM Speed Control
}

void parar(int speedA, int speedB)
{
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
}
