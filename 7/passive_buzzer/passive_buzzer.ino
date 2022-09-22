#define button 12
#define buzzer 8
#define potpin 0

void setup() {
    Serial.begin(115200);
    pinMode(button, INPUT);
    pinMode(buzzer, OUTPUT);
}

int time = 100;
int swit;
int val = 0;

void loop() {
  swit=digitalRead(button);
  val = analogRead(potpin);
  Serial.println(val);
  if(swit){
	  tone(buzzer, (double)val/1023*523, time);
	  delay(time);
      Serial.println("button_on");
      Serial.println(swit);
  }

}
