/* autogenerated by Processing revision 1283 on 2022-06-16 */
import processing.core.*;
import processing.data.*;
import processing.event.*;
import processing.opengl.*;

import processing.serial.*;
import cc.arduino.*;

import java.util.HashMap;
import java.util.ArrayList;
import java.io.File;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

public class sketch___1_2 extends PApplet {




Arduino arduino;
int input0 = 0;
int velocityX;
float x;

 public void setup(){
  /* size commented out by preprocessor */;
  arduino = new Arduino(this, "COM4", 57600);
  arduino.pinMode(input0, Arduino.INPUT);
  frameRate(20);
}

 public void draw(){
  background(0);
  fill(255);
  int analog0 = arduino.analogRead(input0);
  print(analog0);
  text("input0 = " + analog0, 10, 20);
  float velocityX = map(analog0, 0, 1024, 0, 10);
  if(x<=10){
    x=10;
  }
  else if(x>=width-10){
    x=width-10;
  }
  else{
    x += velocityX-5;
  }
  fill(255, 255, 50);
  ellipse(x, height/2, 20, 20);
}


  public void settings() { size(640, 480); }

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "sketch___1_2" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}