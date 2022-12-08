String getTime(){
    int s = second();
    int m = minute();
    int h = hour();
    return (h + ":" + m + ":" + s);
}

void remake(){
  println("new file");
  output.flush();
  output.close();
  output = createWriter("data/" + t1.str + ".csv");
  output.println("Time,Emotion,Temperature,Humidity,discomfort");
  output.flush();
}

void showgrid(){
    strokeWeight(1);
    for(int i=10; i<width; i+=10){
        if(i%100==0){
            stroke(255, 0, 255);
        }
        else{
            stroke(255, 255, 255);
        }

        line(i, 0, i, height);
    }
    for(int i=10; i<height; i+=10){
        if(i%100==0){
            stroke(255, 0, 255);
        }
        else{
            stroke(255, 255, 255);
        }

        line(0, i, width, i);
    }
}
