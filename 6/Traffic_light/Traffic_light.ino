#define rPin 13
#define yPin 12
#define gPin 8

void setup() {
	Serial.begin(115200);
	pinMode(rPin, OUTPUT);
	pinMode(yPin, OUTPUT);
	pinMode(gPin, OUTPUT);
}

void loop() {
	digitalWrite(rPin, HIGH);
	delay(1000);
	digitalWrite(rPin, LOW);
	digitalWrite(yPin, HIGH);
	delay(200);
	digitalWrite(yPin, LOW);
	digitalWrite(gPin, HIGH);
	delay(1000);
	digitalWrite(gPin, LOW);
}
