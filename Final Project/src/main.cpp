#include <Arduino.h> //needed only for Sei() function, couldn't use it otherwise
#include <avr/io.h>  //Needed to define ports
#include "timer.h"
#include "switch.h"
#include "pwm.h"
#include "ultrasonic.h"
#include "i2c.h"
#include "mpu.h"
#include "buzzer.h"


typedef enum { // state declerations for PushButtonSwitch 53 (PowerSwitch)
  High, High_Debounce, Low, Low_Debounce
} PowerSwitchState;

PowerSwitchState CurrentPowerSwitchState = High;      // initialize to high
bool Is_Sleeping = 1;                                 // initialize to true

 
int main(){

    initTimer0();                                    //initializing main features
    initTimer1();
    initSwitchPB0();
    init_Left_PWM_Pins();
    init_Right_PWM_Pins();
    Motor_Calibration();   // Calibrates the motors
    InitUltrasonics();
    InitBuzzer();
    sei();      // enables global inturrupts

    InitI2C();           // initialize the I2C communication protocol
    StartI2C_Trans(0x68);
    Write(0x6B); // Power management
    Write(0x00); // Wake up
    StopI2C_Trans();

    while(1){

    double FrontDistance, LeftDistance, RightDistance;     // three variables to store Distance from Front and Sides
    FrontDistance = GetFrontDistanceCM();
    delayMs(30);                            //Delays needed since same timer is used to count Echo
    LeftDistance = GetLeftDistanceCM();
    delayMs(30);
    RightDistance = GetRightDistanceCM();
    delayMs(30);


    switch (CurrentPowerSwitchState){               // States for PowerSwitch
    case High:
    break;
    case High_Debounce:
    delayMs(1);
    CurrentPowerSwitchState = Low;
    break;
    case Low:
    break;
    case Low_Debounce:
    delayMs(1);
    CurrentPowerSwitchState = High;
    break;
    }
    
    if(Is_Sleeping){                               //Checks for mode, Sleeping mode turns off motors
        StopMotors();
    }
    else{                                          //Starts moving
        PathFinding(FrontDistance, LeftDistance, RightDistance);
    }
     
    CheckOrientation();                            // Checks for Tilte, excessive tilte triggers Buzzer

    }
}

ISR(PCINT0_vect){                               //Inturrupt, triggered by the switch, controls the mode
  if ((CurrentPowerSwitchState == High)){
    CurrentPowerSwitchState = High_Debounce;
  }
  else if ((CurrentPowerSwitchState == Low)){
    CurrentPowerSwitchState = Low_Debounce;
    Is_Sleeping = !(Is_Sleeping);
  }
  
}

