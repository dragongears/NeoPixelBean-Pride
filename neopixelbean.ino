#include <Adafruit_NeoPixel.h>
#include <PinChangeInt.h>
#include "Easing.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define NEOPIXEL_PIN 5
#define NUMPIXELS 12
#define BRIGHTNESS 60

#define BUTTON_PIN 0

// Cycle Loop
#define CYCLE_SPEED 400

// Easing Loop
#define EASING_SPEED 20
#define EASING_DURATION 12 * 80
#define EASING_RANGE 12 * 80

// Display mode
int currentMode = 0;
static int newMode = 0;

int loopCount;

struct mode {
    void (*setup)(void);
    void (*loop)(void);
};

struct mode modes[2];

int modesCount = NELEMS(modes);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

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


// Call setup for current mode
void modeSetup() {
    modes[currentMode].setup();
}


// Easing mode functions

void displayRainbow(int offset) {
    for (int i = 0; i < NUMPIXELS; i++) {
        int color = (offset % NUMPIXELS)+i;
        pixels.setPixelColor(i, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
    }

    pixels.show();
}

void easingSetup() {
    loopCount = -EASING_DURATION;
    displayRainbow(Easing::easeInOutQuad(abs(loopCount), 0, EASING_RANGE, EASING_DURATION));
}

void easingLoop() {
    if (loopCount < EASING_DURATION - NUMPIXELS) {
        displayRainbow(Easing::easeInOutQuad(abs(loopCount), 0, EASING_RANGE, EASING_DURATION));

        Bean.sleep(EASING_SPEED);

        loopCount++;
    } else {
        loopCount = -EASING_DURATION;
    }
}


// Cycle mode functions

void displayColor(int color) {

    // Array has two entries for each color, so double up
    color = color + color;

    for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
    }

    pixels.show();
}

void cycleSetup() {
    loopCount = 0;
    displayColor(loopCount);
}

void cycleLoop() {
    if (loopCount < 6) {
        displayColor(loopCount);

        Bean.sleep(CYCLE_SPEED);

        loopCount++;
    } else {
        loopCount = 0;
    }
}

// Arduino setup function
void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // Valid interrupt modes are: RISING, FALLING or CHANGE
    attachPinChangeInterrupt(BUTTON_PIN, pinChanged, RISING);

    pixels.begin();  //  Initialize the NeoPixels
    pixels.setBrightness(BRIGHTNESS);

    modes[0].setup = &easingSetup;
    modes[0].loop = &easingLoop;
    modes[1].setup = &cycleSetup;
    modes[1].loop = &cycleLoop;

    modeSetup();
}

// Arduino loop function
void loop() {
    modes[currentMode].loop();

    if (newMode != currentMode) {
        currentMode = newMode;
        modeSetup();
    }
}

// Interrupt service routine (ISR) needs to return void and accept no arguments
void pinChanged() {
    newMode++;
    if (newMode >= modesCount) {
        newMode = 0;
    }
}