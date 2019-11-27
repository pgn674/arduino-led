#include "FastLED.h"

#define NUM_LEDS 50
#define OFF_TIME 1020

CRGB leds[NUM_LEDS];
CRGBSet ledset(leds, NUM_LEDS);

bool pulsing[NUM_LEDS];
int color[NUM_LEDS];
int goingDirection[NUM_LEDS];
int pulseDelay[NUM_LEDS];
int delayCounter[NUM_LEDS];

void setup() {
  randomSeed(analogRead(0));
  
  FastLED.addLeds<WS2811, 6>(leds, NUM_LEDS);
  
  // Flash so I know that the program has restarted.
  ledset(0, NUM_LEDS - 1) = CRGB::Black;
  FastLED.show();
  delay(200);
  ledset(0, NUM_LEDS - 1) = CRGB::White;
  FastLED.show();
  delay(200);
  ledset(0, NUM_LEDS - 1) = CRGB::Black;
  FastLED.show();
  delay(200);
}

void loop() {
  for (int led_select = 0; led_select < NUM_LEDS; led_select++) {
    if (!pulsing[led_select]) {
      if (random(OFF_TIME) == 0) {
        pulsing[led_select] = true;
        color[led_select] = random(3);
        goingDirection[led_select] = 1;
        pulseDelay[led_select] = random(3);
        delayCounter[led_select] = pulseDelay[led_select];
      }
    } else {
      if (delayCounter[led_select] != 0) {
        delayCounter[led_select] = delayCounter[led_select] - 1;
      } else {
        switch (color[led_select]) {
          case 0:  // Red
            if (leds[led_select].red == 1 && goingDirection[led_select] == -1) {
              leds[led_select].red = 0;
              pulsing[led_select] = false;
            } else if (leds[led_select].red == 255) {
              goingDirection[led_select] = -1;
              leds[led_select].red = leds[led_select].red + goingDirection[led_select];
            } else {
              leds[led_select].red = leds[led_select].red + goingDirection[led_select];
            }
            break;
          case 1:  // Green
            if (leds[led_select].green == 1 && goingDirection[led_select] == -1) {
              leds[led_select].green = 0;
              pulsing[led_select] = false;
            } else if (leds[led_select].green == 255) {
              goingDirection[led_select] = -1;
              leds[led_select].green = leds[led_select].green + goingDirection[led_select];
            } else {
              leds[led_select].green= leds[led_select].green + goingDirection[led_select];
            }
            break;
          case 2:  // White
            if (leds[led_select].blue == 1 && goingDirection[led_select] == -1) {
              leds[led_select] = CRGB(0, 0, 0);
              pulsing[led_select] = false;
            } else if (leds[led_select].blue == 255) {
              goingDirection[led_select] = -1;
              leds[led_select] = CRGB(leds[led_select].blue + goingDirection[led_select], leds[led_select].blue + goingDirection[led_select], leds[led_select].blue + goingDirection[led_select]);
            } else {
              leds[led_select] = CRGB(leds[led_select].blue + goingDirection[led_select], leds[led_select].blue + goingDirection[led_select], leds[led_select].blue + goingDirection[led_select]);
            }
            break;
        }
        delayCounter[led_select] = pulseDelay[led_select];
      }
    }
  }
  FastLED.show();
}
