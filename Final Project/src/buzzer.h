#ifndef BUZZER_H
#define BUZZER_H

void InitBuzzer();                    //initializer Buzzer's Pin to output and sends LOW.
void BuzzerStatus(bool BuzzerON);     // Turns Buzzer ON/OFF according to boolean input
void CheckOrientation();              // Triggers Buzzer if Tilte exceeds a threshold value.

#endif