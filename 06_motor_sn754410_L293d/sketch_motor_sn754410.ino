/* Управление двигателем через драйвер SN754410*/

const int EN = 9;                 //Вход включения двигателя EN
const int MC1 = 3;                //Вход 1 управления двигателем
const int MC2 = 2;                //Вход 2 управления двигателем
const int POT = 0;                //Аналоговый вход 0 для подключения потенциометра
int val = 0;                      //Переменная для хранения значений потенциометра
int velocity = 0;                 //Переменная для хранения скорости вращения двигателя (0-255)

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake();                        //Остановка двигателя при инициализации
}

void loop() {
  val = analogRead(POT);

  //Движение вперед
  if (val > 562) {
    velocity = map(val, 563, 1023, 0, 255);
    forward(velocity);
  }

  //Движение назад
  else if (val < 462) {
    velocity = map(val, 461, 0, 0, 255);
    reverse(velocity);
  }

  //Остановка
  else {
    brake();
  }
}

//Вращение вперед с заданной скоростью (диапазон 0-255)
void forward(int rate) {
  digitalWrite(EN, HIGH);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
}

//Вращение в обратном направлении с заданной скоростью (диапазон 0-255)
void reverse (int rate) {
  digitalWrite(EN, HIGH);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);
}

//Остановка двигателя
void brake() {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, HIGH);
}
