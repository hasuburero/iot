
#define USE_ARDUINO_INTERRUPTS false
#include<PulseSensorPlayground.h>
#include<BluetoothSerial.h>

int Threshold = 2000;
int inpin = 34;
int led = 4;
char e[20];
double Emotion=0;
int BPM, Signal;
const int fade = 5;
const int OUTPUT_TYPE = SERIAL_PLOTTER;
//const int OUTPUT_TYPE = PROCESSING_VISUALIZER;

BluetoothSerial blue;

PulseSensorPlayground pulseSensor;
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

volatile SemaphoreHandle_t timerSemaphore;
hw_timer_t *timer1 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer1(){
  portENTER_CRITICAL_ISR(&timerMux);
  //Serial.println("interrupt");
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pulseSensor.analogInput(inpin);
  pulseSensor.blinkOnPulse(led);
  pulseSensor.fadeOnPulse(fade);
  pulseSensor.setSerial(Serial);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
  
  if (!pulseSensor.begin()) {
    for(;;){
      digitalWrite(led, LOW);
      delay(50);
      digitalWrite(led, HIGH);
      delay(50);
    }
    
  }
  //Serial.println("We created a pulseSensor Object !");
  timerSemaphore = xSemaphoreCreateBinary();
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, &onTimer1, true);
  timerAlarmWrite(timer1, 1000000, true);
  timerAlarmEnable(timer1);

  blue.begin("pulsesensor");
}

void loop(){
	if(pulseSensor.sawNewSample()){
		if(--samplesUntilReport == (byte)0){
			samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
			//pulseSensor.outputSample();

		}
		if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
			char e[20];
			Emotion = getEmotion();
			sprintf(e, "%.2f", Emotion);
			portENTER_CRITICAL_ISR(&timerMux);
			//client.print("send emotion");
			//client.print(e);
			//timerAlarmEnable(timer1);

			blue.println(100);

			portEXIT_CRITICAL_ISR(&timerMux);
			sprintf(e, "Emotion = %5f", Emotion);
			//Serial.println(e);

		}
	}
}

int XXcount = 0;
int XXList[31];
int XXIBI;
double XX_aa;
double getEmotion(){
	//pulseSensor.outputSample();
	if (pulseSensor.sawStartOfBeat()){
		XXcount++;
		pulseSensor.outputBeat();
		XXIBI = pulseSensor.getInterBeatIntervalMs();
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
			for (int i = 0; i < 30; i++){
				if (abs(XXList[i] - XXList[i + 1]) > 50){
				  XXcal++;
				}
			}
			XXcal = (XXcal / 30) * 100;
			XX_aa = XXcal;
			Serial.println(XXcal);
			return XXcal;
		}
		Serial.println(XX_aa);
		return XX_aa;
	}
}
