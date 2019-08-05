#include "delay.h"

void Delay::setPrecision(uint32_t precision){
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(RCC_HP_HCLK / precision);
}

void Delay::operator()(int32_t count){
    m_count = count;
    while(m_count > 0);
}

void SysTick_Handler(){
    Delay::instance().__dec();
}