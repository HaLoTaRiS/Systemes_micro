/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  AnalogOut.h
 *
 *  FONCTION analog Q3.6
 *
 */

#ifndef INC_ANALOGOUT_H_
#define INC_ANALOGOUT_H_

//Structure pour notre DAC
typedef struct  {
	// Configuration des bits de communication DAC
	uint8_t DAC_Write;		// 0 : Write to DAC  (Bit 15)
	uint8_t DAC_Buf;		// 1 : Buffered      (Bit 14)
	uint8_t DAC_Ga;		    // 1 : Gain  		 (Bit 13)
	uint8_t DAC_SHDN;		// 1 : OuputShutdown (Bit 12)
	// Génération des signaux
	uint8_t amplitude;
	uint8_t updown;
} DAC_t;


void AnalogOutInit(void);

void AnalogOutConvert(uint8_t value);

void AnalogOutPulse(void);

#endif
