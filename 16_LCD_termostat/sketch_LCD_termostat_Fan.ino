/* Программа автоматического регулятора температуры */

// Для вывода температуры используются 2 знака

#include<Wire.h>                       // Использование библиотеки Wire с установкой адреса
#define TEMP_ADDR 72
#include<LiquidCrystal.h>             // Использование библиотеки LiquidCrystal
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Инициализация экземпляра библиотеки LiquidCrystal

byte degree[8] = {                    // Пользовательский символ градуса
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

const int SPEAKER = 8;              // Вывод подключения динамика
const int DOWN_BUTTON = 9;          // Вывод подключения кнопки DOWN
const int UP_BUTTON = 10;           // Вывод подключения кнопки UP
const int FAN = 11;                 // Вывод подключения вентилятора

// Переменные для устранения дребезга контактов кнопок
boolean lastDownTempButton = LOW;
boolean currentDownTempButton = LOW;
boolean lastUpTempButton = LOW;
boolean currentUpTempButton = LOW;

int set_temp = 28;                  // Значение граничного уровня температуры
boolean one_time = false;           // Флаг звука динамика

void setup() {                    
 pinMode(FAN, OUTPUT);
 Wire.begin();                      // Создание объекта Wire (I2C-датчик температуры)
 lcd.begin(16, 2);                  // Настройки дисплея (число столбцов и строк)

    // Определить пользовательские символы
 lcd.createChar(0, degree);

    // Вывод закрепленных сообщений на дисплей
 lcd.setCursor(0, 0);
 lcd.print("Current:");
 lcd.setCursor(10, 0);
 lcd.write((byte)0);
 lcd.setCursor(11, 0);
 lcd.print("C");
 lcd.setCursor(13, 0);
 lcd.print("Fan");
 lcd.setCursor(0, 1);
 lcd.print("Set:");
 lcd.setCursor(10, 1);
 lcd.write((byte)0);
 lcd.setCursor(11, 1);
 lcd.print("C");
}

    // Функция проверки на дребезг контактов для нескольких кнопок
boolean debounce(boolean last, int pin) {
  boolean current = digitalRead(pin);
  if (last != current) {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

void loop() {
  Wire.beginTransmission(TEMP_ADDR);       // Получить значение от датчика температуры
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(TEMP_ADDR, 1);
  while (Wire.available() == 0);              // Ожидание передачи
  int c = Wire.read();                        // Получение 1 байта
  lcd.setCursor(8, 0);                        // Установка курсора
  lcd.print(c);                               // Вывести текущее значение
  
  currentDownTempButton = debounce(lastDownTempButton, DOWN_BUTTON);      // Проверка на дребезг контактов двух кнопок
  currentUpTempButton = debounce(lastUpTempButton, UP_BUTTON);

      // Уменьшить пороговое значение температуры
  if (lastDownTempButton == LOW && currentDownTempButton == HIGH) {
    set_temp--;
  }
      // Уменьшить пороговое значение температуры
  else if (lastUpTempButton == LOW && currentUpTempButton == HIGH) {
    set_temp++;
  }

      // Вывод порогового значения температуры на экран
  lcd.setCursor(8, 1);
  lcd.print(set_temp);
  lastDownTempButton = currentDownTempButton;
  lastUpTempButton = currentUpTempButton;

      // Очень жарко
  if (c >= set_temp) {
    if (!one_time) {                          // Однократный звуковой сигнал
      tone(SPEAKER, 400);
      delay(500);
      one_time = true;
    }
    else {                                    // Отключить вывод звука
      noTone(SPEAKER);
    }

    digitalWrite(FAN, HIGH);                  // Включить вентилятор и вывести значок на экран
    lcd.setCursor(13, 1);
    lcd.write("on ");
  }

    // Не жарко
  else {
    noTone(SPEAKER);                          // Выключить динамик
    one_time = false;                         // Сбросить состояние one_time в false
    digitalWrite(FAN, LOW);                   // Выключить вентилятор и значок на экране
    lcd.setCursor(13, 1);
    lcd.write("off");
  }
}
