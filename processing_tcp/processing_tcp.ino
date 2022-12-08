
#define USE_ARDUINO_INTERRUPTS false
#define DHTPIN 33
#define DHTTYPE DHT11
#include<DHT.h>
#include<PulseSensorPlayground.h>
#include<Ticker.h>
#include<WiFi.h>
#include"SSD1306.h"

SSD1306 display(0x3c, 21, 22);

//const char* ssid = "Buffalo-B700";
//const char* pass = "pxehn3csh3p4t";
const char* ssid = "aterm-5df4ab-g";
const char* pass = "742e6c40125a5";
const int port = 8080;
//const char* host = "192.168.11.8";
const char* host = "192.168.93.1";

WiFiClient client;

int Threshold = 2500;
int inpin = 34;
int led = 21;
char e[30];
char buf[20];
double Emotion = 0;
int BPM, Signal;
const int fade = 5;
const int OUTPUT_TYPE = SERIAL_PLOTTER;

PulseSensorPlayground pulseSensor;
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

volatile SemaphoreHandle_t timerSemaphore;
hw_timer_t *timer1 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

DHT dht11(DHTPIN, DHTTYPE);
float humidity = 0.0f;
float temp = 0.0f;

void IRAM_ATTR onTimer1() {
  portENTER_CRITICAL_ISR(&timerMux);
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  portEXIT_CRITICAL_ISR(&timerMux);
}

//void task(void* arg){
//	client.print(e);
//	vTaskDelete(NULL);
//}

void setup() {
  Serial.begin(115200);
  delay(10);

  display.init();
  display.setFont(ArialMT_Plain_10);

  WiFi.begin(ssid, pass);
  Serial.println("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
  //Serial.print("WiFi connected - IP address: ");
  //Serial.println(WiFi.localIP());
  client.connect(host, port);
  client.println("connect");
  //Serial.println("connect");
  delay(500);

  dht11.begin();

  pulseSensor.analogInput(inpin);
  pulseSensor.blinkOnPulse(led);
  pulseSensor.fadeOnPulse(fade);
  pulseSensor.setSerial(Serial);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

  if (!pulseSensor.begin()) {
    for (;;) {
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
}

void loop() {
  if (pulseSensor.sawNewSample()) {
    pulseSensor.outputSample();
    if (--samplesUntilReport == (byte)0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
    }

    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) {
      Emotion = getEmotion();
      humidity = dht11.readHumidity();
      temp = dht11.readTemperature();

      display.clear();
      char s[32];
      sprintf(s, "%f", Emotion);
      display.drawString(0, 0, "Emotion");
      display.drawString(10, 10, s);
      
      sprintf(s, "%f", humidity);
      display.drawString(0, 20, "humidity");
      display.drawString(10, 30, s);

      sprintf(s, "%f", temp);
      display.drawString(0, 40, "temperature");
      display.drawString(10, 50, s);

      display.display();
      
      sprintf(e, "%f,%f,%f", Emotion, temp, humidity);

      client.print(e);
      //xTaskCreatePinnedToCore(task, "task", 8192, NULL, 24, NULL, 0);
      
      //Serial.println(e);
    }
  }
}

int XXcount = 0;
int XXList[31];
int XXIBI;
double XX_aa;
double getEmotion() {
  //pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
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
      for (int i = 0; i < 30; i++) {
        if (abs(XXList[i] - XXList[i + 1]) > 50) {
          XXcal++;
        }
      }
      XXcal = (XXcal / 30) * 100;
      XX_aa = XXcal;
      //Serial.println(XXcal);
      return XXcal;
    }
    //Serial.println(XX_aa);
    return XX_aa;
  }
}
