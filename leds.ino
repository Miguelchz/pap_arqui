int detector1;
int detector2;
int detector3;
int detector4;
int detector5;
int detector6;

const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(detector1,INPUT);
  pinMode(detector2,INPUT);
  pinMode(detector3,INPUT);
  pinMode(detector4,INPUT);
  pinMode(detector5,INPUT);
  pinMode(detector6,INPUT);




  
}

void loop() {
  //int value = 0;
  detector1 = analogRead(A0);
  detector2 = analogRead(A1);
  detector3 = analogRead(A2);
  detector4 = analogRead(A3);
  detector5 = analogRead(A4);
  detector6 = analogRead(A5);
  

  //value = digitalRead(detector);
  //Serial.println (detector);

  if (detector1 > 70) {

    Serial.println ("Detectado obstaculo sensor 1");

    digitalWrite(LED1, HIGH);
  }
  else{ 
    digitalWrite(LED1, LOW);
    }
    
   if (detector2 > 70) {

    Serial.println ("Detectado obstaculo sensor 2 ");

    digitalWrite(LED2, HIGH);
  }
  else{
    digitalWrite(LED2, LOW);
    }
    if (detector3 > 70) {

    Serial.println ("Detectado obstaculo sensor 3");

    digitalWrite(LED3, HIGH);
  }
   else{
    digitalWrite(LED3, LOW);
    }
   if (detector4> 70) {

    Serial.println ("Detectado obstaculo sensor 4");

    digitalWrite(LED4, HIGH);
  }
   else{
    digitalWrite(LED4, LOW);
    }
   if (detector5 > 70) {

    Serial.println ("Detectado obstaculo sensor 5");

    digitalWrite(LED5, HIGH);
  }
   else{
    digitalWrite(LED5, LOW);
    }
    if (detector6 > 70) {

    Serial.println ("Detectado obstaculo sensor 6");

    digitalWrite(LED6, HIGH);
  }
  else {
    
   digitalWrite(LED6,LOW);

  }
    
  
  }
