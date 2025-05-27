#include "pwm.h"
#include "timer.h"

const int Throttle_Forward_Max = 1000; // 10% DutyCycle
const int Throttle_Forward_Left = 1425;
const int Throttle_Forward_Right = 1425;
const int Throttle_Stop = 1500;        // 7.5% DutyCycle
const int Throttle_Reverse_Left = 1575;
const int Throttle_Reverse_Right = 1575;
const int Throttle_Reverse_Max = 2000; // 5% DutyCycle



void init_Left_PWM_Pins(){        
    //fast PWM, mode 15 for variable frequency
    TCCR3A |= (1 << WGM30) | (1 << WGM31);
    TCCR3B |= (1 << WGM32) | (1 << WGM33);
    //Fast PWM non-inverting mode
    TCCR3A &= ~(1 << COM3C0);
    TCCR3A |= (1 << COM3C1);
    //set prescaler to 64
    TCCR3B |= (1 << CS30);
    TCCR3B |= (1 << CS31);

    DDRE |= (1 << DDE5); // Set Pin 3 on board to output, which is OC3C,PWM}
    OCR3A = 5000 - 1;    //OCR3A is frequancy, OCR3C is dutycycle
}

void ChangeDutyCycle_Left(int input){  //use throttle values from 1000 to 2000
    OCR3C = input/4;
}



void init_Right_PWM_Pins(){//fast PWM, mode 15 for variable frequency.
    TCCR4A |= (1 << WGM40) | (1 << WGM41);
    TCCR4B |= (1 << WGM42) | (1 << WGM43);
    //Fast PWM non-inverting mode
    TCCR4A &= ~(1 << COM4C0);
    TCCR4A |= (1 << COM4C1);
    //set prescaler to 64
    TCCR4B |= (1 << CS40);
    TCCR4B |= (1 << CS41);

    DDRH |= (1 << DDH5); // Set Pin 8 on board to output, which is OC4C,PWM}
    OCR4A = 5000 - 1;    //OCR3A is frequancy, OCR3C is dutycycle.
}

void ChangeDutyCycle_Right(int input){  //use throttle values from 1000 to 2000
    OCR4C = input/4;
}

void StopMotors(){                      //stops motors by sending throttle of 1500 (microsecond) which is 7.5% dutycycle.
    ChangeDutyCycle_Left(Throttle_Stop);
    ChangeDutyCycle_Right(Throttle_Stop);
}

void Motor_Calibration(){
    //Send Maximum Forward throttle
    ChangeDutyCycle_Left(Throttle_Forward_Max);
    ChangeDutyCycle_Right(Throttle_Forward_Max);
    delayMs(1000);

    //Send Maximum Reverse Throttle
    ChangeDutyCycle_Left(Throttle_Reverse_Max);
    ChangeDutyCycle_Right(Throttle_Reverse_Max);
    delayMs(1000);

    StopMotors();
    delayMs(1000);
}

void PathFinding(double FrontDistance, double LeftDistance, double RightDistance){//Pathfinding algorithem, priority for obsticals infront
    if(FrontDistance > 30){ // Go Forward
        ChangeDutyCycle_Left(Throttle_Forward_Left);
        ChangeDutyCycle_Right(Throttle_Forward_Right); 
    }
    else if (LeftDistance >= RightDistance){ //Turn Left
        StopMotors();
        delayMs(250);
        ChangeDutyCycle_Left(Throttle_Reverse_Left);
        ChangeDutyCycle_Right(Throttle_Forward_Right);
        delayMs(475);
    }
    else if (LeftDistance < RightDistance){ //Turn Right
        StopMotors();
        delayMs(250);
        ChangeDutyCycle_Left(Throttle_Forward_Left); 
        ChangeDutyCycle_Right(Throttle_Reverse_Right);
        delayMs(475);
    } 
 }


