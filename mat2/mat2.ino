#include<BleKeyboard.h>

#define pin1 27
#define pin2 14
#define pin3 12
#define pin4 13
#define num 4

BleKeyboard bkey("esp keyboard");

typedef struct Matfunc{
	int timer;
	int state = HIGH;
	int pin;
	char s;
}matfunc;

matfunc mat[num];

void setup() {
	Serial.begin(115200);
	pinMode(pin1, INPUT_PULLUP);
	pinMode(pin2, INPUT_PULLUP);
	pinMode(pin3, INPUT_PULLUP);
	pinMode(pin4, INPUT_PULLUP);

	for(int i=0; i<num; ++i){
		mat[i].timer = millis();
	}
	mat[0].pin = pin1;
	mat[1].pin = pin2;
	mat[2].pin = pin3;
	mat[3].pin = pin4;
	mat[0].s = 's';
	mat[1].s = 'f';
	mat[2].s = 'j';
	mat[3].s = 'l';

	bkey.begin();
}

void loop() {
	for(int i=0; i<num; ++i){
		if(digitalRead(mat[i].pin) == LOW){
			Serial.println("LOW");
			if(mat[i].state == HIGH){
				if(millis() - mat[i].timer > 100){
					mat[i].timer = millis();
					mat[i].state = LOW;
					if(bkey.isConnected()){
						Serial.println("press");
						bkey.press(mat[i].s);
						//bkey.print("a");
						//bkey.write(0x04);
						delay(10);
					}
				}
			}
		}
		else{
			if(mat[i].state == LOW){
				if(millis() - mat[i].timer > 100){
					mat[i].state = HIGH;
					Serial.println("release");
					bkey.release(mat[i].s);
				}
			}
		}
	}
}
