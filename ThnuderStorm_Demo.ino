// DFPlayer Mini Mp3 by Makuna - Version: Latest

//   MRH Thunderstorm Sound and Stobes with Control Pin
//   G. Bunza 2016
//
/*
   DFPlayer_Mini_Mp3, This library provides a quite complete function for
   DFPlayer mini mp3 module.Files on SD Card must be in \mp3\0001.mp3 to 0005.mp3
*/
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(17, 16); // PRO MINI RX, PRO MINI TX

int lightning_pin[] = {5, 6, 7, 8, 9};
#define brightness 15     //Brightness can be set from 0 - 255
#define DEBUG
int busy_pin    =    15;
int control_pin =    14;   // Control Pin is Pin 14 (A0) Low/Ground is OFF
int next_storm_delay = 4;  //number of minutes delay before next storm after start
int del_tim = 600;
int thunder_tim = 1500;
int tctr, i;
int volumeOffset = 2;

void setup () {
  Serial.begin(115200);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    //set softwareSerial for DFPlayer-mini mp3 module
  delay(del_tim);
  pinMode(busy_pin, INPUT);
  pinMode(control_pin, INPUT_PULLUP);
  for (int x = 0; x <= sizeof(lightning_pin); x++) {
    pinMode(x, OUTPUT);
  }
  mp3_reset ();
#ifdef DEBUG
  Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
  Serial.println("Setup Complete");
#endif
  delay(100);
}

void loop () {
  if ((digitalRead(control_pin) == HIGH)) { //check control pin to start the entire sequence
    //Sequence #1 - Just lightning in the backgrond for a while
    for (int x = 1; x <= 2; x++) {
      Bolt1(lightning_pin[0], 1 * x, 100 * x / 2);
      delay(del_tim * 6);
      Bolt1(lightning_pin[0], 4 * x, 180 * x / 2);
      delay(del_tim * 2);
      Bolt2(lightning_pin[0], lightning_pin[1], 12, 50 * x / 2);
    }
    delay(thunder_tim);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 1 complete");
#endif
    //End Seq 1

    delay(thunder_tim * random(5, 15)); //Add a delay between sequences

    //Sequence #2 - Lightning in the background with some rumble
    Bolt1(lightning_pin[0], 4, 50);
    mp3_set_volume (5 / volumeOffset);
    delay(del_tim);
    mp3_play(4);
    Bolt2(lightning_pin[1], lightning_pin[0], 12, 50);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 7, 70);
    mp3_set_volume (4 / volumeOffset);
    delay(thunder_tim);
    mp3_play(10);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 14, 70);
    Bolt2(lightning_pin[4], lightning_pin[0], 7, 150);
    delay(del_tim);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 7, 70);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 2 complete");
#endif
    //End Seq 2

    delay(thunder_tim * random(2, 8)); //Add a delay between sequences

    //Sequence #3 - Storm is getting closer
    Bolt1(lightning_pin[2], 12, 50);
    mp3_set_volume(15 / volumeOffset);
    delay(del_tim);
    mp3_play(4);
    delay(thunder_tim * 3);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt3(lightning_pin[2], lightning_pin[3], lightning_pin[1], 15, 110);
    mp3_play(6);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 14, 70);
    Bolt2(lightning_pin[4], lightning_pin[0], 7, 150);
    delay(del_tim);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 7, 70);
    delay(thunder_tim * 1);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 7, 70);
    Bolt2(lightning_pin[4], lightning_pin[0], 7, 150);
    mp3_set_volume(6 / volumeOffset);
    delay(del_tim);
    mp3_play(7);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 3 complete");
