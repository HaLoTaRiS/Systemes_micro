/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  timebase.c
 *
 *  FONCTION Timer21 Q 3.3
 *
 */

#include "timebase.h"
#include "main.h"

// Initialise le timer
void TimeBaseStartIT(){
	LL_TIM_EnableUpdateEvent(TIM21);
	LL_TIM_EnableIT_UPDATE(TIM21);
	LL_TIM_EnableCounter(TIM21);

}
