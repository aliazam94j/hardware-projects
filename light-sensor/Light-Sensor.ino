int SensorPin = A2;
int value = 0;
int ledstate = 0;
int led = 9;
int buttonpin = 2;
int buttonNew;
int buttonOld =1;
int brightness;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(buttonpin,INPUT_PULLUP);
}

void loop() {
  
  buttonNew = digitalRead(buttonpin);
  value = analogRead(SensorPin);
  Serial.print(buttonNew); 
  Serial.print("|");
  Serial.println(value,DEC);
  delay(250);
  if(buttonOld == 0 && buttonNew == 1){
    if(ledstate == 0){
      ledstate = 1;
    }else{
      ledstate = 0;
}
  }
  buttonOld=buttonNew;

  if(ledstate == 1){
    brightness = map(value,0,16,255,0);
    analogWrite(led,brightness);
  }else{
    analogWrite(led,LOW);
  }
}

