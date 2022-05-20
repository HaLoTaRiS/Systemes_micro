#include "main.h"
#include "AnalogOut.h"
#include "stm32l0xx_ll_spi.h"

// Initialise les données de la struture
DAC_t DacSPI = { 0, 1 , 1 , 1,  0 , 0 };

void AnalogOutInit(void){
	// Active la communication SPI1
	LL_SPI_Enable(SPI1);
	// Mise à 1 de nCS
	LL_GPIO_SetOutputPin(DAC_nCS_GPIO_Port, DAC_nCS_Pin);
	// Mise à 0 nDAC => Active le périphérique MCP4901
	LL_GPIO_ResetOutputPin(DAC_nLDAC_GPIO_Port, DAC_nLDAC_Pin);
}

void AnalogOutConvert(uint8_t value){

	// Décalage des bits pour la transmission
	uint16_t TxData = (DacSPI.DAC_Write << 15) + (DacSPI.DAC_Buf << 14) + (DacSPI.DAC_Ga << 13) + (DacSPI.DAC_SHDN << 12)  + (value << 4) ;

	// Mise à 0 de nCS (Début de la communication SPI)
	LL_GPIO_ResetOutputPin(DAC_nCS_GPIO_Port, DAC_nCS_Pin);

	while(!LL_SPI_IsActiveFlag_TXE(SPI1));
	LL_SPI_TransmitData16(SPI1, TxData);


	// Mise à 1 de nCS (Fin de la communication SPI)
	LL_GPIO_SetOutputPin(DAC_nCS_GPIO_Port, DAC_nCS_Pin);
}

void AnalogOutPulse(void){

	//augmentation l'amplitude du signal
	if (DacSPI.updown == 0) {
		DacSPI.amplitude++;
	}
	// Diminution de l'amplitude du signal
	else {
		DacSPI.amplitude--;
	}

	// En mode signal descendent
	if (DacSPI.amplitude == 255){
		DacSPI.updown = 1;
	}

	// En mode signal montant
	if (DacSPI.amplitude == 0){
		DacSPI.updown = 0;
	}
	AnalogOutConvert(DacSPI.amplitude);
}
