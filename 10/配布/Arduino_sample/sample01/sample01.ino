

/*
   Code to detect pulses from the PulseSensor,
   using an interrupt service routine.

   Here is a link to the tutorial\
   https://pulsesensor.com/pages/getting-advanced

   Copyright World Famous Electronics LLC - see LICENSE
   Contributors:
     Joel Murphy, https://pulsesensor.com
     Yury Gitman, https://pulsesensor.com
     Bradford Needham, @bneedhamia, https://bluepapertech.com

   Licensed under the MIT License, a copy of which
   should have been included with this software.

   This software is not intended for medical use.
*/

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int PIN_INPUT = A0;
const int PIN_BLINK = 4;    // Pin 13 is the on-board LED
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle
int BPM, Signal;
double Emotion;

//const int OUTPUT_TYPE  = SERIAL_PLOTTER;
const int OUTPUT_TYPE = PROCESSING_VISUALIZER;
/*
   All the PulseSensor Playground functions.
*/

PulseSensorPlayground pulseSensor;

void setup() {

  Serial.begin(115200);

  // Configure the PulseSensor manager.

  pulseSensor.analogInput(PIN_INPUT);//
  pulseSensor.blinkOnPulse(PIN_BLINK);

  pulseSensor.setSerial(Serial);
  pulseSensor.setThreshold(THRESHOLD);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  // Now that everything is ready, start reading the PulseSensor signal.
  if (!pulseSensor.begin()) {

    for (;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PIN_BLINK, LOW);
      delay(50);
      digitalWrite(PIN_BLINK, HIGH);
      delay(50);
    }
  }
}

void loop() {
  delay(1000);
  Emotion = getEmotion();
  Serial.println(Emotion);
}









//the end of code




























































































































































































//Do Not Rewrite
int XXcount = 0;
int XXList[31];
int XXIBI;
double XX_aa;
double getEmotion() {
  pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
    XXcount++;
    pulseSensor.outputBeat();
    XXIBI = pulseSensor.getInterBeatIntervalMs();
    Serial.println(XXIBI);
    if (XXcount < 30) {
      XXList[XXcount - 1] = XXIBI;
      return -1;
    } else {
      for (int i = 0; i < 31; i++) {
        if (i == 30) {
          XXList[i] = XXIBI;
        } else {
          XXList[i] = XXList[i + 1];
        }
      }
      double XXcal = 0;
      for (int i = 0; i < 30; i++) {
        if (abs(XXList[i] - XXList[i + 1]) > 50) {
          XXcal ++;
        }
      }
      XXcal = (XXcal / 30) * 100;
      XX_aa = XXcal;
      return XXcal;
    }
    return XX_aa;
  }
}
