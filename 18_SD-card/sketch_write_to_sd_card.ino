/* Запись данных на SD-карту */

#include<SD.h>                    // Подключение библиотеки SD

// Подключение выводов
//MOSI = pin 11
//MISO = pin 12
//SCLK = pin 13

const int CS_PIN = 10;            // Подключение контакта выбора CS
const int POW_PIN = 8;            // Контакт для питания SD-карты

void setup() {                    
 Serial.begin(9600);
 Serial.println("Initializing Card");
 pinMode(CS_PIN, OUTPUT);         // Установить CS как выход
 pinMode(POW_PIN, OUTPUT);        // Для питания карты (используется вывод 8) установить HIGH
 digitalWrite(POW_PIN, OUTPUT);
 if (!SD.begin(CS_PIN)) {
  Serial.println("Card Failure");
  return;
 }
 Serial.println("Card Ready");
}

void loop() {
 long timeStamp = millis();
 String dataString = "Hello There!";
 File dataFile = SD.open("log.csv", FILE_WRITE);        // Открыть файл и записать в него
 if (dataFile) {
  dataFile.print(timeStamp);
  dataFile.print(",");
  dataFile.println(dataString);
  dataFile.close();                         // Данные не записаны, пока соединение не закрыто!

  // Вывод в монитор для отладки
  Serial.print(timeStamp);
  Serial.print(",");
  Serial.println(dataString);
 }
 else {
  Serial.println("Couldn't open log file");
 }
 delay(5000);
}
