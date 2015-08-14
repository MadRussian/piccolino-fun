#include <SPI.h>
#include <Wire.h>
#include <Piccolino_OLED.h>

/**
 * Nodar Nutsubidze
 *
 * A drawing experiment for now ...
 */

Piccolino_OLED display;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void setup()
{
  Serial.begin(9600);
  display.begin();
}

/**
 * Show content to the serial. This allows for a formatted string
 *
 * This adds a \r\n so that serial output looks good
 */
void debug(const char *format, ...)
{
  char buffer[128];
  va_list ap;
  int done;

  va_start(ap, format);
  done = vsnprintf(buffer, sizeof(buffer), format, ap);
  va_end(ap);
  Serial.print(buffer);
  Serial.print("\r\n");
}

/**
 * Show random dots every 10ms
 */
void random_dots()
{
  int x = rand() % SCREEN_WIDTH;
  int y = rand() % SCREEN_HEIGHT;

  display.clear();
  display.drawPixel(x, y, WHITE);
  debug("(%d,%d)", x, y);
  display.update();
  delay(10);
}

void loop()
{
  random_dots();
}
