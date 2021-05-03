/* Программное устранение дребезга контактов кнопки*/

const int LED = 6;                // Определение номера порта для LED
const int BUTTON = 2;             // Определение номера порта для BUTTON
boolean lastButton = LOW;         // Переменная для сохранения предыдущего состояния BUTTON
boolean currentButton = LOW;      // Переменная для сохранения текущего состояния BUTTON
boolean ledOn = false;            // Текущее состояние светодиода

/* Функция устранения дребезга принимает в качестве аргумента предыдущее состояние кнопки и выдает текущее*/

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);      // Считывание текущего состояния кнопки
  if (last != current) {                      // Если предыдущее состояние не равно текущему состоянию...
    delay(5);                                 // ... задержка 5 мс
    current = digitalRead(BUTTON);            // Снова считывание текущего состояния кнопки
    return current;                           // Возврат текущего состояния кнопки
  }
}

void setup() {
  pinMode(LED, OUTPUT);            // Конфигурация порта как выход
  pinMode(BUTTON, INPUT);          // Конфигурация порта как вход
}

void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {         // Если кнопка нажата (последнее значение LOW и текущее HIGH)
    ledOn = !ledOn;                                         // Состояние светодиода инвертируется
  }
  lastButton = currentButton;                               // Последнее состояние кнопки принимает значение текущего
  digitalWrite(LED, ledOn);                                 // Изменяется состояние светодиода
}
