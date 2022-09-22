import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int input0=0;
int input1=1;
float velocity = 0;
float angle = 0;
float g = 9.8;
float i = 0.1;

void setup(){
	size(1200, 900);
	arduino = new Arduino(this, "COM3", 57600);
	arduino.pinMode(input0, Arduino.INPUT);
	arduino.pinMode(input1, Arduino.INPUT);
	frameRate(60);
}

void draw(){
	background(0);
	fill(255);
	int analog0 = arduino.analogRead(input0);
	int analog1 = arduino.analogRead(input1);
	float x = 10;
	float y = height-10;

	velocity = map(analog0, 0, 1024, 0, 300);
	angle = map(analog1, 0, 1024, (float)Math.PI*3/2, (float)Math.PI*2);
	angle = (float)Math.PI*7*2 - angle;


	text("angle = " + angle, 10, 10);
	text("velocity = " + velocity, 10, 20);

	float velocityx = velocity*(float)Math.cos(angle);
	float velocityy = -velocity*(float)Math.sin(angle); 
	text("velocityx = " + velocityx, 10, 30);
	text("velocityy = " + velocityy, 10, 40);

	ellipse(x, y, 20, 20);

	int j=0;
	while(true){
		x += velocityx*i;
		y += velocityy*i+g*i*i/2;
		velocityy = velocityy + g*i;
		if(x>width-1-10){
			velocityx = -velocityx;
			x = width-1-10;
		}
		else if(x<10){
			velocityx = -velocityx;
			x = 10;
		}
		if(y>height-1-10){
			velocityy = -velocityy*4/5;
			y = height-1-10;
		}
		else if(y<10){
			velocityy = -velocityy*4/5;
			y = 10;
		}
		if(j==4){
			ellipse(x, y, 20, 20);
			j=0;
		}
		else{
			++j;
		}
		if(velocityy >= -5 && velocityy <= 5 && y >= height-1-10-2){
			break;
		}
	}
}
