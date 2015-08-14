#include <SPI.h>
#include <Wire.h>
#include <Piccolino_OLED.h>
#include <math.h>

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
 * NOTE: Do not include %f into the format string. This will not
 * work with avr libc. You must use dtostrf first.
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
 * Debug a double value
 */
void debug_double(double val, int precision, const char *msg)
{
  char val_str[32];
  dtostrf(val, precision, precision, val_str);
  debug("%s: %s", msg, val_str);
}

/**
 * Show random dots every 10ms
 */
void random_dots()
{
  int x = rand() % SCREEN_WIDTH;
  int y = rand() % SCREEN_HEIGHT;

  display.clear();
  debug("(%d,%d)", x, y);
  display.drawPixel(x, y, WHITE);
  display.update();
}

/**
 * Show random sized dots every 10ms
 */
void random_sized_dots()
{
  int x = rand() % SCREEN_WIDTH;
  int y = rand() % SCREEN_HEIGHT;
  int size = rand() % 10;

  display.clear();
  debug("(%d,%d) size: %d", x, y, size);
  int ix, jx;
  for(ix = x - size; ix < x + size; ix++) {
    for(jx = y - size; jx < y + size; jx++) {
      display.drawPixel(ix, jx, WHITE);
    }
  }
  display.update();
}

/**
 * Draw a circle
 *
 * @param cx Center of the circle - X
 * @param cy Center of the circle - Y
 * @param radius Radius of the circle
 * @param bg If true this will fill in the circle
 */
void draw_circle(int cx, int cy, int radius, bool bg)
{
  int deg;
  double px, py;
  for(deg = 0; deg < 360; deg++) {
    px = cx + (cos(deg) * radius);
    py = cy + (sin(deg) * radius);
    display.drawPixel(px, py, WHITE);

    // Filling
    if(bg) {
      int ix;
      if(px >= cx) {
        for(ix = cx; ix < px; ix++) {
          display.drawPixel(ix, py, WHITE);
        }
      } else {
        for(ix = cx; ix > px; ix--) {
          display.drawPixel(ix, py, WHITE);
        }
      }
    }
  }
  display.update();
}

/**
 * Draw random circles
 */
void random_circles()
{
  display.clear();
  int cx = 20 + rand() % (SCREEN_WIDTH / 2);
  int cy = 5 + rand() % (SCREEN_HEIGHT / 2);
  int radius = rand() % 20;
  int bg = rand() % 2;
  draw_circle(cx, cy, radius, bg);
}

void loop()
{
  random_dots();
  random_sized_dots();
  random_circles();
}
