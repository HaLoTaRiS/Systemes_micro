/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  RCFilter.c
 *
 *  FONCTION Fitlre RC Q3.8
 *
 */

#include "RCFilter.h"

hRCFilter_t hRCFilter;

// cutoffFrequency : Fréquence de coupure Fc
// samplingFrequency : Fréquence d'échantillonage Fs

void RCFilterInit(hRCFilter_t * hRCFilter, uint16_t cutoffFrequency, uint16_t samplingFrequency){
	hRCFilter->coeffA =  1;
	hRCFilter->coeffB = samplingFrequency/(cutoffFrequency*2*3.14159);
	hRCFilter->coeffD = 1 + samplingFrequency/(cutoffFrequency*2*3.14159);
	hRCFilter->out_prev = 0;
}

uint16_t RCFilterUpdate(hRCFilter_t * hRCFilter, uint16_t input){
	uint16_t Filtre_output = (input * hRCFilter->coeffA + hRCFilter->coeffB * hRCFilter->out_prev ) / hRCFilter->coeffD;

	return Filtre_output;
}
