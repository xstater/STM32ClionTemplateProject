#include "one_wire.h"

/**
 * @brief Initialize the GPIO
 * @note use RCC_AHB1PeriphClockCmd() to enable the GPIO's clock
 * @param port:GPIOA ~ GPIOF
 * @param pin:GPIO_Pin_0 ~ GPIO_Pin_15
 */
OneWire::OneWire(GPIO_TypeDef *port,uint16_t pin)
    :m_delay(Delay::instance()),
     m_port(port),
     m_pin(pin){
    m_delay.setPrecision(DELAY_PRECISION_US);

    GPIO_InitTypeDef gpioinit = {
        .GPIO_Pin = m_pin,
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_OType = GPIO_OType_OD,
        .GPIO_PuPd = GPIO_PuPd_NOPULL
    };
    GPIO_Init(port,&gpioinit);
}

OneWire::~OneWire() = default;

/**
 * @brief reset and check the 1-wire device's response
 * @return return true if success ,otherwise return false
 */
bool OneWire::reset(){
    GPIO_ResetBits(m_port,m_pin);
    m_delay(600);
    GPIO_SetBits(m_port,m_pin);
    m_delay(20);

    uint32_t count;
    for(count = 0;count < 500;++count){
        if(GPIO_ReadInputDataBit(m_port,m_pin) == RESET)
            break;
        m_delay(1);
    }

    m_delay(500 - count);

    return (count < 480);
}
/**
 * @brief read a byte
 * @return return a byte
 */
uint8_t OneWire::read(){
    uint8_t data = 0;
    for(uint32_t i = 0;i < 8;++i){
        GPIO_ResetBits(m_port,m_pin);
        m_delay(5);
        GPIO_SetBits(m_port,m_pin);
        m_delay(20);
        data >>= 1;
        if(GPIO_ReadInputDataBit(m_port,m_pin)){
            data |= 0x80;
        }
        m_delay(35);
    }
    return data;
}
/**
 * @brief write a byte
 * @param data:a byte will be wrote
 */
void OneWire::write(uint8_t data){
    for(uint32_t i = 0; i < 8;++i){
        if(data & 0x01){
            GPIO_ResetBits(m_port,m_pin);
            m_delay(5);
            GPIO_SetBits(m_port,m_pin);
            m_delay(75);
        }else{
            GPIO_ResetBits(m_port,m_pin);
            m_delay(80);
            GPIO_SetBits(m_port,m_pin);
        }
        m_delay(5);
        data >>= 1;
    }
}

