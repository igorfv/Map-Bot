#include <Servo.h>
#include <Ultrasonic.h>

int E1 = 6;
int M1 = 7;
int E2 = 5;                         
int M2 = 4;

long bt = 0; //Ultimo botao precionado

Servo headServo;
Servo neckServo;

#define headServoCenter 0
#define neckServoCenter 90
#define neckServoLeft 120
#define neckServoRight 60

#define mindist 20


#define TRIGGER_PIN 12
#define ECHO_PIN    13

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

boolean goon = true;
boolean doublechecked = true;

char lookto = 'c';
char lookingto = 'c';
int checkdist = 0;
char shouldgo = 'c';

void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  headServo.attach(10);
  neckServo.attach(9);
  
  headServo.write(headServoCenter);
  neckServo.write(neckServoCenter);
}

void loop()
{
  
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  if(!goon)
  {
    switch (lookingto) {
      case 'l':
        //Left distance
        checkdist = cmMsec;
        shouldgo = 'l';
        break;
      case 'r':
        //Right Distance
        if(cmMsec > checkdist)
        {
          checkdist = cmMsec;
          shouldgo = 'r';
        }
        break;
      default: 
        // Center distance (double checks)
        if(cmMsec > checkdist)
        {
          checkdist = cmMsec;
          shouldgo = 'c';
        }
        
        if(checkdist < mindist)
        {
          shouldgo = 'b';
        }
        
        thebestway();
        
        break;
    }
  }
  
  
  if(cmMsec < mindist && goon)
  {
    goon = false;
    doublechecked = false;
    lookto = 'l';
  }
  
  
  if(goon)
  {
    andarFrente(0,0);
  }
  else
  {    
    parar(0,0);

    switch (lookto) {
      case 'l':
        //Look left and check
        neckServo.write(neckServoLeft);
        lookto = 'r';
        lookingto = 'l';
        break;
      case 'r':
        //look right
        neckServo.write(neckServoRight);
        lookto = 'c';
        lookingto = 'r';
        break;
      default: 
        // Go back to center
        neckServo.write(neckServoCenter);
        lookingto = 'c';
    }
    
    delay(1000);
  }
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

void thebestway()
{
  switch (shouldgo) {
    case 'l':
      andarEsquerda(0,0);
      break;
    case 'r':
      andarDireita(0,0);
      break;
    case 'b':
      andarRe(0,0);
      delay(1000);
      andarDireita(0,0);
      delay(1500);
      break;
    default:
      break;
  }
  
  delay(500);
  parar(0,0);
  goon = true;
}
