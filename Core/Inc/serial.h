/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  serial.h
 *
 *  FONCTION Uart Q 3.4
 *
 */
#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include "main.h"

uint8_t SerialTransmit(char * pData, uint16_t Size);

char SerialReceiveChar(void);

#endif
