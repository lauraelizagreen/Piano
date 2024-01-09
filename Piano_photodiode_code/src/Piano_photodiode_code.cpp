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
//SYSTEM_MODE(AUTOMATIC);//enable for room control web connection


SYSTEM_THREAD(ENABLED);
//declare component pins
const int WEMO1=1;
const int BULB=2;//hue bulb at my desk
const int PHOTODIODEONE=A0;
const int PHOTODIODETWO=A1;
const int PHOTODIODETHREE=A2;
const int PHOTODIODEFOUR=A5;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN= D16;//PWM
//thresholds and delay times
const int NOTELEVEL=50;//how much light photodiode has to have to trigger hue light
const int NOTEDELAY=2000;//will need to be varied, so maybe later not constant? how long light stays on
const int DURATION=1000;//also may need to be varied-how long note plays, same as delay, so could be same variable
const int PIXELCOUNT=1;//use one neopixel to check hue light when not at FUSE and neopixel for on/off indicator light
//declare all note frequencies
const int CNOTE=131;//freq for C notes could be h file later? or use pitch.h
const int DNOTE=147;//freq for D
const int ENOTE=165;//freq for E
const int FNOTE=175;//freq for F
const int GNOTE=196;//freq for G
const int ANOTE=220;//freq for A
const int BNOTE=247;//freq for B
const int HICNOTE=262;//freq for high C
//declare all button pins
const int HICBUTTON=D17;
const int BBUTTON=D2;
const int ABUTTON=D3;
const int GBUTTON=D4;
const int FBUTTON=D5;
const int EBUTTON=D6;
const int DBUTTON=D7;
const int CBUTTON=D10;
const int ENCSWITCH=D19;
const int GREENLED=D18;
//const int REDLED=D16;//not enough pins?

int lightLevelOne;//photodiode 1-4
int lightLevelTwo;
int lightLevelThree;
int lightLevelFour;
int color;//hue light color
unsigned int timerStart, currentTime;//unsigned saves memory space

int cBState;//not necessary with h file ?
bool onOff;
//create all objects: servo, timers, neopixel, buttons...
Servo cServo;//create object ...servo class built into photon library
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Button hicButton(HICBUTTON);
Button bButton(BBUTTON);
Button aButton(ABUTTON);
Button gButton(GBUTTON);
Button fButton(FBUTTON);
Button eButton(EBUTTON);
Button dButton(DBUTTON);
Button cButton(CBUTTON);
Button encSwitch(ENCSWITCH,FALSE);
IoTTimer noteTimer;
IoTTimer btwNoteTimer;


void setup() {
  Serial.begin(9600); //serial port
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

  pinMode(GREENLED, OUTPUT);//light on encoder switch

  pinMode(BUZZPIN,OUTPUT);//buzzer
  cServo.attach(SERVPIN);//motor for C key (or all keys?)
  onOff=true;//for encoder switch-start true since on is off (ground completes circuit)

pixel.begin();//to initialize neopixel for home tests
pixel.setBrightness (20); 
pixel.show();
btwNoteTimer.startTimer(100);

//tone(BUZZPIN,FNOTE);


  
}


void loop() {
  /////MANUAL MODE AND TO START AUTO
  if(encSwitch.isClicked()) {//using button heterofile with bool function isClicked
    onOff=!onOff;//assigns onoff opposite of existing (toggles)

  }
  digitalWrite(GREENLED,onOff);//low turns on (connects to ground to complete circuit)
  wemoWrite(WEMO1,onOff);//still add turning switch red/green?

  
  //////FOR AUTO MODE WITH SCROLL
  //setHue(BULB,false,50,255); //light off
  lightLevelOne=analogRead(PHOTODIODEONE); //read diodes through hole of scroll
  lightLevelTwo=analogRead(PHOTODIODETWO);
  lightLevelThree=analogRead(PHOTODIODETHREE);
  lightLevelFour=analogRead(PHOTODIODEFOUR);
  Serial.printf("Light level one is %i\n",lightLevelOne); //what light level is usual? use this to de-bug etc
  Serial.printf("Light level two is %i\n",lightLevelTwo);
  Serial.printf("Light level three is %i\n",lightLevelThree);
  Serial.printf("Light level four is %i\n",lightLevelFour);
  /*
  if(lightLevelOne>NOTELEVEL){
    //setHue(BULB,true,HueViolet,50,255);
    //cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take? maybe set as sin wave for piano key movement
    //noteTimer.isTimerReady();
    tone(BUZZPIN,CNOTE);//timing? just as long as exposed to light?
    //delay(DURATION+1000);//may not need
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
  /////FOR MANUAL MODE PRESSING PIANO KEYS
if(hicButton.isPressed()) {
  tone(BUZZPIN,HICNOTE);//stays on while pressed
  }
if(bButton.isPressed())  {//with pull-down resistor 10kohms >2vreads high  <0.8 reads low  avoid in-btw
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
 

  

