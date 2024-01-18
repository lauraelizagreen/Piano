/* 
 * Project Piano_photodiode
 * Author: Laura Green
 * Date: 1/4/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "math.h"
#include "IoTClassroom_CNM.h"
#include "Adafruit_GFX.h"//order matters
#include "Adafruit_SSD1306.h"
//#include <neopixel.h>


SYSTEM_MODE(MANUAL);//enable for room control web connection
//SYSTEM_MODE(SEMI_AUTOMATIC);


//SYSTEM_THREAD(ENABLED);
//declare component pins
const int OLED_RESET=-1;
const int NUMFLAKES=10;//like const (datatype=int?) NUMFLAKES=10; what is this constant?
const int XPOS=0; 
const int YPOS=1;
const int DELTAY=2;
const int WEMOLIGHT=5;//spotlight on my desk
const int WEMOFAN=4;//fan WEMO4 (across room) for now
const int BULB=2;//hue bulb at my desk
const int PHOTODIODEONE=A0;
const int PHOTODIODETWO=A1;
const int PHOTODIODETHREE=A2;
const int PHOTODIODEFOUR=A5;
const int SERVPIN=D15;//has to be PWM
const int BUZZPIN= D16;//PWM

const int NOTELEVEL=800;//how much light photodiode has to have to trigger hue light
/*DONT NEED THESE FOR NOW
//thresholds and delay times
const int NOTEDELAY=2000;//will need to be varied, so maybe later not constant? how long light stays on
const int DURATION=1000;//also may need to be varied-how long note plays, same as delay, so could be same variable
const int PIXELCOUNT=1;//use one neopixel to check hue light when not at FUSE and neopixel for on/off indicator light
*/
//declare all note frequencies: notes could be h file later? or use pitch.h
const int CNOTE=131;//freq for C 
const int DNOTE=147;//freq for D
const int ENOTE=165;//freq for E
const int FNOTE=175;//freq for F
const int GNOTE=196;//freq for G
const int ANOTE=220;//freq for A
const int BNOTE=247;//freq for B
const int HICNOTE=262;//freq for high C
//declare all button pins
const int HICBUTTON=D17;
const int BBUTTON=D2;//D15
const int ABUTTON=D3;
const int GBUTTON=D4;
const int FBUTTON=D5;
const int EBUTTON=D6;
const int DBUTTON=D7;
const int CBUTTON=D10;
const int ENCSWITCH=D19;
const int GREENLED=D18;//light on encoder
//const int REDLED=D16;//not enough pins?


int lightLevelOne;//photodiode 1-4
int lightLevelTwo;
int lightLevelThree;
int lightLevelFour;
int hueColor;//hue light color
int playNote;
unsigned int lastSecond, currentTime;//unsigned saves memory space only positive --undefined starts at )?
float motor;
float t;

//int cBState;//not necessary with h file ?
bool onOff;

//create all objects: servo, timers, neopixel, buttons...
Adafruit_SSD1306 display(OLED_RESET);
Servo cServo;//create object ...servo class built into photon library
//Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);///SPI1 is D2
Button hicButton(HICBUTTON);
Button bButton(BBUTTON);  
Button aButton(ABUTTON);
Button gButton(GBUTTON);
Button fButton(FBUTTON);
Button eButton(EBUTTON);
Button dButton(DBUTTON);
Button cButton(CBUTTON);
Button encSwitch(ENCSWITCH);//false for internal pull-down (not pull-up)
IoTTimer chimeTimer;
//IoTTimer btwNoteTimer;


void setup() {
  Serial.begin(9600); //serial port
  waitFor(Serial.isConnected,10000);

  ///*
  WiFi.on();  //comment out this section when not at FUSE
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }  
  Serial.printf("\n\n");
  //*/
