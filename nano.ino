#include <Adafruit_NeoPixel.h>
#define readPin A4
#define ledPin 6
int numLeds = 45;
int pwm_value;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);
void setup() {
  pinMode(readPin, INPUT_PULLUP);
  Serial.begin(9600);
  strip.begin();
}

void loop() {
  int lightUp = 0;
  int lightOff = 0;
  pwm_value = pulseIn(readPin, LOW) / 4.025;
  Serial.println(pwm_value);
  if (pwm_value < 30) {
    for (int i = 0; i < numLeds; i++) {
      strip.setPixelColor(i, 0, 0, 5);
      strip.show();
    }
    delay(1000);
  }
  else if (pwm_value<= 200) {
    lightUp=(pwm_value-30)*numLeds/170;
    Serial.print(lightUp);
    lightOff=numLeds-lightUp;
    for (int i = 0; i < numLeds; i++) {
      if (lightOff > 0) {
        strip.setPixelColor(i, 0, 0, 5); //Top LEDs
        strip.show();
        lightOff--;
         } else {
        strip.setPixelColor(i, 0, 0, 255); //Bottom LEDs
        strip.show();
      }
    }
    delay(1000);
  } 
  else if (pwm_value > 205 && pwm_value < 225) {
    for (int i = 0; i < numLeds; i++) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
    }
    delay(1000);
  }
    else if (pwm_value >= 225 && pwm_value < 245) {
    for (int i = 0; i < numLeds; i++) {
      strip.setPixelColor(i, 0, 0, 255);
      strip.show();
    }
    delay(1000);
  } 
    else if (pwm_value >= 245) {
      for (int intensity = 0; intensity < 25; intensity++) {
        for (int i = 0; i < numLeds; i++) {
          strip.setPixelColor(i, 0, 0, intensity*10);
          strip.show();}
          delay(1);
      }
      for (int intensity = 25; intensity >=0;) {
        for (int i = 0; i < numLeds; i++) {
          strip.setPixelColor(i, 0, 0, intensity*10);
          strip.show();}
          intensity=intensity-1;
          delay(1);
      }
  } 
}
