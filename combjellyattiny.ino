/*
 * Working on the new set of program codes to address individual LED pixels on the strip
 * This one is also incorporating millis() to get rid of the delay function
 * Which allows the use of outside inputs from the motions sensor.
 * Also incorporating the use of one of the hardware IRQ's
 */

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 2   // the digital output pin on the attiny85 to the neopixel strip
uint16_t NUM_PIXELS = 27; // number of pixels on the strip
uint16_t cp = 0;  // current pixel initialization
uint16_t prevcp = 0; // previous pixel 

const byte PIRpin = 4;   // setup the Motion sensor pin on the interrupt pin
//#define pirLED 0  // set up the pir LED pin
volatile byte pirstatus = 0;

/*
 * Setting up the millis function to create a time delay without a delay
 */
unsigned long interval = 50;  // the time we need to wait
unsigned long previousMillis = 0;

/*
 * Setting up the millis function to create a timed pir sensor reading. every 1/8 second
 */

 unsigned long pir_read_interval = 125;   // the time we need to wait, 1000/8 = 125
 unsigned long prev_pir_read = 0;

 /*
  *  Setting up the millis function to create a timed pir sensor reset if it continues on for a state 
  *  value of 1 (high) for longer than 3 seconds
  */

unsigned long pir_state_interval = 2000;  // time to check if it's been in a HIGH state for too long, 3 seconds
unsigned long prev_pir_state = 0;  

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  
  pinMode(PIRpin, INPUT);  // declare the PIRpin as an input for the pir sensor
  // attachInterrupt(digitalPinToInterrupt(PIRpin),pirRead, RISING); 
  
 // pinMode(pirLED, OUTPUT);  // declare the PIR status pin as an output for the LED indicator
  

  cp = 0;
  prevcp = 0;
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pirstatus = 0;  // set up the initial status of the pirstatus as low
  
  //Serial.begin(9600);
}

void loop() {

    pirRead();
      
    if (pirstatus == 1) {
      
      //digitalWrite(pirLED, HIGH); 
      
      unsigned long current_pir_state = millis();
  
      if ((unsigned long)(current_pir_state - prev_pir_state) >= pir_state_interval) {
        prev_pir_state = millis();

          for (int j = 0; j++; j <= NUM_PIXELS) {
            strip.setPixelColor(j, 0, 0, 0);
            strip.show(); 
          }
          
          strip.setPixelColor(1, 0, 0, 255);
          strip.setPixelColor(2, 0, 255, 0);
          strip.setPixelColor(3, 255, 0, 0);
          strip.setPixelColor(4, 255, 0, 0);
          strip.setPixelColor(5, 0, 255, 0);
          strip.setPixelColor(6, 0, 0, 255);
          strip.show();

      }
        
      
    } else {
      //digitalWrite(pirLED, LOW);
      combjellyon();
    }
    
 
 
  /*
 
    if (pirstatus == 1) {
      digitalWrite(pirLED, HIGH);    
    } else {
      digitalWrite(pirLED, LOW);
    }
    
  } else if ((unsigned long)(current_pir_read - prev_pir_read) >= pir_state_interval) {
    prev_pir_read = millis();
    pirstatus = 0;
  }
*/

    
 

  

  

  //pirstatus = digitalRead(PIRpin);
  //Serial.println(pirstatus);
 /* 
  unsigned long current_pir_state = millis();

  if ((unsigned long)(current_pir_state - prev_pir_state) >= pir_state_interval) {
    prev_pir_state = millis();
    pirstatus = 0;  // reset the pir status
  }
*/

}



