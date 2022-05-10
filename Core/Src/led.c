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

// Structure pour la gestion de a led :
typedef struct data {
	int8_t lumonosite ;
	int8_t updown;
} Led;

// Initialisation des données de la structure
Led ledStatus = { 0 , 0 };

// Fonction pour démarrer le timer
void LedStart(void){
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
}

// Configure le rapport cyclique
void LedSetValue(uint8_t val){
	LL_TIM_OC_SetCompareCH1(TIM2, val);
}

void LedPulse(void){
	//augmentation d'intensité led
	if (ledStatus.updown == 0) {
		ledStatus.lumonosite++;
		if (ledStatus.lumonosite == 124){
			ledStatus.updown = 1;
		}
	}
	//Diminution de l'intensité LedStatus
	else {
		ledStatus.lumonosite--;
		if (ledStatus.lumonosite == 1){
			ledStatus.updown = 0;
		}
	}
	LedSetValue(ledStatus.lumonosite);
}




