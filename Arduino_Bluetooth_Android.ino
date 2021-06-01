// include the library code:
//#include

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char inbyte;    //Setting a char variable as inbyte
int LED = 13;   //LED on pin 13

void setup(){
    // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
  digitalWrite(LED, LOW);
  // initialize the LED pin as an output
  pinMode(LED, OUTPUT);

}

void loop()
{
  // When a character arrives on the serial port this will be true
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);

    //store the first character in var inbyte
    inbyte = Serial.read();
//    if( inbyte == '1' ) function1(); //if the byte is an ASCII 0 execute function 1
//    if( inbyte == '2' ) function2(); //if the byte is an ASCII 9 execute function 2
    Serial.println(inbyte);

    //if it is * then we know to expect text input from Android
    if (inbyte == '*')
    {
      //clear lcd screen
      //lcd.clear();
      // read all the available characters
      while (Serial.available() > 0)
      {
        // display each character to the LCD
        //lcd.write(Serial.read());
        Serial.println(Serial.read());
      }
    }
  }
}

void function1()
{
  //Enter what you want the command to initiate (e.g LED, Servo etc)
  digitalWrite(LED, HIGH);
  //lcd.clear();
  //lcd.write("Function 1");
  Serial.println("Function 1");
}

void function2()
{
  //Enter what you want the command to initiate (e.g LED, Servo etc)
  digitalWrite(LED, LOW);
  //lcd.clear();
  //lcd.write("Function 2");
  Serial.println("Function 2");
}
