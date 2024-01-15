/* 
 * Project test_piano_servo
 * Author: Laura Green
 * Date: January 13, 2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "math.h"
//#include "IoTClassroom_CNM.h"
// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

const int PHOTODIODEONE=A0;
const int SERVPIN=A2;//D15;//has to be PWM 
const int BUZZPIN= D16;//PWM
const int CNOTE=131;//freq for C 
int lightLevelOne;
float motor;
float t;
float tmotor;
float startPos;

Servo cServo;


//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); //serial port
  waitFor(Serial.isConnected,15000);

pinMode(PHOTODIODEONE,INPUT);//photodiode 1
pinMode(BUZZPIN,OUTPUT);//buzzer
cServo.attach(SERVPIN);

t=millis()/1000.0;
//motor=180.0; //then sin wave added to wherever in cycle left off? .00 bc float?
startPos=0;
}
void loop(){


/*
  lightLevelOne=analogRead(PHOTODIODEONE);
  Serial.printf("Light level one is %i\n",lightLevelOne);

  if(lightLevelOne>100) {
    //t=t+(millis()/ 1000.0); //to get current time converted to seconds use decimal since it's a float
    //motor=((180/2.0)* sin(2 * M_PI * .1 * t)+(startPos/2.0));//A(amplitude=height of wave from midpoint) *sin(2pi * v(freq) * t(current time in sec) + B(offset from 0))
    motor=((180/2.0)* sin(2 * M_PI * .1 * t)+90);//voltage stays around 1.6, shouldn't it change as it oscillates?
    //Serial.printf("motor is %f\n",motor,"start position is %f\n",startPos);
    Serial.printf("motor is %f\n",motor,"t is %f\n",t);
    cServo.write(motor);
    //delay(1000);
    
   
    
    
    //noteTimer.isTimerReady();
    tone(BUZZPIN,CNOTE);
  }
  else{
    noTone(BUZZPIN);
  }
//t=t;
Serial.printf("end motor is %f\n",motor,"t is %f\n",t);
delay(1000);

  */
  cServo.write(180);// 30=.03 A,60=.09,90=.14;180=.3A why so low? is this the problem?
}

  

