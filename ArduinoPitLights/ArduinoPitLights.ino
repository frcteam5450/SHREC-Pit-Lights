#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, 6, NEO_GRB + NEO_KHZ800);
// one strip is 28 pixels

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  colorWipe(strip.Color(0, 255, 0), 25);
  colorWipe(strip.Color(100,100,100),25);
  for(int i=0;i<(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(31,41,59));
  }
  
  for(int i=(strip.numPixels()/9);i<2*(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(26,53,58));
  }
  
  for(int i=(2*(strip.numPixels()/9));i<(3*(strip.numPixels()/9));i++){
    strip.setPixelColor(i, strip.Color(97,93,23));
  }
  
  for(int i=3*(strip.numPixels()/9);i<4*(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(84,62,64));
  }
  
  for(int i=4*(strip.numPixels()/9);i<5*(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(33,83,27));
  }
  
  for(int i=5*(strip.numPixels()/9);i<6*(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(95,02,88));
  }
  
  for(int i=6*(strip.numPixels()/9);i<7*(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(41,97,16));
  }
  
  for(int i=(strip.numPixels()/9);i<(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(93,99,37));
  }
  
  for(int i=(strip.numPixels()/9);i<(strip.numPixels()/9);i++){
    strip.setPixelColor(i, strip.Color(51,05,82));
  }
  //53 digits of pi in the strip
  strip.show();
  delay(3141);
  colorWipe(strip.Color(31,41,59),50);
  rainbow(20);
  rainbowCycle(20);
}
//3.14159265358979323846264338327950288419716939937510
/*
 void colorFade(int red1, int green1, int blue1, int red2, int green2, int blue2, int t){
  int red = red1;
  int green = green1;
  int blue = blue1;
  double redChange = (red2-red1)/t;
  double greenChange = (green2-green1)/t;
  double blueChange = (blue2-blue1)/t;
  for(int i = 0;i<=t;i++){
    for(int j = 0;j<=strip.numPixels();j++){
      strip.setPixelColor(j, strip.Color(red,green,blue));
    }
    strip.show();
    red+=redChange;
    green+=greenChange;
    blue+=blueChange;
    delay(1);
  }
}
*/
// a failed function above ;(

void colorAll(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
