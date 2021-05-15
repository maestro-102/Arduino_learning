/* Чтение и запись данных на SD-карту с использованием RTC */

#include<SD.h>                    // Подключение библиотеки SD
#include<Wire.h>                  // Для работы с модулем RTC
#include "RTClib.h"                // Подключение библиотеки RTC

// Подключение устройств SPI и I2C с выводами по умолчанию
// SD-карта - SPI выводы
// RTC модуль - стандартные I2C контакты

// Подключение выводов
//MOSI = pin 11
//MISO = pin 12
//SCLK = pin 13

const int CS_PIN = 10;            // Подключение контакта выбора CS
const int SD_POW_PIN = 8;         // Контакт для питания SD-карты
const int RTC_POW_PIN = A3;
const int RTC_GND_PIN = A2;
int refresh_rate = 5000;          // Скорость опроса по умолчанию (5 сек)
RTC_DS1307 RTC;                   // Создание объекта RTC
String year, month, day, hour, minute, second, time, date;          // Переменные для даты и времени

void setup() {                    
 Serial.begin(9600);
 Serial.println(F("Initializing Card"));
 pinMode(CS_PIN, OUTPUT);             // Установить CS как выход
 pinMode(SD_POW_PIN, OUTPUT);         // Для питания карты (используется вывод 8) установить HIGH
 pinMode(RTC_POW_PIN, OUTPUT);
 pinMode(RTC_GND_PIN, OUTPUT);

 // Установка питания карты и RTC
 digitalWrite(SD_POW_PIN, HIGH);
 digitalWrite(RTC_POW_PIN, HIGH);
 digitalWrite(RTC_GND_PIN, LOW);

 // Инициализация Wire и RTC
 Wire.begin();
 RTC.begin();

 // Если RTC не запущены, загрузить дату/время с компьютера
 if (!RTC.isrunning()) {
  Serial.println(F("RTC is NOT running!"));
  RTC.adjust(DateTime(__DATE__, __TIME__));
 }

 // Инициализация SD-карты
 if (!SD.begin(CS_PIN)) {
  Serial.println(F("Card Failure"));
  return;
 }
 Serial.println(F("Card Ready"));

 // Чтение настроек конфигурационного файла (speed.txt)
 File commandFile = SD.open("speed.txt");     // Открыть файл настроек
 if (commandFile) {
  Serial.println(F("Reading Command File"));
  while (commandFile.available()) {
    refresh_rate = commandFile.parseInt();
  }
  Serial.print(F("Refresh Rate = "));
  Serial.print(refresh_rate);
  Serial.println(F("ms"));
  commandFile.close();                // Закрыть файл настроек
 }
 else {
  Serial.println(F("Could not read command file"));
  return;
 }

 // Запись заголовка
 File dataFile = SD.open("log.csv", FILE_WRITE);
 if (dataFile) {
  dataFile.println(F("\nNew Log Started!"));
  dataFile.println(F("Date, Time, Phrase"));
  dataFile.close();

  // Запись в последовательный порт
  Serial.println(F("\nNew Log Started!"));
  Serial.println(F("Date, Time, Phrase"));
 }
 else {
  Serial.println(F("\nCouldn't open log file"));
 }
}

void loop() {

  // Получить значение даты и времени и перевести в строковые значения
  DateTime datetime = RTC.now();
  year = String(datetime.year(), DEC);
  month = String(datetime.month(), DEC);
  day = String(datetime.day(), DEC);
  hour = String(datetime.hour(), DEC);
  minute = String(datetime.minute(), DEC);
  second = String(datetime.second(), DEC);

  // Собрать строку текущей даты и времени
  date = year + "/" + month + "/" + day;
  time = hour + ":" + minute + ":" + second;
  String dataString = "Hello There!";
  
 //long timeStamp = millis();
 //String dataString = "Hello There!";

 // Открыть файл и записать в него значения
 File dataFile = SD.open("log.csv", FILE_WRITE);        
 if (dataFile) {
  dataFile.print(date);
  dataFile.print(F(","));
  dataFile.print(time);
  dataFile.print(F(","));
  dataFile.println(dataString);
  dataFile.close();                         // Закрыть файл

  // Вывод в последовательный порт для отладки
  Serial.print(date);
  Serial.print(F(","));
  Serial.print(time);
  Serial.print(F(","));
  Serial.println(dataString);
 }
 else {
  Serial.println(F("Couldn't open log file"));
 }
 delay(refresh_rate);
}
