#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 12
#define SPEED 100
#define BRIGHTNESS 60


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint16_t colors[][3] = {
    {255, 0, 0}, //Red
    {255, 0, 0}, //Red
    {255, 32, 0}, //Orange
    {255, 32, 0}, //Orange
    {255, 128, 0},  //Yellow
    {255, 128, 0},  //Yellow
    {0, 128, 0},  //Green
    {0, 128, 0},  //Green
    {0, 0, 255},  //Blue
    {0, 0, 255},  //Blue
    {255, 0, 255},  //Purple
    {255, 0, 255},  //Purple
    {255, 0, 0}, //Red
    {255, 0, 0}, //Red
    {255, 32, 0}, //Orange
    {255, 32, 0}, //Orange
    {255, 128, 0},  //Yellow
    {255, 128, 0},  //Yellow
    {0, 128, 0},  //Green
    {0, 128, 0},  //Green
    {0, 0, 255},  //Blue
    {0, 0, 255},  //Blue
    {255, 0, 255},  //Purple
    {255, 0, 255},  //Purple
    {255, 0, 0}, //Red
    {255, 0, 0}, //Red
  };

void displayRainbow(int offset) {
    for(int i = 0; i < NUMPIXELS; i++) {
        int color = (offset%12)+i;
        pixels.setPixelColor(i, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
    }

    pixels.show();
}

void setup() {
    pixels.begin();  //  Initialize the NeoPixels
    pixels.setBrightness(BRIGHTNESS);
    displayRainbow(0);
}

void loop() {
    for(int j = 0; j < 60; j++) {

    displayRainbow(j);

    // TODO: Replace with sleep
    Bean.sleep(SPEED);
    }
}