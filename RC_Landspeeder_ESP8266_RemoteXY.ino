/*
   RC Landspeeder (ESP8266 + RemoteXY) 

   Uses RemoteXY mobile app for WiFi joystick control.
   Controls a steering servo and an ESC for throttle.

   Controls:
     - Throttle slider:  RemoteXY.Throttle   (-100..100)
     - Steering (joy X): RemoteXY.Steering   (-100..100)

   Pins:
     - D1 (GPIO5) = Steering servo
     - D2 (GPIO4) = ESC

   Notes:
     - Holds neutral for ~1s on boot so the ESC can arm/beep.
     - Sends neutral if the app disconnects.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

//#define REMOTEXY__DEBUGLOG  // enable debug to Serial if needed
#define REMOTEXY_MODE__WIFI_POINT

#include <ESP8266WiFi.h>
#include <RemoteXY.h>
#include <Servo.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "Landspeeder"
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY GUI configuration
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 124 bytes
  { 255,3,0,0,0,117,0,19,0,0,0,76,97,110,100,115,112,101,101,100,
  101,114,0,83,2,106,200,200,84,1,1,5,0,4,14,60,13,86,38,6,
  8,71,32,1,8,129,4,152,35,10,33,78,18,5,64,8,84,104,114,111,
  116,116,108,101,0,129,62,152,37,10,141,77,19,5,64,8,83,116,101,101,
  114,105,110,103,0,129,17,10,73,10,57,2,88,12,64,8,82,67,32,76,
  97,110,100,115,112,101,101,100,101,114,0,5,57,81,46,46,128,24,44,44,
  32,1,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {
  int8_t Throttle;      // from -100 to 100
  int8_t Steering;      // from -100 to 100
  int8_t joystick_01_y; // (unused, from template)
  uint8_t connect_flag; // =1 if wire connected, else =0
} RemoteXY;   
#pragma pack(pop)

//////////////////////////////////////////////
//          Pin assignments & setup         //
//////////////////////////////////////////////

Servo steeringServo;
Servo esc;

#define STEERING_PIN D1
#define ESC_PIN      D2

void setup() {
  RemoteXY_Init(); 

  steeringServo.attach(STEERING_PIN);
  esc.attach(ESC_PIN);

  // Center steering & zero throttle at startup
  steeringServo.write(90);
  esc.writeMicroseconds(1500);

  // Hold neutral for ESC arming
  delay(1000);
}

//////////////////////////////////////////////
//                 Loop                     //
//////////////////////////////////////////////

void loop() { 
  RemoteXY_Handler();

  // Failsafe: if app disconnects, return to neutral
  if (RemoteXY.connect_flag == 0) {
    steeringServo.write(90);
    esc.writeMicroseconds(1500);
    return;
  }

  // Steering: map joystick values (-100..100) to servo angles
  int steeringValue = map(RemoteXY.Steering, -100, 100, 45, 135);
  steeringServo.write(steeringValue);

  // Throttle: map slider (-100..100) to ESC range (1000–2000 µs)
  int throttleValue = map(RemoteXY.Throttle, -100, 100, 1000, 2000);
  esc.writeMicroseconds(throttleValue);

  // Keep loop responsive (~100 Hz)
  RemoteXY_delay(10);
}
