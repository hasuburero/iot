import processing.serial.*;

Serial port1;
Serial port2;

String comPort1 = "COM3";
String comPort2 = "COM4";
String[] data;
int width = 1000;
int height = 700;

void setup()
{
	//fullScreen();
	size(1000, 700);
	try{
		port1 = new Serial(this, comPort1, 115200);
    port2 = new Serial(this, comPort2, 115200); 
		delay(1000);
		port1.clear();
		port1.bufferUntil('\n');
    port2.clear();
    port2.bufferUntil('\n');
	}
	catch(Exception e){
	}

	background(0, 0, 0);
	strokeWeight(1);	//幅
	stroke(0, 100, 0);	//色
	line(100, 100, 200, 200);
	textSize(20);
	text("Hello world", 0, 20);

	strokeWeight(5);
	line(50, height-50, width-50, height-50);

	//for(double i=0; i<9000; ++i){
		//line(i/10-450+500, (i/10-450)(i/10-450)/450+500

}

void draw()
{
	delay(1000);
}

String getTime()
{
	int s = second();
	int m = minute();
	int h = hour();
	return (h + ":" + m + ":" + s);
}
