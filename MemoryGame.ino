int button[5] = {-1,2, 3, 4, 5};       // The four button input pins    // the (-1) is as place holder so that  Button[1] is the firs button ;)
int ledpin[5] = {-1,8, 9, 10, 11};     // LED pins
int randomArray[100];                  // Hope no one gets more ;)

int Press(){
  while(true){ // wait until one of the buttons gets prest
    for(int x=1; x <= 4; x++){ // check all for buttons 
      if(digitalRead(button[x]) == LOW){
        while(digitalRead(button[x]) == LOW){delay(100);}// after button press wait for the button to be released again
        return x;
      }
    }
  }
}

void Output(){
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],LOW);
  }
  int Zaehler = 1;
  while(randomArray[Zaehler] != 0){// runns the Zaeler to the end of the Array while displaing the numbers
    digitalWrite(ledpin[randomArray[Zaehler]],HIGH);
    Serial.print(randomArray[Zaehler]);
    delay(500);
    digitalWrite(ledpin[randomArray[Zaehler]],LOW);
    Zaehler++;
  }
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],LOW);
  }
  Serial.println(" ");
}

void AddRandom(){
  int NewInt = random(1, 5);
  int Befor;
  int Zaehler = 1;
  while(randomArray[Zaehler] != 0){// runns the Zaeler to the end of the Array
    Zaehler ++;
  }
  Befor = Zaehler - 1;
  while(NewInt == randomArray[Befor]){NewInt=random(1, 5);}// to prevent that the random number is the same as the on befor
  randomArray[Zaehler] = NewInt; // makes the number after the last nummber random beetween 1 and 4 
}

void ClearArray(){
  for(int i = 1; i<=99; i++){
    randomArray[i]=0;
  }
}

void BlinkTrue(){
  digitalWrite(ledpin[1],HIGH);
  delay(100);
  for(int x=2; x <= 4; x++){
    digitalWrite(ledpin[x],HIGH);
    digitalWrite(ledpin[x-1],LOW);
    delay(100);
  }
  digitalWrite(ledpin[4],LOW);
  delay(500);// every led stays off
}

void BlinkFalse(){
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],HIGH);
  }  
  delay(750);// every led stays on 
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],LOW);
  }
  delay(750);// every led stays off
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],HIGH);
  }  
  delay(750);// every led stays on 
  for(int x=1; x <= 4; x++){
    digitalWrite(ledpin[x],LOW);
  }
  delay(750);// every led stays off
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  randomSeed(analogRead(0)); // to give the random some more "randomnes" ;)
  
  for(int x=1; x <= 4; x++){// Sets up of LED and Button
    pinMode(ledpin[x], OUTPUT);
    pinMode(button[x], INPUT_PULLUP);  
  }
  ClearArray();
}

void loop() {
  // put your main code here, to run repeatedly:
  AddRandom();
  Output();
  
  int Zaehler = 1;
  while(randomArray[Zaehler] != 0){// runns the Zaeler to the end of the Array
    if(randomArray[Zaehler] != Press()){BlinkFalse(); ClearArray(); break;}
    Zaehler++;
  }
  else{BlinkTrue();}
}
