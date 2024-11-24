#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN         0
#define NUMPIXELS  64
#define BRIGHTNESS  4 // Range of 0 to 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL  250

bool conway[8][8];
bool conway_2[8][8];
bool conway_3[8][8];
int conway_neighbor_counts[8][8];
int tick_count = 0;
int reset_at_tick = 0;
int red = 0;
int green = 0;
int blue = 0;

void init_conway(int rarity) {
  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      conway[x][y] = (random(rarity) == 0);
    }
  }
}

// Convert x,y coordinates to an LED index
int coord_8x8(int x, int y) {
  x = constrain(x, 0, 7);
  y = constrain(y, 0, 7);
  
  // The LED grid snakes back and forth, so the coordsinates must account for
  // that
  return 8*y + (y % 2 ? x : 7 - x);
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  randomSeed(
    (analogRead(A0) & 0xf) << 0 |
    (analogRead(A1) & 0xf) << 4 |
    (analogRead(A2) & 0xf) << 8 |
    (analogRead(A3) & 0xf) << 12
  );
  pixels.begin();
}

void loop() {
  if(tick_count >= reset_at_tick) {
    init_conway(4 + random(3));
    red   = random(2)*2*BRIGHTNESS + random(BRIGHTNESS);
    green = random(2)*2*BRIGHTNESS + random(BRIGHTNESS);
    blue  = random(2)*2*BRIGHTNESS + random(BRIGHTNESS);
    reset_at_tick = tick_count + 240;
  }
  
  memset(conway_neighbor_counts, 0, sizeof(conway_neighbor_counts));
  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      if(conway[x][y]) {
        if(x > 0 && y > 0) ++conway_neighbor_counts[x - 1][y - 1];
        if(x > 0         ) ++conway_neighbor_counts[x - 1][y    ];
        if(x > 0 && y < 7) ++conway_neighbor_counts[x - 1][y + 1];
        if(         y > 0) ++conway_neighbor_counts[x    ][y - 1];
        if(         y < 7) ++conway_neighbor_counts[x    ][y + 1];
        if(x < 7 && y > 0) ++conway_neighbor_counts[x + 1][y - 1];
        if(x < 7         ) ++conway_neighbor_counts[x + 1][y    ];
        if(x < 7 && y < 7) ++conway_neighbor_counts[x + 1][y + 1];
      }
    }
  }
  
  memcpy(conway_3, conway_2, sizeof(conway));
  memcpy(conway_2, conway  , sizeof(conway));
  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      if(conway_neighbor_counts[x][y] <  2) conway[x][y] = false;
      // Two live neighbors causes no change
      if(conway_neighbor_counts[x][y] == 3) conway[x][y] = true;
      if(conway_neighbor_counts[x][y] >  3) conway[x][y] = false;
    }
  }
  if(memcmp(conway, conway_3, sizeof(conway)) == 0) {
    // Adding 6 ticks, plus 2 for the last 2 ticks, means the stuck board will
    // display for 2 s
    reset_at_tick = min(reset_at_tick, tick_count + 6);
  }
  
  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      pixels.setPixelColor(coord_8x8(x, y),
        conway[x][y] ? pixels.Color(red, green, blue) : pixels.Color(0, 0, 0)
      );
    }
  }
  pixels.show();
  
  ++tick_count;
  delay(DELAYVAL);
}
