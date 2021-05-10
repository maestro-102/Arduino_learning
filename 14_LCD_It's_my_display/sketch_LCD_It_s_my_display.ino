/* Текст и значение инкрементируемого счетчика на экране */

#include<LiquidCrystal.h>
int time = 0;                        // Начальное значение time
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Инициализация экземпляра библиотеки LiquidCrystal

void setup() {                    
 lcd.begin(16, 2);                  // Настройка экземпляра дисплея - число столбцов и строк
 lcd.print("It's my display");
}

void loop() {
  lcd.setCursor(0, 1);            // Установить курсор на вторую строку в первую позицию
  lcd.print(time);                // Вывод значения счетчика
  delay(1000);
  time++;                         // Увеличение счетчика
}
