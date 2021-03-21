#ifndef Orcha_h
#define Orcha_h

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <Servo.h>

struct Orc {
	Servo servo;
	byte pin;
	float angle;
	byte home;
};

struct OrcChain {
	Orc * orc;
	byte origin;
	byte angle;
	short delay;
	short time;
};

class Orcha{
	private:
		bool move(OrcChain * chainable, long start, long now);

	public:
		Orcha(void);

		assign(OrcChain * chain);
		setStep(OrcChain * chain, byte angle, int delay, int time);
		reset(OrcChain * chain);
		play(OrcChain * chain, short jitter, short settle);
		clear(OrcChain * chain);
};

#endif
