/* Блокировка компьютера при выключении света */

#include<Keyboard.h>

const int LIGHT     =1;    // Вывод датчика освещенности
const int THRESHOLD =500;  // Значение датчика освещенности для блокировки компьютера

void setup() {
  Keyboard.begin(); 
}

void loop() {
  int brightness = analogRead(LIGHT);    // Чтение данных датчика 
  if (brightness < THRESHOLD)  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  }
}
