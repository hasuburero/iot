// Bezier patch By Maritus Watz:
// http://www.openprocessing.org/sketch/57709
// Normal calculation added by Andres Colubri
// Direct port of sample code by Paul Bourke.
// Original code: http://paulbourke.net/geometry/bezier/

import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

int ni=4, nj=5, RESI=ni*10, RESJ=nj*10;
PVector outp[][], inp[][];
PVector normp[][]; 
boolean autoNormals = false; 

int input0=0;
int input1=1;

 
void setup() {
  size(1024, 768, P3D);
  arduino = new Arduino(this, "COM3", 57600);
  arduino.pinMode(input0, Arduino.INPUT);
  arduino.pinMode(input1, Arduino.INPUT);
  frameRate(60);
  build();
}

float x = 0;
float y = 0;
 
void draw() {
  background(255);
  int analog0=arduino.analogRead(input0);
  int analog1=arduino.analogRead(input1);
  text("input0=" + analog0, 10, 20);
  text("input1=" + analog1, 20, 40);
  translate(width/2,height/2);
  lights();
  scale(0.9);
  rotateY(y += map(analog0,0,1024,-PI/10,PI/10));
  rotateX(x += map(analog1,0,1024,-PI/10,PI/10));
   
  noStroke();
  fill(255);
  for(int i=0; i<RESI-1; i++) {
    beginShape(QUAD_STRIP);
    for(int j=0; j<RESJ; j++) {
      if (!autoNormals) {
        normal(normp[i][j].x, normp[i][j].y, normp[i][j].z);
      }
      vertex(outp[i][j].x,outp[i][j].y,outp[i][j].z);
      vertex(outp[i+1][j].x,outp[i+1][j].y,outp[i+1][j].z);     
    }
    endShape();
  }
}
 
void keyPressed() {
  if(key==' ') build();
  saveFrame("bezPatch.png");
}
 
void build() {
  int i, j, ki, kj;
  double mui, muj, bi, bj, dbi, dbj;
  
  outp=new PVector[RESI][RESJ];
  normp=new PVector[RESI][RESJ];
  inp=new PVector[ni+1][nj+1];
  PVector uitang = new PVector();
  PVector ujtang = new PVector();
  
  for (i=0;i<=ni;i++) {
    for (j=0;j<=nj;j++) {
      inp[i][j]=new PVector(i,j,random(-3,3));
    }
  }
  
  for (i=0;i<RESI;i++) {
    mui = i / (double)(RESI-1);
    for (j=0;j<RESJ;j++) {
      muj = j / (double)(RESJ-1);
      outp[i][j]=new PVector();
      uitang.set(0, 0, 0);
      ujtang.set(0, 0, 0);
      for (ki=0;ki<=ni;ki++) {
        bi = BezierBlend(ki, mui, ni);
        dbi = DBezierBlend(ki, mui, ni);
        for (kj=0;kj<=nj;kj++) {
          bj = BezierBlend(kj, muj, nj);
          dbj = DBezierBlend(kj, muj, nj);
          outp[i][j].x += (inp[ki][kj].x * bi * bj);
          outp[i][j].y += (inp[ki][kj].y * bi * bj);
          outp[i][j].z += (inp[ki][kj].z * bi * bj);
           
          uitang.x += (inp[ki][kj].x * dbi * bj);
          uitang.y += (inp[ki][kj].y * dbi * bj);
          uitang.z += (inp[ki][kj].z * dbi * bj);
           
          ujtang.x += (inp[ki][kj].x * bi * dbj);
          ujtang.y += (inp[ki][kj].y * bi * dbj);
          ujtang.z += (inp[ki][kj].z * bi * dbj);
        }
      }
      outp[i][j].add(new PVector(-ni/2,-nj/2,0));
      outp[i][j].mult(100);
       
      uitang.normalize();
      ujtang.normalize();
      normp[i][j] = uitang.cross(ujtang);     
    }
  }
}
 
double BezierBlend(int k, double mu, int n) {
  int nn, kn, nkn;
  double blend=1;
 
  nn = n;
  kn = k;
  nkn = n - k;
 
  while (nn >= 1) {
    blend *= nn;
    nn--;
    if (kn > 1) {
      blend /= (double)kn;
      kn--;
    }
    if (nkn > 1) {
      blend /= (double)nkn;
      nkn--;
    }
  }
  if (k > 0)
    blend *= Math.pow(mu, (double)k);
  if (n-k > 0)
    blend *= Math.pow(1-mu, (double)(n-k));
 
  return(blend);
}

double DBezierBlend(int k, double mu, int n) {
  int nn, kn, nkn;
  double dblendf = 1;
  
  nn = n;
  kn = k;
  nkn = n - k;
  
  while (nn >= 1) {
    dblendf *= nn;
    nn--;
    if (kn > 1) {
      dblendf /= (double)kn;
      kn--;
    }
    if (nkn > 1) {
      dblendf /= (double)nkn;
      nkn--;
    }
  }
   
  double fk = 1;
  double dk = 0;
  double fnk = 1;
  double dnk = 0;   
  if (k > 0) {
    fk = Math.pow(mu, (double)k);
    dk = k*Math.pow(mu, (double)k-1);
  } 
  if (n-k > 0) {
    fnk = Math.pow(1-mu, (double)(n-k));
    dnk = (k-n)*Math.pow(1-mu, (double)(n-k-1));
  }
  dblendf *= (dk * fnk + fk * dnk);
  
  return(dblendf); 
}
