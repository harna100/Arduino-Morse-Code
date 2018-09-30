#include <Arduino.h>
#include "MorseCode.h"
#include "CodedChar.h"
#include "Duration.h"

MorseCode::MorseCode(){

};

MorseCode::~MorseCode(){

};

void MorseCode::SendWord(char* word, void(*duringOn)(), void(*duringOff)()){
	for (int i = 0; word[i] != '\0'; ++i){
		char currChar = word[i];
		Serial.print("Displaying Character: ");
		Serial.print(currChar);
		Serial.print("\n");
		if(currChar == ' '){
			duringOff();
			delay(this->dotTime*7);
			continue;
		}
		else {
			CodedChar codedChar = GetCharacter(currChar);
			for (int i = 0; i < codedChar.codesLength; ++i){
				duringOn();
				if(codedChar.codes[i] == CODE_SHORT){
					delay(this->dotTime);
				}
				else{
					delay(this->dashTime);
				}
				
				duringOff();
				delay(dotTime);
			}
		}
		delay(dotTime*3);
	}
}


CodedChar MorseCode::GetCharacter(char toGet){
	for (int i = 0; i < 36; ++i){
		if(this->MORSE_VALUES[i].character == toGet){
			return this->MORSE_VALUES[i];
		}
	}
	Serial.print("Char not found\n");
	return (CodedChar){'A',0,{}};;
}


void MorseCode::setDotTime(int toSet){
	this->dotTime = toSet;
	this->dashTime = dotTime*3;
}
