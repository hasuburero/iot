int sec = 0;
int s = 0;

void setup() {
	Serial.begin(115200);
}

void loop() {
	if((s = millis()) > sec){
		sec = s;
		Serial.println(s);
	}
	else{
		Serial.println(sec);
	}
}
