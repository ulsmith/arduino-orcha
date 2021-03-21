#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <Orcha.h>
#include <Servo.h>

Orcha::Orcha(void) {}

Orcha::assign(OrcChain * chain) {
	unsigned int i =0;
	while (chain[i].orc)
	{
		chain[i].orc->servo = Servo();
		chain[i].orc->servo.attach(chain[i].orc->pin);
		i++;
	}
}

Orcha::setStep(OrcChain * chain, byte angle, int delay, int time) {
	chain->angle = angle;
	chain->delay = delay;
	chain->time = time;
}

Orcha::reset(OrcChain * chain) {
	unsigned int i =0;
	while (chain[i].orc)
	{
		chain[i].orc->angle = chain[i].orc->home;
		chain[i].orc->servo.write(chain[i].orc->angle);
		i++;
	}
}

Orcha::play(OrcChain * chain, short jitter, short settle) {
	long start = millis();
	long now = millis();
	bool done = false;

	while (!done) {
		done = true;

		unsigned int i = 0;
		while (chain[i].orc) {
			now = millis();
			bool res = move(&chain[i], start, now);
			if (done) done = res;
			if (jitter) delay(jitter);
			i++;
		}
	}
	
	// clear up cache
	unsigned int ii = 0;
	while (chain[ii].orc) {
		chain[ii].origin = NULL;
		ii++;
	}

	if (settle) delay(settle);
}

Orcha::clear(OrcChain * chain) {
	// reset chain values
	unsigned int i = 0;
	while (chain[i].orc) {
		// do we shift data?
		chain[i].origin = NULL;
		chain[i].angle = NULL;
		chain[i].delay = NULL;
		chain[i].time = NULL;
		i++;
	}
}

bool Orcha::move(OrcChain * chainable, long start, long now) {
	// capture the start position
	if (!chainable->origin) chainable->origin = chainable->orc->angle;

	// capture the increment amount if not set
	float inc = ((float) chainable->angle - (float) chainable->origin) / (float) chainable->time;

	// move by increment over time added to current angle
	if (now >= start + (long) chainable->delay && chainable->angle != chainable->orc->angle) {
		// write new angle
		chainable->orc->angle = ((int)chainable->origin + (inc * (float)(now - (start + chainable->delay))));
		
		// should we overrid it if past?
		if (chainable->angle > chainable->origin && chainable->orc->angle > chainable->angle) chainable->orc->angle = chainable->angle;
		else if (chainable->angle < chainable->origin && chainable->orc->angle < chainable->angle) chainable->orc->angle = chainable->angle;

		// write movement
		chainable->orc->servo.write((int) chainable->orc->angle);
	}

	// did we make it all the way?
	if (chainable->angle != chainable->orc->angle) return false;
	return true;
}