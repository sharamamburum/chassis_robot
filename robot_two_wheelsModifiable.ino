#include <AFMotor.h> // Подключаем библиотеку для управления двигателями

const int Trig = A2;
const int Echo = A1;
const int ledPin = 13;
//Создаем объекты для двигателей
AF_DCMotor motor1(1); //канал М1 на Motor Shield — задний левый
AF_DCMotor motor2(2); //канал М2 на Motor Shield — задний правый
//AF_DCMotor motor3(3); //канал М3 на Motor Shield — передний левый
//AF_DCMotor motor4(4); //канал М4 на Motor Shield — передний правый

//подключаем выход SIG модуля к выводу 9 платы Arduino.
int led = 9;       // выбираем вывод 9
int brightness;    // устанавливаем начальный уровень яркости
//int fadeAmount = 0;    // шаг изменения яркости
int echoPin = 0;
int trigPin = 1;

void setup()
{
  // delay(5000);
  pinMode(led, OUTPUT);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(ledPin, OUTPUT);
}

unsigned int time_us = 0;
unsigned int distance_sm = 0;

void loop()
{
  int s;
  digitalWrite(Trig, HIGH); // Подаем сигнал на выход микроконтроллера
  delayMicroseconds(10); // Удерживаем 10 микросекунд
  digitalWrite(Trig, LOW); // Затем убираем
  time_us = pulseIn(Echo, HIGH); // Замеряем длину импульса
  distance_sm = time_us / 58; // Пересчитываем в сантиметры
  Serial.println(distance_sm); // Выводим на порт
  if (distance_sm < 45) // Если расстояние менее 45 сантиметром
  {
    digitalWrite(ledPin, 1); // Зажигаем светодиод
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    //motor3.run(RELEASE);
    //motor4.run(RELEASE);
    //отъезжаем назад для маневра
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    //motor3.run(BACKWARD);
    //motor4.run(BACKWARD);
    delay(random(10, 300));
    // Поворот вправо в течении 2 секунд
    s = random(1, 10);
    if (s >= 5)
    {
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      //motor3.run(FORWARD);
      //motor4.run(BACKWARD);
    } else
    {
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      //motor3.run(BACKWARD);
      //motor4.run(FORWARD);
    }
  }
  else
  {
    digitalWrite(ledPin, 0);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    //motor3.run(FORWARD);
    //motor4.run(FORWARD);
  }

  { //motor4.setSpeed(255);
    //motor3.setSpeed(255);
    motor1.setSpeed(255);
    motor2.setSpeed(255);
  }
delay(500);

}
