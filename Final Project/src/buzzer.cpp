#include <Arduino.h> //needed for the abs() function
#include <avr/io.h>
#include "buzzer.h"
#include "i2c.h"
#include "mpu.h"

void InitBuzzer(){            // Initialize Buzzer Pin to output and sens LOW
    DDRA |= (1<<DDA0);
    PORTA &= ~(1<<PORTA0);
}

void BuzzerStatus(bool BuzzerON){  // Turn ON/OFF Buzzer according to boolean input
    if(BuzzerON){
        PORTA |= (1 << DDA0);
      }
    else{
        PORTA &= ~(1 << DDA0);
      }
}

void CheckOrientation(){            // Check for orientation and update BuzzerStatus Accordingly, also calls BuzzerStatus() to trigger it.
  bool BuzzerON;
  const int TilteThreshold = 10000;

  int accY = ReadAxisData(0x3D);
  int accX = ReadAxisData(0x3B);

  if ((abs(accY) > TilteThreshold) || (abs(accX) > TilteThreshold)){
    BuzzerON = true;
  }
  else{
    BuzzerON = false;
  }

  BuzzerStatus(BuzzerON);
}