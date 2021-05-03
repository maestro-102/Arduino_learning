/* Управление светодиодом с помощью кнопки и стягивающего резистора */

const int LED = 6;                // Определение номера порта для LED
const int BUTTON = 2;             // Определение номера порта для BUTTON

void setup() {
  pinMode(LED, OUTPUT);            // Конфигурация порта как выход
  pinMode(BUTTON, INPUT);          // Конфигурация порта как вход
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}
