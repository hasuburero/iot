#define pin 13

int count = 500;
void setup() {
	pinMode(pin, OUTPUT);
}

void loop() {
	digitalWrite(pin, HIGH);
	delay(500);
	digitalWrite(pin, LOW);
	delay(500);
}