//OLED initialization
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with 12C address----not sure I understand this....??
void setRotation(uint8_t rotation);//how to use this to flip?
display.clearDisplay();   // clears the screen and buffer
display.display();
  //pinMode(BBUTTON,INPUT);//to test if still voltage at pin D2
  

  pinMode(PHOTODIODEONE,INPUT);//photodiode 1
  pinMode(PHOTODIODETWO,INPUT);//photodiode 2
  pinMode(PHOTODIODETHREE,INPUT);//photodiode 3
  pinMode(PHOTODIODEFOUR,INPUT);//photodiode 4

  pinMode(GREENLED, OUTPUT);//light on encoder switch

  pinMode(BUZZPIN,OUTPUT);//buzzer
  cServo.attach(SERVPIN);//motor for C key (or all keys?)
  onOff=true;//for encoder switch-start true since on is off (ground completes circuit)
/*
pixel.begin();//to initialize neopixel for home tests
pixel.setBrightness (20); 
pixel.show();
//btwNoteTimer.startTimer(100);
*/
 
//tone(BUZZPIN,FNOTE);//just to test buzzer
digitalWrite(GREENLED,onOff);//not sure if I need this
wemoWrite(WEMOLIGHT,FALSE);
wemoWrite(WEMOFAN,FALSE);
playNote=0;




  
}


