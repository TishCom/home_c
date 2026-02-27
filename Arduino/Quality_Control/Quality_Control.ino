#include <PWM.h>

#define PUSK        2     //Пин кнопки пуск
#define STOP        3     //Пин кнопки стоп
#define STEP        4     //Пин тактирования
#define ENB         5     //Пин enable
#define DIR         6     //Пин напрвыления двигателя
#define ENGINE      7     //Пин основного двигателя
#define IND_ENGINE  8     //Пин основного датчика индуктивности
#define IND_LEFT    9     //Пин левого датчика индуктивности 
#define IND_RIGHT   10    //Пин правого датчика индуктивности 
#define TIME        A0    //Пин enable

#define DELBT       100   //Задержка для проверки истинности нажатия кнопки, по умолчанию 250 мсек.

#define FREQ        1500  //Частота шагового двигателя

#define LEFT        0
#define RIGHT       1

//Флаг запуска (1) или остановки (0) двигателя
bool flgRun = false;  

//Флаг запуска нахождения основного датчика
bool flgEng = false; 

//Переменные для антистатической кнопки
bool flgbtn1 = false;
bool flgbtn2 = false;
uint32_t timing1 = 0;
uint32_t timing2 = 0;

//Таймер отработки датчика
uint32_t timing3 = 0;

void setup() 
{
  InitTimersSafe(); 
  SetPinFrequencySafe(STEP, FREQ);
  
  pinMode(PUSK, INPUT);
  pinMode(STOP, INPUT);
  pinMode(IND_ENGINE, INPUT);
  pinMode(IND_LEFT, INPUT);
  pinMode(IND_RIGHT, INPUT);

  pinMode(ENB, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENGINE, OUTPUT);
  pinMode(STEP, OUTPUT);

  digitalWrite(ENGINE, 0);
  digitalWrite(ENB, 0);
  digitalWrite(DIR, LEFT);
  pwmWrite(STEP, 0);
}

void loop() {
  CheckButton();

  if(flgRun)
    digitalWrite(ENGINE, 1);
  else if(!flgRun)
    digitalWrite(ENGINE, 0);

  if(digitalRead(IND_ENGINE))
  {
    timing3 = millis();
    pwmWrite(STEP, 128);
    flgEng = true; 
  }

  if(flgEng && (millis() - timing3 > analogRead(TIME)))
  {
    pwmWrite(STEP, 0);
    flgEng = false; 
  }

  if(digitalRead(IND_LEFT))
    digitalWrite(DIR, RIGHT);
  else if(digitalRead(IND_RIGHT))
    digitalWrite(DIR, LEFT);
}

//Обработчик нажатия кнопок
void CheckButton(void) 
{
  PressPUSK();
  PressSTOP();                     
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

//Обработчик нажатия кнопки СТОП
void PressSTOP(void) 
{
  if (digitalRead(STOP) && !flgbtn2) 
  {                      
    timing2 = millis();                                     
    flgbtn2 = true;                                         
  }
  else if (!digitalRead(STOP))
  {
    flgbtn2 = false;  
  }
  
  if (flgbtn2 && (millis() - timing2 > DELBT))     
     flgRun = false;                      
}
