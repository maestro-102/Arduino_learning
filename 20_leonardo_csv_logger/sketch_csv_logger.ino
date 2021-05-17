/* Запись данных температуры и освещенности */

#include<Keyboard.h>

const int TEMP   =0;      // Вывод датчика температуры
const int LIGHT  =1;      // Вывод датчика освещенности
const int LED    =3;      // Вывод светодиода
const int BUTTON =2;      // Вывод для кнопки

boolean lastButton = LOW;    // Последнее состояние кнопки
boolean currentButton = LOW; // Текущее состояние кнопки
boolean running = false;     // По умолчанию запись включена
int counter = 1;             // Индекс записываемых данных

void setup() {
  pinMode (LED, OUTPUT);   //Выход светодиода OUTPUT
  Keyboard.begin();        // Запуск эмуляции клавиатуры
}

void loop() {
  currentButton = debounce(lastButton);           // Чтение состояния кнопки
 
  if (lastButton == LOW && currentButton == HIGH) // Если было нажатие...
    running = !running;                           // Изменить статус кнопки
  
  lastButton = currentButton;                     // Установить статус кнопки
 
  if (running) {                                  // Запись включена
    digitalWrite(LED, HIGH);                      // Включить светодиод
    if (millis() % 1000 == 0) {                   // Прошла 1 сек
      int temperature = analogRead(TEMP);         // Чтение данных датчика температуры
      int brightness = analogRead(LIGHT);         // Чтение данных датчика освещенности
      Keyboard.print(counter);                    // Вывод индекса данных
      Keyboard.print(",");                        // Вывод разделителя
      Keyboard.print(temperature);                // Вывод данных температуры
      Keyboard.print(",");                        // Вывод разделителя
      Keyboard.println(brightness);               // Вывод освещенности
      counter++;                                  // Инкремент индекса
    }
  }
  else {
    digitalWrite(LED, LOW);                       //Запись выключена, светодиод погашен
  }
}

/* Функция устранения дребезга контактов кнопки */
boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);       // Чтение состояния кнопки
  if (last != current) {                       // Если состояние измениловь...
    delay(5);                                  // Ожидание 5 мс
    current = digitalRead(BUTTON);             // Чтение состояния кнопки
  }
  return current;                              // Возврат текущего состояния кнопки
}
