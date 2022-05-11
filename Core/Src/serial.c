/*
 *  TP Systèmes à microcontrôleur
 *  Jeremy VICENTE & Baptiste FRITOT
 *  serial.c
 *
 *  FONCTION LED Q 3.2
 */

#include "serial.h"
#include "main.h"

uint8_t SerialTransmit(char * pData, uint16_t Size) {
	for (uint16_t i= 0; i< Size; i++) {
		LL_USART_TransmitData8(USART2, pData[i]);
		while(LL_USART_IsActiveFlag_TXE(USART2)==0);
	}
	return 0;
//	LL_USART_TransmitData8(USART2, *pData);
//	return 0;
}

char SerialReceiveChar (void) {
	while(LL_USART_IsActiveFlag_RXNE(USART2)==0);
	return LL_USART_ReceiveData8(USART2);
}

char SerialReceiveByte (void) {
	while(LL_USART_IsActiveFlag_RXNE(USART2)==0);
	return LL_USART_ReceiveData8(USART2);
}
