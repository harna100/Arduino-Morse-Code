#ifndef CODEDCHAR_H
#define CODEDCHAR_H

#include "Duration.h"

struct CodedChar {
	char character;
	int codesLength;
	DURATION codes[5];
};


#endif