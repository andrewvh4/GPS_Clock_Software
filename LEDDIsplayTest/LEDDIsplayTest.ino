#include "LedControl_modified.h"

LedControl Display(10, 11, 12, 1);
void setup() {
  // put your setup code here, to run once:
  Display.shutdown(0, false);
  Display.clearDisplay(0);
  Display.setIntensity(0, 15);
  delay(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  Display.setRow(0, 0, B11111111);
}
