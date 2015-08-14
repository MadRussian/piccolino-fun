#include <Wire.h>
#include <CapacitiveSensor.h>
#include <Piccolino_OLED.h>
/**
 * Nodar Nutsubidze
 *
 * This shows text to the screen and using the sensors in the Piccolino changes
 * the font size of the text. Left to decrease and Right to increase.
 */

Piccolino_OLED     screen;
CapacitiveSensor   tleft = CapacitiveSensor(2,3);
CapacitiveSensor   tright = CapacitiveSensor(2,4);
int font_size      = 2;

#define TRIGGER_LEVEL 100// change as appropriate

void setup()
{
   Serial.begin(9600);
   screen.begin();
}

/**
 * Whether a sensor is being touched
 */
bool touched(long sensor)
{
  if(sensor > TRIGGER_LEVEL) {
    return true;
  }
  return false;
}

/**
 * Show and log a message
 */

void loop()
{
    long start = millis();
    long sen_left =  tleft.capacitiveSensor(30)/10;
    long sen_right =  tright.capacitiveSensor(30)/10;

    screen.clear();
    screen.setCursor(0,0);

    screen.setTextSize(2);
    if(touched(sen_left) && touched(sen_right)) {
      screen.setTextSize(2);
      Serial.print(F("Press one or the other\n"));
      screen.print(F("Press one or the other\n"));
    } else if(touched(sen_left)) {
      font_size--;
      Serial.print(F("Font size decreased\n"));
    } else if(touched(sen_right)) {
      font_size++;
      Serial.print(F("Font size increased\n"));
    }
    if(font_size < 1) {
      font_size = 1;
    }
    if(font_size > 3) {
      font_size = 3;
    }
    screen.setTextSize(font_size);
    screen.print("Hello World!\n");
    screen.update();
}
