#include "pwm.h"

PWM::PWM(TIM_TypeDef *tim,uint8_t channel,uint32_t period)
    :m_tim(tim),
     m_period(period){
    TIM_DeInit(tim);
    TIM_TimeBaseInitTypeDef timebaseinit = {
        .TIM_Prescaler = RCC_HP_APB1_TIMCLK / 1000000 - 1,//us
        .TIM_CounterMode = TIM_CounterMode_Up,
        .TIM_Period = period - 1,
        .TIM_ClockDivision = TIM_CKD_DIV1,
        .TIM_RepetitionCounter = 0
    };
    TIM_TimeBaseInit(tim,&timebaseinit);
    TIM_ARRPreloadConfig(tim,ENABLE);

    TIM_OCInitTypeDef ocinit = {
        .TIM_OCMode = TIM_OCMode_PWM1,
        .TIM_OutputState = TIM_OutputState_Enable,
        .TIM_OutputNState = TIM_OutputNState_Enable,
        .TIM_Pulse = period >> 1,
        .TIM_OCPolarity = TIM_OCPolarity_High,
        .TIM_OCNPolarity = TIM_OCNPolarity_Low,
        .TIM_OCIdleState = TIM_OCIdleState_Set,
        .TIM_OCNIdleState = TIM_OCNIdleState_Reset
    };
    if((channel & PWM_CHANNEL_1) == PWM_CHANNEL_1){
        TIM_OC1Init(tim,&ocinit);
        TIM_OC1PreloadConfig(tim,TIM_OCPreload_Enable);
    }else if((channel & PWM_CHANNEL_2) == PWM_CHANNEL_2){
        TIM_OC2Init(tim,&ocinit);
        TIM_OC2PreloadConfig(tim,TIM_OCPreload_Enable);
    }else if((channel & PWM_CHANNEL_3) == PWM_CHANNEL_3){
        TIM_OC3Init(tim,&ocinit);
        TIM_OC3PreloadConfig(tim,TIM_OCPreload_Enable);
    }else if((channel & PWM_CHANNEL_4) == PWM_CHANNEL_4){
        TIM_OC4Init(tim,&ocinit);
        TIM_OC4PreloadConfig(tim,TIM_OCPreload_Enable);
    }
    TIM_Cmd(tim,ENABLE);
    //TIM_CtrlPWMOutputs(tim,ENABLE);
}

PWM::~PWM() = default;

void PWM::on() noexcept{
    TIM_Cmd(m_tim,ENABLE);
}

void PWM::off() noexcept{
    TIM_Cmd(m_tim,DISABLE);
}

void PWM::setDutyCycle(uint32_t num,uint32_t den,uint8_t channel) noexcept{
    if((channel & PWM_CHANNEL_1) == PWM_CHANNEL_1){
        TIM_SetCompare1(m_tim,m_period * num / den);
    }else if((channel & PWM_CHANNEL_2) == PWM_CHANNEL_2){
        TIM_SetCompare2(m_tim,m_period * num / den);
    }else if((channel & PWM_CHANNEL_3) == PWM_CHANNEL_3){
        TIM_SetCompare3(m_tim,m_period * num / den);
    }else if((channel & PWM_CHANNEL_4) == PWM_CHANNEL_4){
        TIM_SetCompare4(m_tim,m_period * num / den);
    }
}

