#include <PreciseLM35.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SleepyDog.h>
#include <DigitalIO.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

DigitalPin<2> RELAY_PIN;
PreciseLM35 LM35(A0, DEFAULT);
const float TARGET_TEMPERATURE=33.0;
const float TARGET_TEMPERATURE_MIN=30;
const float TARGET_TEMPERATURE_MAX=36.0;
const int TARGET_SUSTAIN_TIME=120;

void setup() {
  Serial.begin(9600);
  RELAY_PIN.mode(OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

  Watchdog.enable(5000);
}

void printValue(int counter, float temp) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.print(counter);
    display.setCursor(12,12);
    display.setTextSize(3);
    display.print(((int)(temp*100))/100.0);
    display.print("C");
    display.display();

    delay(1);
}

unsigned long getTempStartTime;

float getTemp() {
  double avgTemp=0;
  int count=0;
  getTempStartTime=millis();
  while( millis()-getTempStartTime<1000 ) {
    avgTemp+=LM35.readCelsius();
    count++;
  }
  return (float)(avgTemp/count);
}

void loop() {
  float currTemp=getTemp();
  if ( currTemp >= TARGET_TEMPERATURE ) {
    RELAY_PIN.high();
    int counter=0;
    while (counter<TARGET_SUSTAIN_TIME) {
      float reading=getTemp();
      printValue(counter,reading);
      if (reading < TARGET_TEMPERATURE_MIN) counter=TARGET_SUSTAIN_TIME;
      else if (reading < TARGET_TEMPERATURE) counter++;
      else counter=0;
      Watchdog.reset();
    }
    RELAY_PIN.low();
    counter=0;
    while (counter<TARGET_SUSTAIN_TIME) {
      float reading=getTemp();
      printValue(counter,reading);
      if (reading >= TARGET_TEMPERATURE_MAX) counter=TARGET_SUSTAIN_TIME;
      else if (reading >= TARGET_TEMPERATURE) counter++;
      else counter=0;
      Watchdog.reset();
    }
  } else {
      RELAY_PIN.low();
      printValue(0,currTemp);
      Watchdog.reset();
  }
}

