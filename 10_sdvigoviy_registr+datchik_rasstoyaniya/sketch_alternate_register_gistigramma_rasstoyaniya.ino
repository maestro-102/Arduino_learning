/* Гистограмма расстояния на сдвиговом регистре */

const int SER = 8;                // Подключение вывода DATA
const int LATCH = 9;              // Подключение вывода LATCH
const int CLK = 10;               // Подключение вывода CLOCK
const int DIST = 0;               // Подключение датчика расстояния

int vals[9] = {0, 1, 3, 7, 15, 31, 63, 127, 255};     // Возможные значения светодиодов
int maxVal = 500;                                     // Максимальное значение расстояния
int minVal = 0;                                       // Минимальное значение расстояния

void setup() {                    // Конфигурация выводов как выход
 pinMode(SER, OUTPUT);
 pinMode(LATCH, OUTPUT);
 pinMode(CLK, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  int distance = analogRead(DIST);
  distance = map(distance, minVal, maxVal, 0, 8);
  distance = constrain(distance, 0, 8);
  Serial.println(distance);
  digitalWrite(LATCH, LOW);        // LATCH - низкий уровень - начало отправки
  shiftOut(SER, CLK, MSBFIRST, vals[distance]);     // Старший бит - первый
  digitalWrite(LATCH, HIGH);                   // LATCH - высокий уровень
  delay(30);                     // Скорость анимации
}
