#ifndef _TOOLS_ONE_WIRE_H_
#define _TOOLS_ONE_WIRE_H_

#include "delay.h"
#include "rcc_config.h"
#include "stm32f4xx.h"

class OneWire{
public:
    OneWire(GPIO_TypeDef *port,uint16_t pin);
    ~OneWire();

    bool reset();
    uint8_t read();
    void write(uint8_t data);
protected:
private:
    Delay &m_delay;
    GPIO_TypeDef *m_port;
    uint16_t m_pin;
};

#endif //_TOOLS_ONE_WIRE_H_