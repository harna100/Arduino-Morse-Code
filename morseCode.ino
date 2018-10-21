#include "FastLED.h"
#include "Duration.h"
#include "MorseCode.h"
#include "CodedChar.h"

#define NUM_LEDS 7
#define DATA_PIN 6
#define BRIGHTNESS 84

#define SWITCH_PIN 2

#define DOT_TIME 250
#define TIME_BEFORE_START 2500
#define WORD_TO_SEND "SOS\0"

char* toSend;
Morse::MorseCode* coder;

CRGB leds[NUM_LEDS];

void setup()
{
	Serial.begin(57600);
	toSend = WORD_TO_SEND;
	coder = new Morse::MorseCode();
	coder->setDotTime(DOT_TIME);
	coder->setResetCheck(checkForReset);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(BRIGHTNESS);
	pinMode(SWITCH_PIN, INPUT_PULLUP);
}


void loop()
{	
	setAllToBlack();
	Serial.print("Start Loop\n");
	if(checkForReset()){
		delay(10);
		return;
	}
	setAllToColor(CRGB::Green);
	Morse::MorseCode::delayWithCheck(TIME_BEFORE_START, checkForReset);

	Serial.print("Start sending\n");
	coder->SendWord(toSend, setAllOn, setAllToBlack);

	Serial.print("Finished sending\n");
	setAllToBlack();
}

void setAllOn(){
	setAllToColor(CRGB::Red);
}

void setAllToColor(CRGB color){
	for (int i = 0; i < NUM_LEDS; ++i){
		leds[i] = color;
	}
	FastLED.show();
}

void setAllToBlack(){
	for (int i = 0; i < NUM_LEDS; ++i){
		leds[i] = CRGB::Black;
	}
	FastLED.show();	
}

bool checkForReset(){
	return digitalRead(SWITCH_PIN) == true;
}
