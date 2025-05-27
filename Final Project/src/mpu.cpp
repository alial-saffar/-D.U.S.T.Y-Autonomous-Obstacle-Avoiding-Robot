#include "i2c.h"
#include "timer.h"

#define MPU_ADDR 0x68   // I2C address of the MPU6050

// Reads 2 bytes from a given axis register (high + low), combines into 16-bit value
int ReadAxisData(int regHighAddr)
{
  Read_from(MPU_ADDR, regHighAddr); // Request high byte from sensor
  int high = Read_data();           // Read high byte

  Read_from(MPU_ADDR, regHighAddr + 1); // Request low byte from sensor
  int low = Read_data();                // Read low byte

  float value = (high << 8) | low; // Combine bytes into signed 16-bit int
  return value;
}