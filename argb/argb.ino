/*
original firmware taken from NEON AIRSHIP: https://www.youtube.com/watch?v=HJnjesdXlAA
*/

#include <Adafruit_NeoPixel.h>


/* HW PINOUT DEFINES */
#define BUTTON_PIN          22    // Digital IO pin connected to the button.  This will be
                                  // driven with a pull-up resistor so the switch should
                                  // pull the pin to ground momentarily.

#define TOGGLE_ONOFF_PIN    13    //toggle to enable or disabled the entire loop
#define PIXEL_PIN           27    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT         16    // Number of leds on the strip

/* PROGRAM DEFINES*/
#define MAX_STATE             9
#define MIN_STATE             1
#define DEBOUNCE_TIME_BUTTON  350 //in ms
#define DEBOUNCE_TIME_TOGGLE  100 //in ms

struct Button {
  const uint8_t PIN;
  uint32_t state;
  bool pressed;
};
Button button1 = {BUTTON_PIN, MIN_STATE, false};
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

unsigned long toggle_time = 0;  
unsigned long last_toggle_time = 0; 
int toggleState = 0;         // variable for reading the pushbutton status
bool g_toggle_pressed = false;
bool g_loop_animation = true;
bool light_locked = false;


// Parameter 1 = number of pixels in strip, ARTIC Freezer A35 ( argb fan ) have 16 ( empiric tests :) )
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for ARTIC Freezer A35 ( argb fan ) 
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for ARTIC Freezer A35 ( argb fan ) 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void IRAM_ATTR isr_button() {
  
  button_time = millis();
  if (button_time - last_button_time > DEBOUNCE_TIME_BUTTON)
  {
    button1.state++;
  
    if (button1.state > MAX_STATE)
    {
      button1.state = MIN_STATE;
    }

    button1.pressed = true;
    g_loop_animation = false;
    Serial.printf("Status changed to %u state \n", button1.state);
    last_button_time = button_time;
  }
  
}

void IRAM_ATTR isr_toggle_on_off() {
  
  toggle_time = millis();
  if (toggle_time - last_toggle_time > DEBOUNCE_TIME_TOGGLE)
  {
    toggleState = digitalRead(TOGGLE_ONOFF_PIN);
    g_toggle_pressed = true; 
    g_loop_animation = false;
    Serial.printf("Toggle switched %d\n", (toggleState == LOW ? 1 : 0) );
    // if(toggleState == HIGH) ---> IT BREAKES EVERYTHING
    // {
    //   colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
    // }
    
    last_toggle_time = toggle_time;
  }
  
}


// INTERRUPT ATTRIBUTES
//LOW  Triggers the interrupt whenever the pin is LOW
//HIGH  Triggers the interrupt whenever the pin is HIGH
//CHANGE  Triggers the interrupt whenever the pin changes value, from HIGH to LOW or LOW to HIGH
//FALLING Triggers the interrupt when the pin goes from HIGH to LOW
//RISING  Triggers the interrupt when the pin goes from LOW to HIGH


void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP ); // INPUT_PULLUP: if you don't have resistor, INPUT if you have
  pinMode(TOGGLE_ONOFF_PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr_button, RISING);
  attachInterrupt(TOGGLE_ONOFF_PIN, isr_toggle_on_off, CHANGE);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  toggleState = digitalRead(TOGGLE_ONOFF_PIN); //initial status
  g_toggle_pressed = true;
}

void loop()
{
    if(g_toggle_pressed) 
    {
      g_toggle_pressed = false;
      if(toggleState == HIGH) 
      {
        Serial.println("Toggle OFF");
        colorWipe(strip.Color(0, 0, 0), 1);    // Black/off
        light_locked = true;
      }
      else 
      {
        Serial.println("Toggle ON");
        light_locked = false;
        button1.pressed = true;
      }
    }
    if(button1.pressed && !light_locked)
    {
      button1.pressed = false; //reset status isr_button 
      g_loop_animation = true; //reset animation loop status
      Serial.printf("OK changed to %u state \n", button1.state);
      startShow(button1.state);
    }
    
//// NO BUTTON -> time based change version
//  showType++;
//  if (showType > 9)
//    showType = 1;
//  startShow(showType);
//
//  delay(2000);

}

bool checkGlobalPressed(void)
{
  return (!button1.pressed || !g_toggle_pressed);
}


/* 
 *  @brief: smart implementation for delay function: if extern events occurs (interrupt on button1) then leave immediatly 
 *  @param: milli is time in miliseconds to wait before leaving the function
*/
void delayClever(uint32_t milli)
{
    //delay time but with miilis (which is in all lighting function)
    uint32_t stime = millis();

    while ((millis() - stime < milli) && checkGlobalPressed());    
}


void startShow(uint32_t i) {
  switch (i) {
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
      break;
    case 1: colorWipe(strip.Color(0, 255, 0), 50);  // Green
      break;
    case 2: colorWipe(strip.Color(255, 0, 0), 50);  // Red
      break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
      break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
      break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
      break;
    case 7: rainbowCycle(100);
      break;
    case 8: rainbowCycle(20);
      break;
    case 9: theaterChaseRainbow(50);
      break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delayClever(5);
    if (button1.pressed || g_toggle_pressed) break;
  }
}

void rainbow(uint32_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delayClever(wait);
    if (button1.pressed || g_toggle_pressed) break;
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint32_t wait) {
  uint16_t i, j;

  while(g_loop_animation)
  {
    // 5 cycles of all colors on wheel
    for (j = 0; j < 256 * 5; j++)
    { 
      for (i = 0; i < strip.numPixels(); i++) 
      {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      strip.show();
      delayClever(wait);
      if (button1.pressed || g_toggle_pressed) break;
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint32_t wait) {
  while(g_loop_animation)
  {   
    //do 10 cycles of chasing
    for (int j = 0; j < 10; j++) 
    { 
      for (int q = 0; q < 3; q++) 
      {
        for (int i = 0; i < strip.numPixels(); i = i + 3) 
        {
          strip.setPixelColor(i + q, c);  //turn every third pixel on
        }
        strip.show();
  
        delayClever(wait);
        if (button1.pressed || g_toggle_pressed) break;
  
        for (int i = 0; i < strip.numPixels(); i = i + 3) 
        {
          strip.setPixelColor(i + q, 0);      //turn every third pixel off
        }
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint32_t wait) {

  while(g_loop_animation)
  {
    // cycle all 256 colors in the wheel
    for (int j = 0; j < 256; j++)
    {   
      for (int q = 0; q < 3; q++)
      {
        for (int i = 0; i < strip.numPixels(); i = i + 3) 
        {
          strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
        }
        strip.show();
  
        delayClever(wait);
        if (button1.pressed || g_toggle_pressed) break;
  
        for (int i = 0; i < strip.numPixels(); i = i + 3) 
        {
          strip.setPixelColor(i + q, 0);      //turn every third pixel off
        }
      }
      if (button1.pressed || g_toggle_pressed) break;
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
