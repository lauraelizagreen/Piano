/* 
 * Project Piano_photodiode
 * Author: Laura Green
 * Date: 1/4/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include <neopixel.h>





SYSTEM_MODE(SEMI_AUTOMATIC);
//SYSTEM_MODE(AUTOMATIC);//for room control


SYSTEM_THREAD(ENABLED);
const int BULB=2;
const int PHOTODIODEONE=A0;
const int PHOTODIODETWO=A1;
const int PHOTODIODETHREE=A2;
const int PHOTODIODEFOUR=A5;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN= D16;//PWM
const int NOTELEVEL=50;//how much light photodiode has to have to trigger hue light
const int NOTEDELAY=2000;//will need to be varied, so maybe later not constant? how long light stays on
const int DURATION=1000;//also may need to be varied-how long note plays, same as delay, so could be same variable
const int PIXELCOUNT=1;//use one neopixel to check hue light when not at FUSE
const int CNOTE=131;//freq for C notes could be h file later? or use pitch.h
const int DNOTE=147;//freq for D
const int ENOTE=165;//freq for E
const int FNOTE=175;//freq for F
const int GNOTE=196;//freq for G
const int ANOTE=220;//freq for A
const int BNOTE=247;//freq for B
const int HICNOTE=262;//freq for high C

const int HICBUTTON=D17;
const int BBUTTON=D2;
const int ABUTTON=D3;
const int GBUTTON=D4;
const int FBUTTON=D5;
const int EBUTTON=D6;
const int DBUTTON=D7;
const int CBUTTON=D10;

int lightLevelOne;//photodiode 1
int lightLevelTwo;
int lightLevelThree;
int lightLevelFour;
int color;
unsigned int timerStart, currentTime;

int cBState;
bool onOff;

Servo cServo;//create object ...servo class built into photon library
IoTTimer btwNoteTimer;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Button hicButton(HICBUTTON),bButton(BBUTTON),aButton(ABUTTON),gButton(GBUTTON),fButton(FBUTTON),eButton(EBUTTON),dButton(DBUTTON),cButton(CBUTTON);
IoTTimer noteTimer;


void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,15000);

  /*
  WiFi.on();  //comment out this section when not at FUSE
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }  
  Serial.printf("\n\n");
  */

  pinMode(PHOTODIODEONE,INPUT);//photodiode 1
  pinMode(PHOTODIODETWO,INPUT);//photodiode 2
  pinMode(PHOTODIODETHREE,INPUT);//photodiode 3
  pinMode(PHOTODIODEFOUR,INPUT);//photodiode 4

  pinMode(BUZZPIN,OUTPUT);//buzzer
  cServo.attach(SERVPIN);//motor for C key (or all keys?)
  onOff=false;

pixel.begin();//to initialize neopixel for home tests
pixel.setBrightness (20); 
pixel.show();
btwNoteTimer.startTimer(100);

//tone(BUZZPIN,FNOTE);


  
}


void loop() {
  //setHue(BULB,false,50,255); //light off
  lightLevelOne=analogRead(PHOTODIODEONE); //read diodes through hole of scroll
  lightLevelTwo=analogRead(PHOTODIODETWO);
  lightLevelThree=analogRead(PHOTODIODETHREE);
  lightLevelFour=analogRead(PHOTODIODEFOUR);
  Serial.printf("Light level one is %i\n",lightLevelOne); //what light level is usual?
  Serial.printf("Light level two is %i\n",lightLevelTwo);
  Serial.printf("Light level three is %i\n",lightLevelThree);
  Serial.printf("Light level four is %i\n",lightLevelFour);
  /*
  if(lightLevelOne>NOTELEVEL){
    //setHue(BULB,true,HueViolet,50,255);
    //cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take?
    //noteTimer.isTimerReady();
    tone(BUZZPIN,CNOTE);//timing? just as long as exposed to light?
    //delay(DURATION+1000);
  }
  if(lightLevelTwo>NOTELEVEL) {
    tone(BUZZPIN,DNOTE);
  }
  if(lightLevelThree>NOTELEVEL) {
    tone(BUZZPIN,ENOTE);
  }
  */
  if(lightLevelFour>NOTELEVEL) {
    tone(BUZZPIN,FNOTE);
  }
if(hicButton.isPressed()) {
tone(BUZZPIN,HICNOTE);//stays on while pressed
}
if(bButton.isPressed())  {
  tone(BUZZPIN,BNOTE);
}
if(aButton.isPressed())  {
  tone(BUZZPIN,ANOTE);
}
if(gButton.isPressed())  {
  tone(BUZZPIN,GNOTE);
}
if(fButton.isPressed())  {
  tone(BUZZPIN,FNOTE);
}
if(eButton.isPressed())  {
  tone(BUZZPIN,ENOTE);
}
if(dButton.isPressed())  {
  tone(BUZZPIN,DNOTE);
}
if(cButton.isPressed())  {
  tone(BUZZPIN,CNOTE);
}

//noteTimer.isTimerReady() 
  noTone(BUZZPIN);


 
}

  //btwNoteTimer.startTimer(NOTEDELAY); //how long light stays on/in between notes if looped
    
  //delay(1000);
   //setHue(BULB,false,50,255); //how to turn off btw and timing (set timer with variable as target?  )
    //delay(5000);
 

  

