
const int NUMBER_OF_PINS = 3;
const int buttonOrder[NUMBER_OF_PINS] = {11, 13, 11}; // order of the pins
boolean state[NUMBER_OF_PINS]; // remember of correct pins. If all are true -> relay will switch on.
const int outputPin = 3;
const int relayTime = 1000; // ms

void setup() {
  Serial.begin(9600);
  for ( int i = 0; i < NUMBER_OF_PINS; i++ ) {
    pinMode(buttonOrder[i], INPUT_PULLUP);
  }
  clear();
  pinMode(outputPin, OUTPUT);
  Serial.println("Setup complete");
}

// Check that not all or other pins are pushed at once.
// return true when another then the given pin us set. Parameter is here for example: otherPressed(13,LOW)
boolean otherPressed(int pin, int onLevel) {
  for ( int i = 0; i < NUMBER_OF_PINS; i++ ) {
    if (digitalRead(buttonOrder[i]) == onLevel && i != pin ) {
      return true;
    }
  }
  return false;
}

void clear() {
  for ( int i = 0; i < NUMBER_OF_PINS; i++ ) {
    state[i]=false;
  }
}

boolean buttonReleased = true; // find breaks between presses
int lastButtonPressed = -1;
long lastButtonTime = 0; // set to the new timestamp on each key down.
const long buttonTimeout = 5000; // milliseconds. After that time -> reset the state array

void loop() {

  Serial.println("loop ");

  // Sequence started so a timeout makes sense
  if (millis() - lastButtonTime > buttonTimeout && state[0]) {
    Serial.println("Timeout detected-> reset");
    clear();
    lastButtonPressed = -1;
  }

  // last codepart correctly entered -> trigger relais
  if (state[NUMBER_OF_PINS - 1]) {
    Serial.println("CODE COMPLETED");
    digitalWrite(outputPin, HIGH);
    delay(relayTime);
    digitalWrite(outputPin, LOW);
    clear();
  }

  if (!buttonReleased) { // handle button release first
    Serial.println("buttonReleased 1");
    while (digitalRead(buttonOrder[lastButtonPressed]) == LOW) {
      delay(100); // debounce
    }
    buttonReleased = true;
    lastButtonTime = millis(); // just released
    Serial.println("buttonReleased 2");
  }

  for ( int i = 0; i < NUMBER_OF_PINS; i++ ) {
    Serial.print("loop ");
    Serial.println(i);
    
    if (state[i]) {
      Serial.print("skip ");
      Serial.println(i);
      continue; // skip this button as it is not the next one
    }

    if (digitalRead(buttonOrder[i]) == LOW /*&& !otherPressed(i, LOW)*/) { // the right one is the only one
      Serial.print("add ");
      Serial.println(i);
      state[i] = true;
      buttonReleased = false;
      lastButtonPressed = i;
      lastButtonTime = millis();
    }
    break;

  }
  delay(500); // at least wait for that
}
