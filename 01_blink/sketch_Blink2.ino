/* Изменение скорости мерцания светодиода */

const int LED = 6;                // Определение номера порта для LED

void setup() {
  pinMode(LED, OUTPUT);            // Конфигурация порта как выход
}

void loop() {
  for (int i = 50; i <= 1000; i = i + 50) {
  digitalWrite(LED, HIGH);        // Зажечь светодиод...
  delay(i);                       // ... на величину i
  digitalWrite(LED, LOW);         // Погасить светодиод...
  delay(i);                       // ... на величину i
  }
}
