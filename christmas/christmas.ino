#include "FastLED.h"

#define NUM_LEDS 50
#define OFF_TIME 1020

// It makes sense for OFF_TIME to be a multiple of 255

CRGB leds[NUM_LEDS];
CRGBSet ledset(leds, NUM_LEDS);

bool pulsing[NUM_LEDS];
int color[NUM_LEDS];
int goingDirection[NUM_LEDS];
int pulseLength[NUM_LEDS];
int delayCounter[NUM_LEDS];
int skipUp[NUM_LEDS];
int ledToBe;

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
        pulseLength[led_select] = random(5);
        if (pulseLength[led_select] >= 2) {
          delayCounter[led_select] = pulseLength[led_select] - 2;
          skipUp[led_select] = 1;
        } else {
          skipUp[led_select] = delayCounter[led_select] * -1 + 3;
        }
      }
    } else {
      if (pulseLength[led_select] >= 2 && delayCounter[led_select] != 0) {
        delayCounter[led_select] = delayCounter[led_select] - 1;
      } else {
        switch (color[led_select]) {
          case 0:  // Red
            if (leds[led_select].red == 255) {
              goingDirection[led_select] = -1;
            }
            ledToBe = leds[led_select].red + goingDirection[led_select] * skipUp[led_select];
            if (ledToBe > 255) {
              ledToBe = 255;
            } else if (ledToBe <= 0) {
              ledToBe = 0;
              pulsing[led_select] = false;
            }
            leds[led_select].red = ledToBe;
            break;
          case 1:  // Green
            if (leds[led_select].green == 255) {
              goingDirection[led_select] = -1;
            }
            ledToBe = leds[led_select].green + goingDirection[led_select] * skipUp[led_select];
            if (ledToBe > 255) {
              ledToBe = 255;
            } else if (ledToBe <= 0) {
              ledToBe = 0;
              pulsing[led_select] = false;
            }
            leds[led_select].green = ledToBe;
            break;
          case 2:  // White
            if (leds[led_select].blue == 255) {
              goingDirection[led_select] = -1;
            }
            ledToBe = leds[led_select].blue + goingDirection[led_select] * skipUp[led_select];
            if (ledToBe > 255) {
              ledToBe = 255;
            } else if (ledToBe <= 0) {
              ledToBe = 0;
              pulsing[led_select] = false;
            }
            leds[led_select] = CRGB(ledToBe, ledToBe, ledToBe);
            break;
        }
        delayCounter[led_select] = pulseLength[led_select];
      }
    }
  }
  FastLED.show();
}
