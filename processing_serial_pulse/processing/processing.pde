import java.util.*;
import processing.serial.*;

Table input;
PrintWriter output;
Serial port;

Button b1;
Button b2;
Button b3;
Textbox t1;
Textbox t2;

int width = 1000;
int height = 700;

String[] time;
float[] emotion, temp, humidity, dis;

int data_row, data_column;
int head = 0;
int tail = 0;
int count;
String comPort = "COM4";
String[] data;
String s;
String ofilename = "data/data5.csv";
String ifilename = "";

int mode = 0;
PFont selectfont;
PFont scalefont;
PFont linefont;

void setup(){
	size(1000, 700);
	frameRate(60);
	background(0);
	strokeWeight(1);
	fill(255, 255, 255);
	selectfont = createFont("MS Gothic", 30);
	scalefont = createFont("MS Gothic", 10);
	linefont = createFont("MS Gothic", 20);
	try{
		port = new Serial(this, comPort, 115200);
		delay(1000);
		port.clear();
		port.bufferUntil('\n');
	}
	catch(Exception e){
	}

	b1 = new Button(300, 650, 75, 40);
	b2 = new Button(600, 650, 105, 40);
	b3 = new Button(width/2-37, 650, 75, 40);
	t1 = new Textbox(415, 170, 300, 40);
	t2 = new Textbox(415, 170, 360, 40);
}

void draw(){
	switch(mode){
		case 0:
			background(0);
			//showgrid();
			fill(255, 0, 0);
			stroke(255, 255, 255);
			rect(b1.x, b1.y, b1.sizex, b1.sizey);
			rect(b2.x, b2.y, b2.sizex, b2.sizey);
			fill(255, 255, 255);
			textFont(selectfont);
			text("graph", b1.x, 30+b1.y);
			text("measure", b2.x, 30+b2.y);
			break;
		case 1:
			background(0);
			//showgrid();
			fill(255, 255, 255);
			textFont(selectfont);
			text("filename:data/", 200, 200);
			stroke(255, 255, 255);
			fill(0, 0, 0);
			rect(t2.x, t2.y, t2.sizex, t2.sizey);
			fill(255, 255, 255);
			text(t2.str, t2.x, t2.y+30);
			break;
		case 2:
			background(0);
			//showgrid();
			fill(255, 255, 255);
			textFont(selectfont);
			text("filename:data/", 200, 200);
			stroke(255, 255, 255);
			fill(0, 0, 0);
			rect(t1.x, t1.y, t1.sizex, t1.sizey);
			fill(255, 255, 255);
			text(".csv", 715, 200);
			text(t1.str, t1.x, t1.y+30);
			break;
		case 3:
			background(0);
			fill(255, 255, 255);
			textFont(selectfont);
			text("running", 450, 200);
			text("press \"a\" to close file", 325, 300);
			//showgrid();
			break;
		case 4:
			background(0);
			//showgrid();
			stroke(255, 255, 255);
			fill(255, 0, 0);
			rect(b3.x, b3.y, b3.sizex, b3.sizey);
			fill(255, 255, 255);
			textFont(selectfont);
			text("close", b3.x, 30+b3.y);
			fill(255, 255, 255);
			stroke(255, 255, 255);
			strokeWeight(1);
			textFont(scalefont);
			for(int scale=0; scale<=500; scale+=50){
				text(scale/5, 950, height-100-scale);
				line(50, height-100-scale, 950, height-100-scale);
			}
			line(950, 100, 950, height-100);
			line(50, 100, 50, height-100);
			line(50, height-100, 950, height-100);

			if(mousePressed){
				int bufh = head;
				int buft = tail;
				if(data_row < 901){
				}
				else{
					head += pmouseX - mouseX;
					tail += pmouseX - mouseX;
					if(head >= data_row){
						head = data_row-1;
						tail = data_row - 900;
					}
					if(tail < 1){
						tail = 1;
						head = 900;
					}
				}
			}

			for(int i=head, j=950, k=0; i!=tail; --i, --j, ++k){
				textFont(linefont);
				stroke(255, 0, 0);
				line(j, 600 - emotion[i]*5, j-1, 600 - emotion[i-1]*5);
				line(200, 50, 220, 50);
				text("emotion", 221, 60);

				stroke(0, 255, 0);
				line(j, 600 - temp[i]*5, j-1, 600 - temp[i-1]*5);
				line(350, 50, 370, 50);
				text("temperature", 371, 60);

				stroke(0, 0, 255);
				line(j, 600 - humidity[i]*5, j-1, 600 - humidity[i-1]*5);
				line(500, 50, 520, 50);
				text("humidity", 521, 60);

				stroke(0, 255, 255);
				line(j, 600 - dis[i]*5, j-1, 600 - dis[i-1]*5);
				line(650, 50, 670, 50);
				text("discomfort", 671, 60);

				if(k%100==0){
					textFont(scalefont);
					stroke(255, 255, 255);
					line(950-k, 600, 950-k, 100);
					text(time[i], 950-k-15, height-90);
				}
			}
			break;
	}
}

void keyPressed(){
	switch(mode){
		case 1:
			t2.addstring(key);
			if(t2.flag){
				mode = 4;
				t2.flag = false;
				input = loadTable("data/" + t2.str);
				data_row = input.getRowCount();
				data_column = input.getColumnCount();
				time = new String[data_row];
				emotion = new float[data_row];
				temp = new float[data_row];
				humidity = new float[data_row];
				dis = new float[data_row];

				for(int i=1; i<data_row; ++i){
					time[i]		= input.getString(i, 0);
					emotion[i] 	= input.getFloat(i, 1);
					temp[i]		= input.getFloat(i, 2);
					humidity[i] = input.getFloat(i, 3);
					dis[i] 		= input.getFloat(i, 4);
				}
				head = data_row-1;
				if(data_row < 901){
					tail = 1;
				}
				else{
					tail = data_row - 900;
				}
			}
			break;

		case 2:
			t1.addstring(key);
			if(t1.flag){
				mode = 3;
				println("new file");
				println(t1.str);
				output = createWriter("data/" + t1.str + ".csv");
				output.println("Time,Emotion,Temperature,Humidity,discomfort");
				output.flush();
				t1.flag = false;
			}
			break;

		case 3:
			if(key == 'a'){
				output.flush();
				output.close();
				mode = 0;
				t1.str = "";
			}
			break;
	}
}

void mousePressed(){
	switch(mode){
		case 0:
			// graph
			if(b1.x <= mouseX && mouseX <= b1.x+b1.sizex){
				if(b1.y <= mouseY && mouseY <= b1.y+b1.sizey){
					mode = 1;
				}
			}
			// measure
			if(b2.x <= mouseX && mouseX <= b2.x+b2.sizex){
				if(b2.x <= mouseY && mouseY <= b2.y+b2.sizey){
					mode = 2;
				}
			}
			break;
		case 4:
			if(b3.x <= mouseX && mouseX <= b3.x+b3.sizex){
				if(b3.y <= mouseY && mouseY <= b3.y+b3.sizey){
					mode = 0;
					t2.str = "";
				}
			}
			break;
	}
}
