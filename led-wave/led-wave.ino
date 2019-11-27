#include "FastLED.h"
#define SLOWNESS 256
#define NUM_LEDS 50
#define BRIGHTNESS 1.0
#define SLOW_SPEED 9.0
#define MEDIUM_SPEED 10.0
#define FAST_SPEED 11.0
#define SLOW_DIRECTION 1
#define MEDIUM_DIRECTION -1
#define FAST_DIRECTION 1
#define WAVE_LENGTH 50
#define RANDOM true
#define CHANGE_PERIOD 2500


// Defaults
// SLOWNESS: 256.0
//     (OR): 64.0
// NUM_LEDS: 50
// BRIGHTNESS: 1.0
// SLOW_SPEED: 3.0/3.0
// MEDIUM_SPEED: 4.0/3.0
// FAST_SPEED: 5.0/3.0
// SLOW_DIRECTION: 1
// MEDIUM_DIRECTION: 1
// FAST_DIRECTION: 1
// WAVE_LENGTH: 50
// RANDOM false
// CHANGE_PERIOD 2500

// Slow is Red
// Medium is Green
// Fast is Blue
// "Slowness" is "How many steps it takes to get from minimum brightness to maximum"

// If you wish to change the speeds, I recomend this method:
// Chose three positive seqencial integers: A, B, C. If these hold true:
// LCM(A,B)=A*B
// LCM(A,C)=A*C
// LCM(B,C)=B*C
// LCM(A,B,C)=A*B*C
// Then you got a good set. Set the speeds like this:
// Slow speed: A/A
// Medium speed: B/A
// Fast speed: C/A
// A higher set of integers will result in a longer pattern before it repeats.
// Some examples are | 3,4,5 | 5,6,7 | 7,8,9 | 9,10,11 |


// Creates fancy array named "leds" of size 1
CRGB leds[NUM_LEDS];
CRGBSet ledset(leds, NUM_LEDS);
//CRGBArray<NUM_LEDS> ledset;

int timey = 0;
int slow;
int medium;
int fast;
int current_slow_speed = SLOW_SPEED;
int current_medium_speed = MEDIUM_SPEED;
int current_fast_speed = FAST_SPEED;

void setup() {
  randomSeed(analogRead(0));
  
  // NEOPIXEL is WS2811
  // Using data pin 6 on the board
  // Uses variable named "leds"
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
  if (RANDOM && timey % CHANGE_PERIOD == 0) {
    // 1/2 of the time, don't change; 1/4 of the time, reduce speed; 1/4 of the time, increase speed. Cap maximum and minimum at FAST_SPEED.
    current_slow_speed = max(min(current_slow_speed + random(-1,2), FAST_SPEED), FAST_SPEED * -1);
    current_medium_speed = max(min(current_medium_speed + random(-1,2), FAST_SPEED), FAST_SPEED * -1);
    current_fast_speed = max(min(current_fast_speed + random(-1,2), FAST_SPEED), FAST_SPEED * -1);
  }
  for (int led_select = 0; led_select < NUM_LEDS; led_select++) {
    slow = round(((sin((((float)timey * SLOW_DIRECTION * ( current_slow_speed / SLOW_SPEED ) + (SLOWNESS / (float)WAVE_LENGTH) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    medium = round(((sin((((float)timey * MEDIUM_DIRECTION * ( current_medium_speed / SLOW_SPEED ) + (SLOWNESS / (float)WAVE_LENGTH) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    fast = round(((sin((((float)timey * FAST_DIRECTION * ( current_fast_speed / SLOW_SPEED ) + (SLOWNESS / (float)WAVE_LENGTH) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    leds[led_select] = CRGB(slow, medium, fast);
  }
  FastLED.show();
  timey++;
}