#endif
    //End Seq3

    delay(thunder_tim * random(2, 15)); //Add a delay between sequences

    //Sequence #4 - Storm has arrived
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 17, 10);
    Bolt3(lightning_pin[0], lightning_pin[3], lightning_pin[4], 15, 70);
    mp3_set_volume(25 / volumeOffset);
    delay(del_tim);
    mp3_play(1);
    delay(thunder_tim * 1);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt2(lightning_pin[3], lightning_pin[4], 17, 30);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 5, 10);
    mp3_set_volume(20 / volumeOffset);
    delay(del_tim);
    mp3_play(4);
    Bolt2(lightning_pin[3], lightning_pin[2], 7, 300);
    delay(del_tim * 3);
    Bolt3(lightning_pin[3], lightning_pin[4], lightning_pin[2], 5, 10);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt3(lightning_pin[4], lightning_pin[3], lightning_pin[2], 5, 10);
    mp3_set_volume(30 / volumeOffset);
    delay(del_tim);
    mp3_play(9);
    Bolt2(lightning_pin[3], lightning_pin[1], 17, 10);
    Bolt3(lightning_pin[3], lightning_pin[0], lightning_pin[4], 10, 130);
    delay(del_tim);
    Bolt3(lightning_pin[0], lightning_pin[1], lightning_pin[4], 4, 70);
    delay(del_tim * 3);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 17, 30);
    Bolt2(lightning_pin[0], lightning_pin[4], 6, 100);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 12, 70);
    delay(del_tim * 2);
    Bolt2(lightning_pin[0], lightning_pin[4], 3, 180);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 12, 40);
    delay(del_tim * 2);
    Bolt3(lightning_pin[0], lightning_pin[3], lightning_pin[4], 5, 100);
    Bolt2(lightning_pin[0], lightning_pin[4], 12, 80);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 8, 50);
    delay(del_tim * 2);
    Bolt2(lightning_pin[2], lightning_pin[3], 6, 120);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 17, 70);
    delay(del_tim * 2);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[1], 10, 130);
    Bolt2(lightning_pin[2], lightning_pin[3], 12, 80);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 8, 180);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt2(lightning_pin[3], lightning_pin[4], 17, 30);
    delay(del_tim * 3);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[2], 5, 10);
    mp3_set_volume(20 / volumeOffset);
    delay(del_tim);
    mp3_play(10);
    Bolt3(lightning_pin[3], lightning_pin[0], lightning_pin[4], 10, 130);
    Bolt3(lightning_pin[2], lightning_pin[1], lightning_pin[4], 4, 70);
    delay(del_tim * 3);
    Bolt3(lightning_pin[2], lightning_pin[1], lightning_pin[0], 15, 100);
    Bolt3(lightning_pin[4], lightning_pin[1], lightning_pin[3], 8, 70);
    delay(del_tim / 2);
    Bolt2(lightning_pin[4], lightning_pin[3], 3, 150);
    Bolt3(lightning_pin[3], lightning_pin[1], lightning_pin[4], 12, 70);
    delay(del_tim * 2);
    Bolt2(lightning_pin[0], lightning_pin[4], 10, 50);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 4 complete");
#endif
    //End Seq 4

    delay(thunder_tim * random(10, 25)); //Add a delay between sequences

    //Sequnce #5 - Storm is moving away
    mp3_set_volume(15 / volumeOffset);
    delay(del_tim);
    mp3_play(10);
    Bolt3(lightning_pin[3], lightning_pin[0], lightning_pin[4], 8, 60);
    Bolt3(lightning_pin[0], lightning_pin[1], lightning_pin[4], 12, 90);
    delay(del_tim);
    Bolt3(lightning_pin[2], lightning_pin[1], lightning_pin[0], 10, 120);
    Bolt3(lightning_pin[0], lightning_pin[1], lightning_pin[4], 4, 60);
    delay(del_tim * 2);
    Bolt2(lightning_pin[0], lightning_pin[4], 9, 100);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 16, 70);
    delay(thunder_tim * 3);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    Bolt2(lightning_pin[3], lightning_pin[4], 7, 200);
    mp3_play(8);
    Bolt3(lightning_pin[3], lightning_pin[4], lightning_pin[2], 5, 10);
    delay(thunder_tim * 1);
    delay(del_tim);
    Bolt3(lightning_pin[2], lightning_pin[1], lightning_pin[0], 10, 120);
    Bolt3(lightning_pin[0], lightning_pin[1], lightning_pin[4], 4, 60);
    delay(del_tim / 2);
    Bolt2(lightning_pin[0], lightning_pin[4], 9, 100);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 16, 70);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    mp3_set_volume(10 / volumeOffset);
    delay(del_tim);
    mp3_play(7);
    Bolt1(lightning_pin[3], 7, 160);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 5 complete");
