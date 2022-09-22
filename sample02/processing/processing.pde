import processing.serial.*;
Serial port;

int count;
String comPort = "COM3";
String[] data;

void setup(){
	try{
		port = new Serial(this, comPort, 115200);
		delay(1000);
		port.clear();
		port.bufferUntil('\n');
	}
	catch(Exception e){
	}

}


void draw(){
	print(getTime() + "  ");
	for(int i=0; i<data.length; ++i){
		print(data[i] + ",");
	}
	println("");
	delay(1000);
}

void keyPressed(){
	if(key == 'a'){
		print("exit");
		exit();
	}
}

String getTime(){
	int s = second();
	int m = minute();
	int h = hour();
	return (h + ":" + m + ":" + s);
}
