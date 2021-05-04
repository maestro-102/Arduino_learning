/* Управление двигателем через драйвер SN754410*/

const int EN1 = 9;                // Вход включения двигателя 1 EN1
const int EN2 = 8;                // Вход включения двигателя 2 EN2
const int MC1 = 3;                // Вход 1 управления двигателем 1
const int MC2 = 2;                // Вход 2 управления двигателем 1
const int MC3 = 5;                // Вход 3 управления двигателем 2
const int MC4 = 4;                // Вход 4 управления двигателем 2
const int POT1 = 0;               // Аналоговый вход A0 для подключения потенциометра
const int POT2 = 1;               // Аналоговый вход A1 для подключения потенциометра
int val1 = 0;                     // Переменная для хранения значений потенциометра 1
int val2 = 0;                     // Переменная для хранения значений потенциометра 2
int velocity1 = 0;                // Переменная для хранения скорости вращения двигателя 1 (0-255)
int velocity2 = 0;                // Переменная для хранения скорости вращения двигателя 2 (0-255)

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(MC3, OUTPUT);
  pinMode(MC4, OUTPUT);
  brake1();                        // Остановка 1 двигателя при инициализации
  brake2();                        // Остановка 2 двигателя при инициализации
}

void loop() {
  val1 = analogRead(POT1);
  val2 = analogRead(POT2);

  // Движение вперед 1 двигателя
  if (val1 > 562) {
    velocity1 = map(val1, 563, 1023, 0, 255);
    forward1(velocity1);
  }
  // Движение назад 1 двигателя
  else if (val1 < 462) {
    velocity1 = map(val1, 461, 0, 0, 255);
    reverse1(velocity1);
  }
  // Остановка 1 двигателя
  else {
    brake1();
  }
  
  // Движение вперед 2 двигателя
  if (val2 > 562) {
    velocity2 = map(val2, 563, 1023, 0, 255);
    forward2(velocity2);
  }
  // Движение назад 2 двигателя
  else if (val2 < 462) {
    velocity2 = map(val2, 461, 0, 0, 255);
    reverse2(velocity2);
  }
  // Остановка 2 двигателя
  else {
    brake2();
  }
}

// Вращение вперед с заданной скоростью 1 двигателя(диапазон 0-255)
void forward1(int rate) {
  digitalWrite(EN1, HIGH);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN1, rate);
}
// Вращение вперед с заданной скоростью 2 двигателя(диапазон 0-255)
void forward2(int rate) {
  digitalWrite(EN2, HIGH);
  digitalWrite(MC3, HIGH);
  digitalWrite(MC4, LOW);
  analogWrite(EN2, rate);
}

// Вращение в обратном направлении с заданной скоростью 1 двигателя(диапазон 0-255)
void reverse1 (int rate) {
  digitalWrite(EN1, HIGH);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN1, rate);
}
// Вращение в обратном направлении с заданной скоростью 2 двигателя(диапазон 0-255)
void reverse2 (int rate) {
  digitalWrite(EN2, HIGH);
  digitalWrite(MC3, LOW);
  digitalWrite(MC4, HIGH);
  analogWrite(EN2, rate);
}

// Остановка двигателя 1 двигателя
void brake1() {
  digitalWrite(EN1, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN1, HIGH);
}
// Остановка двигателя 2 двигателя
void brake2() {
  digitalWrite(EN2, LOW);
  digitalWrite(MC3, LOW);
  digitalWrite(MC4, LOW);
  digitalWrite(EN2, HIGH);
}
