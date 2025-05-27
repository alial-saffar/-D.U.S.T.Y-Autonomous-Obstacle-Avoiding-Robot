#include "ultrasonic.h"
#include "timer.h"

void InitTimer5(){ //used to time Trigger and Echo
    TCCR5A &= ~((1<<WGM51)|(1<<WGM50)); //Normal mode
    TCCR5B &= ~((1<<WGM53)|(1<<WGM52));

    TCCR5B |= (1<<CS51);              //Prescaler of 8
    TCCR5B &= ~((1<<CS52)|(1<<CS50));
}

void InitUltrasonics(){
    DDRL |= (1<<DDL3);     //Front Ultrasonic, Trigger 46 output, Echo 47 input (initialize trig to Low)
    PORTL &= ~(1<<PORTL3);
    DDRL &= ~(1<<DDL2);

    DDRL |= (1<<DDL5);     //Right Ultrasonic, Trigger 44 output, Echo 45 input (initialize trig to Low)
    PORTL &= ~(1<<PORTL5);
    DDRL &= ~(1<<DDL4);

    DDRL |= (1<<DDL1);     //Left Ultrasonic, Trigger 46 output, Echo 47 input (initialize trig to Low)
    PORTL &= ~(1<<PORTL1);
    DDRL &= ~(1<<DDL0);

    InitTimer5();
}

double GetFrontDistanceCM(){      //Gives Front Distance
    double Distance;
    double Echo_us;

    PORTL |= (1<<PORTL3);  //Set Front Trigger to High
    delayUs(10);
    PORTL &= ~(1<<PORTL3); //Set back to Low

    while ( !(PINL & (1 << PINL2)) ); // Wait Echo to go High, like a switch
    TCNT5 = 0;                        //Resetting the counting register, used to count the time the Echo is High
    while ( PINL & (1 << PINL2));     // Wait Echo to go Low

    Echo_us = TCNT5 * 0.5;            // prescaler of 8 thus each tick is 0.5 microsec
    Distance = Echo_us/58;            // this is the actual distance in CM, accurate and verified
    return Distance;
}

double GetLeftDistanceCM(){  //Gives Left Distance
    double Distance;
    double Echo_us;

    PORTL |= (1<<PORTL1);  //Set Front Trigger to High
    delayUs(10);
    PORTL &= ~(1<<PORTL1); //Set back to Low

    while ( !(PINL & (1 << PINL0)) ); // Wait to go High, like a switch
    TCNT5 = 0;                        //Resetting the counting register, used to count the time the Echo is High
    while ( PINL & (1 << PINL0));     // Wait to go Low

    Echo_us = TCNT5 * 0.5;           // prescaler of 8 thus each tick is 0.5 microsec
    Distance = Echo_us/58;           // this is the actual distance in CM, accurate and verified
    return Distance;
}

double GetRightDistanceCM(){    //Gives Right Distance
    double Distance;
    double Echo_us;

    PORTL |= (1<<PORTL5);  //Set Front Trigger to High
    delayUs(10);
    PORTL &= ~(1<<PORTL5); //Set back to Low

    while ( !(PINL & (1 << PINL4)) ); // Wait to go High, like a switch
    TCNT5 = 0;                        //Resetting the counting register, used to count the time the Echo is High
    while ( PINL & (1 << PINL4));     // Wait to go Low

    Echo_us = TCNT5 * 0.5;            // prescaler of 8 thus each tick is 0.5 microsec
    Distance = Echo_us/58;            // this is the actual distance in CM, accurate and verified
    return Distance;
}




