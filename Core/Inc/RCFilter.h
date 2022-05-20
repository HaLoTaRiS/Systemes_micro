/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  RCFilter.h
 *
 *  FONCTION Fitlre RC Q3.8
 *
 */

#ifndef INC_RCFILTER_H_
#define INC_RCFILTER_H_

#include "main.h"

typedef struct {
	uint32_t coeffA;
	uint32_t coeffB;
	uint32_t coeffD;
	uint16_t out_prev;
} hRCFilter_t;

void RCFilterInit(hRCFilter_t * hRCFilter,
		uint16_t cutoffFrequency, uint16_t samplingFrequency);

// Implémente l'équation de récurrence
uint16_t RCFilterUpdate(hRCFilter_t * hRCFilter, uint16_t input);

#endif
