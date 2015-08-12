#include <Wire.h>
#include <CapacitiveSensor.h>
#include <Piccolino_OLED.h>
/**
 * Based on which sensor is pressed this shows different messages
 */

Piccolino_OLED     screen;
CapacitiveSensor   tleft = CapacitiveSensor(2,3);
CapacitiveSensor   tright = CapacitiveSensor(2,4);

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

void loop()
{
    long start = millis();
    long sen_left =  tleft.capacitiveSensor(30)/10;
    long sen_right =  tright.capacitiveSensor(30)/10;

    screen.clear();
    screen.setTextSize(2);
    screen.setCursor(0,0);

    if(touched(sen_left) && touched(sen_right)) {
      screen.setTextSize(1);
      Serial.print(F("BOTH\n"));
      screen.print(F("STOP IT!!\nOnly one at a time!\nUnless you want the\nMadRussian to come\nafter you\n"));
    } else if(touched(sen_left)) {
      Serial.print(F("LEFT\n"));
      screen.print(F("Red Pill\n"));
    } else if(touched(sen_right)) {
      Serial.print(F("RIGHT\n"));
      screen.print(F("Blue Pill\n"));
    } else {
      screen.print(F("Touch my\nsensors!!!"));
    }
    screen.update();
}
