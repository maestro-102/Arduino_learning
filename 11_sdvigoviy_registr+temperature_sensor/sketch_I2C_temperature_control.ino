/* Чтение температуры из I2C-датчика, отображение на светодиодной шкале
и вывод значений в Processing-приложение */

#include <Wire.h>                  // Подключение библиотеки Wire
const int SER = 8;                 // Подключение вывода DATA 74HC595
const int LATCH = 9;               // Подключение вывода LATCH 74HC595
const int CLK = 10;                // Подключение вывода CLOCK 74HC595
int temp_adress = 72;              // Запись адреса 1001000

int vals[8] = {1, 3, 7, 15, 31, 63, 127, 255};      // Значения светодиодов

void setup() {                    
 Serial.begin(9600);              // запуск последовательного порта
 Wire.begin();                    // Создание объекта Wire
    // Конфигурация портов как выход
 pinMode(SER, OUTPUT);
 pinMode(LATCH, OUTPUT);
 pinMode(CLK, OUTPUT);
}

void loop() {
    // Отправка запроса
  Wire.beginTransmission(temp_adress);    // Выбор устройства отправкой адреса устройства
  Wire.write(0);                          // Установка бита asking в 0 для чтения
  Wire.endTransmission();                 // Отправка стоп-бита

    // Чтение данных (температуры) из устройства
  Wire.requestFrom(temp_adress, 1);       // Получить 1 байт по адресу устройства
  while(Wire.available() == 0);           // Ожидание ответа
  int c = Wire.read();                    // Чтение данных в переменную с
  

    // Масштабирование температуры для светодиодной шкалы
  int graph = map(c, 24, 31, 0, 7);
  graph = constrain(graph, 0, 7);
  digitalWrite(LATCH, LOW);               // LATCH - низкий - начало отправки
  shiftOut(SER, CLK, MSBFIRST, vals[graph]);    // Отправка, старший бит - первый
  digitalWrite(LATCH, HIGH);              // LATCH - высокий - окончание отправки

  int f = round(c*9.0/5.0 + 32.0);        // Перевод данных из шкалы Цельсия в шкалу Фаренгейта

    // Отправка значений в градусах Цельсия и Фаренгейта в последовательный порт
  Serial.print(c);
  Serial.print("C, ");
  Serial.print (f);
  Serial.print("F. ");
  delay(500);
}
