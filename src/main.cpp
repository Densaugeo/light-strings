#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 15

int red = 0;
int green = 0;
int blue = 0;
int red_or_green;
//int blue_or_green;

void set_flame_shade(int pixel, int shade) {
  int green, blue;
  
  if(shade >= 256) {
    green = 255;
    blue = shade - 256;
  } else {
    green = shade;
    blue = 0;
  }
  
  pixels.setPixelColor(pixel, pixels.Color(255, green, blue));
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  // Blue/green/violet
  red_or_green = random(2);
  blue = random(256);
  
  if(red_or_green && blue > 0x80) {
    red = random(256);
    green = 0;
  } else {
    red = 0;
    green = random(256);
  }
  
  /*
  // Halloween
  red = random(256);

  if(red > 0x80) {
    green = random(red);
    blue = 0;
  } else {
    green = 0;
    blue = 0;
  }*/
  
  // Shared for both above
  pixels.setPixelColor(random(NUMPIXELS), pixels.Color(red, green, blue));
  pixels.show();
  delay(DELAYVAL);
  
  // Fire
  /*pixels.setPixelColor(14, pixels.Color(0, 255, 0));
  pixels.setPixelColor(15, pixels.Color(0, 255, 0));
  pixels.setPixelColor(48, pixels.Color(0, 255, 0));
  pixels.setPixelColor(49, pixels.Color(0, 255, 0));
  pixels.setPixelColor(83, pixels.Color(0, 255, 0)); // right at end
  
  
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.setPixelColor(30, pixels.Color(0, 0, 255));
  pixels.setPixelColor(31, pixels.Color(0, 0, 255));
  pixels.setPixelColor(65, pixels.Color(0, 0, 255));
  pixels.setPixelColor(66, pixels.Color(0, 0, 255));
  pixels.setPixelColor(99, pixels.Color(0, 0, 255));
  
  for(int i =  0; i <= 14; ++i) set_flame_shade(i, (200 + random(200))*(14 - i)/14);
  for(int i = 30; i >= 15; --i) set_flame_shade(i, (200 + random(200))*(i - 15)/15);
  
  pixels.show();
  delay(250);*/
}
