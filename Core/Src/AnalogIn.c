/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  AnalogOut.c
 *
 *  FONCTION analogIn Q3.7
 *
 */

#include "main.h"
#include "AnalogIn.h"
#include "stm32l0xx_ll_adc.h"

void AnalogInInit(void){
	// Active l'ADC
	LL_ADC_Enable(ADC1);
}

void AnalogInStartConversion(void){
	//Lance la conversion et reste tant que cela n'est pas fini
	LL_ADC_REG_StartConversion (ADC1);
	while(LL_ADC_IsActiveFlag_EOC(ADC1) == 0 );
}

uint8_t AnalogInGetValue(void){
	return LL_ADC_REG_ReadConversionData8(ADC1);
}
