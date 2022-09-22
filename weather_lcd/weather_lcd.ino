#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>

#include<Wire.h>
#include"SSD1306.h"

SSD1306 display(0x3c, 21, 22);

const char *ssid = "Buffalo-B700";
const char *password = "pxehn3csh3p4t";

const String api_key = "1a1563e8b9fc4af491821652221409";
const String location = "Saitama";

struct Weather{
	const char *region;
	float temperature;
	int humidity;
	const char *last_updated;
};

void setup() {
	Serial.begin(115200);
	WiFi.begin(ssid, password);

	while(WiFi.status() != WL_CONNECTED){
		Serial.println("Waiting for Wi-Fi connection....");
		delay(500);
	}
	Serial.println("Connected to Wi-Fi");

	display.init();
}

void loop()
{
	display.clear();

	HTTPClient http;
	String target_url = "http://api.weatherapi.com/v1/current.json";
	target_url += ("?key=" + api_key + "&q=" + location + "&api=no");
	http.begin(target_url);

	int http_code = http.GET();

	Serial.printf("status code : %d\n", http_code);
	if(http_code > 0){
		if(http_code == HTTP_CODE_OK){
			String payload = http.getString();
			Serial.println(payload);
			Weather weather = parse(payload);
			Serial.println("------weather--------");
			Serial.println(weather.region);
			Serial.println(weather.temperature);
			Serial.println(weather.humidity);
			Serial.println(weather.last_updated);
			display.setFont(ArialMT_Plain_10);
			display.drawString(0, 0, "region:");
			display.drawString(0, 12, "temperature:");
			display.drawString(0, 24, "humidity:");
			display.drawString(0, 36, "last_updated:");
			display.drawString(65, 0, weather.region);
			display.drawString(65, 12, String(weather.temperature) + "°c");
			display.drawString(65, 24, String(weather.humidity) + "％");
			display.drawString(30, 48, weather.last_updated);

			display.display();
		}
		else if(http_code > 500){
			Serial.printf("Server Error: %d", http_code);
		}
		else if(http_code > 400){
			Serial.printf("Client Error: %d", http_code);
		}
	}
	else{
		Serial.println(http.errorToString(http_code).c_str());
	}
	http.end();
	delay(60000);
}

Weather parse(String input)
{
	Serial.println("parse......");
	StaticJsonDocument<1536> doc;
	DeserializationError error = deserializeJson(doc, input);

	if(error){
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		Weather weather = {"", 0, 0};
		return weather;
	}

	JsonObject location = doc["location"];
	const char *location_region = location["region"];

	JsonObject current = doc["current"];

	const char *current_last_updated = current["last_updated"];
	float current_temp = current["temp_c"];
	int current_humidity = current["humidity"];

	Weather weather = {location_region, current_temp, current_humidity, current_last_updated};

	return weather;
}
