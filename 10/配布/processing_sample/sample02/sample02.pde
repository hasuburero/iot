
import processing.serial.*;  
Serial port;

int Signal;      
int BPM;        
double Emotion;     
int heart = 0;   
boolean beat = false; 
String comPort = "COM4";

void setup() {
  try {
    port = new Serial(this, comPort, 115200); 
    delay(1000);
    port.clear(); 
    port.bufferUntil('\n');  
  }
  catch(Exception e) {
  }
}



void draw() {
  println("Signal :" + Signal);
  println("BPM : " +BPM);                    
  println("Emotion :" + Emotion);
  println("************");
  delay(20);
}  //end of draw loop
