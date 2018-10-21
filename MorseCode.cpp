#include <Arduino.h>
#include "MorseCode.h"
#include "CodedChar.h"
#include "Duration.h"


namespace Morse{
	MorseCode::MorseCode(){
		this->dotTime = 250;
		this->resetCheck = []()->bool{return false;};
	};

	MorseCode::~MorseCode(){

	};

	void MorseCode::SendWord(char* word, void(*duringOn)(), void(*duringOff)()){
		if(this->resetCheck() == true){
			return;
		}
		for (int i = 0; word[i] != '\0'; ++i){
			if(this->resetCheck() == true){
				return;
			}
			char currChar = word[i];
			Serial.print("Displaying Character: ");
			Serial.print(currChar);
			Serial.print("\n");
			if(currChar == ' '){
				duringOff();
				delayWithCheck(this->dotTime*7, this->resetCheck);
				continue;
			}
			else {
				CodedChar codedChar = GetCharacter(currChar);
				for (int i = 0; i < codedChar.codesLength; ++i){
					if(this->resetCheck() == true){
						return;
					}
					duringOn();
					if(codedChar.codes[i] == CODE_SHORT){
						delayWithCheck(this->dotTime, this->resetCheck);
					}
					else{
						delayWithCheck(this->dashTime, this->resetCheck);
					}

					duringOff();
					delayWithCheck(dotTime, this->resetCheck);
				}
			}
			delayWithCheck(dotTime*3, this->resetCheck);
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

	void MorseCode::setResetCheck(bool(*toSet)()){
		this->resetCheck = toSet;
	}


	static void MorseCode::delayWithCheck(int milliseconds, bool(*resetCheck)()){
		int count = 0;
		while(count < milliseconds){
			if(resetCheck() == true){
				return;
			}
			count += 1;
			delay(1);
		}
	}	
}
