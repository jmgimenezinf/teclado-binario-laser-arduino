#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
public:
	Morse(int pin);
	void Write(String message);
	void dot();
	void dash();
private:
	int _pin;

	void toMorse(char letter);
};
#endif