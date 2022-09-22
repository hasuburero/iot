#include<WiFi.h>
#include<WiFiClient.h>

WiFiServer server(5000);

const char* ssid = "Buffalo-B700";
const char* pass = "pxehn3csh3p4t";

String str = "";

void setup() {
	Serial.begin(115200);
	delay(500);
	
	WiFi.begin(ssid, pass);
	Serial.println("Connecting.");
	while(WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.print("WiFi connected - IP address: ");
	Serial.println(WiFi.localIP());
	
	server.begin();
	Serial.println("server.begin()");
}

void loop() {
	WiFiClient client = server.available();

	if(client){
		Serial.println("New Client.");
		while(client.connected()){
			int size = client.available();
			if(size){
				Serial.println();
				Serial.print("size:");
				Serial.println(size);
				for(int i=0; i<size; ++i){
					//uint8_t c = client.read();
					char c = client.read();
					str += c;
				}
				Serial.println(str);
				str = "";
			}
			delay(1);
		}
		client.stop();
		Serial.println();
		Serial.println("client.stop()");
	}
}
