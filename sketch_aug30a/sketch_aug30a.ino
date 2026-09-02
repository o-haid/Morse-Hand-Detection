#include <LiquidCrystal.h>

const int CONTRAST_PIN = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite(CONTRAST_PIN, 110);
  delay(200);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Morse: ");
  lcd.setCursor(0, 1);
  lcd.print("Text: ");

  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    int delimiterIndex = data.indexOf('|');
    if (delimiterIndex != -1) {
      String morsePart = data.substring(0, delimiterIndex);
      String textPart = data.substring(delimiterIndex + 1);

      lcd.setCursor(7, 0);
      lcd.print(morsePart);

      for (int i = morsePart.length(); i < 9; i++) {
        lcd.print(" ");
      }

      lcd.setCursor(6, 1);
      if (textPart.length() > 10) {
        textPart = textPart.substring(textPart.length() - 10);
      }
      lcd.print(textPart);
      for (int i = textPart.length(); i < 10; i++) {
        lcd.print(" ");
      }
    }
  }
}