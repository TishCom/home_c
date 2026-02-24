#include <PWM.h>

#define PUSK    2     //Пин кнопки пуск/стоп
#define STEP    3     //Пин тактирования
#define ENB     5     //Пин отключения двигателя
#define INDUP   6     //Пин датчика индуктивности верхнего

#define DELBT   50   //Задержка для проверки истинности нажатия кнопки, по умолчанию 250 мсек.

bool flgRun = false;  //Флаг запуска (1) или остановки (0) двигателя

//Переменные для антистатической кнопки
bool flgbtn1 = false;
uint32_t timing1 = 0;
uint32_t timing2 = 0;

void setup() 
{
  InitTimersSafe(); 

  SetPinFrequencySafe(STEP, 885);
  
  pinMode(PUSK, INPUT);
  pinMode(INDUP, INPUT);

  pinMode(ENB, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void loop() {
  PressPUSK();

  if(flgRun)
  {
 //   timing2 = millis();
    digitalWrite(ENB, 0);
    pwmWrite(STEP, 128);
    flgRun = false;
  }
 /*
  if((millis() - timing2 > 200))
  {
    pwmWrite(STEP, 0);
    
    digitalWrite(ENB, 1);
    delay(1000);
  }
*/

  if(!digitalRead(INDUP))
  {
    pwmWrite(STEP, 0);
    digitalWrite(ENB, 1);
    delay(3000);
  }
}

//Обработчик нажатия кнопки ПУСК
void PressPUSK(void) 
{
  if (digitalRead(PUSK) && !flgbtn1) 
  {                      
    timing1 = millis();                                     
    flgbtn1 = true;                                         
  }
  else if (!digitalRead(PUSK))
  {
    flgbtn1 = false;  
  }
  
  if (flgbtn1 && (millis() - timing1 > DELBT))     
     flgRun = true;                      
}
