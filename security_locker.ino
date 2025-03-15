#include <Keypad.h>

const byte row = 4;
const byte col = 4;
const byte redLed = 10;
const byte greenLed = 11;
const byte piezo = 12;

char numPad[row][col] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPin[row] = {9, 8, 7, 6};
byte colPin[col] = {5, 4, 3, 2};

String password = "2502";
String vstup = "";

// Corrected Keypad initialization
Keypad cKeypad = Keypad(makeKeymap(numPad), rowPin, colPin, row, col);

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(piezo, OUTPUT);
  digitalWrite(redLed, HIGH);
  Serial.begin(9600);
  Serial.print("Enter Passcode: ");
}

void loop() {
  char cKey = cKeypad.getKey();

  if (cKey) {
    if (vstup.length() < 4) {
      Serial.print(".");
      vstup += cKey;
    }
  }

  if (vstup.length() == 4) {
    delay(1500);
    if (password == vstup) {
      Serial.println("\nEnter");
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      tone(piezo, 500);
      delay(100);
      noTone(piezo);
    } else {
      Serial.println("\nWrong Passcode");
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);  // Fixed typo here
      tone(piezo, 1000);
      delay(800);
      tone(piezo, 1000);
      delay(800);
      noTone(piezo);
    }
    delay(1500);
    vstup = "";
    Serial.println("Enter Passcode: ");
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
}
