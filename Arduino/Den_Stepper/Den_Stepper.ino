#include <PWM.h>

#define PUSK      2               //Пин кнопки пуск/стоп
#define STEP      3               //Пин тактирования
#define DIR       4               //Пин направления
#define ENB       5               //Пин отключения двигателя
#define INDUP     6               //Пин датчика индуктивности верхнего

#define DIR_UP    0               //Направление вверх
#define DIR_DWN   1               //Направление вниз

#define FREQ_UP   735             //Частота при направлении вверх
#define FREQ_DWN  FREQ_UP * 4     //Частота при направлении вниз

#define TIMING    5000            //Время отработки движения вниз(мс)

#define DELBT     100             //Задержка для проверки истинности нажатия кнопки, по умолчанию 250 мсек.

bool flgRun = false;  //Флаг запуска (1) или остановки (0) двигателя

//Переменные для антистатической кнопки
bool flgbtn1 = false;
uint32_t timing1 = 0;
uint32_t timing2 = 0;

bool flgUp = false;

void setup() 
{
  InitTimersSafe(); 
  
  pinMode(PUSK, INPUT);
  pinMode(INDUP, INPUT);

  pinMode(ENB, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void loop() {
  PressPUSK();

  if(flgRun)
  {
    SetPinFrequencySafe(STEP, FREQ_UP);
    digitalWrite(ENB, 0);
    digitalWrite(DIR, DIR_UP);
    pwmWrite(STEP, 128);
    flgRun = false;
  }

  if(!digitalRead(INDUP))
  {
    digitalWrite(DIR, DIR_DWN);
    SetPinFrequencySafe(STEP, FREQ_DWN);
    pwmWrite(STEP, 128);
    timing2 = millis();
    flgUp = true;
  }

  if(flgUp && (millis() - timing2 > TIMING))
  {
    pwmWrite(STEP, 0);
    digitalWrite(ENB, 1);
    delay(1000);
    flgUp = false;
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
