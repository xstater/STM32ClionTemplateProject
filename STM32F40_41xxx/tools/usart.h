#ifndef _TOOLS_USART_H_
#define _TOOLS_USART_H_

#include "stm32f4xx.h"

class USART{
public:
    static USART &instance()noexcept{
        static USART usart;
        return usart;
    }

    enum class CtrlChar : uint8_t {
        set_precision = 0,
    };
    struct Ctrl{
        CtrlChar ctr;
        uint32_t data;
    };

    static Ctrl setPrecision(uint32_t precision)noexcept{
        return {CtrlChar::set_precision,precision};
    }

    const static char endl = '\n';
    const static char tab = 't';
    const static char space = ' ';


    USART &operator<<(int data);
    USART &operator<<(int32_t data);
    USART &operator<<(uint32_t data);
    USART &operator<<(float data);
    USART &operator<<(const char *);
    USART &operator<<(char);
    USART &operator<<(Ctrl ctrl);

    USART &operator>>(char &);
    //USART &operator>>(int &);

protected:
private:
    int32_t m_precision;

    USART();
    ~USART();
};

#endif //_TOOLS_USART_H_