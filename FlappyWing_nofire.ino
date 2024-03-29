//Inputs
byte upIN=A0;
byte downIN=A1;
byte sensitivity=75;
byte currentIN=A2;

//Outputs
byte up=2;
byte flap=4;
byte flapPin=6;
int current_limit=600;

//State
boolean initial_direction;
boolean current_direction;
unsigned long time_diff=0;
unsigned long last=0;
unsigned long duration=0;
unsigned long time_limit=4600;
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
  if(millis()<5000){duration=500; digitalWrite(13,1);}
  else if(bootup){duration=0; bootup=0;digitalWrite(13,0);}
  if(analogRead(upIN)<sensitivity && check_time(1)){
    current_direction=1;
    digitalWrite(up,initial_direction);
    digitalWrite(up+1,!initial_direction);
    check_current();
  }
 else if(analogRead(downIN)<sensitivity && check_time(0)){
   current_direction=0;
   digitalWrite(up,!initial_direction);
   digitalWrite(up+1,initial_direction);
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
      if(current_direction){duration=time_limit;}
      else{duration=0;}
      Serial.println(analogRead(currentIN));
      digitalWrite(13,1);
      delay(1000);
      digitalWrite(13,0);
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
  
