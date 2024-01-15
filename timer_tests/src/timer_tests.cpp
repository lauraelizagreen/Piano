/* 
 * Project: timer_tests
 * Author: Laura Green
 * Date: 1/14/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
int currentTime;
int lastSecond;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,10000);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  currentTime=millis();
  if((currentTime-lastSecond)>1000) {//isn't lastSecond undefined at this point???  or is an undefined variable set at 0? (would 0 be same as millis?)
    lastSecond=millis();
    Serial.printf(".");
  }
  
  
}
