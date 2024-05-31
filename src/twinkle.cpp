#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN         0
#define NUMPIXELS 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL    5

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
  int red = 0;
  int green = 0;
  int blue = 0;
  
  // Blue/green/violet twinkle
  blue = random(0x80);
  if(blue > 0x40 && random(2)) {
    red = random(0x80);
    green = 0;
  } else {
    red = 0;
    green = random(0x80);
  }
  
  // Halloween
  //red = random(0x100);
  //green = red > 0x80 ? random(red) : 0;
  
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
