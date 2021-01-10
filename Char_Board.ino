#include <FastLED.h>

#define LED_PIN     2
#define BUTTON_PIN  3
#define NUM_LEDS    60
#define BRIGHTNESS  170
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
uint8_t mode = 0;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern const TProgmemPalette16 White_p PROGMEM;
extern const TProgmemPalette16 Black_p PROGMEM;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    pinMode(BUTTON_PIN, INPUT);
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    if (digitalRead(BUTTON_PIN)==HIGH)
      ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{   
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
    mode += 15;
    if( mode > 60)   { mode = 0; }
    if( mode ==  0)  { currentPalette = RainbowColors_p; currentBlending = LINEARBLEND; }
    if( mode == 15)  { currentPalette = OceanColors_p; currentBlending = LINEARBLEND; }
    if( mode == 30)  { currentPalette = LavaColors_p; currentBlending = LINEARBLEND; }
    if( mode == 45)  { currentPalette = White_p; currentBlending = LINEARBLEND;  }
    if( mode == 60)  { currentPalette = Black_p; currentBlending = LINEARBLEND;  }
    delay(200);
}

// Saves the color black as a pallet
const TProgmemPalette16 Black_p PROGMEM =
{
    CRGB::Black,
    CRGB::Black, 
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black,
    CRGB::Black
};

// Saves the color white as a pallet
const TProgmemPalette16 White_p PROGMEM =
{
    CRGB::White,
    CRGB::White, 
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White,
    CRGB::White
};