void loop() {
  /////MANUAL MODE AND TO START AUTO
  if(encSwitch.isClicked()) {//using button heterofile with bool function isClicked
    onOff=!onOff;//assigns onoff opposite of existing (toggles)

  }
  digitalWrite(GREENLED,onOff);//low turns on (connects to ground to complete circuit)

  //still add turning switch red/green? 
//Serial.printf("onOff=%i\n",onOff);//un-comment to check

//////FOR AUTO MODE WITH SCROLL
if(onOff==TRUE){
  
  playNote=0;

  //setHue(BULB,false); //light off
  wemoWrite(WEMOLIGHT,TRUE);//spotlight on
   display.clearDisplay();
  display.setTextSize(2);//
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  //display.printf("%c\n",threeBlindMice[0]); //song lyrics here "three blind mice"? make into array and loop through with each note
  display.printf("AUTOMATIC");
  //display.startscrollright(0x00, 0x0F);
  display.display();
//FOR FAN AND CHIMES EVERY 30 SECONDS
///*
chimeTimer.startTimer(10000);
if(chimeTimer.isTimerReady()) {
  wemoWrite(WEMOFAN,TRUE);
}

   chimeTimer.startTimer(3000);
   if(chimeTimer.isTimerReady()) {
    wemoWrite(WEMOFAN,FALSE);
   }
   /*
  if((currentTime-lastSecond)>30000) {//isn't lastSecond undefined at this point???  or is an undefined variable set at 0? (would 0 be same as millis?)
      wemoWrite(WEMOFAN,FALSE);
      lastSecond=0;
 }
*/
  
  //cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take? maybe set as sin wave for piano key movement
    t=millis()/1000.0; //to get current time
    motor=(180/2)* sin(2 * M_PI * .1 * t)+(180/2);
    cServo.write(motor);
   
  lightLevelOne=analogRead(PHOTODIODEONE); //read diodes through hole of scroll
  lightLevelTwo=analogRead(PHOTODIODETWO);
  lightLevelThree=analogRead(PHOTODIODETHREE);
  lightLevelFour=analogRead(PHOTODIODEFOUR);
  ///*
  Serial.printf("Light level one is %i\n",lightLevelOne); //what light level is usual? use this to de-bug etc
  Serial.printf("Light level two is %i\n",lightLevelTwo);
  Serial.printf("Light level three is %i\n",lightLevelThree);
  Serial.printf("Light level four is %i\n",lightLevelFour);
  //*/

  ///*
  //1 only = C yellow
  if((lightLevelOne>NOTELEVEL) && (lightLevelTwo<NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour<NOTELEVEL)){
      hueColor=HueYellow;
      playNote=CNOTE;
  }
  
  //2 only=D indigo
  if((lightLevelOne<NOTELEVEL) && (lightLevelTwo>NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour<NOTELEVEL)) {
    hueColor=HueIndigo;
    playNote=DNOTE;
  }
  //3 only=E orange
  if((lightLevelOne<NOTELEVEL) && (lightLevelTwo<NOTELEVEL)&&(lightLevelThree>NOTELEVEL)&&(lightLevelFour<NOTELEVEL)) {
    hueColor=HueOrange;
    playNote=ENOTE;
  }
  //4 only=F green
  if((lightLevelOne<NOTELEVEL) && (lightLevelTwo<NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour>NOTELEVEL)) {
    hueColor=HueGreen;
    playNote=FNOTE;
  }
  //1 and 2=G violet
  if((lightLevelOne>NOTELEVEL) && (lightLevelTwo>NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour<NOTELEVEL)){
  hueColor=HueViolet;
  playNote=GNOTE;
}
//1 and 3=A red
if((lightLevelOne>NOTELEVEL) && (lightLevelTwo<NOTELEVEL)&&(lightLevelThree>NOTELEVEL)&&(lightLevelFour<NOTELEVEL)){
  hueColor=HueRed;
    playNote=ANOTE;
}
//1 and 4 =B Blue
if((lightLevelOne>NOTELEVEL) && (lightLevelTwo<NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour>NOTELEVEL)){
  hueColor=HueBlue;
    playNote=BNOTE;
}
//2 and 4=Hi C yellow
if((lightLevelOne<NOTELEVEL) && (lightLevelTwo>NOTELEVEL)&&(lightLevelThree<NOTELEVEL)&&(lightLevelFour>NOTELEVEL)) {
   hueColor=HueYellow;
    playNote=HICNOTE;
}
//*/

/////TRY SIMPLER
/*
if(lightLevelOne>NOTELEVEL) {
  hueColor=HueYellow;
  playNote=CNOTE;
}
*/
if(playNote!=0) {
tone(BUZZPIN,playNote); //or comment out for color only play :)
setHue(BULB,true,hueColor,50,255);//comment out if auto mode too slow
}
else {
  noTone(BUZZPIN);
  setHue(BULB,false);

}

/////if all photodiodes > NOTELEVEL FAN ON (CHIMES) maybe simplify this condition....?
/*
  if((lightLevelOne>NOTELEVEL)&&(lightLevelTwo>NOTELEVEL)&&(lightLevelThree>NOTELEVEL)&&(lightLevelFour>NOTELEVEL)) {
    wemoWrite(WEMOFAN,TRUE);//wemo with fan and chimes
  }
  else {
    wemoWrite(WEMOFAN,FALSE);
  }
  */
}
/////FOR MANUAL MODE PRESSING PIANO KEYS
else {
  wemoWrite(WEMOLIGHT,FALSE);
  wemoWrite(WEMOFAN,FALSE);
  playNote=0;
  
  
   display.clearDisplay();
  display.setTextSize(3);//
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.printf("MANUAL MODE");
  display.display();

playNote=0;
setHue(BULB,false); //light off

//assignments for all 8 buttons (notes and colors)  
if(hicButton.isPressed()) {
   playNote=HICNOTE;
   hueColor=HueYellow;
   }
  
if(bButton.isPressed())  {//with pull-down resistor 10kohms >2vreads high  <0.8 reads low  avoid in-btw
  playNote=BNOTE;
  hueColor=HueBlue;
}

if(aButton.isPressed())  {
  playNote=ANOTE;
  hueColor=HueRed;
  }
  
if(gButton.isPressed())  {
   playNote=GNOTE;
   hueColor=HueViolet;
  }
  
 
if(fButton.isPressed())  {
  playNote=FNOTE;
  hueColor=HueGreen;
  }
  
if(eButton.isPressed())  {
  playNote=ENOTE;
  hueColor=HueOrange;
  }
  
if(dButton.isPressed())  {
  playNote=DNOTE;
  hueColor=HueIndigo;
  }
  
if(cButton.isPressed())  {
   playNote=CNOTE;
   hueColor=HueYellow;
  }
 //play what note is defined as if note has been defined 
if(playNote!=0) {
    Serial.printf("tone=%i\n",playNote);
  tone(BUZZPIN,playNote);
  setHue(BULB,true,hueColor,50,255);//comment out this line if manual mode too slow
  }
  else {
  noTone(BUZZPIN);
  setHue(BULB,false);
  }
}
}

  
  
  


 

  

