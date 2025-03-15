# Security_Locker
# Keypad-Based Security System

This project implements a simple keypad-based security system using an Arduino. The system requires a predefined passcode to activate a green LED while an incorrect entry triggers a red LED and a buzzer alarm.

## Components Used
- Arduino Board
- 4x3 Keypad
- Red LED
- Green LED
- Piezo Buzzer
- Resistors
- Connecting Wires

## How It Works
1. The system prompts the user to enter a 4-digit passcode.
2. As each key is pressed, a dot (`.`) is displayed on the serial monitor.
3. Once 4 digits are entered, the system checks the passcode:
   - If correct:
     - The red LED turns off.
     - The green LED turns on.
     - A short buzzer tone plays.
   - If incorrect:
     - The red LED stays on.
     - The green LED remains off.
     - A buzzer alarm sounds twice.
4. The system resets after a delay, allowing for a new passcode entry.

## Code
```cpp
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
      digitalWrite(greenLed, LOW);
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
```

## Installation & Usage
1. Connect the components as per the wiring diagram.
2. Upload the Arduino code to your board.
3. Open the serial monitor to interact with the system.

## Customization
- Change the passcode by modifying the `password` variable in the code.
- Adjust the buzzer tones and delays for different feedback sounds.

## License
This project is open-source and free to use.

