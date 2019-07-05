#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define readPin A4
#define numLeds 45
#define numRingLeds 93
int pwm_value;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numLeds, 2, NEO_GRB + NEO_KHZ800); //Left vertical LED strip
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(numLeds, 3, NEO_GRB + NEO_KHZ800); //Right vertical LED strip
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(numRingLeds, 5, NEO_GRB + NEO_KHZ800); //LED ring on lid

void setup() {
  pinMode(readPin, INPUT_PULLUP);
  Serial.begin(9600);
  strip2.begin();
  strip3.begin();
  strip5.begin();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip5.numPixels(); i++) {
    strip5.setPixelColor(i, c);
    strip5.show();
    delay(wait);
  }
}

void loop() {
  int lightUp = 0;
  int lightOff = 0;
  pwm_value = pulseIn(readPin, LOW) / 4.025;
  Serial.println(pwm_value);

  //Standby colors. Cannot reliably detect PWM lower than 30.
  if (pwm_value < 30) {
    for (int i = 0; i < numLeds; i++) {
      strip2.setPixelColor(i, 25, 25, 0);
      strip2.show();
      strip3.setPixelColor(i, 25, 25, 0);
      strip3.show();
    }

    for (int i = 0; i < numRingLeds; i++) {
        strip5.setPixelColor(i, 25, 25, 0); //Top LEDs
        strip5.show();
      }
    
    delay(1000);
  }

    //Printer Available - Calming Sway of Lights - Select PWM of 35
    else if (pwm_value >= 30 && pwm_value < 40) {
      for (int intensity = 0; intensity < 25; intensity++) {
        for (int i = 0; i < numLeds; i++) {
          strip2.setPixelColor(i, intensity*5, intensity*5, 0);
          strip2.show();
          strip3.setPixelColor(i, intensity*5, intensity*5, 0);
          strip3.show();
          }
          delay(1);
      }
      for (int intensity = 25; intensity >=0;) {
        for (int i = 0; i < numLeds; i++) {
          strip2.setPixelColor(i, intensity*5, intensity*5, 0);
          strip2.show();
          strip3.setPixelColor(i, intensity*5, intensity*5, 0);
          strip3.show();
          intensity=intensity-1;
          delay(1);
      }
      for (int i = 0; i < numRingLeds; i++) {
        strip5.setPixelColor(i, intensity*5, intensity*5, 0); //Top LEDs
        strip5.show();
        }
      }
    } 

  //Heating Cycle - Select PWM of 45
  else if (pwm_value >= 40 && pwm_value < 50) {
    for (int i = 0; i < numLeds; i++) {
      strip2.setPixelColor(i, 255, 0, 0);
      strip2.show();
      strip3.setPixelColor(i, 255, 0, 0);
      strip3.show();
    }

      for (int i = 0; i < numRingLeds; i++) {
      strip5.setPixelColor(i, 255, 255, 255); //Top LEDs
      strip5.show();
      }  
    delay(1000);
  }

  //Progress LED light bar
  else if (pwm_value<= 240) {
    lightUp=(pwm_value-50)*numLeds/190;
    Serial.print(lightUp);
    lightOff=numLeds-lightUp;
    for (int i = 0; i < numLeds; i++) {
      if (lightOff > 0) {
        strip2.setPixelColor(i, 5, 5, 0); //Top LEDs
        strip2.show();
        strip3.setPixelColor(i, 5, 5, 0); //Top LEDs
        strip3.show();
        lightOff--;
         } else {
        strip2.setPixelColor(i, 255, 255, 0); //Bottom LEDs
        strip2.show();
        strip3.setPixelColor(i, 255, 255, 0); //Bottom LEDs
        strip3.show();
      }
    }
    
    for (int i = 0; i < numRingLeds; i++) {
        strip5.setPixelColor(i, 255, 255, 255); //Top LEDs
        strip5.show();
      }  
    delay(1000);
  } 



    //Print Complete, Celebrate then Cool Down for 5 minutes
    else if (pwm_value >= 245) {
    for (int i = 0; i < numLeds; i++) {
      strip2.setPixelColor(i, 255, 255, 0);
      strip2.show();
      strip3.setPixelColor(i, 255, 255, 0);
      strip3.show();
    }
  colorWipe(strip5.Color(200, 0, 0), 50); // Red
  colorWipe(strip5.Color(0, 200, 0), 50); // Green
  colorWipe(strip5.Color(0, 0, 200), 50); // Blue
  colorWipe(strip5.Color(200, 200, 200), 50); // White RGBW
  
      }
    delay(1000);
  }
