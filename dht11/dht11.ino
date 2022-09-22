#include "DHT.h"

#define pin 33
#define DHTTYPE DHT11

DHT dht11(pin, DHTTYPE);

volatile SemaphoreHandle_t timerSemaphore;
hw_timer_t *timer1 = NULL;
portMUX_TYPE timerMUX = portMUX_INITIALIZER_UNLOCKED;

float humidity = 0.0f;
float temp = 0.0f;
char str[30];

void IRAM_ATTR onTimer1()
{
	portENTER_CRITICAL_ISR(&timerMUX);
	xSemaphoreGiveFromISR(timerSemaphore, NULL);
	portEXIT_CRITICAL_ISR(&timerMUX);
}

void setup() {
	Serial.begin(115200);
	dht11.begin();	
	timerSemaphore = xSemaphoreCreateBinary();
	timer1 = timerBegin(0, 80, true);
	timerAttachInterrupt(timer1, &onTimer1, true);
	timerAlarmWrite(timer1, 1000000, true);
	timerAlarmEnable(timer1);
}

void loop() {
	if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
		temp = dht11.readTemperature();
		humidity = dht11.readHumidity();
		sprintf(str, "temp:%f, humidity:%f", temp, humidity);
		Serial.println(str);
	}
}
