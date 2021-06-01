int n = 0;
int start = 0;
int echo = 12;
int trig = 13;
int left_motor_backward = 2; 
int left_motor_forward = 3;
int right_motor_forward = 4;
int right_motor_backward = 5;
 
int totalPrice = 0;
int wrongCount = 0;
int multiplePrintPrice = 0;
int selected = 0;

int btnLifeboy = 6;
int ledLifeboy = 8;
int btnClemon = 7;
int ledClemon = 9;
int btnMarker = 11;

int printLifeboy = 0;
int printClemon = 0;
int printMarker = 0;
int multiplePrintLifeboy = 0;
int multiplePrintClemon = 0;
int multiplePrintMarker = 0;

char code;
String completeCode = "";
int count = 0;

void setup() {
 pinMode(A0, OUTPUT);
 pinMode(A1, OUTPUT);
 pinMode(ledLifeboy, OUTPUT);
 pinMode(btnLifeboy, INPUT);
 pinMode(ledClemon, OUTPUT);
 pinMode(btnClemon, INPUT);
 pinMode(btnMarker, INPUT);
 
  pinMode(A2, INPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
 
 Serial.begin(9600); // Default connection rate for my BT module
}
 
void loop() {
  //digitalWrite(A0, HIGH);
  //Pressing the input buttons
  int btnStateLifeboy = digitalRead(btnLifeboy);
  int btnStateClemon = digitalRead(btnClemon);
  int btnStateMarker = digitalRead(btnMarker);

  //only print once on screen
  if(btnStateLifeboy == 1 && printLifeboy == 0){
    Serial.println("You have chosen Lifeboy (Soup)");
    completeCode = "";
    printLifeboy = 1;
    digitalWrite(ledLifeboy, HIGH);
    selected = 1;
  }

  if(btnStateClemon == 1 && printClemon ==0){
    Serial.println("You have chosen Clemon");
    completeCode = "";
    printClemon = 1;
    digitalWrite(ledClemon, HIGH);
    selected = 1;
  }

  if(btnStateMarker == 1 && printMarker ==0){
    Serial.println("You have chosen Luxo Marker (Black)");
    completeCode = "";
    printMarker = 1;
    digitalWrite(A0, HIGH);
    selected = 1;
  }

  //LED on until correct barcode scanned

  
  int ledStateLifeboy = digitalRead(ledLifeboy);
  int ledStateClemon = digitalRead(ledClemon);
  int ledStateMarker = digitalRead(A0);
  //Serial.println(ledStateMarker);

  int btnStateStart = digitalRead(A2);
  if(btnStateStart==1){
    start = 1;
  }
  if(start==1){
    long distance, duration;
    
    if(n<1000){
      digitalWrite(trig, LOW);
      delay(2);
      digitalWrite(trig, HIGH);
      delay(10);
      digitalWrite(trig, LOW);
      
      duration = pulseIn(echo, HIGH);
      distance = (duration/2)/29.1;
      
    
      if (distance < 25)
      {
        digitalWrite(left_motor_forward, LOW);
        digitalWrite(right_motor_forward, HIGH);
        digitalWrite(left_motor_backward, HIGH);
        digitalWrite(right_motor_backward, LOW);
      }
    
      
      else
      {
        digitalWrite(left_motor_forward, LOW);
        digitalWrite(right_motor_forward, LOW);
        digitalWrite(left_motor_backward, HIGH);
        digitalWrite(right_motor_backward, HIGH);
      }
    
      delay(10);
      n++;
    }
    else{
      digitalWrite(left_motor_forward, LOW);
        digitalWrite(right_motor_forward, LOW);
        digitalWrite(left_motor_backward, LOW);
        digitalWrite(right_motor_backward, LOW);
        start = 0;
        n = 0;
          //Lifeboy and Clemon and Marker
  if(ledStateLifeboy==1 && ledStateClemon==1 && ledStateMarker==1){
    //Serial.println("ALL THREE!");
    //Serial.println(btnStateLifeboy);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("8941100649329")){
          if(multiplePrintLifeboy==0){
            Serial.println("Lifeboy (Soup) --------------------------------- 38tk");
            multiplePrintLifeboy = 0;
            completeCode = "";
            digitalWrite(ledLifeboy, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printLifeboy = 0;
            totalPrice = totalPrice + 38;
          }
       }
       else if(completeCode.equals("184716000445")){
          if(multiplePrintClemon==0){
            Serial.println("Clemon (250ml) --------------------------------- 25tk");
            multiplePrintClemon = 0;
            completeCode = "";
            digitalWrite(ledClemon, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printClemon = 0;
            totalPrice = totalPrice + 25;
          }
       }
       else if(completeCode.equals("8901069917570")){
          if(multiplePrintMarker==0){
            Serial.println("Luxo Marker (Black) --------------------------------- 12tk");
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(A0, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
       }
    }
  }

  
  //Lifeboy and Clemon
  else if(ledStateLifeboy==1 && ledStateClemon==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateLifeboy);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("8941100649329")){
          if(multiplePrintLifeboy==0){
            Serial.println("Lifeboy (Soup) --------------------------------- 38tk");
            multiplePrintLifeboy = 0;
            completeCode = "";
            digitalWrite(ledLifeboy, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printLifeboy = 0;
            totalPrice = totalPrice + 38;
          }
       }
       else if(completeCode.equals("184716000445")){
          if(multiplePrintClemon==0){
            Serial.println("Clemon (250ml) --------------------------------- 25tk");
            multiplePrintClemon = 0;
            completeCode = "";
            digitalWrite(ledClemon, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printClemon = 0;
            totalPrice = totalPrice + 25;
          }
       }
       else if(completeCode.equals("8901069917570")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }


//Lifeboy and Marker
  else if(ledStateLifeboy==1 && ledStateMarker==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateLifeboy);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("8941100649329")){
          if(multiplePrintLifeboy==0){
            Serial.println("Lifeboy (Soup) --------------------------------- 38tk");
            multiplePrintLifeboy = 0;
            completeCode = "";
            digitalWrite(ledLifeboy, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printLifeboy = 0;
            totalPrice = totalPrice + 38;
          }
       }
       else if(completeCode.equals("8901069917570")){
          if(multiplePrintMarker==0){
            Serial.println("Luxo Marker (Black) --------------------------------- 12tk");
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(A0, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
       }
       else if(completeCode.equals("184716000445")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }


  //Clemon and Marker
  else if(ledStateClemon==1 && ledStateMarker==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateLifeboy);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("184716000445")){
          if(multiplePrintClemon==0){
            Serial.println("Clemon (250ml) --------------------------------- 25tk");
            multiplePrintClemon = 0;
            completeCode = "";
            digitalWrite(ledClemon, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printClemon = 0;
            totalPrice = totalPrice + 25;
          }
       }
       else if(completeCode.equals("8901069917570")){
          if(multiplePrintMarker==0){
            Serial.println("Luxo Marker (Black) --------------------------------- 12tk");
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(A0, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
       }
       else if(completeCode.equals("8941100649329")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }

  
  //For Lifeboy Soup
  else if(ledStateLifeboy==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateLifeboy);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("8941100649329")){
          if(multiplePrintLifeboy==0){
            Serial.println("Lifeboy (Soup) --------------------------------- 38tk");
            multiplePrintLifeboy = 0;
            completeCode = "";
            digitalWrite(ledLifeboy, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printLifeboy = 0;
            totalPrice = totalPrice + 38;
          }
       }
       else if(completeCode.equals("184716000445")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("8901069917570")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }
  

  //For Clemon
  else if(ledStateClemon==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateClemon);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("184716000445")){
          if(multiplePrintClemon==0){
            Serial.println("Clemon (250ml) --------------------------------- 25tk");
            multiplePrintClemon = 0;
            completeCode = "";
            digitalWrite(ledClemon, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printClemon = 0;
            totalPrice = totalPrice + 25;
          }
       }
       else if(completeCode.equals("8941100649329")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("8901069917570")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }


  //For Marker
  else if(ledStateMarker==1){
    //Serial.println("LED ON!");
    //Serial.println(btnStateClemon);
    if(Serial.available() > 0){
     code = Serial.read();
     completeCode = completeCode+code;
     //Serial.println("code: "+code);
     //Serial.println("Complete Code: "+completeCode);
     count++;
    }
   
    if(count>=12){
        if(completeCode.equals("8901069917570")){
          if(multiplePrintMarker==0){
            Serial.println("Luxo Marker (Black) --------------------------------- 12tk");
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(A0, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
        }
       else if(completeCode.equals("8941100649329")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("184716000445")){
          Serial.println("Wrong Item Scanned!");
          wrongCount++;
          digitalWrite(A1, HIGH);
          completeCode = "";
       }
    }
  }
  else{
    //Serial.println("LED OFF.");
  }

  if(ledStateLifeboy==0 && ledStateClemon==0 && ledStateMarker==0){
    digitalWrite(A1, LOW);
    if(selected==1 && multiplePrintPrice==0){
      Serial.print("Total Price: ");
      Serial.print(totalPrice);
      Serial.println("tk");
      multiplePrintPrice = 1;
    }
  }
    }
    
    Serial.println(n);
  }
  

}
