#include <Adafruit_NeoPixel.h>
#include <PinChangeInt.h>
#include "Easing.h"

#define PIN 5
#define NUMPIXELS 12
#define BRIGHTNESS 60

// Easing Loop
#define SPEED 80
#define DURATION 12 * 80
#define RANGE 12 * 80

// Display mode
int mode = 0;
static int newMode = 0;

int j;

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
    {255, 0, 0} //Red
  };

void displayRainbow(int offset) {
    for(int i = 0; i < NUMPIXELS; i++) {
        int color = (offset%12)+i;
        pixels.setPixelColor(i, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
    }

    pixels.show();
}

void modeSetup() {
    switch (mode) {
        case 0:
            easingSetup();
            break;

        case 1:
            cycleSetup();
            break;
    }
}

void easingSetup() {
    j = -DURATION;
    displayRainbow(Easing::easeInOutSine(abs(j), 0, RANGE, DURATION));
}

void easingLoop() {
    if (j < DURATION -12) {
        displayRainbow(Easing::easeInOutSine(abs(j), 0, RANGE, DURATION));

        Bean.sleep(SPEED);

        j++;
    } else {
        j = -DURATION;
    }
}

void displayColor(int color) {
    color = color + color;

    for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
    }

    pixels.show();
}

void cycleSetup() {
    j = 0;
    displayColor(j);
}

void cycleLoop() {
    if (j < 6) {
        displayColor(j);

        Bean.sleep(SPEED * 5);

        j++;
    } else {
        j = 0;
    }
}

void setup() {
    pinMode(0, INPUT_PULLUP);
    // Valid interrupt modes are: RISING, FALLING or CHANGE
    attachPinChangeInterrupt(0, pinChanged, RISING);

    pixels.begin();  //  Initialize the NeoPixels
    pixels.setBrightness(BRIGHTNESS);

    modeSetup();
}

void loop() {
    switch (mode) {
        case 0:
            easingLoop();
            break;

        case 1:
            cycleLoop();
            break;
    }

    if (newMode != mode) {
        buttonPressed();
        mode = newMode;
    }
}

void buttonPressed() {
    mode++;

    if (mode >= 2) {
        mode = 0;
    }

    modeSetup();

}

// Interrupt service routine (ISR) needs to return void and accept no arguments
void pinChanged() {
    newMode++;
    if (newMode >=2) {
        newMode = 0;
    }
}