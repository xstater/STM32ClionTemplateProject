#include "rcc_config.h"

uint8_t RCC_config_HighPerformance(){
    RCC_DeInit();

    RCC_PLLCmd(DISABLE);

    RCC_HSEConfig(RCC_HSE_ON);
    if(RCC_WaitForHSEStartUp() != SUCCESS){
        return 1;
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div4);
    RCC_PCLK2Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSE,4,168,2,4);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    return 0;
}
