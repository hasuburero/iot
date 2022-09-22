import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int input0=0;
float velocity;
float x;
float y;
float angle;

void setup(){
	size(900, 600);
	arduino = new Arduino(this, "COM3", 57600);
	arduino.pinMode(input0, Arduino.INPUT);
	frameRate(60);
	angle = (float)(Math.PI/4);
}

void draw(){
	background(0);
	fill(255);
	int analog0 = arduino.analogRead(input0);
	//print(analog0);
	//text("input0 = " + analog0, 10, 20);

	velocity = map(analog0, 0, 1024, 0, 30);
	x += velocity*Math.cos(angle);
	y += velocity*Math.sin(angle);
	if(x<10){
		x=10;
		angle = (float)(Math.PI-angle);
	}
	else if(x>width-1-10){
		x=width-1-10;
		angle = (float)(Math.PI-angle);
	}
	if(y<10){
		y=10;
		angle = -angle;
	}
	else if(y>height-1-10){
		y=height-1-10;
		angle = -angle;
	}
	fill(255, 255, 50);
	ellipse(x, y, 20, 20);
	text("angle=" + angle/Math.PI, 10, 20);
}
