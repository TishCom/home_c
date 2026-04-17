#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define INPUT_COUNTER   3                               //Пин для входа импульсов энкодер
#define STROB           9                               //Пин стробирующий от сигнала на руб

//Флаг руба(true - рубит, false -  не рубит)
bool flgCut = false;
//Флаг строба
bool flagStrob = false;

//Счетчик входных импульсов от энкодера
volatile uint32_t counter = 0;
//Количество импульсов между рубами
uint32_t counterCut = 0;

//Экран
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  pinMode(INPUT_COUNTER, INPUT);
  startCounting();

  pinMode(STROB, INPUT);

  lcd.init();                     
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Count: ");

  counter = 0;
}

void loop() 
{
  if (!flgCut && digitalRead(STROB))
  {
    flagStrob = true;
    flgCut = true;
  }
  else if (!digitalRead(STROB))
    flgCut = false;

  if (flagStrob)
  {
    counterCut = counter;
    counter = 0;
    flagStrob = false;
    printMenu();
  } 
}

void countPulse(void)
{
  counter++;
}

void printMenu(void)
{
  lcd.setCursor(7,0);
  lcd.print("     ");
  lcd.setCursor(7,0);
  lcd.print(counterCut);
}

void stopCounting(void) 
{
  detachInterrupt(digitalPinToInterrupt(INPUT_COUNTER));
}

void startCounting(void) 
{
  attachInterrupt(digitalPinToInterrupt(INPUT_COUNTER), countPulse, RISING);
}
