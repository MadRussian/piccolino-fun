#include <Wire.h>
#include <CapacitiveSensor.h>
#include <Piccolino_OLED.h>
/**
 * Nodar Nutsubidze
 *
 * This will start off in a blinking mode where it turns on the
 * LED at pin 15.
 *
 * When both the sensors are held Piccolino will go into User Mode.
 * In user mode when the left sensor is held it will switch the LED off.
 * When the right sensor is held it will switch the LED on.
 *
 * To go back into blink mode just hold down both sensors again.
 *
 * Pin 15 is used so that you can play around with a custom LED. If you
 * do not have an LED lying around (who are you!!). If you have the carrier
 * board you can switch the led variable to be 13. The carrier board has an led
 * on pin 13.
 */

Piccolino_OLED     screen;
CapacitiveSensor   tleft = CapacitiveSensor(2,3);
CapacitiveSensor   tright = CapacitiveSensor(2,4);

#define TRIGGER_LEVEL 50// change as appropriate
int led = 15;

// Whether its under user control
bool user_controlled = false;

// LED state
int led_state = HIGH;

void setup()
{
   Serial.begin(9600);
   screen.begin();
   screen.setTextSize(3);
   pinMode(led, OUTPUT);
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
 * Print to the screen a message
 * This will also log it to the serial console.
 */
void print_screen(const __FlashStringHelper *msg)
{
  screen.clear();
  screen.setCursor(0,0);
  screen.print(msg);
  screen.update();
  Serial.print(msg);
}

/**
 * Sets the global LED state, this is used when the LED
 * is user controlled
 */
void set_led_state(int state)
{
  led_state = state;
  digitalWrite(led, state);
  if(state == HIGH) {
    print_screen(F("ON\n"));
  } else {
    print_screen(F("OFF\n"));
  }
}

/**
 * Perform 1 blink
 */
void do_blink()
{
  digitalWrite(led, HIGH);
  print_screen(F("ON\n"));
  delay(500);
  digitalWrite(led, LOW);
  print_screen(F("OFF\n"));
  delay(500);
}

void loop()
{
  // Get how long each sensor has been held
  long start = millis();
  long sen_left =  tleft.capacitiveSensor(30)/10;
  long sen_right =  tright.capacitiveSensor(30)/10;

  // If both are pressed then we toggle whether its user controlled
  if(touched(sen_left) && touched(sen_right)) {
    user_controlled = !user_controlled;
    screen.setTextSize(1);
    if(user_controlled) {
      print_screen(F("User Control"));
    } else {
      print_screen(F("Blink mode"));
    }
    screen.setTextSize(3);
    delay(1000);
    return;
  }
  // Blink mode
  if(!user_controlled) {
    do_blink();
  } else if(touched(sen_left)) {
    set_led_state(LOW);
  } else if(touched(sen_right)) {
    set_led_state(HIGH);
  } else {
    set_led_state(led_state);
  }
}
