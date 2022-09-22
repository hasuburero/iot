#define button 12
#define buzzer 8
#define potpin 0

void setup() {
		Serial.begin(115200);
		pinMode(button, INPUT);
    pinMode(buzzer, OUTPUT);
}

int time = 2;
int swit;
int val = 0;

void loop() {
  swit=digitalRead(button);
  val = analogRead(potpin);
  Serial.println(val);
  if(swit){
	  for(int i=0; i<10; ++i){
		  digitalWrite(buzzer, HIGH);
		  delay(time=(double)val/1023*10);
		  digitalWrite(buzzer, LOW);
		  delay(time);
      Serial.println("button_on");
      Serial.println(swit);
	  }
  }
  delay(1);

}
