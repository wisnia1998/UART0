#ifndef leds_h
#define leds_h

void ledsInitialize(void);

void ledsOff (void);
void ledsOn (void);
void ledGreenOff (void);
void ledGreenOn (void);

void startStopFSM(void);
void ledsService1ms(void);
void nextLedState(void);
/////my
void my_sequence(void);

unsigned char phaseA(void);
unsigned char phaseB(void);
unsigned char phaseC(void);

void fastSlowFSM(void);

extern unsigned char slowFSM;


#endif
