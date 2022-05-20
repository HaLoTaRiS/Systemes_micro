/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  led.c
 *
 *  FONCTION LED Q 3.2
 */

#include <stdio.h>
#include "led.h"
#include "main.h"


// Initialisation des données de la structure
Led_t ledStatus = { 0 , 0 };

// Fonction pour démarrer le timer
void LedStart(void){
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
}

// Configure le rapport cyclique
void LedSetValue(uint8_t val){
	LL_TIM_OC_SetCompareCH1(TIM2, val);
}

// Gere l'intensité
void LedPulse(void){
	//augmentation d'intensité led
	if (ledStatus.updown == 0) {
		ledStatus.luminosite++;
	}
	// Diminution de l'intensité
	else {
		ledStatus.luminosite--;
	}

	// En mode décrémente
	if (ledStatus.luminosite == 255){
		ledStatus.updown = 1;
	}

	// En mode incrémente
	if (ledStatus.luminosite == 0){
		ledStatus.updown = 0;
	}
	LedSetValue(ledStatus.luminosite);
}
