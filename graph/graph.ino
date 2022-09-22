int count1 = 0;
int count2 = 0;
int count3 = 0;

void setup() 
{
	Serial.begin(115200);
}

void loop() 
{
	delay(1000);
	String str1, str2, str3;
	str1 = count1;
	str2 = count2;
	str3 = count3;
	Serial.println(str1 + "," + str2 + "," + str3);
	++count1;
	count2 += 2;
	count3 += 3;
}
