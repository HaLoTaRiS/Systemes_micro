/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  AnalogOut.h
 *
 *  FONCTION analogIn Q3.7
 *
 */

void AnalogInInit(void);

void AnalogInStartConversion(void);

// Cette fonction fait du polling, même si c'est pas bien
uint8_t AnalogInGetValue(void);
