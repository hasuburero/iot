#define pin 33
#define ledpin 27

volatile int state = 0;

void setup() {
	Serial.begin(115200);
	pinMode(pin, INPUT_PULLUP);
	pinMode(ledpin, OUTPUT);
	attachInterrupt(pin, switchMode, FALLING);
}

void loop() {
	if(state%3 == 0){
		digitalWrite(ledpin, LOW);
	}
	else if(state%3 == 1){
		digitalWrite(ledpin, HIGH);
	}
	else{
		digitalWrite(ledpin, LOW);
		delay(500);
		digitalWrite(ledpin, HIGH);
		delay(500);
	}
}

void switchMode()
{
	Serial.println("interrupted!!");
	delay(200);
	state++; 
}
