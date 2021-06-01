// Needed for SmartCart

#include <LCD.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal.h>
LiquidCrystal_SR lcd(12, 13, 8); 
            //  DATA CLOCK LATCH

//SH_CP->CLOCK->13
//ST_CP->LATCH->8
//DS->DATA->12

int totalPrice = 0;
int wrongCount = 0;
int multiplePrintPrice = 0;
int selected = 0;

int btnLifeboy = 6;
int ledLifeboy = 5;
int btnClemon = 7;
int ledClemon = 9;
int btnMarker = 11;
int ledMarker = 4;

int redLed = 3;

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
 pinMode(ledMarker, OUTPUT);
 pinMode(redLed, OUTPUT);
 pinMode(ledLifeboy, OUTPUT);
 pinMode(btnLifeboy, INPUT);
 pinMode(ledClemon, OUTPUT);
 pinMode(btnClemon, INPUT);
 pinMode(btnMarker, INPUT);

 lcd.begin(16, 2); // set up the LCD's number of columns and rows: 
 //lcd.clear(); // clear the screen
 
 Serial.begin(9600); // Default connection rate for my BT module
}
 
void loop() {
  //digitalWrite(A0, HIGH);

  //LCD welcome message
  if(selected == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome To");
    lcd.setCursor(0, 1);
    lcd.print("Our SmartCart");
    delay(1000);
  }
  
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You selected: ");
    lcd.setCursor(0, 1);
    lcd.print("Lifeboy (Soup)");
    delay(1000);
    selected = 1;
    multiplePrintPrice = 0;
  }

  if(btnStateClemon == 1 && printClemon ==0){
    Serial.println("You have chosen Clemon");
    completeCode = "";
    printClemon = 1;
    digitalWrite(ledClemon, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You selected: ");
    lcd.setCursor(0, 1);
    lcd.print("Clemon (250ml)");
    delay(1000);
    selected = 1;
    multiplePrintPrice = 0;
  }

  if(btnStateMarker == 1 && printMarker ==0){
    Serial.println("You have chosen Luxo Marker (Black)");
    completeCode = "";
    printMarker = 1;
    digitalWrite(ledMarker, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You selected: ");
    lcd.setCursor(0, 1);
    lcd.print("Luxo Marker");
    delay(1000);
    selected = 1;
    multiplePrintPrice = 0;
  }

  //LED on until correct barcode scanned

  
  int ledStateLifeboy = digitalRead(ledLifeboy);
  int ledStateClemon = digitalRead(ledClemon);
  int ledStateMarker = digitalRead(ledMarker);
  //Serial.println(ledStateMarker);


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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lifeboy - 38tk");
            delay(2000);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Clemon - 25tk");
            delay(2000);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Luxo Marker - 12tk");
            delay(3000);
            lcd.setCursor(16, 0);
            lcd.autoscroll();
            for (int i = 0; i < 2; i++) {
              char cA[] = {'t','k'};
              lcd.print(cA[i]);
              delay(500);
            }
            lcd.noAutoscroll();
            delay(2000);
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(ledMarker, LOW);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lifeboy - 38tk");
            delay(2000);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Clemon - 25tk");
            delay(2000);
            multiplePrintClemon = 0;
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
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lifeboy - 38tk");
            delay(2000);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Luxo Marker - 12tk");
            delay(3000);
            lcd.setCursor(16, 0);
            lcd.autoscroll();
            for (int i = 0; i < 2; i++) {
              char cA[] = {'t','k'};
              lcd.print(cA[i]);
              delay(500);
            }
            lcd.noAutoscroll();
            delay(2000);
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(ledMarker, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
       }
       else if(completeCode.equals("184716000445")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Clemon - 25tk");
            delay(2000);
            multiplePrintClemon = 0;
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Luxo Marker - 12tk");
            delay(3000);
            lcd.setCursor(16, 0);
            lcd.autoscroll();
            for (int i = 0; i < 2; i++) {
              char cA[] = {'t','k'};
              lcd.print(cA[i]);
              delay(500);
            }
            lcd.noAutoscroll();
            delay(2000);
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(ledMarker, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
       }
       else if(completeCode.equals("8941100649329")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lifeboy - 38tk");
            delay(2000);
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
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("8901069917570")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Clemon - 25tk");
            delay(2000);
            multiplePrintClemon = 0;
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
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("8901069917570")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Luxo Marker - 12tk");
            delay(3000);
            lcd.setCursor(16, 0);
            lcd.autoscroll();
            for (int i = 0; i < 2; i++) {
              char cA[] = {'t','k'};
              lcd.print(cA[i]);
              delay(500);
            }
            lcd.noAutoscroll();
            delay(2000);
            multiplePrintMarker = 0;
            completeCode = "";
            digitalWrite(ledMarker, LOW);
            Serial.println("LED off. Your Item has been added to the cart!");
            printMarker = 0;
            totalPrice = totalPrice + 12;
          }
        }
       else if(completeCode.equals("8941100649329")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
          completeCode = "";
       }
       else if(completeCode.equals("184716000445")){
          Serial.println("Wrong Item Scanned!");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong item!");
          delay(2000);
          wrongCount++;
          digitalWrite(redLed, HIGH);
          completeCode = "";
       }
    }
  }
  else{
    //Serial.println("LED OFF.");
  }

  if(ledStateLifeboy==0 && ledStateClemon==0 && ledStateMarker==0){
    digitalWrite(redLed, LOW);
    if(selected==1 && multiplePrintPrice==0){
      Serial.print("Total Price: ");
      Serial.print(totalPrice);
      Serial.println("tk");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price: ");
      lcd.setCursor(0, 1);
      lcd.print(totalPrice);
      lcd.setCursor(3, 1);
      lcd.print("tk");
      totalPrice = 0;
      multiplePrintPrice = 1;
    }
  }
}
