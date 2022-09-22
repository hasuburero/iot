int potpin = 0;
int val = 0;
int buzzer = 12;


void setup() {
    Serial.begin(115200);
}

int start =0;

void loop() {
    val = analogRead(potpin);
    //tone(buzzer, start+((double)val/1023*523), 300);
    delay(10);
    Serial.println(val);
}
