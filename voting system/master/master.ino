#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
#include <EEPROM.h>

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

// EEPROM values
uint8_t num_vote;
int num0_ADDR = 0;
int num1_ADDR = 1;
int num2_ADDR = 2;
int num3_ADDR = 3;
int num4_ADDR = 4;
int num5_ADDR = 5;
int num6_ADDR = 6;
int num7_ADDR = 7;
int num8_ADDR = 8;
int num9_ADDR = 9;

void setup() {
  lcd.begin(16, 2);

  Wire.begin(1); // join i2c bus
  Wire.onReceive(receiveData);

}
void loop() {
  char key = kpd.getKey();
  if (key != NO_KEY)
    DetectButtons(key);
}


void DetectButtons(char key) {
  lcd.clear();
  if (key == '2' )        // total number of votes
    total();
  else if ( key == '5')   // stop voting
    stop_voting();
  else if ( key == '8')   // result
    result();
  else
    lcd.print("Not Valid!");
}

void total() {
  lcd.print("total votes: ");
  int n0 = EEPROM.read(num0_ADDR);
  int n1 = EEPROM.read(num1_ADDR);
  int n2 = EEPROM.read(num2_ADDR);
  int n3 = EEPROM.read(num3_ADDR);
  int n4 = EEPROM.read(num4_ADDR);
  int n5 = EEPROM.read(num5_ADDR);
  int n6 = EEPROM.read(num6_ADDR);
  int n7 = EEPROM.read(num7_ADDR);
  int n8 = EEPROM.read(num8_ADDR);
  int n9 = EEPROM.read(num9_ADDR);
  int total = n0 + n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9;
  if(total > 1000){
    for (int i = 0 ; i < 10 ; i++)
      EEPROM.write(i, 0);
    total = 0;
  }
  lcd.setCursor(0, 1);
  lcd.print(total);
}

void stop_voting() {
  lcd.clear();
  lcd.print("stop");
}

void result() {
  int max_num = 0;
  int max_vote = 0;

  lcd.print("result is: ");
  delay(100);
  lcd.clear();
  lcd.print("number 0: ");
  int n0 = EEPROM.read(0);
  lcd.print(n0);

  if (max_num < n0) {
    max_num = n0;
    max_vote = 0;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 1: ");
  int n1 = EEPROM.read(1);
  lcd.print(n1);

  if (max_num < n1) {
    max_num = n1;
    max_vote = 1;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 2: ");
  int n2 = EEPROM.read(2);
  lcd.print(n2);

  if (max_num < n2) {
    max_num = n2;
    max_vote = 2;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 3: ");
  int n3 = EEPROM.read(3);
  lcd.print(n3);

  if (max_num < n3) {
    max_num = n3;
    max_vote = 3;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 4: ");
  int n4 = EEPROM.read(4);
  lcd.print(n4);

  if (max_num < n4) {
    max_num = n4;
    max_vote = 4;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 5: ");
  int n5 = EEPROM.read(5);
  lcd.print(n5);

  if (max_num < n5) {
    max_num = n5;
    max_vote = 5;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 6: ");
  int n6 = EEPROM.read(6);
  lcd.print(n6);

  if (max_num < n6) {
    max_num = n6;
    max_vote = 6;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 7: ");
  int n7 = EEPROM.read(7);
  lcd.print(n7);

  if (max_num < n7) {
    max_num = n7;
    max_vote = 7;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 8: ");
  int n8 = EEPROM.read(8);
  lcd.print(n8);

  if (max_num < n8) {
    max_num = n8;
    max_vote = 8;
  }

  delay(100);
  lcd.clear();
  lcd.print("number 9: ");
  int n9 = EEPROM.read(9);
  lcd.print(n9);

  if (max_num < n9) {
    max_num = n9;
    max_vote = 9;
  }

  delay(100);
  lcd.clear();

  lcd.print("the winner is: ");
  lcd.print(max_vote);
  lcd.setCursor(0, 1);
  lcd.print("with ");
  lcd.print(max_num);
  lcd.print(" votes.");

}

void vote() {
  int n = EEPROM.read(num_vote);
  n++;
  EEPROM.write(num_vote, n);
}

void receiveData(int howMany) {

  int x = Wire.read();    // receive byte as an integer
  lcd.clear();
  lcd.print(x);         // print the character

  num_vote = x;
  vote();
}
