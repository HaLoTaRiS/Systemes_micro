#include "timebase.h"
#include "main.h"

void TimeBaseStartIT(){
	LL_TIM_EnableCounter(TIM21);
	LL_TIM_EnableUpdateEvent(TIM21);

}
