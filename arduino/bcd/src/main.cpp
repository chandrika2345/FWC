#include <Arduino.h>

// Define pins used on Arduino
#define PIN_a 2
#define PIN_b 3
#define PIN_c 4
#define PIN_d 5
#define PIN_e 6
#define PIN_f 7
#define PIN_g 8
#define PIN_A 9
#define PIN_B 10
#define PIN_C 11
#define PIN_D 12

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to INPUT and OUTPUT as appropriate
    pinMode(PIN_a, OUTPUT);
    pinMode(PIN_b, OUTPUT);
    pinMode(PIN_c, OUTPUT);
    pinMode(PIN_d, OUTPUT);
    pinMode(PIN_e, OUTPUT);
    pinMode(PIN_f, OUTPUT);
    pinMode(PIN_g, OUTPUT);
    pinMode(PIN_A, INPUT);  
    pinMode(PIN_B, INPUT);
    pinMode(PIN_C, INPUT);
    pinMode(PIN_D, INPUT);
}

// Loop: code that executes forever goes here
void loop() {
    int A, B, C, D, a, b, c, d, e, f, g;
    // Read input pins
    A = digitalRead(PIN_A);
    B = digitalRead(PIN_B);
    C = digitalRead(PIN_C);
    D = digitalRead(PIN_D);
	// Boolean functions for each pin
	a = (C&&!B&&!A)||(!D&&!C&&!B&&A);
	b = (C&&!B&&A)||(C&&B&&!A);
	c = !C&&B&&!A;
	d = (!D&&!C&&!B&&A)||(C&&!B&&!A)||(C&&B&&A);
	e = (!B||A)&&(C||B||A);
	f = (!D&&!C&&A)||(!C&&B)||(B&&A);
	g = (!D&&!C&&!B)||(C&&B&&A);
	// Write to pins
	digitalWrite(PIN_a, a);
	digitalWrite(PIN_b, b);
	digitalWrite(PIN_c, c);
	digitalWrite(PIN_d, d);
	digitalWrite(PIN_e, e);
	digitalWrite(PIN_f, f);
	digitalWrite(PIN_g, g);
}

// Define BCD output pins connected to 74LS47 (A = LSB)
/*int bcdPins[4] = {2, 3, 4, 5}; // A = 2, B = 3, C = 4, D = 5

// Function prototype (required because function is after loop)
void displayBCD(int value);

void setup() {
  // Set all BCD pins as OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(bcdPins[i], OUTPUT);
  }
}

void loop() {
  // Loop from 0 to 9 and display each number for 1 second
  for (int num = 0; num <= 9; num++) {
    displayBCD(num);
    delay(1000);
  }
}

// Function to output BCD to the 74LS47
void displayBCD(int value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(bcdPins[i], (value >> i) & 1);
  }
  }
  */


