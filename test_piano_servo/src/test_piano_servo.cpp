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
#include "IoTClassroom_CNM.h"
// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

const int PHOTODIODEONE=A0;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN= D16;//PWM
const int CNOTE=131;//freq for C 
int lightLevelOne;
float motor;
float t;

Servo cServo;


//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); //serial port
  waitFor(Serial.isConnected,15000);

pinMode(PHOTODIODEONE,INPUT);//photodiode 1
pinMode(BUZZPIN,OUTPUT);//buzzer
cServo.attach(SERVPIN);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  lightLevelOne=analogRead(PHOTODIODEONE);
  Serial.printf("Light level one is %i\n",lightLevelOne);

  if(lightLevelOne>100) {
    t=millis()/1000.0; //to get current time
    motor=(180/2)* sin(2 * M_PI * .2 * t)+(180/2);
    //cServo.write(motor);
    cServo.write(90);
    //noteTimer.isTimerReady();
    tone(BUZZPIN,CNOTE);
  }
  else{
    noTone(BUZZPIN);
  }

  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
