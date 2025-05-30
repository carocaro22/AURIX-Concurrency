#ifndef TRICORE_DEBUG__TASKING__LEDS_H_
#define TRICORE_DEBUG__TASKING__LEDS_H_

// Initializes P0.1, P0.3, P0.5, P0.7, and P0.9 as outputs and sets them low
void initLEDs(void);

// Sets P0.1, P0.3, P0.5, P0.7, and P0.9 to high (turns on the LEDs)
void turnOnLEDs(void);

#endif /* TRICORE_DEBUG__TASKING__LEDS_H_ */
