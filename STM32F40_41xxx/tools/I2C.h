#ifndef _TOOLS_I2C_H_
#define _TOOLS_I2C_H_

#include "stm32f4xx.h"
#include "delay.h"

#define RETRY_COUNT_WAIT_FOR_ACK 250

class I2C{
public:
    /**
     * @brief initialize the I2C port and pin
     * @note I2C must have a outside up-pull resistance which is about 4.7KOhm
     * @param port:the I2C's port
     * @param pin_scl:the I2C's SCL pin
     * @param pin_sda:the I2C's SDA pin
     */
    I2C(GPIO_TypeDef *port_scl,uint16_t pin_scl,GPIO_TypeDef *port_sda,uint16_t pin_sda);
    ~I2C();

    void send_start();
    void send_stop();
    void send_ack();
    void send_nack();
    /**
     * @brief wait for an ACK
     * @return return true if receive a ACK,return false if receive a NACK
     */
    bool recv_ack();
    void send_byte(uint8_t data);
    uint8_t recv_byte();
protected:
private:



    Delay &m_delay;
    GPIO_TypeDef *m_port_scl,*m_port_sda;
    uint16_t m_pin_scl,m_pin_sda;
};

#endif //_TOOLS_I2C_H_