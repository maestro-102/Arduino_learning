/* Arduino WEB-сервер */

#include<Ethernet.h>                 
#include<SPI.h>                  

const int BLUE = 5;            
const int GREEN = 6;         
const int RED = 7;
const int SPEAKER = 3;

// Переменные для управления RGB светодиодом и динамиком (и для дополнительных устройств)
int freq = 0;
int pin;

// МАС-адрес устройства (на самом устройстве или указанный ниже)
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x4A, 0xE0};

// Сервер на порту 80
EthernetServer server = EthernetServer(80);         // Порт 80
boolean receiving = false;                          // Отслеживание данных GET

void setup() {                    
 Serial.begin(9600);
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT);

 // Соединение с DHCP
 if (!Ethernet.begin(mac)) {
  Serial.println("Could not Configure Ethernet with DHCP");
  return;
 }
 else {
  Serial.println("Ethernet Configured!");
 }

 // Запуск сервера
 server.begin();
 Serial.print("Server Started.\nLocal IP: ");
 Serial.println(Ethernet.localIP());
}

void loop() {
 EthernetClient client = server.available();
 if (client) {

  // Запрос НТТР заканчивается пустой строкой
  boolean currentLineIsBlank = true;
  boolean sentHeader = false;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();                           // Чтение из буфера
      if (receiving && c == ' ') receiving = false;     // Окончание передачи
      if (c == '?') receiving = true;

      // Ожидание данных
      if (receiving) {
        // Данные управления светодиодом (переменная L)
        if (c == 'L') {
          Serial.print("Toggling Pin ");
          pin = client.parseInt();
          Serial.println(pin);
          digitalWrite(pin, !digitalRead(pin));
          break;
        }
        // Команда управления динамиком (переменная S)
        else if (c == 'S') {
          Serial.print("Setting Frequency to ");
          freq = client.parseInt();
          Serial.println(freq);
          if (freq == 0)
            noTone(SPEAKER);
          else
            tone(SPEAKER, freq);
          break;
        }
        // Код для управления дополнительными устройствами добавляется сюда
      }

      // Отправка заголовка ответа
      if (!sentHeader) {
        // Отправить стандартный заголовок НТТР ответа
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html\n");

        // Кнопка переключения красного для RGB
        client.println("<form action='' method='get'>");
        client.println("<input type='hidden' name='L' value='7' />");
        client.println("<input type='submit' value='Toggle Red' />");
        client.println("</form>");

        // Кнопка переключения зеленого для RGB
        client.println("<form action='' method='get'>");
        client.println("<input type='hidden' name='L' value='6' />");
        client.println("<input type='submit' value='Toggle Green' />");
        client.println("</form>");

        // Кнопка переключения синего для RGB
        client.println("<form action='' method='get'>");
        client.println("<input type='hidden' name='L' value='5' />");
        client.println("<input type='submit' value='Toggle Blue' />");
        client.println("</form>");

        // Ползунок выбора частоты динамика
        client.println("<form action='' method='get'>");
        client.print("<input type='range' name='S' min='0' max='1000' step='100' value='0' />");
        client.println("<input type='submit' value='Set Freq.' />");
        client.println("</form>");

        // Добавить формы управления дополнительными устройствами

        sentHeader = true;
      }
      
      if (c == '\n' && currentLineIsBlank) break;
      if (c == '\n') {
        currentLineIsBlank = true;
      }
      else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  delay(5);                           // Дать время веб-браузеру на получение данных
  client.stop();                      // Закрыть соединение
 }
}