#endif
    //End Seq 5

    delay(thunder_tim * random(5, 15)); //Add a delay between sequences

    //Sequence #6 - Storm almost gone
    Bolt2(lightning_pin[4], lightning_pin[3], 8, 50);
    delay(thunder_tim / 2);
    Bolt1(lightning_pin[4], 4, 25);
    while (digitalRead(busy_pin)) {
      delay(1);
    }
    mp3_set_volume(5 / volumeOffset);
    delay(del_tim);
    mp3_play(10);
    delay(thunder_tim);
    Bolt1(lightning_pin[4], 4, 90);
    delay(del_tim);
    Bolt3(lightning_pin[3], lightning_pin[4], lightning_pin[2], 10, 120);
    delay(del_tim / 2);
    Bolt2(lightning_pin[3], lightning_pin[4], 9, 100);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 16, 70);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 6 complete");
#endif
    //End Seq 6

    delay(thunder_tim * random(5, 15)); //Add a delay between sequences

    //Sequence #7 - Storm ending
    Bolt2(lightning_pin[3], lightning_pin[4], 9, 100);
    Bolt3(lightning_pin[3], lightning_pin[2], lightning_pin[4], 16, 70);
    delay(del_tim * 5);
    Bolt1(lightning_pin[4], 4, 50);
    delay(del_tim * 4);
    Bolt1(lightning_pin[4], 2, 10);
    Bolt2(lightning_pin[3], lightning_pin[4], 9, 100);
    delay(del_tim * 3);
    Bolt1(lightning_pin[4], 2, 100);
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Sequnce 7 complete");
#endif
    //End Seq 7

    for (i = 0; i < next_storm_delay; i++) {
      for (tctr = 0; tctr < 7; tctr++) {
        delay (10000);              //10 second delay X 6 = 1 minute total delay
      }
    }
#ifdef DEBUG
    Serial.print("Time is: "); Serial.print(micros() / 1000000); Serial.print("s ");
    Serial.println("Program complete, restarting");
#endif
  }
}

//Added Function by DLowe for LED Lightning effects
void Bolt1(int LEDpin, int brightnessFactor, int lightningOn) {
  analogWrite(LEDpin,  brightness * brightnessFactor * 2);
  delay (lightningOn);
  analogWrite(LEDpin,  brightness);
  delay (lightningOn);
  analogWrite(LEDpin,  brightness * brightnessFactor);
  delay (lightningOn);
  analogWrite(LEDpin, 0);
}

void Bolt2(int LEDpin1, int LEDpin2, int brightnessFactor, int lightningOn) {
  analogWrite(LEDpin1,  brightness * brightnessFactor * .5);
  delay (lightningOn);
  analogWrite(LEDpin1,  brightness);
  delay (lightningOn * 2);
  analogWrite(LEDpin1,  brightness * brightnessFactor);
  analogWrite(LEDpin2,  brightness);
  delay (lightningOn);
  analogWrite(LEDpin1, 0);
  analogWrite(LEDpin2,  brightness * brightnessFactor * .75);
  delay (lightningOn);
  analogWrite(LEDpin2, 0);
}

void Bolt3(int LEDpin1, int LEDpin2, int LEDpin3, int brightnessFactor, int lightningOn) {
  analogWrite(LEDpin1,  brightness * brightnessFactor);
  delay (lightningOn / 2);
  analogWrite(LEDpin1,  brightness * 25);
  delay (lightningOn);
  analogWrite(LEDpin1,  brightness * brightnessFactor);
  analogWrite(LEDpin2,  brightness * 2);
  delay (lightningOn * 4);
  analogWrite(LEDpin1, 0);
  analogWrite(LEDpin2,  brightness * brightnessFactor);
  analogWrite(LEDpin3,  brightness / 2 * brightnessFactor);
  delay (lightningOn * 2);
  analogWrite(LEDpin2, 0);
  analogWrite(LEDpin3,  brightness * 1.2);
  delay(lightningOn);
  analogWrite(LEDpin3, 0);
}
