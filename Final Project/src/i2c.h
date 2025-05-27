#ifndef I2C_H
#define I2C_H

void InitI2C(); // set up communication w/ arduino
void StartI2C_Trans(unsigned char SLA); // starts the transmision w/ accelorometer
void StopI2C_Trans(); //ends i2c transmision
void Write(unsigned char data); // sends data byte to slave device w/ i2c
void Read_from(unsigned char SLA, unsigned char MEMADDRESS); // initiates a read from specific register on i2c dev
unsigned char Read_data(void); // Returns the byte that was last read from the I2C bus.

#endif
