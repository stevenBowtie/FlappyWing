//Inputs
byte upIN=A0;
byte downIN=A1;
byte sensitivity=75;
byte currentIN=A2;

//Outputs
byte up=2;
byte flap=4;
byte flapPin=6;
byte current_limit=500;

//State
boolean dirUP;
unsigned long time_diff=0;
unsigned long last=0;
unsigned long duration=0;
unsigned long time_limit=2800;
boolean bootup=1;

void setup(){
  Serial.begin(9600);
  pinMode(upIN, INPUT_PULLUP); //Up switch
  pinMode(downIN, INPUT_PULLUP); //Down switch
  for(int x=2;x<7;x++){
    pinMode(x,OUTPUT);
  }
  pinMode(13,OUTPUT);

}

void loop(){
  if(millis()<10000){duration=500; digitalWrite(13,1);}
  else if(bootup){duration=0; bootup=0;digitalWrite(13,0);}
  if(analogRead(upIN)<sensitivity && check_time(1)){
    digitalWrite(up,dirUP);
    digitalWrite(up+1,!dirUP);
    check_current();
  }
 else if(analogRead(downIN)<sensitivity && check_time(0)){
    digitalWrite(up,!dirUP);
    digitalWrite(up+1,dirUP);
    check_current();
  }
  else{
    digitalWrite(up,1);
    digitalWrite(up+1,1);
    delay(500);
    digitalWrite(up,0);
    digitalWrite(up+1,0);
  }
}

void check_current(){
  if(analogRead(currentIN)>current_limit){
    delay(200);
    if(analogRead(currentIN)>current_limit){
      digitalWrite(up,0);
      digitalWrite(up+1,0);
      duration=0;
      Serial.println(analogRead(currentIN));
      delay(1000);
    }
  }
}

boolean check_time(boolean count_dir){
  if(count_dir){duration=min(duration++,time_limit);}
  else{duration=max(3,duration--);}
  if(duration==time_limit && count_dir){
    digitalWrite(up,0);
    digitalWrite(up+1,0);
    delay(1000); 
    return 0;
  }
  if(duration<4 && !count_dir){
    digitalWrite(up,0);
    digitalWrite(up+1,0);
    delay(1000); 
    return 0;
  }
  return 1;    
}
  
