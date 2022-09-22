#include<WiFi.h>
#include<Wire.h>
#include<math.h>
#include"SSD1306.h"

SSD1306 display(0x3c, 21, 22);

WiFiClient client;

int count = 0;
String str = "";
String s = "";
boolean flag = true;

const char* ssid = "Buffalo-B700";
const char* pass = "pxehn3csh3p4t";
const char* host = "192.168.11.3";
const int port = 50000;

volatile SemaphoreHandle_t timerSemaphore;
hw_timer_t *timer1 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer1()
{
	portENTER_CRITICAL_ISR(&timerMux);
	xSemaphoreGiveFromISR(timerSemaphore, NULL);
	portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() 
{
	Serial.begin(115200);
	WiFi.begin(ssid, pass);
	Serial.println("Connecting.");
	while(WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.println("\nWiFi connected - IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("Connectiong to TCP server .");
	while(!client.connect(host, port)){	//TCPサーバへの接続要求
		Serial.print(".");
		delay(500);
	}
	client.print("start");
	Serial.println("\nstart");

	timerSemaphore = xSemaphoreCreateBinary();
	timer1 = timerBegin(0, 80, true);
	timerAttachInterrupt(timer1, &onTimer1, true);
	timerAlarmWrite(timer1, 1000000, true);
	timerAlarmEnable(timer1);

	display.init();
	display.setFont(ArialMT_Plain_24);
}

void loop() {
	if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
		if(flag){
			double x = 10 * sin(3.14/4*count/10) + 10;
			char mess[10];
			sprintf(mess, "%f", x);
			Serial.println(mess);
			client.print(mess);	//空だと送ってくれない
			++count;
		}
		else{
			client.print(" ");
		}
	}
	s = client.readStringUntil('\n');	//パケットに改行文字は含まれていない
	if(s == ""){	//空の状態はなにもしない
	}
	else{
		str = s;
		Serial.println(str);
		if(str == "run"){
			flag = true;
		}
		else if(str == "stop"){
			flag = false;
		}
	}
	display.clear();
	display.drawString(0, 0, str);
	if(flag){
		display.drawString(0, 30, "run");
	}
	else{
		display.drawString(0, 30, "stop");
	}
	display.display();
}
