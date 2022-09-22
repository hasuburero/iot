int potpin = 0;
int ledpin = 13;
int val = 0;


void setup() {
	Serial.begin(115200);
	pinMode(ledpin, OUTPUT);
}

void loop() {
	digitalWrite(ledpin, HIGH);
	delay(50);
	digitalWrite(ledpin, LOW);
	delay(50);
	val = analogRead(potpin);
	Serial.println(val);
}
