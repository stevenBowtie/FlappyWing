//Inputs
byte upIN=A0;
byte downIN=A1;
byte sensitivity=75;
byte currentIN=A2;

//Outputs
byte up=2;
byte flap=4;
byte flapPin=6;
byte current_limit=200;

//State
boolean dirUP;
unsigned long time_diff=0;
unsigned long last=0;
unsigned long duration=0;
unsigned long time_limit=6000;

void setup(){
  Serial.begin(9600);
  pinMode(upIN, INPUT_PULLUP); //Up switch
  pinMode(downIN, INPUT_PULLUP); //Down switch
  for(int x=2;x<7;x++){
    pinMode(x,OUTPUT);
  }

}

void loop(){
  if(analogRead(upIN)<sensitivity){
    digitalWrite(up,dirUP);
    digitalWrite(up+1,!dirUP);
    check_current();
    check_time();
  }
  else{
    digitalWrite(up,0);
    digitalWrite(up+1,0);
  }
}

void check_current(){
  if(analogRead(currentIN)>current_limit){
    delay(1000);
    if(analogRead(currentIN)>current_limit){
      digitalWrite(up,0);
      digitalWrite(up+1,0);
      Serial.println(analogRead(currentIN));
      delay(1000);
    }
  }
}

void check_time(){
  duration++;
  if(duration>time_limit){
    dirUP=!dirUP;
    duration=0;
    digitalWrite(up,0);
    digitalWrite(up+1,0);
    delay(1000); 
  }
}
  
