/**
 * @file Shell.c
 * @author Laurent Fiack
 * @brief A simple shell to call functions from a remote serial console
 *
 * # How to use this driver
 *
 * - Just try typing stuff!
 */

#include "Shell.h"
#include <stdio.h>
#include "AnalogOut.h"
#include "led.h"
#include "RCFilter.h"
#include <stdlib.h>

// Récupération des données pour lire dans le shell
extern DAC_t DacSPI;
extern Led_t ledStatus;
extern DAC_ADC valeur;
extern hRCFilter_t hRCFilter;

//float DAC_reso = 3.3/255;
////		(10/3)* valeur.ADC_IN/255;

int shHelp(hShell_t * hShell, int argc, char ** argv) {
	int i;

	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\nThe following commands are available:\r\n");
	hShell->transmitCb(hShell->printBuffer, size);

	for(i = 0 ; i < hShell->funcListSize ; i++) {
		uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\t%c - %s\r\n", hShell->funcList[i].c, hShell->funcList[i].description);
		hShell->transmitCb(hShell->printBuffer, size);
	}

	return 0;
}

int shHello(hShell_t * hShell, int argc, char ** argv) {
	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, " {•̃_•̃} Hello World !!! \r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	return 0;
}

int shRead(hShell_t * hShell, int argc, char ** argv) {

// Mis en commentaire pour libérer la mémoire
	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n === Lecture des valeurs ===\r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "LED :\r\n   Luminosité : %d/255 \r\n", ledStatus.luminosite);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Augmentation(0)/Diminution(1) : %d \r\n", ledStatus.updown);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "Signal Triangle :\r\n   Amplitude : %d/255\r\n", DacSPI.amplitude);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Montant(0)/Descendant(1) : %d \r\n", DacSPI.updown);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "Lecture ADC :\r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Résolution(8bits) : %d/255\r\n", valeur.ADC_IN);
	hShell->transmitCb(hShell->printBuffer, size);


// Mauvaise idee : Demande trop de place dans la mémoire
//	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "Tension (Volt) :\r\n %f \r\n", DAC_reso*valeur.ADC_IN);
//	hShell->transmitCb(hShell->printBuffer, size);

	return 0;
}

int shWriteFilter(hShell_t * hShell, int argc, char ** argv) {
	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n === Filtre RC : Ecriture A,B et D===\r\n");
	hShell->transmitCb(hShell->printBuffer, size);

	if (argc == 4) {
		hRCFilter.coeffA = atoi(argv[1]);			// on écrit dans coeff A
		hRCFilter.coeffB = atoi(argv[2]);			// on écrit dans coeff B
		hRCFilter.coeffD = atoi(argv[3]);			// on écrit dans coeff D
	}
	else {
		size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   ! Erreur arguments A, B, et D \r\n");
		hShell->transmitCb(hShell->printBuffer, size);
	}
	return 0;
}

int shReadFilter(hShell_t * hShell, int argc, char ** argv) {
	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n === Filtre RC : Lecture A,B et D ===\r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Coeff A : %lu\r\n", hRCFilter.coeffA);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Coeff B : %lu\r\n", hRCFilter.coeffB);
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "   Coeff D : %lu\r\n", hRCFilter.coeffD);
	hShell->transmitCb(hShell->printBuffer, size);
	return 0;
}

uint8_t isChar(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '+') || (c == '-')) {
		return 1;
	}
	else {
		return 0;
	}
}

uint8_t isSpace(char c) {
	if (c == ' ') {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * @brief Initialises the Shell driver
 *
 * @param hShell      Shell handle
 * @param transmitCb  Function to be called when character has to be called
 * @retval Status (0 if successful)
 */
uint8_t ShellInit(hShell_t * hShell, ShellTransmitCb_t transmitCb) {
	if (hShell == NULL) {
		return 255;
	}

	hShell->funcListSize = 0;
	hShell->transmitCb = transmitCb;
	hShell->cmdLinePosition = 0;
	hShell->arrowPending = 0;
	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n\r\n   3DN : TP Microcontroleur\r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "Baptiste FRITOT - Jeremy VICENTE\r\n");
	hShell->transmitCb(hShell->printBuffer, size);
	size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "===== Monsieur Shell v0.4 =====\r\n");
	hShell->transmitCb(hShell->printBuffer, size);

	ShellAdd(hShell, 'h', shHelp, "Displays this help message");
	ShellAdd(hShell, 'a', shHello, "Hello World");
	ShellAdd(hShell, 'z', shRead, "Read Value");
	ShellAdd(hShell, 'q', shWriteFilter, "Filter : Modify Coef A, B and D");
	ShellAdd(hShell, 's', shReadFilter, "Filter : Read Data A, B and D");

	hShell->transmitCb("\r\n> ", 4);

	return 0;
}

