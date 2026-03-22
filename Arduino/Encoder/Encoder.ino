#include <GyverPWM.h>
#include <GyverEncoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define INPUT_COUNTER   3                               //Пин для входа импульсов энкодер
#define STEP            9                               //Пин тактирования драйвера
#define CUT             7                               //Пин руба
#define SW              4                               //Пин энкодер
#define DT              5                               //Пин энкодер
#define CLK             6                               //Пин энкодер
#define SET_FREQ        A0                              //Пин настройки частоты тактирования драйвера

#define BASE_MULT_FREQ  1000L                           //Константа мультипликатор для частоты
#define MAX_FREQ        1500L                           //ЧМаксимальная частота тактирования драйвера
#define STANDART_FREQ   ((MAX_FREQ) * (BASE_MULT_FREQ)) //Стартовая частота тактирования драйвера
#define FREQ(freq)      ((freq) * (MAX_FREQ))           //Макрос обертка настройки частоты драйвера

#define COUNT_LIMIT     1000                            //Стартовая настройка количества импульсов счета до отруба

#define TIME_CUT        100                             //Время на отруб иглы в мс
#define TIME_STEP       200                             //Время отключения двигателя в мс

//Таймер для руба
uint32_t timingCut = 0;
//Таймер для выключения двигателя
uint32_t timingStep = 0;

//Флаг руба(true - рубит, false -  не рубит)
bool flgCut = false;
//Флаг вращения двигателя(true - вращается, false - не вращается)
bool flagStep = true;

//Меню(true - второй пункт(отображение руба), false - первый пункт(настройка))
bool menu = false;

//Счетчик входных импульсов от энкодера
volatile uint32_t counter = 0;
//Количество импульсов необходимых для руба
uint32_t limCounter = COUNT_LIMIT;

//Энкодер
Encoder enc1(CLK, DT, SW);

//Экран
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  pinMode(STEP, OUTPUT);
  PWM_frequency(STEP, STANDART_FREQ, FAST_PWM);
  PWM_set(STEP, 32000);

  pinMode(CUT, OUTPUT);
  digitalWrite(CUT, LOW);

  pinMode(INPUT_COUNTER, INPUT);
  startCounting();

  enc1.setType(TYPE2);

  lcd.init();                     
  lcd.backlight();
  lcd.clear();
}

void loop() 
{
  uint32_t counterCut = 0;
  int setFreq = analogRead(SET_FREQ);
  PWM_frequency(STEP, FREQ(setFreq), FAST_PWM);

  lcd.clear();
  
  enc1.tick();

  if (enc1.isDouble())
    menu = !menu;

  if (!menu)
  {
    lcd.setCursor(0,0);
    lcd.print("Count: ");
    lcd.print(limCounter);
    lcd.setCursor(0,1);
    lcd.print("Frequency: ");
    lcd.print(setFreq);

    if (enc1.isRight())
      limCounter++; 
    if (enc1.isLeft())
      limCounter--;
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Count: ");
    lcd.print(counter);
    lcd.setCursor(0,1);
    lcd.print("Count cut: ");
    lcd.print(counterCut);
  }
  
  if (counter >= limCounter)
  {
    counter = 0;
    stopCounting();
    counterCut++;

    PWM_set(STEP, 0);
    flagStep = false;
    
    digitalWrite(CUT, HIGH);
    flgCut = true;
    
    timingStep = timingCut = millis();
  }

  if (flgCut && (millis() - timingCut >= TIME_CUT))
  {
    digitalWrite(CUT, LOW);
    flgCut = false;
  }

  if (!flagStep && (millis() - timingStep >= TIME_STEP))
  {
    PWM_set(STEP, 32000);
    flagStep = true;
    startCounting();
  }
}

void countPulse(void) 
{
  counter++;
}

void stopCounting(void) 
{
  detachInterrupt(digitalPinToInterrupt(INPUT_COUNTER));
}

void startCounting(void) 
{
  attachInterrupt(digitalPinToInterrupt(INPUT_COUNTER), countPulse, RISING);
}
