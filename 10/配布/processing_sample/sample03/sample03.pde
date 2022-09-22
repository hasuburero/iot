
PrintWriter output;
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
  output = createWriter("3/output8.csv");
  output.println("Time,Signal,BPM,Emotion"); //Header of the csv file
  output.flush();
}



void draw() {
  output.print(getTime() + ",");
  output.print(Signal + ",");
  output.print(BPM + ",");                    
  output.println(Emotion);
  print(getTime() + ",");
  print(Signal + ",");
  print(BPM + ",");                    
  println(Emotion);
  // Add code to flush values.
  
  
  delay(1000);
}
//If "a" key is pressed the process stops and the writing of the csv file is completed.
void keyPressed() { 
  if (key == 'a') {
    output.flush();
    output.close(); 
    exit();
  }
}

String getTime() {
  int s = second(); 
  int m = minute();  
  int h = hour();    
  return (h + ":" + m + ":" + s);
}
