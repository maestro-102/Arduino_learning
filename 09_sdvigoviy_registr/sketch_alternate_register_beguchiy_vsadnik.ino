/* Бегущий огонь на сдвиговом регистре */

const int SER = 8;                // Подключение вывода DATA
const int LATCH = 9;              // Подключение вывода LATCH
const int CLK = 10;               // Подключение вывода CLOCK

int seq[14] = {1, 2, 4, 8, 16, 32, 64, 128, 64, 32, 16, 8, 4, 2};     // Последовательность включения светодиодов

void setup() {                    // Конфигкрация выводов как выход
 pinMode(SER, OUTPUT);
 pinMode(LATCH, OUTPUT);
 pinMode(CLK, OUTPUT);
}

void loop() {
  for(int i = 0; i < 14; i++) {
    digitalWrite(LATCH, LOW);        // LATCH - низкий уровень
    shiftOut(SER, CLK, LSBFIRST, seq[i]);     // Старший бит - последний
    digitalWrite(LATCH, HIGH);                   // LATCH - высокий уровень
    delay(500);                     // Скорость анимации
  }
}
