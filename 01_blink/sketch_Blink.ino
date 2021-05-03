/* Мерцание светодиода */

const int LED = 6;                // Определение номера порта для LED

void setup() {
  pinMode(LED, OUTPUT);            // Конфигурация порта как выход
}

void loop() {
  digitalWrite(LED, HIGH);        // Зажечь светодиод...
  delay(1000);                    // ... на 1000 мс = 1 сек
  digitalWrite(LED, LOW);         // Погасить светодиод...
  delay(1000);                    // ... на 1000 мс = 1 сек
}
