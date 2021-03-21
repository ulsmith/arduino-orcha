# Arduino Orcha

Orchastrate mutliple servos in groups and move them as a single unit. Use angles, delays and times to plan complex movement patterns, play chains of patterns without loops!

This library came about for the want to create complex movement orchastration as little seemed to be available to do this with ease.

The idea was to chain together servos, setting angle, delay and time to complete full movement in a isingle command with the abaility to play the chain once complete.

Use as many chains as you like to group chunks of movement.

Use many sequneces to build routines.

## Introducation

## Example

Setup 

```cpp
#include <Orcha.h>

Orcha orcha;
OrcChain chain[9];
Orc rfshoulder, rfmain, rffoot;
Orc rmshoulder, rmmain, rmfoot;
Orc rbshoulder, rbmain, rbfoot;

// setup orc servo pins and home angle (0-180) all servos have 180 degree movement
orcSetup () {
	// arduino pins
	&rfshoulder->pin = 22;
	&rfmain->pin = 24;
	&rffoot->pin = 26;
	&rmshoulder->pin = 28;
	&rmmain->pin = 30;
	&rmfoot->pin = 32;
	&rbshoulder->pin = 34;
	&rbmain->pin = 36;
	&rbfoot->pin = 38;

	// servo home position (resets to this)
	&rfshoulder->home = 90;
	&rfmain->home = 90;
	&rffoot->home = 90;
	&rmshoulder->home = 90;
	&rmmain->home = 90;
	&rmfoot->home = 90;
	&rbshoulder->home = 90;
	&rbmain->home = 90;
	&rbfoot->home = 90;
}

// build a chain from orc objects, each being a servo
buildChain () {
	chain[0].orc = &rfshoulder;
	chain[1].orc = &rfmain;
	chain[2].orc = &rffoot;
	chain[3].orc = &rmshoulder;
	chain[4].orc = &rmmain;
	chain[5].orc = &rmfoot;
	chain[6].orc = &rbshoulder;
	chain[7].orc = &rbmain;
	chain[8].orc = &rbfoot;
}

// assign the servos to arduino pins
assignChain () {
	orcha.assign(chain);
}

// reset a chain to home points
resetChain () {
	orcha.reset(chain);
}

// Now you are ready to do some sequences...

play () {
	// set a chainable angle, delay and time in ms
	// servos start at different times and perform movement at different speeds but all finish at the same time 400ms
	orcha.setStep(&chain[0], 40, 100, 300);
	orcha.setStep(&chain[1], 50, 200, 200);
	orcha.setStep(&chain[2], 60, 300, 100);
	orcha.setStep(&chain[3], 40, 100, 300);
	orcha.setStep(&chain[4], 50, 200, 200);
	orcha.setStep(&chain[5], 60, 300, 100);
	orcha.setStep(&chain[6], 40, 100, 300);
	orcha.setStep(&chain[7], 50, 200, 200);
	orcha.setStep(&chain[8], 60, 300, 100);

	// run chain
	orcha.play(chain, 1, 0);

	// set a chainable angle, delay and time in ms
	// all servos start at same time and complet the movment to the angle in 400ms
	orcha.setStep(&chain[0], 140, 0, 400);
	orcha.setStep(&chain[1], 150, 0, 400);
	orcha.setStep(&chain[2], 160, 0, 400);
	orcha.setStep(&chain[3], 140, 0, 400);
	orcha.setStep(&chain[4], 150, 0, 400);
	orcha.setStep(&chain[5], 160, 0, 400);
	orcha.setStep(&chain[6], 140, 0, 400);
	orcha.setStep(&chain[7], 150, 0, 400);
	orcha.setStep(&chain[8], 160, 0, 400);

	// run chain
	orcha.play(chain, 1, 0);
}

```