uint8_t ShellAdd(hShell_t * hShell, char c, ShellFuncPtr_t pFunc, char * description) {
	if (!isChar(c)) {
		return 255;
	}

	if (hShell->funcListSize < _SHELL_FUNC_LIST_MAX_SIZE) {
		hShell->funcList[hShell->funcListSize].c = c;
		hShell->funcList[hShell->funcListSize].func = pFunc;
		hShell->funcList[hShell->funcListSize].description = description;
		hShell->funcListSize++;
		return 0;
	}

	return 255;
}

uint8_t ShellExec(hShell_t * hShell) {
	int argc;
	char * argv[_ARGV_SIZE];

	char * cmdLine = hShell->cmdLineBuffer;

	for(uint16_t i = 0 ; i < hShell->funcListSize ; i++) {
		if (hShell->funcList[i].c == cmdLine[0]) {
			argc = 1;
			argv[0] = cmdLine;

			// Replacing the spaces with '\0' to be usable by the called function
			for(uint16_t i = 0 ; (i < hShell->cmdLinePosition && argc < _ARGV_SIZE) ; i++){
				if(cmdLine[i] == ' ') {
					cmdLine[i] = '\0';

					uint16_t next = i+1;
					if (next < hShell->cmdLinePosition && (isChar(cmdLine[next]))) {
						argv[argc++] = &(cmdLine[next]);
					}
				}
			}

			// Actual call of the function
			int ret = hShell->funcList[i].func(hShell, argc, argv);

			// Error display
			if (ret == 0) {
				uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n%c returned successfully\r\n", cmdLine[0]);
				hShell->transmitCb(hShell->printBuffer, size);
			}
			else {
				uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n%c returned with error code %d\r\n", cmdLine[0], ret);
				hShell->transmitCb(hShell->printBuffer, size);
			}

			return 0;
		}
	}

	uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\n%c: no such command\r\n", cmdLine[0]);
	hShell->transmitCb(hShell->printBuffer, size);

	return 255;
}

uint8_t ShellProcess(hShell_t * hShell, char c) {
	if (hShell->arrowPending == 0) {
		if (c == '\r') {
			hShell->transmitCb("\r\n:", 3);
			hShell->transmitCb(hShell->cmdLineBuffer, hShell->cmdLinePosition);
			hShell->transmitCb("\r\n", 2);

			// Add zero char to be used with newlib functions
			hShell->cmdLineBuffer[hShell->cmdLinePosition] = '\0';

			ShellExec(hShell);

			hShell->cmdLinePosition = 0;            //reset buffer

			hShell->transmitCb("\r\n> ", 4);
		}
		else if (c == '\b') {
			if (hShell->cmdLinePosition > 0) {      //is there a char to delete?
				hShell->cmdLinePosition--;          //remove it in buffer
				hShell->cmdLineBuffer[hShell->cmdLinePosition] = '\0'; //store

				hShell->transmitCb("\b \b", 3);
			}
		}
		else if (isChar(c) || isSpace(c)) {
			//only store characters if buffer has space
			if (hShell->cmdLinePosition < _COMMAND_LINE_SIZE) {
				hShell->transmitCb((&c), 1);
				hShell->cmdLineBuffer[hShell->cmdLinePosition++] = c; //store
			}
		}
		else if (c == _ARROW_FIRST) {
			hShell->arrowPending++;
		}
		//		else {
		//			uint16_t size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\nReceived char is %d (in decimal)\r\n", c);
		//			hShell->transmitCb(hShell->printBuffer, size);
		//
		//			size = snprintf(hShell->printBuffer, _PRINT_BUFFER_SIZE, "\r\nSkipping line!\r\n");
		//			hShell->transmitCb(hShell->printBuffer, size);
		//
		//			hShell->cmdLinePosition = 0;            //reset buffer
		//			hShell->transmitCb("\r\n> ", 4);
		//		}
	}
	else {
		if (hShell->arrowPending == 1) {
			if (c == _ARROW_SECOND) {
				hShell->arrowPending++;
			}
		}
		else if (hShell->arrowPending == 2) {
			switch (c) {
			case _ARROW_THIRD_UP:
				break;
			case _ARROW_THIRD_DOWN:
				break;
			case _ARROW_THIRD_RIGHT:
				break;
			case _ARROW_THIRD_LEFT:
				break;
			default:
				break;
			}

			hShell->arrowPending = 0;

		}
	}

	return 0;
}
