#ifndef _TOOLS_DELAY_H_
#define _TOOLS_DELAY_H_

#include "stm32f4xx.h"
#include "rcc_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DELAY_PRECISION_MS 1000
#define DELAY_PRECISION_US 1000000

class Delay{
public:
    static Delay &instance()noexcept{
        static Delay delay;
        return delay;
    }

    void setPrecision(uint32_t precision);
    void operator()(int32_t count);
    void reset();
    uint32_t getTime();

    void __dec()noexcept{
        --m_count;
    }
    void __inc()noexcept{
        ++m_count2;
    }
protected:
private:
    volatile int32_t m_count;
    volatile uint32_t m_count2;
};

void SysTick_Handler();

#ifdef __cplusplus
}
#endif


#endif //_TOOLS_DELAY_H_