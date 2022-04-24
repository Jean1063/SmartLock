/*
    Smartlock
    v1.0  21/03/2020
    Jean Bénard
 */
 
// Attribution des pins
int led = 8;
int interlo = 6;
int interul = 7;

// Variables globales
int pas = 0;
int etat = HIGH;
int etatprecedent = HIGH;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(interlo, INPUT); 
  pinMode(interul, INPUT); 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,pas,current");  
}


// the loop routine runs over and over again forever:
void loop() {
  
  readinter();
  blinkled(pas);
  
  Serial.print(etatprecedent);
  Serial.print(" ");
  Serial.println(etat);
  
  commandemoteur();
  printcurrent(pas);
  
  pas += 1;
  if (pas == 900 - 1) {
    pas = 0;
  }
  delay(1);
  //Serial.println("ROW,SET,2");
}

int blinkled(int pas) {
  int on;
  on = pas % 300;
  if (on == 0 && etat == HIGH) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else if (on == 100) {
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
}


int readinter() {
  etat = digitalRead(interlo);
}

int printcurrent(int pas) {
  if ((pas % 10) == 0) {
    // read the input on analog pin 0:
    int sensorValue1 = analogRead(A0);
    int sensorValue2 = analogRead(A0);
    int sensorValue3 = analogRead(A0);
    int sensorValue = (sensorValue1 + sensorValue2 + sensorValue3) / 3.0;
    // print out the value you read:
    //Serial.println(sensorValue/1.023);
    //Serial.print("DATA,TIME,"); 
    //Serial.print(pas); Serial.print(","); 
    //Serial.println(sensorValue/1.023);
  }
  return 0;
}

int commandemoteur() {
  if (etatprecedent == HIGH && etat == LOW) {
    // Deverrouillage
    
    etatprecedent = LOW;
  } else if (etatprecedent == LOW && etat == HIGH) {
    // Verouillage
    
    etatprecedent = HIGH;
  }
}

