#include "FastLED.h"
#include "Duration.h"
#include "MorseCode.h"
#include "CodedChar.h"

#define NUM_LEDS 7
#define DATA_PIN 6
#define BRIGHTNESS 84

#define DOT_TIME 250
#define TIME_BEFORE_START 5000
#define TIME_BETWEEN_SENDING 5000

char* toSend;
MorseCode* coder;

CRGB leds[NUM_LEDS];


void setup()
{
	Serial.begin(57600);
	toSend = "HELLO WORLD\0";
	coder = new MorseCode();
	coder->setDotTime(DOT_TIME);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(BRIGHTNESS);
}


void loop()
{	
	Serial.print("Start Loop\n");
	setAllToColor(CRGB::Green);
	delay(TIME_BEFORE_START);

	Serial.print("Start sending\n");
	coder->SendWord(toSend, sendToNeopixel);

	Serial.print("Finished sending\n");
	setAllToBlack();
	delay(TIME_BETWEEN_SENDING);
}


void sendToNeopixel(CodedChar character, int shortPulseTime, int longPulseTime){
	for (int i = 0; i < character.codesLength; ++i){
		setAllToColor(CRGB::Red);
		if(character.codes[i] == CODE_SHORT){
			delay(shortPulseTime);
		}
		else{
			delay(longPulseTime);
		}
		setAllToBlack();
		delay(shortPulseTime);
	}
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