//DO NOT REWRITING
int IBI;
void serialEvent(Serial port) {
  try {
    String inData = port.readStringUntil('\n');
    inData = trim(inData);                 // cut off white space (carriage return)

    if (inData.charAt(0) == 'S') {           // leading 'S' means Pulse Sensor data packet
      inData = inData.substring(1);        // cut off the leading 'S'
      Signal = int(inData);                // convert the string to usable int
    }
    if (inData.charAt(0) == 'B') {          // leading 'B' for BPM data
      inData = inData.substring(1);        // cut off the leading 'B'
      BPM = int(inData);                   // convert the string to usable int
      beat = true;                         // set beat flag to advance heart rate graph
      heart = 20;                          // begin heart image 'swell' timer
      getValence();
    }
    if (inData.charAt(0) == 'Q') {            // leading 'Q' means IBI data
      inData = inData.substring(1);        // cut off the leading 'Q'
      IBI = int(inData);                   // convert the string to usable int
    }
  } 
  catch(Exception e) {
    println(e.toString());
  }
}// END OF SERIAL EVENT



















































int[] XX_List = new int[31];
int XX_count = 0;
double XX_Valence = -1;
void getValence() {
  XX_count++;
  if(XX_count <30){
    XX_List[XX_count] = IBI;
  }else{
    for (int i = 0; i < 31; i++) {
        if (i == 30) {
          XX_List[i] = IBI;
        } else {
          XX_List[i] = XX_List[i + 1];
        }
      }
      double cal = 0;
      for (int i = 0; i < 30; i++) {
        if (abs(XX_List[i] - XX_List[i + 1]) > 50) {
          cal ++;
        }
      }
      cal = (cal / 30) * 100;
      XX_Valence =cal;
      Emotion = cal;
  }
  
}
