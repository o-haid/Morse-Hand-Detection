int numbers[5] = {0, 0, 0, 0, 0}; 

void setup() {
  Serial.begin(9600); 
  
  for (int i = 13; i >= 9; i--) {
    pinMode(i, OUTPUT);
  }
}

void loop() {

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); 
    if (data.length() == 5) {
      for (int i = 0; i < 5; i++) {
        numbers[i] = data[i] - '0'; 
      }
    }
  }
  
  for (int i = 13; i >= 9; i--) {
    int array_index = 13 - i; 
    
    if (numbers[array_index] == 1) {
      digitalWrite(i, HIGH); 
    } else {
      digitalWrite(i, LOW);  
    }
  }
}