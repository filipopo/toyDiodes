const uint8_t patternPin = 3;
const uint8_t speedPin = 2;

const uint16_t defaultSpeed = 600;
const uint8_t patternCount = 8;

uint16_t speed = defaultSpeed;
uint8_t pattern = 0;
uint8_t patternIndex = 0;

const uint8_t patterns[patternCount][10][5] = {
  {{8}, {7}, {6}, {5}, {4}},
  //{{4}, {5}, {6}, {7}, {8}},
  {{4}, {4, 5}, {5, 6}, {6, 7}, {7,8}, {8}, {}},
  {{8, 4}, {7, 5}, {6}},
  {{6}, {7, 5}, {8, 4}},
  //{{8}, {8, 7}, {8, 7, 6}, {8, 7, 6, 5}, {8, 7, 6, 5, 4}, {7, 6, 5, 4}, {6, 5, 4}, {5, 4}, {4}, {}},
  {{4}, {5, 4}, {6, 5, 4}, {7, 6, 5, 4}, {8, 7, 6, 5, 4}, {8, 7, 6, 5}, {8, 7, 6}, {8, 7}, {8}, {}},
  {{8}, {6}, {7}, {5}, {6}, {4}, {5}},
  //{{4}, {6}, {5}, {7}, {6}, {8}, {7}},
  //{{8, 7}, {8}, {7, 6}, {7}, {6, 5}, {6}, {5, 4}, {5}, {4, 8}, {4}},
  {{4, 5}, {4}, {5, 6}, {5}, {6, 7}, {6}, {7, 8}, {7}, {8, 4}, {8}},
  {{4, 5, 6, 7, 8}, {}}
};

const uint8_t patternSize[patternCount] = {5, 7, 3, 3, 10, 7, 10, 2};

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  for (uint8_t i = 4; i < 10; i++)
    pinMode(i, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(patternPin), changePattern, FALLING);
  attachInterrupt(digitalPinToInterrupt(speedPin), changeSpeed, FALLING);
}

void loop() {
  showPatternStep();
  delay(speed);
}

void showPatternStep() {
  for (uint8_t i = 4; i < 9; i++)
    digitalWrite(i, LOW);

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
