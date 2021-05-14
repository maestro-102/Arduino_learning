/* Кнопка с аппаратной противодребезговой защитой, управляемая прерыванием */

// Контакт кнопки
const int BUTTON_INT = 0;               // Прерывание 0 (вывод 2 для Uno)
const int RED = 11;                     // Вывод красного света RGB
const int GREEN = 10;                   // Вывод зеленого света RGB
const int BLUE = 9;                     // Вывод синего света RGB

// Переменные volatile можно изменять внутри функции обработки прерывания
volatile int selectedLED = RED;

void setup() {                    
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT);

 // Режим прерывания RISING (переход с LOW на HIGH)
 attachInterrupt(BUTTON_INT, swap, RISING);
}

void swap() {
  analogWrite(selectedLED, 0);          // Выключитьтекущий цвет
  if (selectedLED == GREEN)             // Новое значение для переменной selectedLED
    selectedLED = RED;
  else if (selectedLED == RED)
    selectedLED = BLUE;
  else if (selectedLED == BLUE)
    selectedLED = GREEN;
}

void loop() {
 for (int i = 0; i < 256; i++) {
  analogWrite(selectedLED, i);
  delay(10);
 }
 for (int i = 255; i >= 0; i--) {
  analogWrite(selectedLED, i);
  delay(10);
 }
}
