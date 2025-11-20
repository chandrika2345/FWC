#include <Arduino.h>
// 4-to-1 multiplexer simulation using Arduino

const int P = 0;
const int Q = 1;
const int R = 2;
const int S = 3;

const int C0 = 4;
const int C1 = 5;

const int Y = 6;

void setup() {
  // Input data lines
  pinMode(P, INPUT);
  pinMode(Q, INPUT);
  pinMode(R, INPUT);
  pinMode(S, INPUT);

  // Select lines
  pinMode(C0, INPUT);
  pinMode(C1, INPUT);

  // Output line
  pinMode(Y, OUTPUT);
}

void loop() {
  int c0 = digitalRead(C0);
  int c1 = digitalRead(C1);
  int selected = (c1 << 1) | c0;

  int muxOut;

  switch (selected) {
    case 0: muxOut = digitalRead(P); break;
    case 1: muxOut = digitalRead(Q); break;
    case 2: muxOut = digitalRead(R); break;
    case 3: muxOut = digitalRead(S); break;
  }

  digitalWrite(Y, muxOut);
}
