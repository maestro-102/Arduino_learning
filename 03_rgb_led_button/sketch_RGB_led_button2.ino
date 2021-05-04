/* Управление RGB-светодиодом с помощью кнопки*/

const int RLED = 8;                       // Определение порта для RLED
const int GLED = 9;                       // Определение порта для GLED
const int BLED = 10;                      // Определение порта для BLED
const int BUTTON = 2;                     // Определение порта для BUTTON
boolean lastButton = LOW;                 // Переменная для сохранения предыдущего статуса кнопки
boolean currentButton = LOW;              // Переменная для сохранения текущего статуса кнопки
int ledMode = 0;                          // Значение статуса RGB lED

/* Функция устранения дребезга контактов кнопки принимает в качестве аргумента предыдущее состояние кнопки и выдает текущее*/

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);      // Считывание текущего состояния кнопки
  if (last != current) {                      // Если предыдущее состояние не равно текущему состоянию...
    delay(5);                                 // ... задержка 5 мс
    current = digitalRead(BUTTON);            // Снова считывание текущего состояния кнопки
    return current;                           // Возврат текущего состояния кнопки
  }
}

/* Выбор режима работы светодиода. 
   Передача номера режима работы и установка заданного режима. */
   
void setMode(int mode) {
  if (mode == 1) {                      // Красное свечение
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  else if (mode == 2) {                 // Зеленое свечение
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
  else if (mode == 3) {                 // Синее свечение
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
  else if (mode == 4){                  // Красное + синее свечение
    analogWrite(RLED, 255);
    analogWrite(GLED, 0);
    analogWrite(BLED, 127);
  }
  else if (mode == 5) {                 // Синее + зеленое свечение
    analogWrite(RLED, 0);
    analogWrite(GLED, 255);
    analogWrite(BLED, 50);
  }
  else if (mode == 6) {                 // Красное + зеленое свечение
    analogWrite(RLED, 255);
    analogWrite(GLED, 80);
    analogWrite(BLED, 0);
  }
  else if (mode == 7) {                 // Белое свечение (красный + зеленый + синий)
    analogWrite(RLED, 255);
    analogWrite(GLED, 80);
    analogWrite(BLED, 80);
  }
  else {                                // Выключен
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
}

void setup() {
  pinMode(RLED, OUTPUT);                // Конфигурация порта как выход
  pinMode(GLED, OUTPUT);                // Конфигурация порта как выход
  pinMode(BLED, OUTPUT);                // Конфигурация порта как выход
  //pinMode(BUTTON, INPUT);               // Можно не указывать, т.к. по умолчанию все порты - INPUT
}

void loop() {
  currentButton = debounce(lastButton);                   // Чтение статуса кнопки
  if (lastButton == LOW && currentButton == HIGH) {       // Если кнопка нажата...
    ledMode++;                                            // Инкремент переменной статуса светодиода (увеличение на 1)
  }
  lastButton = currentButton;
  if (ledMode == 8)
    ledMode = 0;
  setMode(ledMode);
}
