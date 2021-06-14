#include "Adafruit_ThinkInk.h"
#include "Adafruit_NeoPixel.h"
#include <Fonts/FreeSans9pt7b.h>

ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, -1, -1);

int n = 0;
int yesterday = 200;

void mainText() {
  display.setTextSize(2);
  display.setCursor(10, 40);
  display.print("Yesterday: ");
  display.print(yesterday);
  display.setCursor(10, 88);
  display.print("Today: ");
  display.print(n);
}

void buttonLabels() {
  display.setTextSize(1);
  display.setCursor(12, 122);
  display.print("+1");
  display.setCursor(80, 122);
  display.print("+10");
  display.setCursor(153, 122);
  display.print("+20");
  display.setCursor(215, 122);
  display.print("new day");
}

void screenDisplay() {
  display.clearBuffer();
  mainText();
  buttonLabels();
  display.display();
}

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);
  pinMode(NEOPIXEL_POWER, OUTPUT);

  display.begin(THINKINK_GRAYSCALE4);

  display.setFont(&FreeSans9pt7b);
  display.setTextColor(EPD_BLACK);
  screenDisplay();
  digitalWrite(NEOPIXEL_POWER, HIGH);
}

void loop() {

  if (! digitalRead(BUTTON_A)) {
    n = n + 1;
    screenDisplay();
  }

  if (! digitalRead(BUTTON_B)) {
    n = n + 10;
    screenDisplay();
  }

  if (! digitalRead(BUTTON_C)) {
    n = n + 20;
    screenDisplay();
  }

  if (! digitalRead(BUTTON_D)) {
    yesterday = n;
    n = 0;
    screenDisplay();
  }

  // delay
  delay(120);
}
