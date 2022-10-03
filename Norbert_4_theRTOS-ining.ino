#include <Arduino_FreeRTOS.h>
#include <Servo.h>
#include <NewPing.h> 

//Displaye settings
#include "U8glib.h"
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

// define tasks prototypes
void TaskRangeFind(void *pvParameters );
void TaskBumpCLiffDetect(void *pvParameters );
void TaskNavigate(void *pvParameters );
TaskHandle_t TaskHandle_Navigate;
TaskHandle_t TaskHandle_Rangefind;
TaskHandle_t TaskHandle_BumpCLiffDetect;

//Flag to turn serial data reporting on and off
#define DEBUG false
//Bumpers and IR detector pair 
#define BUMP_L 3 //0 is bumped, 1 is normal state 
#define BUMP_R 2 //0 is bumped, 1 is normal state 
#define CLIFF 7 //1 is no bottom detected, 0 is normal state 
bool _Bump_L = 1;
bool _Bump_R = 1;
bool _Cliff = 0;

//define pins and max range for ultrasonic sensor and servo
#define TRIGGER_PIN  4
#define ECHO_PIN     10
#define MAX_DISTANCE 200  //Appears pings beyond this show as 0, can change in library?
#define servoPin 9

Servo myservo;  // create servo object to control a servo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//set our servo positions TODO tune these. Make a sketch using serial to adjust?
#define posLeft 140
#define posRight 55
#define posCenter 94

//set our ranges TODO determine in needful
//int triggerDistance = 30;

//pre-set our int for range
int intRangeCenter = 200;
int intRangeRight = 200;
int intRangeLeft = 200;


// HG7881 Motor section//////////////////////
//B is right motor
#define HG7881_B_IA 5 // D3 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 6 // D4 --> Motor B Input B --> MOTOR B -
//A is left motor
#define HG7881_A_IA 11 // D3 --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 12 // D4 --> Motor A Input B --> MOTOR A -
 
// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction
#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor A Direction
  
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 175  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 240 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 500 // brief delay for abrupt motor changes


/*--------------------------------------------------*/
/*---------------------- Setup ---------------------*/
/*--------------------------------------------------*/
// the setup function runs once when you press reset or power the board
void setup() 
{
// initialize serial communication at 9600 bits per second:
    if(DEBUG)
    {
    Serial.begin(115200);
    }
//set up servo
pinMode(servoPin, OUTPUT);
myservo.attach(servoPin);  // attaches the servo on pin 10 to the servo object
delay(10);
myservo.write(posCenter); //set servo to 90 degrees to start (forward)
    if(DEBUG)
    {
    Serial.println(F("Servo centered"));
    }
delay(250);

//Set up HC-SR04 ultrasonicsensor
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
    if(DEBUG)
    {
    Serial.println(F("Initialized rangefinder"));
    }
//set up edge detector
pinMode(BUMP_L, INPUT_PULLUP);
pinMode(BUMP_R, INPUT_PULLUP);
pinMode(CLIFF, INPUT);
    if(DEBUG)
    {
    Serial.println(F("Initialized Cliff and Bump detection"));
    }
pinMode(LED_BUILTIN, OUTPUT);


//set up motor
pinMode( MOTOR_B_DIR, OUTPUT ); //Set pinmode for motor
pinMode( MOTOR_B_PWM, OUTPUT );
digitalWrite( MOTOR_B_DIR, LOW ); //turn motors off
digitalWrite( MOTOR_B_PWM, LOW );
pinMode( MOTOR_A_DIR, OUTPUT );
pinMode( MOTOR_A_PWM, OUTPUT );
digitalWrite( MOTOR_A_DIR, LOW );
digitalWrite( MOTOR_A_PWM, LOW );
  if(DEBUG)
  {
  Serial.println(F("H-bridge set up"));
  }
delay(10);


  // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  //TODO see if needed on nano
  //while (!Serial) {;} 
      

/*--------------------------------------------------*/
/*--------------------Task Setup--------------------*/
/*--------------------------------------------------*/
  xTaskCreate(
    TaskRangeFind
    ,  "RangeFind"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskHandle_Rangefind);
        if(DEBUG)
        {
        Serial.println(F("added Range Finder"));
        }
  xTaskCreate(
    TaskBumpCLiffDetect
    ,  "BumpDetect"
    ,  100  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  &TaskHandle_BumpCLiffDetect);
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
      if(DEBUG)
      {
      Serial.println(F("added t2 Bump Detect"));
      }

xTaskCreate(
  TaskNavigate
    ,  "Navigate"
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskHandle_Navigate);
      if(DEBUG)
      {
      Serial.println(F("added t3 Navigation module"));  
      }

  vTaskStartScheduler();     
      if(DEBUG)
          {
          Serial.println(F("Task scheduling started"));  
          }
 }
   
void loop()
{
  // Empty. Things are done in Tasks.
}



/*--------------------------------------------------*/
/*-------------------Temp Tasks----------------------*/
/*--------------------------------------------------*/
/*
void TaskStackSize(void *pvParameters) 
{
(void) pvParameters;
//Stacksize for debug
//TODO remove later
int StackSize;
for (;;)
  {
  //StackSize = (RAMEND - SP);
  Serial.print(F("Stack size: "));  
  Serial.println(RAMEND - SP); 
  vTaskDelay(pdMS_TO_TICKS(1000));
  } 
}*/
