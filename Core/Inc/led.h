/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  led.h
 *
 *  FONCTION LED Q 3.2
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

// Fonction qui démarre le timer
void LedStart(void);

// Fonction qui configure le rapport cyclique de la PWM
void LedSetValue(uint8_t val);

// fonction qui incrémente puis décremente la luminosité de la led
void LedPulse(void);

#endif
