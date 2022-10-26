#include<BleKeyboard.h>

BleKeyboard bKey("esp keyboard");

void setup() {
	Serial.begin(115200);
	bKey.begin();

	pinMode();
}

void loop() {
	if(bKey.isConnected()){
		bKey.print("");
		bKey.write(KEY_RETURN);
	}
}
