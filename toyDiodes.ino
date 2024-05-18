#define pinLen 5
uint8_t p[pinLen] = {4, 5, 6, 7, 8};

const uint8_t patternPin = 3;
const uint8_t speedPin = 2;

const uint16_t defaultSpeed = 600;
const uint8_t patternCount = 8;

uint16_t speed = defaultSpeed;
uint8_t pattern = 0;
uint8_t patternIndex = 0;

const uint8_t patterns[patternCount][10][pinLen] = {
{{p[4]}, {p[3]}, {p[2]}, {p[1]}, {p[0]}},
//{{p[0]}, {p[1]}, {p[2]}, {p[3]}, {p[4]}},
{{p[0]}, {p[0], p[1]}, {p[1], p[2]}, {p[2], p[3]}, {p[3],p[4]}, {p[4]}, {}},
{{p[4], p[0]}, {p[3], p[1]}, {p[2]}},
{{p[2]}, {p[3], p[1]}, {p[4], p[0]}},
//{{p[4]}, {p[4], p[3]}, {p[4], p[3], p[2]}, {p[4], p[3], p[2], p[1]}, {p[4], p[3], p[2], p[1], p[0]}, {p[3], p[2], p[1], p[0]}, {p[2], p[1], p[0]}, {p[1], p[0]}, {p[0]}, {}},
{{p[0]}, {p[1], p[0]}, {p[2], p[1], p[0]}, {p[3], p[2], p[1], p[0]}, {p[4], p[3], p[2], p[1], p[0]}, {p[4], p[3], p[2], p[1]}, {p[4], p[3], p[2]}, {p[4], p[3]}, {p[4]}, {}},
{{p[4]}, {p[2]}, {p[3]}, {p[1]}, {p[2]}, {p[0]}, {p[1]}},
//{{p[0]}, {p[2]}, {p[1]}, {p[3]}, {p[2]}, {p[4]}, {p[3]}},
//{{p[4], p[3]}, {p[4]}, {p[3], p[2]}, {p[3]}, {p[2], p[1]}, {p[2]}, {p[1], p[0]}, {p[1]}, {p[0], p[4]}, {p[0]}},
{{p[0], p[1]}, {p[0]}, {p[1], p[2]}, {p[1]}, {p[2], p[3]}, {p[2]}, {p[3], p[4]}, {p[3]}, {p[4], p[0]}, {p[4]}},
{{p[0], p[1], p[2], p[3], p[4]}, {}}
};

const uint8_t patternSize[patternCount] = {5, 7, 3, 3, 10, 7, 10, 2};

void setup() {
  pinMode(patternPin, INPUT_PULLUP);
  pinMode(speedPin, INPUT_PULLUP);

  for (uint8_t pin : p)
    pinMode(pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(patternPin), changePattern, FALLING);
  attachInterrupt(digitalPinToInterrupt(speedPin), changeSpeed, FALLING);
}

void loop() {
  showPatternStep();
  delay(speed);
}

void showPatternStep() {
  for (uint8_t pin : p)
    digitalWrite(pin, LOW);

  for (uint8_t i = 0; i < sizeof(patterns[pattern][patternIndex]); i++)
    digitalWrite(patterns[pattern][patternIndex][i], HIGH);

  patternIndex += 1;
  if (patternIndex >= patternSize[pattern])
    patternIndex = 0;
}

void changePattern() {
  delayMicroseconds(5000);
  if (digitalRead(patternPin) == 0) {
    pattern += 1;
    patternIndex = 0;
    if (pattern >= patternCount)
      pattern = 0;
  }
}

void changeSpeed() {
  delayMicroseconds(5000);
  if (digitalRead(speedPin) == 0) {
    speed -= 100;
    if (speed < 100)
      speed = defaultSpeed;
  }
}
