#ifndef _TOOLS_PWM_H_
#define _TOOLS_PWM_H_

#include "stm32f4xx.h"
#include "rcc_config.h"

#define PWM_CHANNEL_NONE 0x00
#define PWM_CHANNEL_1    0x01
#define PWM_CHANNEL_2    0x02
#define PWM_CHANNEL_3    0x04
#define PWM_CHANNEL_4    0x08
#define PWM_CHANNEL_ALL  0x0F

class PWM{
public:
    /**
     * @brief Initialize PWM with a timer and output channel
     * @param tim The timer you want to use
     * @param channel The output channel you want to use.It can be PWM_CHANNEL_X where x is [1..4]
     * @param period The period of the PWM
     */
    PWM(TIM_TypeDef *tim,uint8_t channel,uint32_t period);
    ~PWM();

    /**
     * @brief Set PWM's duty cycle
     * @param num the numerator of the duty cycle
     * @param den the denominator of the duty cycle
     * @param channel the channel you want to set
     */
    void on()noexcept;
    void off()noexcept;
    void setDutyCycle(uint32_t num,uint32_t den,uint8_t channel)noexcept;
protected:
private:
    TIM_TypeDef *m_tim;
    uint32_t m_period;
};

#endif //_TOOLS_PWM_H_