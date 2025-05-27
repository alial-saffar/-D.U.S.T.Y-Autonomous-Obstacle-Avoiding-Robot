#ifndef PWM_H
#define PWM_H

void init_Left_PWM_Pins();              //initializing Modes, prescaler, output pwm pin and frequancy. 
void ChangeDutyCycle_Left(int input);   //Changes the DutyCycle

void init_Right_PWM_Pins();             //initializing Modes, prescaler, output pwm pin and frequancy. 
void ChangeDutyCycle_Right(int input);  //Changes the DutyCycle

void StopMotors();                      //Stops Motors by sending a throttle value of 1500 microseconds, or 7.5% dutycycle
void Motor_Calibration();               //Calibrates BLDC motors
void PathFinding(double FrontDistance, double LeftDistance, double RightDistance); //the Obstical avoiding algorithem.

#endif