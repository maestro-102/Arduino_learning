/* Температурный оповещатель с датчиком TMP36 на 24 град. С v1.0 */

const int BLED = 8;               // Определение порта для BLED
const int GLED = 9;               // Определение порта для GLED
const int RLED = 10;              // Определение порта для RLED
const int TEMP = 0;               // Определение порта для входа датчика температуры TEMP

const int LOWER_BOUND = 151;      // Нижний порог температуры
const int UPPER_BOUND = 153;      // Верхний порог температуры
int val = 0;                      // Переменная для хранения аналогового значения

void setup() {
  Serial.begin(9600);             // Настройка скорости передачи данных на порт компьютера
  
  pinMode(BLED, OUTPUT);          // Конфигурация порта BLED как выход
  pinMode(GLED, OUTPUT);          // Конфигурация порта GLED как выход
  pinMode(RLED, OUTPUT);          // Конфигурация порта RLED как выход
}

void loop() {
 val = analogRead(TEMP);          // Считывание данных с аналогового датчика температуры
 
 Serial.println(val);             // Вывод на компьютер данных датчика температуры
 delay(1000);                     // Задержка вывода данных на компьютер для чтения
 
 if (val < LOWER_BOUND) {         // Если температура ниже нижнего порога...
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, HIGH);
 }
 else if (val > UPPER_BOUND) {    //...иначе, если температура выше верхнего порога...
  digitalWrite(RLED, HIGH);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, LOW);
 }
 else {                           //...иначе...
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, LOW);
 }
}
