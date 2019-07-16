#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include "stm32f4xx.h"

void NMI_Handler();
void HardFault_Handler();
void MemManage_Handler();
void BusFault_Handler();
void UsageFault_Handler();
void SVC_Handler();
void DebugMon_Handler();
void PendSV_Handler();
void SysTick_Handler();


#endif //_INTERRUPTS_H_
