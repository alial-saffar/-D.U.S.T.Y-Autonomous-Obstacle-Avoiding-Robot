#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();                   //initializes the timer's mode, prescaler.
void delayMs(unsigned int delay);    //Custom delay function in milliseconds

void initTimer1();                   //initializes the timer's mode, prescaler.
void delayUs(unsigned int delay) ;   //Custom delay function in microseconds

#endif
