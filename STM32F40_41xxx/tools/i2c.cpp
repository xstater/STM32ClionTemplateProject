#include "i2c.h"

#define SCL_HIGH() GPIO_SetBits(m_port_scl,m_pin_scl)
#define SCL_LOW() GPIO_ResetBits(m_port_scl,m_pin_scl)
#define SDA_HIGH() GPIO_SetBits(m_port_sda,m_pin_sda)
#define SDA_LOW() GPIO_ResetBits(m_port_sda,m_pin_sda)

I2C::I2C(GPIO_TypeDef *port_scl,uint16_t pin_scl,GPIO_TypeDef *port_sda,uint16_t pin_sda)
    :m_delay(Delay::instance()),
     m_port_scl(port_scl),
     m_port_sda(port_sda),
     m_pin_scl(pin_scl),
     m_pin_sda(pin_sda){
    ///initialize Delay Precision
    m_delay.setPrecision(DELAY_PRECISION_US);

    ///initialize SCL
    GPIO_InitTypeDef gpioinit = {
        .GPIO_Pin = m_pin_scl,
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_OType = GPIO_OType_OD,
        .GPIO_PuPd = GPIO_PuPd_NOPULL
    };
    GPIO_Init(m_port_scl,&gpioinit);
    SCL_HIGH();
    ///initialize SDA
    gpioinit.GPIO_Pin = m_pin_sda;
    GPIO_Init(m_port_sda,&gpioinit);
    SDA_HIGH();
}


I2C::~I2C() = default;

void I2C::send_start(){
    SDA_HIGH();
    SCL_HIGH();
    m_delay(5);
    SDA_LOW(); //When SCL is high,the SDA fall into low
    m_delay(5);
    SCL_LOW(); //lock i2c bus and wait for send or receive data
}

void I2C::send_stop(){
    SCL_LOW();
    SDA_LOW();
    m_delay(5);
    SCL_HIGH();
    m_delay(1);
    SDA_HIGH();
    m_delay(5);
}

bool I2C::recv_ack(){
    uint32_t timeout = RETRY_COUNT_WAIT_FOR_ACK;
    SDA_HIGH();m_delay(1);
    SCL_HIGH();m_delay(1);
    for(;timeout != 0;--timeout){
        if(GPIO_ReadInputDataBit(m_port_sda,m_pin_sda) == SET){
            ///Read a 1
            ///NACK
            send_stop();
            return false;
        }
    }
    SCL_LOW();
    return true;
}

void I2C::send_ack(){
    SCL_LOW();
    m_delay(2);
    SDA_LOW();
    m_delay(2);
    SCL_HIGH();
    m_delay(5);
    SCL_LOW();
}

void I2C::send_nack(){
    SCL_LOW();
    m_delay(2);
    SDA_HIGH();
    m_delay(2);
    SCL_HIGH();
    m_delay(5);
    SCL_LOW();
}

void I2C::send_byte(uint8_t data){
    for(uint32_t i = 0; i < 8;++i){
        SCL_LOW();
        m_delay(2);
        if(data & 0x80){
            SDA_HIGH();
        }else{
            SDA_LOW();
        }
        data <<= 1;
        m_delay(2);
        SCL_HIGH();
        m_delay(5);
    }
    SCL_LOW();
}

uint8_t I2C::recv_byte(){
    uint8_t data;
    for(uint32_t i = 0;i < 8;++i){
        SCL_LOW();
        m_delay(2);
        SCL_HIGH();
        data <<= 1;
        if(GPIO_ReadInputDataBit(m_port_sda,m_pin_sda) == SET){
            data |= 0x01;
        }
        m_delay(5);
    }
    return data;
}


#undef SCL_HIGH
#undef SCL_LOW
#undef SDA_HIGH
#undef SDA_LOW
