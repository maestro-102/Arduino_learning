/* Изменение яркости свечения светодиода с помощью ШИМ */

const int LED = 6;                // Определение номера порта для LED

void setup() {
  pinMode(LED, OUTPUT);            // Конфигурация порта как выход
}

void loop() {
  for (int i = 0; i < 256; i = i + 5) {   // Увеличение яркости светодиода
  analogWrite(LED, i);        
  delay(50);                      
  }
  for (int i = 255; i >= 0; i = i - 5) {      // Уменьшение яркости светодиода
  analogWrite(LED, i);        
  delay(50);                       
  }
}
