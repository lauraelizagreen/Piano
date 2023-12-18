/* 
 * Project Piano Test Code
 * Author: Laura Green  
 * Date: 12/15/23
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
//#include "pitches.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(MANUAL);
const int BULB=2;
const int PHOTODIODE=A1;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN=  ;//PWM?
const int NOTELEVEL=100;//how much light photodiode has to have to trigger hue light
const int NOTEDELAY=1000;//will need to be varied, so maybe later not constant? how long light stays on
const int DURATION=1000;//also may need to be varied-how long note plays, same as delay, so could be same variable
const int CNOTE=33;//frequency for c from pitches.h or make my own h file
int lightLevelC;
int color;
unsigned int cNote;//frequency for C
unsigned int timerStart, currentTime;
Servo cServo;//create object ...servo class built into photon library
IoTTimer timer;

//SYSTEM_THREAD(ENABLED);

//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,15000);

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }  
  Serial.printf("\n\n");

  pinMode(PHOTODIODE,INPUT);//photodiode
  pinMode(BUZZPIN,OUTPUT);//buzzer
  cServo.attach(SERVPIN);//motor for C key

  
 
}



// loop() runs over and over again, as quickly as it can execute.
void loop() {
  setHue(BULB,false,50,255); light off
  lightLevelC=analogRead(PHOTODIODE); //read light through hole of scroll
  Serial.printf("Light level is %i\n",//lightLevelC); what light level is usual?
  
  if(lightLevelC>NOTELEVEL){
    setHue(BULB,true,HueViolet,50,255);
    cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take?
    tone(BUZZPIN,CNOTE,DURATION);
  }
  timer.startTimer(NOTEDELAY); //how long light stays on
    if(timer.isTimerReady()){
  //delay(1000);
   setHue(BULB,false,50,255); //how to turn off btw and timing (set timer with variable as target?  )
    //delay(5000);
  }

     
}

