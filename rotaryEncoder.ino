#include <Encoder.h>

Encoder myEnc(D1, D2);

int pinTaster = D6;
int pinLed = D5;
int pinRelay = D7;

long oldPosition = -999;
boolean isButtonPressed = false;
long lastUpdateMillis = 0;

void handleKey() {
  isButtonPressed = true;
}
 
void setup() {
  Serial.begin(115200);
  pinMode(D3, INPUT_PULLUP);
  attachInterrupt(D3, handleKey, RISING);

  pinMode(pinTaster, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinRelay, OUTPUT);
}

int basisInterval = 1000;

void loop() {
  long newPosition = myEnc.read() / 4;
  if (newPosition < 0) {
    newPosition = 0;
    myEnc.write(0);
  }
  delay(100);
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  if (isButtonPressed && millis() - lastUpdateMillis > 50) {
    isButtonPressed = false;
    lastUpdateMillis = millis();
    myEnc.write(0);
  }

  int buttonState = digitalRead(pinTaster);
  if (buttonState == 1) {
    Serial.println("AN");
    digitalWrite(pinLed, HIGH);
    digitalWrite(pinRelay, HIGH);
    delay(newPosition * basisInterval);
    digitalWrite(pinLed, LOW);
    digitalWrite(pinRelay, LOW);
  }
  delay(200);
}
