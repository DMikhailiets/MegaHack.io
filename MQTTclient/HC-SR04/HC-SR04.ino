//Тестировалось на Arduino IDE 1.0.1
#define Trig 9
#define Echo 8
#define ledPin 13

void setup() 
{  
  pinMode(Trig, OUTPUT); //инициируем как выход 
  pinMode(Echo, INPUT); //инициируем как вход 
  pinMode(ledPin, OUTPUT); 
  pinMode(4, OUTPUT); 
  Serial.begin(9600); 
  /* задаем скорость общения. В нашем случае с компьютером */
} 
unsigned int impulseTime=0; 
unsigned int distance_sm=0; 

void loop() 
{  
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем 
  impulseTime=pulseIn(Echo, HIGH); // Замеряем длину импульса 
  distance_sm=impulseTime/58; // Пересчитываем в сантиметры 
  Serial.println(distance_sm); // Выводим на порт 
  if (distance_sm<60) // Если расстояние менее 30 сантиметром 
  {     
    digitalWrite(4, HIGH); // Светодиод горит 
  }  
  else 
  {   
    digitalWrite(4, LOW); // иначе не горит 
  }   
  delay(100); 
  /* ждем 0.1 секунды, Следующий импульс может быть излучён, только после исчезновения эха от предыдущего. 
   Это время называется периодом цикла (cycle period). 
   Рекомендованный период между импульсами должен быть не менее 50 мс.  */
}
