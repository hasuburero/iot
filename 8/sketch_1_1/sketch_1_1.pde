import processing.serial.*;
import cc.arduino.*;
Arduino arduino;

int input = 0;
float x;
int velocityX = 1;
int flag=0;


void setup(){
  size(400, 300);
  x = 0;
  
}

void draw(){
  background(0);
   if(flag==1){
     x-=velocityX;
   }
   else{
     x+=velocityX;
   }
   fill(255, 255, 50);
   ellipse(x, height/2, 20, 20);
   if(x>=width-10){
     flag = 1;
   }
   else if(x<=10){
     flag = 0;
   }
}
