#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 16
#define SPEED 400
#define BRIGHTNESS 60


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint16_t colors[6][3] = {
    {255, 0, 0}, //Red
    {255, 32, 0}, //Orange
    {255, 128, 0},  //Yellow
    {0, 128, 0},  //Green
    {0, 0, 255},  //Blue
    {255, 0, 255}  //Purple
  };

void setup() {
    pixels.begin();  //  Initialize the NeoPixels
    pixels.setBrightness(BRIGHTNESS);
}

void loop() {
    for(int j = 0; j < 6; j++) {
        for(int i = 0; i < NUMPIXELS; i++) {
            pixels.setPixelColor(i, pixels.Color(colors[j][0], colors[j][1], colors[j][2]));
        }

        pixels.show();

        Bean.setLed(colors[j][0], colors[j][1], colors[j][2]);

    // TODO: Replace with sleep
    Bean.sleep(SPEED);
    }
}