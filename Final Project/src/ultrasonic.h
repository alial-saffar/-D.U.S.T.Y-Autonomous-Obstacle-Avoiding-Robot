#ifndef ULTRASONIC_H
#define ULTRASONIC_H

void InitTimer5();           //Initializes timer 5 to count Echo time     
void InitUltrasonics();      //Initializes Ultrasonic Sensors Pins
double GetFrontDistanceCM(); //Gives Front Distance
double GetLeftDistanceCM();  //Gives Left Distance
double GetRightDistanceCM(); //Gives Right Distance


#endif
