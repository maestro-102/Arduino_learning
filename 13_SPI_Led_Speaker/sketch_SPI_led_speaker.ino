/* Изменение яркости светодиодоа и громкости динамика регулировкой напряжения */

#include<SPI.h>                      // Подключение библиотеки SPI

/* При подключении библиотеки SPI ПО УМОЛЧАНИЮ используются выводы: 11 - MOSI, 12 - MISO, 13 - CLK */

const int SPEAKER = 8;               // Определение вывода подключения динамика
int freq = 100;
const int SS1 = 10;                  // Определение вывода SS MCP4231
const byte REG0 = B00000000;         // Команда записи в регистр 0 - выбор первого потенциометра
const byte REG1 = B00010000;         // Команда записи в регистр 1 - выбор второго потенциометра

void setup() {                    
 pinMode(SS1, OUTPUT);               // Настройа вывода выбора SS как выход
 SPI.begin();                        // Инициализация аппаратного SPI
}

/* Подпрограмма выбора и отправки данных */
// Chip (SS1 10) регистр 0 - динамик
// Chip (SS1 10) регистр 1 - желтый

void setReg(int SS1, int reg, int level) {
  digitalWrite(SS1, LOW);            // Установить SS в низкий уровень (выбор)
  SPI.transfer(reg);                // Отправка команды
  SPI.transfer(level);              // Отправка значения (0 - 128)
  digitalWrite(SS1, HIGH);           // Установить SS в высокий уровень
}

void loop() {
  tone(SPEAKER, freq);              // Частота звука
    for(int i = 0; i <= 128; i++) {
      setReg(SS1, REG0, i);
      setReg(SS1, REG1, i);
      delay(10);
    }
    delay(300);
    for(int i = 128; i >= 0; i--) {
      setReg(SS1, REG0, i);
      setReg(SS1, REG1, i);
      delay(10);
    }
    delay(300);
    freq = freq + 100;
    if(freq > 2000) freq = 100;
}
