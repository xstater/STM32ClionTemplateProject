#include "usart.h"

USART::USART()
    :m_precision(8){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    USART_InitTypeDef usartinit = {
            .USART_BaudRate = 115200,
            .USART_WordLength = USART_WordLength_8b,
            .USART_StopBits = USART_StopBits_1,
            .USART_Parity = USART_Parity_No,
            .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
            .USART_HardwareFlowControl = USART_HardwareFlowControl_None
    };
    USART_Init(USART1,&usartinit);
    USART_Cmd(USART1,ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef gpioinit = {
            .GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10,
            .GPIO_Mode = GPIO_Mode_AF,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd = GPIO_PuPd_UP
    };
    GPIO_Init(GPIOA,&gpioinit);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
}

USART::~USART() = default;

USART &USART::operator<<(int32_t data){
    char s[13],*p = s,*q = s;///q is the position of the first digit
    if(data < 0){
        *(p++) = '-';
        data = -data;
    }
    q = p;
    ///get digits
    for(;data > 0;data /= 10){
        *(p++) = data % 10 + '0';
    }
    *p = '\0';
    ///reverse the sequence
    for(--p;p >= q;--p,++q){
        char c = *p;
        *p = *q;
        *q = c;
    }
    ///output to uart
    for(p = s;*p != '\0';++p){
        *this << *p;
    }
    return *this;
}

USART& USART::operator<<(const char *str){
    for(;*str != '\0';++str){
        *this << *str;
    }
    return *this;
}

//[[gnu::always_inline]]
USART& USART::operator<<(char ch){
    USART1->SR;///read SR to set TC to 0
    USART_SendData(USART1,ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
    return *this;
}

USART &USART::operator>>(char &ch){
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != SET);
    ch = USART_ReceiveData(USART1);
    return *this;
}

USART &USART::operator<<(uint32_t data){
    char s[13],*p = s,*q = s;///q is the position of the first digit
    ///get digits
    for(;data > 0;data /= 10){
        *(p++) = data % 10 + '0';
    }
    *p = '\0';
    ///reverse the sequence
    for(--p;p >= q;--p,++q){
        char c = *p;
        *p = *q;
        *q = c;
    }
    ///output to uart
    for(p = s;*p != '\0';++p){
        *this << *p;
    }
    return *this;
}

USART &USART::operator<<(int data){
    char s[13],*p = s,*q = s;///q is the position of the first digit
    if(data < 0){
        *(p++) = '-';
        data = -data;
    }
    q = p;
    ///get digits
    for(;data > 0;data /= 10){
        *(p++) = data % 10 + '0';
    }
    *p = '\0';
    ///reverse the sequence
    for(--p;p >= q;--p,++q){
        char c = *p;
        *p = *q;
        *q = c;
    }
    ///output to uart
    for(p = s;*p != '\0';++p){
        *this << *p;
    }
    return *this;
}

USART &USART::operator<<(float data){
    ///output the integer part
    *this << static_cast<int32_t>(data);
    ///abs
    if(data < 0){
        data = -data;
    }
    *this << '.';
    ///get the decimal part
    data -= static_cast<int32_t>(data);
    for(int i = 0;i < m_precision;++i){
        data *= 10;
    }
    ///round
    auto t = static_cast<uint32_t>(data * 10);
    if(t % 10 > 4){
        t /= 10;
        ++t;
    }else{
        t /= 10;
    }
    return *this << t;
}

USART &USART::operator<<(USART::Ctrl ctrl){
    switch(ctrl.ctr){
        case CtrlChar::set_precision :
            m_precision = ctrl.data;
            break;
    }
    return *this;
}




