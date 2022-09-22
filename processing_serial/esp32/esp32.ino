int count1 = 0;
int count2 = 0;

volatile SemaphoreHandle_t timerSemaphore;
hw_timer_t *timer1 = NULL;	//タイマー管理用構造体のポインター
portMUX_TYPE timerMUX = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer1()
{
	portENTER_CRITICAL_ISR(&timerMUX);	//排他制御．ほかの処理が使っていた場合，待機する. 
	xSemaphoreGiveFromISR(timerSemaphore, NULL);	//セマフォに許可を与える．
	portEXIT_CRITICAL_ISR(&timerMUX);
}

void setup() {
	Serial.begin(115200);
	timerSemaphore = xSemaphoreCreateBinary();
	timer1 = timerBegin(0, 80, true);	//使用タイマーの指定と初期化
	timerAttachInterrupt(timer1, &onTimer1, true);	//割り込み関数の設定
	timerAlarmWrite(timer1, 1000000, true);	//タイマー動作間隔の指定
	timerAlarmEnable(timer1);	//タイマーの有効化
}

void loop() {
	if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
		String str1, str2;
		str1 = count1;
		str2 = count2;
		Serial.println(str1 + "," + str2);
		++count1;
		count2 += 2;
	}
}
