#ifndef _TOOLS_USART_H_
#define _TOOLS_USART_H_

#include "stm32f4xx.h"

class USART{
public:
    static USART &instance()noexcept{
        static USART usart;
        return usart;
    }


    const static char endl = '\n';
    const static char tab = 't';
    const static char space = ' ';


    USART &operator<<(int data);
    USART &operator<<(int32_t data);
    USART &operator<<(uint32_t data);
    USART &operator<<(const char *);
    USART &operator<<(char);

    USART &operator>>(char &);
    //USART &operator>>(int &);

protected:
private:
    USART();
    ~USART();
};

#endif //_TOOLS_USART_H_