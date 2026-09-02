#include <LiquidCrystal.h>

const int CONTRAST_PIN = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String lastData = "";

void setup() {

  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite(CONTRAST_PIN, 110);
  delay(200);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fingers: [00000]");
  lcd.setCursor(0, 1);
  lcd.print("Count: 0 raised");

  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data.length() == 5 && data != lastData) {
      lastData = data;

      int countRaised = 0;
      for (int i = 0; i < 5; i++) {
        if (data[i] == '1') {
          countRaised++;
        }
      }

      lcd.setCursor(10, 0);
      lcd.print(data);

      lcd.setCursor(7, 1);
      lcd.print(countRaised);
      lcd.print(" raised ");
    }
  }
}