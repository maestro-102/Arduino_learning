/* Чтение и запись данных на SD-карту */

#include<SD.h>                    // Подключение библиотеки SD

// Подключение выводов
//MOSI = pin 11
//MISO = pin 12
//SCLK = pin 13

const int CS_PIN = 10;            // Подключение контакта выбора CS
const int POW_PIN = 8;            // Контакт для питания SD-карты
int refresh_rate = 5000;          // Скорость опроса по умолчанию

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

 // Чтение настроек (speed.txt)
 File commandFile = SD.open("speed.txt");     // Открыть файл настроек
 if (commandFile) {
  Serial.println("Reading Command File");
  while (commandFile.available()) {
    refresh_rate = commandFile.parseInt();
  }
  Serial.print("Refresh Rate = ");
  Serial.print(refresh_rate);
  Serial.println("ms");
  commandFile.close();                // Закрыть файл настроек
 }
 else {
  Serial.println("Could not read command file");
  return;
 }
}

void loop() {
 long timeStamp = millis();
 String dataString = "Hello There!";

 // Открыть файл и записать в него
 File dataFile = SD.open("log.csv", FILE_WRITE);        
 if (dataFile) {
  dataFile.print(timeStamp);
  dataFile.print(",");
  dataFile.println(dataString);
  dataFile.close();                         // Закрыть файл

  // Вывод в последовательный порт для отладки
  Serial.print(timeStamp);
  Serial.print(",");
  Serial.println(dataString);
 }
 else {
  Serial.println("Couldn't open log file");
 }
 delay(refresh_rate);
}
