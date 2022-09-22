//set in Led’s digital IO pin control
int Led1 = 1;
int Led2 = 2;
int Led3 = 3;
int Led4 = 4;
int Led5 = 5;
int Led6 = 6;
//led lamp run the example 1 program
void style_1(void)
{
 unsigned char j;
 for(j=1;j<=6;j++)//every 200ms light up one of led lamps with 1~6 pin in turn
 { 
	 digitalWrite(j,HIGH);//light up the led lamps with j pin
	 delay(200);//delay 200ms 
 } 
 for(j=6;j>=1;j--)//every 200ms got out one of led lamps with 6~1 pin in turn
 {
	 digitalWrite(j,LOW);//go out the led lamps with j pin
	 delay(200);//delay 200ms 
 } 
}
//led lamp blink example program
void flash(void) 
{ 
 unsigned char j,k;
 for(k=0;k<=1;k++)//blink twice
 { 
	 for(j=1;j<=6;j++)//light up led lamps with 1~6 pin
	 {
	 digitalWrite(j,HIGH);//light up led lamp with j pin
	 delay(200);//delay 200ms 
	 }
	 for(j=1;j<=6;j++)//go out the led lamp with 1~6 pin
	 {
	 digitalWrite(j,LOW);//go out the led lamp with j pin
	 delay(200);//delay 200ms 
	 }
 } 
}
//led lamp run the example 2 program
void style_2(void)
{
 unsigned char j,k;   
 k=1;//set k is 1
 for(j=3;j>=1;j--)
 { 
	 digitalWrite(j,HIGH);//light up
	 digitalWrite(j+k,HIGH);//light up
	 delay(400);//delay 400ms 
	 k +=2;//k plus 2
 } 
 k=5;//set k is 5
 for(j=1;j<=3;j++)
 { 
	 digitalWrite(j,LOW);//go out
	 digitalWrite(j+k,LOW);//go out
	 delay(400);//delay 400ms 
	 k -=2;//k sub 2
 } 
}
// led lamp run the example 3 program 
void style_3(void)
{
 unsigned char j,k;//led lamp run the example 3 program
 k=5;//set k is 5
 for(j=1;j<=3;j++)
 { 
	 digitalWrite(j,HIGH);//light up
	 digitalWrite(j+k,HIGH);//light up
	 delay(400);//delay 400ms 
	 digitalWrite(j,LOW);//go out
	 digitalWrite(j+k,LOW);//go out
	 k -=2;//k sub 2
} 
 k=3;//set k is 3
 for(j=2;j>=1;j--)
 { 
	 digitalWrite(j,HIGH);//light up
	 digitalWrite(j+k,HIGH);//light up
	 delay(400);//delay 400ms 
	 digitalWrite(j,LOW);//go out
	 digitalWrite(j+k,LOW);//go out
	 k +=2;//k plus 2
 } 
}
void setup()
{
 unsigned char i;
 for(i=1;i<=6;i++)//set 1~6 pin output in turn
 pinMode(i,OUTPUT);//set i pin output
}
void loop()
{ 
 style_1();//example 1
 flash();//blink
 style_2();//example 2
 flash();//blink
 style_3();//example 3
 flash();//blink
}
