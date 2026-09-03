#include <LiquidCrystal.h>

const int CONTRAST_PIN = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int BUTTON_PIN = A0;
int lastButtonState = HIGH;
int currentPage = 0;

String currentMorse = "";
String currentText = "";

void setup() {
  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite(CONTRAST_PIN, 110);
  delay(200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

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
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && lastButtonState == HIGH) {
    int totalPages = currentText.length() / 10;
    if (currentText.length() % 10 != 0 || currentText.length() == 0) {
      totalPages++;
    }

    currentPage++;
    
    if (currentPage >= totalPages) {
      currentPage = 0; 
    }
    
    updateDisplay();
    delay(50);
  }
  lastButtonState = buttonState;

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    int delimiterIndex = data.indexOf('|');
    if (delimiterIndex != -1) {
      currentMorse = data.substring(0, delimiterIndex);
      currentText = data.substring(delimiterIndex + 1);
      
      int totalPages = currentText.length() / 10;
      if (currentText.length() % 10 != 0 || currentText.length() == 0) {
        totalPages++;
      }
      
      currentPage = totalPages - 1;
      if (currentPage < 0) currentPage = 0;
      
      updateDisplay();
    }
  }
}

void updateDisplay() {

  lcd.setCursor(7, 0);
  lcd.print(currentMorse);
  for (int i = currentMorse.length(); i < 9; i++) {
    lcd.print(" ");
  }

  lcd.setCursor(6, 1);
  int startIndex = currentPage * 10;
  
  String visibleText = currentText.substring(startIndex, startIndex + 10);
  lcd.print(visibleText);

  for (int i = visibleText.length(); i < 10; i++) {
    lcd.print(" ");
  }
}