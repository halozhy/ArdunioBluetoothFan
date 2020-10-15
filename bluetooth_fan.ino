#include<string.h>
int rightsensor = 6;
int leftsensor = 5;
int IN1=8;   
int IN2=9;   
int IN3=10;  
int IN4=11;  
bool lfrun=0;
bool rfrun=0;
bool waiterr=0;
bool waiterl=0;
bool bluemd=0;
bool sensormd=1;
bool mixmd=0;

char c;
String blue="bluemode";
String mix="mixmode";
String sensor="sensormode";
//String leftrun="";
void setup() {  
  pinMode(6, INPUT);  
  pinMode(5, INPUT); 
  pinMode(8, OUTPUT);  
  pinMode(9,OUTPUT); 
  pinMode(10, OUTPUT);  
  pinMode(11, OUTPUT); 
  Serial.begin(9600);  
}  

void leftfanstop(){
  //stop 停止  
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,LOW);    
}
void rightfanstop(){
  //stop 停止  
  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,LOW);    
}
void leftfanrun(){     
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW); 
}
void rightfanrun(){     
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW); 
}


void leftfan(){
  if(digitalRead(leftsensor)==0){
    waiterl=1;
  }
  if(digitalRead(leftsensor)==1&&waiterl==1){
    
    if(lfrun==0){
      leftfanrun();
      lfrun=1;
      waiterl=0;
    }
    else if(lfrun==1){
      leftfanstop();
      lfrun=0;
      waiterl=0;
    }
  }
}

void rightfan(){
  if(digitalRead(rightsensor)==0){
    waiterr=1;
  }
  if(digitalRead(rightsensor)==1&&waiterr==1){
    
    if(rfrun==0){
      rightfanrun();
      rfrun=1;
      waiterr=0;
    }
    else if(rfrun==1){
      rightfanstop();
      rfrun=0;
      waiterr=0;
    }
    
  }
}

int cmp(String a,String b){
  int lena=a.length();
  int lenb=b.length();
  int i;
  int res=0;
  for(i=0;i<lenb;i++){
    if(a[i]!=b[i]){
      res=1;
      break;
    }
  }
  return res;
}


void loop(){

  c=Serial.read();
//  Serial.println(cmp(c,blue));
//  Serial.println(c);
  
  if(c=='b'){
    sensormd=0;bluemd=1;mixmd=0;
    
  }
  if(c=='m'){
    sensormd=0;bluemd=0;mixmd=1;
  }
  if(c=='s'){
    sensormd=1;bluemd=0;mixmd=0;
  }
  if(sensormd==1){
    leftfan();
    rightfan();
    //Serial.println("sensormd");
  }
  if(bluemd==1){
    if(c=='1'){
      leftfanrun();
    }
    if(c=='2'){
      leftfanstop();
    }
    if(c=='3'){
      rightfanrun();
    }
    if(c=='4'){
      rightfanstop();
    }
  }
  if(mixmd==1){
    if(c=='1'){
      leftfanrun();
      lfrun=1;
    }
    if(c=='2'){
      leftfanstop();
      lfrun=0;
    }
    if(c=='3'){
      rightfanrun();
      rfrun=1;
    }
    if(c=='4'){
      rightfanstop();
      rfrun=0;
    }
    leftfan();
    rightfan();
  }
  

  
}  
