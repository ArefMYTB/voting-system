#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {

  {'1', '2', '3'},

  {'4', '5', '6'},

  {'7', '8', '9'},

  {'*', '0', '#'}

};

byte rowPins[ROWS] = { 27, 28, 29, 30}; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 24, 25, 26 };    // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

int KeyCheck = 0;
int Number = 0;

void setup() {

  lcd.begin(16, 2);
  lcd.print("PLZ Vote :)");
  lcd.setCursor(0, 1);

  pinMode(32, OUTPUT);

  Wire.begin(); // join i2c bus
}

void loop() {
  char key = kpd.getKey();
  if (key != NO_KEY)
    DetectButtons(key);

}

void DetectButtons(char key) {
  lcd.clear();
  if (
    key == '0' ||
    key == '1' ||
    key == '2' ||
    key == '3' ||
    key == '4' ||
    key == '5' ||
    key == '6' ||
    key == '7' ||
    key == '8' ||
    key == '9' ) {
    if (Number == 0) {
      Number = key - '0';
      lcd.print(Number);
    } else
      lcd.print("not valid");

  }
  else if ( key == '#'){ // # for reset
    Number = 0;
    lcd.print("PLZ Vote :)");
  }else if ( key == '*') // * for confirm
    vote();
  else
    lcd.print("Not Valid!");
}

void vote() {
  Wire.beginTransmission(1); // transmit to device #1
  Wire.write(Number);        // sends one byte  
  Wire.endTransmission();
  
  lcd.clear();
  lcd.print("Your vote: ");
  lcd.print(Number);
  lcd.setCursor(0,1);
  lcd.print("Thanks :)");
  digitalWrite(32, HIGH);
  delay(100);
  digitalWrite(32, LOW);
}
