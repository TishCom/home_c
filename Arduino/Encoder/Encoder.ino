#include <GyverButton.h>
#include <GyverPWM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define INPUT_COUNTER   3                               //Пин для входа импульсов энкодер
#define STEP            9                               //Пин тактирования драйвера
#define CUT             7                               //Пин руба
#define BTNUP           4                               //Пин энкодер
#define BTNDN           5                               //Пин энкодер
#define BTNEN           6                               //Пин энкодер
#define SET_FREQ        A7                              //Пин настройки частоты тактирования драйвера

#define BASE_MULT_FREQ  1000L                           //Константа мультипликатор для частоты
#define MAX_FREQ        1500L                           //ЧМаксимальная частота тактирования драйвера
#define STANDART_FREQ   ((MAX_FREQ) * (BASE_MULT_FREQ)) //Стартовая частота тактирования драйвера
#define FREQ(freq)      ((freq) * (MAX_FREQ))           //Макрос обертка настройки частоты драйвера

#define COUNT_LIMIT     1000                            //Стартовая настройка количества импульсов счета до отруба

#define TIME_DAELAY     50                              //Время на отруб иглы в мс
#define TIME_CUT        50                              //Время на отруб иглы в мс
#define TIME_STEP       TIME_DAELAY + TIME_CUT + 50     //Время отключения двигателя в мс

//Таймер для руба
uint32_t timingCut = 0;
//Таймер для выключения двигателя
uint32_t timingStep = 0;
//Таймер для выключения двигателя
uint32_t timingRead = millis();

//Флаг руба(true - рубит, false -  не рубит)
bool flgCut = false;
//Флаг вращения двигателя(true - вращается, false - не вращается)
bool flagStep = true;

//Меню(true - второй пункт(отображение руба), false - первый пункт(настройка))
bool menu = false;
int setFreq = 0;

//Счетчик входных импульсов от энкодера
volatile uint32_t counter = 0;
//Количество импульсов необходимых для руба
uint32_t limCounter = COUNT_LIMIT;
//Количество импульсов необходимых для рубаКолличество отрубленных игл
uint32_t counterCut = 0;

//Экран
LiquidCrystal_I2C lcd(0x27, 16, 2);

GButton buttUp(BTNUP);
GButton buttDn(BTNDN);
GButton buttEn(BTNEN);

void setup() 
{
  pinMode(STEP, OUTPUT);
  PWM_square_D9(MAX_FREQ);

  pinMode(CUT, OUTPUT);
  digitalWrite(CUT, LOW);

  pinMode(INPUT_COUNTER, INPUT);
  startCounting();

  buttUp.setType(HIGH_PULL);
  buttDn.setType(HIGH_PULL);
  buttEn.setType(HIGH_PULL);

  lcd.init();                     
  lcd.backlight();
  lcd.clear();

  counter = 0;
}

void loop() 
{
  setFrequencyStep();
  checkButton();
  printMenu();
  cutPuls();
  
//  if (counter >= limCounter)
//  {
//    counter = 0;
//    stopCounting();
//    counterCut++;
//
//    PWM_detach(9);
//    flagStep = false;
//    
//    digitalWrite(CUT, HIGH);
//    flgCut = true;
//    
//    timingStep = timingCut = millis();
//  }
//
//  if (flgCut && (millis() - timingCut >= TIME_CUT))
//  {
//    digitalWrite(CUT, LOW);
//    flgCut = false;
//  }
//
//  if (!flagStep && (millis() - timingStep >= TIME_STEP))
//  {
//    PWM_set(STEP, 128);
//    flagStep = true;
//    startCounting();
//    counter = 0;
//  }
}

void countPulse(void) 
{
  counter++;
}

void setFrequencyStep(void) 
{
  if (flagStep && millis() - timingRead >= 50)
  {
    timingRead = millis();
    setFreq = analogRead(SET_FREQ);
    PWM_square_D9(setFreq);
  }
}

void checkButton(void) 
{
  buttUp.tick();
  buttDn.tick();
  buttEn.tick();

  if (buttEn.isPress())
    menu = !menu;
    
  if (buttUp.isPress() || buttUp.isHold())
    limCounter++; 
  else if (buttDn.isPress() || buttDn.isHold())
    limCounter--;

  if (buttUp.isRelease())
    buttUp.resetStates(); 
  if (buttDn.isRelease())
    buttDn.resetStates();
}

void printMenu(void) 
{
  if (!menu)
  {
    lcd.setCursor(0,0);
    lcd.print("Count: ");
    lcd.print("     ");
    lcd.setCursor(7,0);
    lcd.print(limCounter);
    lcd.setCursor(0,1);
    lcd.print("Frequency: ");
    lcd.print("     ");
    lcd.setCursor(11,1);
    lcd.print(setFreq);
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Count: ");
    lcd.print("     ");
    lcd.setCursor(7,0);
    lcd.print(counter);
    lcd.setCursor(0,1);
    lcd.print("Count cut: ");
    lcd.print("     ");
    lcd.setCursor(12,1);
    lcd.print(counterCut);
  }
}

void cutPuls(void) 
{
  if (counter >= limCounter)
  {
    counter = 0;
    stopCounting();
    counterCut++;

    PWM_detach(9);
    flagStep = false;
    
    timingStep = timingCut = millis();
  }

  if ((millis() - timingCut >= TIME_DAELAY))
  {
    digitalWrite(CUT, HIGH);
    flgCut = true;
    timingCut = millis();
  }

  if (flgCut && (millis() - timingCut >= TIME_CUT))
  {
    digitalWrite(CUT, LOW);
    flgCut = false;
  }

  if (!flagStep && (millis() - timingStep >= TIME_STEP))
  {
    PWM_set(STEP, 128);
    flagStep = true;
    startCounting();
    counter = 0;
  }
}

void stopCounting(void) 
{
  detachInterrupt(digitalPinToInterrupt(INPUT_COUNTER));
}

void startCounting(void) 
{
  attachInterrupt(digitalPinToInterrupt(INPUT_COUNTER), countPulse, RISING);
}
