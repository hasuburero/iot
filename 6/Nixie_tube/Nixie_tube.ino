int a=7;
int b=6;
int c=5;
int d=11;
int e=10;
int f=8;
int g=9;
int dp=4;
int count=0;

void digital_1(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_2(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_3(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_4(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_5(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(a, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_6(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(a, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(dp, HIGH);
}

void digital_7(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, LOW);
	}
	digitalWrite(dp, HIGH);
	for(j=5; j<=8; ++j){
		digitalWrite(j, HIGH);
	}
}

void digital_8(void)
{
	unsigned char j;
	for(j=4; j<=11; ++j){
		digitalWrite(j, HIGH);
	}
}

void digital_9(void)
{
	unsigned char j;
	for(j=4; j<=9; ++j){
		digitalWrite(j, HIGH);
	}
	digitalWrite(d, HIGH);
	digitalWrite(e, LOW);
}

void setup() {
  Serial.begin(115200);
	int i;
	for(i=4; i<=11; ++i){
		pinMode(i, OUTPUT);
	}
}

void loop() {
	char str[20];
  sprintf(str, "%2d ", count);
  strcat(str, "Hello world!!");
	while(1){
    Serial.println(str);
		digital_1();
		delay(1000);
		digital_2();
		delay(1000);
		digital_3();
		delay(1000);
		digital_4();
		delay(1000);
		digital_5();
		delay(1000);
		digital_6();
		delay(1000);
		digital_7();
		delay(1000);
		digital_8();
		delay(1000);
		digital_9();
		delay(1000);
	}
}
