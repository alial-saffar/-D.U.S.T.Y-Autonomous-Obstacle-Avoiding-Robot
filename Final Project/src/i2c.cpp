#include <avr/io.h>
#include "i2c.h"

#define wait_for_completion while (!(TWCR & (1 << TWINT))) //Wait for TWINT flag set
#define I2C_WRITE 0
#define I2C_READ 1

// set up communication w/ arduino
void InitI2C()
{ 
    TWCR = (1 << TWEN) | (1 << TWINT); // Enable TWI, clear TWINT, no start yet

    TWSR &= ~((1 << TWPS1) | (1 << TWPS0)); // Prescaler = 1

    TWBR = 72; // if prescaler is one we need to find ((16000000 / 100000) - 16) / 2 = (160 - 16) / 2 = 72
}

// starts the transmision w/ accelorometer
void StartI2C_Trans(unsigned char SLA)
{ 
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA); // Send START
    wait_for_completion;

    TWDR = (SLA << 1) | I2C_WRITE; // Shifts the 7-bit slave address to the left to make room for the R/W bit

    TWCR = (1 << TWINT) | (1 << TWEN); // clr twint and int enable
    wait_for_completion;
}

//ends i2c transmision
void StopI2C_Trans()
{ 
    // Send STOP
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

// sends data byte to slave device w/ i2c
void Write(unsigned char data)
{ 
    TWDR = data; // Two wire data reg equals to incoming data

    TWCR = (1 << TWINT) | (1 << TWEN); // trigger action
    wait_for_completion;
}

// initiates a read from specific register on i2c dev
void Read_from(unsigned char SLA, unsigned char MEMADDRESS)
{ 
    StartI2C_Trans(SLA); // start transmission for sla
    Write(MEMADDRESS);   // write to memaddress

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    wait_for_completion;

    // Send SLA + read bit
    TWDR = (SLA << 1) | I2C_READ; // Always reading from MPU6050
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_for_completion;

    // Do not send ACK because we're reading only 1 byte (NACK)
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_for_completion;
    StopI2C_Trans();
}

// Returns the byte that was last read from the I2C bus.
unsigned char Read_data(void)
{ 
    return TWDR;
}