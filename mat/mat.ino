#include<BleKeyboard.h>

#define pin 2
#define pin2 12
#define pin3 14

BleKeyboard bkey("esp keyboard");

volatile SemaphoreHandle_t Semaphore;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onswitch()
{
	portENTER_CRITICAL_ISR(&mux);
	//portDISABLE_INTERRUPTS();
	xSemaphoreGiveFromISR(Semaphore, NULL);
	Serial.println("on!!");
	delay(100);
	portEXIT_CRITICAL_ISR(&mux);
	//portENABLE_INTERRUPTS();
}

void IRAM_ATTR onbutton()
{
	portENTER_CRITICAL_ISR(&mux);
	//portDISABLE_INTERRUPTS();
	xSemaphoreGiveFromISR(Semaphore, NULL);
	Serial.println("button!!");
	delay(100);
	portEXIT_CRITICAL_ISR(&mux);
	//portENABLE_INTERRUPTS();
}

void setup() {
	Serial.begin(115200);
	pinMode(pin, INPUT_PULLUP);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, INPUT_PULLUP);

	bkey.begin();

	Semaphore = xSemaphoreCreateBinary();
	attachInterrupt(pin, onswitch, FALLING);
	attachInterrupt(pin3, onbutton, FALLING);
}

void loop() {
	if(xSemaphoreTake(Semaphore, 0) == pdTRUE){
		portENTER_CRITICAL_ISR(&mux);
		digitalWrite(pin2, HIGH);
		Serial.println("shot");
		if(bkey.isConnected()){
			bkey.print("a");
		}
		delay(100);
		portEXIT_CRITICAL_ISR(&mux);
	}
	else{
		digitalWrite(pin2, LOW);
	}
}
