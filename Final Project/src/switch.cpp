#include "switch.h"
#include <avr/io.h>

void initSwitchPB0(){        // initialize pin 53 as input and enable pull-up resistor, also enable pin change inturrupt.
    DDRB &= ~(1 << DDB0);
    PORTB |= (1 << PORTB0);
  
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<PCINT0);
}
