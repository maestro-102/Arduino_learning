/* Создание компьютерной мыши */

#include<Mouse.h>

const int LEFT_BUTTON   =4;  // Вход левой кнопки мыши
const int MIDDLE_BUTTON =3;  // Вход средней кнопки мыши
const int RIGHT_BUTTON  =2;  // Вход правой кнопки мыши
const int X_AXIS        =0;  // А0 для оси X джойстика
const int Y_AXIS        =1;  // А1 для оси Y джойстика

void setup() {
  Mouse.begin();
}

void loop(){
  int xVal = readJoystick(X_AXIS);         // Получить отклонение джойстика по оси Х
  int yVal = readJoystick(Y_AXIS);         // Получить отклонение по оси Y
  Mouse.move(xVal, yVal, 0);               // Перемещение мыши - джойстиком

  readButton(LEFT_BUTTON, MOUSE_LEFT);     // Чтение состояния левой кнопки
  readButton(MIDDLE_BUTTON, MOUSE_MIDDLE); // Чтение состояния средней кнопки
  readButton(RIGHT_BUTTON, MOUSE_RIGHT);   // Чтение состояния правой кнопки

  delay(5);                                // 
}

// Чтение значений джойстика, масштабирование
int readJoystick(int axis) { 
  int val = analogRead(axis);        // Чтение аналогового значения
  val = map(val, 0, 1023, -10, 10);  // Масштабирование значения

  if (val <= 2 && val >= -2)         // Убрать дрейф мыши
    return 0; 
 
  else                               // Вернуть значение
    return val;
}

// Чтение состояния кнопок и отправка команд мыши
void readButton(int pin, char mouseCommand) {
  // Если кнопка нажата, эмулируем нажатие, если она еще не была нажата
  if (digitalRead(pin) == HIGH) {
    if (!Mouse.isPressed(mouseCommand)) {
      Mouse.press(mouseCommand); 
    }
  } 
  // Отпустить нажатие
  else  {
    if (Mouse.isPressed(mouseCommand))  {
      Mouse.release(mouseCommand); 
    }
  }
}
