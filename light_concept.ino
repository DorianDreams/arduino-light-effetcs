#include <FastLED.h>

#define LED_PIN1     2
#define LED_PIN2     4
#define NUM_LEDS    100
#define BRIGHTNESS  32
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define IDLE_COLOR CRGB::DimGray
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

CRGBPalette16 currentPalette = CRGBPalette16( CRGB::Black );
CRGBPalette16 targetPalette;

String current_color = "0x000000";
String new_color;
#define UPDATES_PER_SECOND 100

enum State {
  OFF,
  PULSATE,
  BLINK,
  SHOW,
  WAVE_UP,
  WAVE_LEFT,
  WAVE_RIGHT
};

State state = OFF;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void setState(int serialData){
  switch(serialData){
      case '0':
        state = OFF;
        break;
      case '1':
        state = PULSATE;
        break;
      case '2':
        state = BLINK;
        break;
      case '3':
        state = SHOW;
        break;
      case '4':
        state = WAVE_UP;
        break;
      case '5':
        state = WAVE_RIGHT;
        break;
      case '6':
        state = WAVE_LEFT;
  }
}

void loop()
{
  if (Serial.available()) {
    String serialData = Serial.readString();
    int stateInfo = serialData.charAt(0);    
    setState(stateInfo);
    if (state == SHOW)
    {
      new_color = serialData.substring(1);
      char* target_color = new char[new_color.length() + 1];
      strcpy(target_color, new_color.c_str()); 
      targetPalette = CRGBPalette16( strtol(target_color, NULL, 0) );

    }
  }
  switch(state){
      case OFF:
        setOff();
        break;
      case PULSATE:
        {
          redpulse();
        break;
        }
        
      case BLINK:
        blink(2, CRGB::Yellow);
        break;
      case SHOW:
        singleColor();
        break;
      case WAVE_UP:
        waveUP();
        break;
      case WAVE_RIGHT:
        waveRIGHT();
        break;
      case WAVE_LEFT:
        waveLEFT();
        break;
      
    }  
}

void singleColor()
{
  uint8_t maxChanges = 24; 
  nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);
  nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);
  nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void waveUP(){
  for( int i = 75; i < 100; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
  FastLED.show();
  FastLED.delay(50);
  for( int i = 0; i < 25; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
    leds1[75-i] = CRGB::Red;
    leds2[75-i] = CRGB::Red;
    FastLED.delay(50);
    FastLED.show();
  }
  for( int i = 25; i < 50; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
  FastLED.show();
  FastLED.delay(500);
  state = OFF;
}

void waveRIGHT(){
  for( int i = 50; i < 75; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }

  FastLED.show();
  FastLED.delay(10);
  for( int i = 25; i < 50; i++) {
    leds1[75-i] = CRGB::Red;
    leds2[75-i] = CRGB::Red;
    leds1[50+i] = CRGB::Red;
    leds2[50+i] = CRGB::Red;
    FastLED.delay(10);
    FastLED.show();
    
  }
  for( int i = 0; i < 25; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
  FastLED.show();

  for( int i = 50; i < 75; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }

  FastLED.show();
  FastLED.delay(10);
  for( int i = 25; i < 50; i++) {
    leds1[75-i] = CRGB::Red;
    leds2[75-i] = CRGB::Red;
    leds1[50+i] = CRGB::Red;
    leds2[50+i] = CRGB::Red;
    FastLED.delay(10);
    FastLED.show();
    
  }
  for( int i = 0; i < 25; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
  FastLED.show();

  FastLED.delay(500);
  state = OFF; 
}

void waveLEFT(){
  for( int i = 0; i < 25; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
  FastLED.show();
  FastLED.delay(10);
  FastLED.show();
  for( int i = 25; i < 50; i++) {
    leds1[0+i] = CRGB::Red;
    leds2[0+i] = CRGB::Red;
    leds1[124-i] = CRGB::Red;
    leds2[124-i] = CRGB::Red;
    FastLED.delay(10);
    FastLED.show();
  }
  for( int i = 50; i < 75; i++) {
    leds1[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
   FastLED.show();
  FastLED.delay(500);
  state = OFF;

}

void setOff() {
  for( int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    leds2[i] = CRGB::Black;
  }    
    FastLED.show();
}

void blink(int n_blinks, CRGB color) {
  // Turn the LED on, then pause
  for ( int n = 0; n < n_blinks; n++) {
    
  for( int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = color;
    leds2[i] = color;
  }
    FastLED.show();
    delay(250);
    // Now turn the LED off, then pause
    for( int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    leds2[i] = CRGB::Black;
  }
    FastLED.show();
    delay(250);
  }
  state = OFF;
}

void redpulse()
{
  CRGBPalette16 yellowPalette = CRGBPalette16( CRGB::Yellow );
  CRGBPalette16 redPalette = CRGBPalette16( CRGB::Red );
  transition(yellowPalette, redPalette);
  yellowPalette = CRGBPalette16( CRGB::Yellow );
  transition(redPalette, yellowPalette);
  
}

void transition(CRGBPalette16 current, CRGBPalette16 target)
{
  while(!palleteEqual(current,target)){
      uint8_t maxChanges = 50; 
      nblendPaletteTowardPalette( current, target, maxChanges);
      nblendPaletteTowardPalette( current, target, maxChanges);
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
      FillLEDsFromPaletteColors(current, startIndex);
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
  }

}


bool palleteEqual(CRGBPalette16 currentPalette, CRGBPalette16 targetPalette )
{
  for (int i; i < 15; i++) 
  {
    if (currentPalette.entries[i]!=targetPalette.entries[i]){
      return false;
    }
  }
  return true;
}


void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), brightness);
    leds2[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), brightness);
    colorIndex += 3;

  }
}


void FillLEDsFromPaletteColors(CRGBPalette16 currentPalette, uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = ColorFromPalette( currentPalette, colorIndex + sin8(i*16), brightness);
    leds2[i] = ColorFromPalette( currentPalette, colorIndex + sin8(i*16), brightness);
    colorIndex += 3;

  }
}

