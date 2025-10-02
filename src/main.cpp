#include <OneButton.h>

const int BUTTON_PIN = 21; 
const int LED_PIN = 5;   

OneButton button(BUTTON_PIN, true, true);


bool ledState = false;
bool blinkMode = false;
unsigned long previousMillis = 0;
unsigned long blinkInterval = 500;
bool ledOnForBlink = false;

void handleSingleClick();
void handleDoubleClick();

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  button.attachClick(handleSingleClick);
  button.attachDoubleClick(handleDoubleClick);
  Serial.begin(115200); 

}

void loop() {
  button.tick();

  if (blinkMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledOnForBlink = !ledOnForBlink;
      digitalWrite(LED_PIN, ledOnForBlink ? HIGH : LOW);
    }
  }
}

void handleSingleClick() {
  Serial.print("g"); 
  if (blinkMode) {
    blinkMode = false;
  }
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

void handleDoubleClick() {
  blinkMode = !blinkMode;
  if (blinkMode) {
    previousMillis = millis();
    ledOnForBlink = false;
    digitalWrite(LED_PIN, LOW);
    Serial.print("LED LOW");
  } else {
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  }
}  