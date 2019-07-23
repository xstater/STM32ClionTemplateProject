#ifndef _TOOLS_RCC_CONFIG_H_
#define _TOOLS_RCC_CONFIG_H_

#include <stm32f4xx.h>

#define RCC_HSI 0
#define RCC_HSE 1
#define RCC_PLL 2

#define RCC_HP_HSE 8000000
#define RCC_HP_PLL_ON
#define RCC_HP_PLL_SOURCE RCC_HSE
#define RCC_HP_PLL_M 4
#define RCC_HP_PLL_N 168
#define RCC_HP_PLL_P 2
#define RCC_HP_PLL_Q 4
#define RCC_HP_SYSCLK_SOURCE RCC_PLL
#define RCC_HP_SYSCLK 168000000
#define RCC_HP_AHB_PSC 1
#define RCC_HP_HCLK_DIV RCC_HP_AHB_PSC
#define RCC_HP_HCLK 168000000
#define RCC_HP_APB1_PSC 4
#define RCC_HP_PCLK1_PSC RCC_HP_APB1_PSC
#define RCC_HP_PCLK1 42000000
#define RCC_HP_APB1_TIMCLK 84000000
#define RCC_HP_APB2_PSC 2
#define RCC_HP_PCLK2_PSC RCC_HP_APB2_PSC
#define RCC_HP_PCLK2  84000000
#define RCC_HP_APB2_TIMCLK 168000000

#ifdef __cplusplus
extern "C" {
#endif

/** @brief config RCC to High Performance mode
  * @details HSE ON!!!
  * @details HSE = 8Mhz
  * @details SYSCLK = 168MHz
  * @details HCLK = 168MHz
  * @details PCLK1 = HCLK/4
  * @details PCLK2 = HCLK/2
  * @retval return 0 if configure failed
  */
uint8_t RCC_config_HighPerformance();

#ifdef __cplusplus
}
#endif


#endif //_TOOLS_RCC_CONFIG_H_