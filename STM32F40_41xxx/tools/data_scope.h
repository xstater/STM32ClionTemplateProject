#ifndef _TOOLS_DATA_SCOPE_H_
#define _TOOLS_DATA_SCOPE_H_

#include "usart.h"

class DataScope{
public:
    static DataScope &instance()noexcept{
        static DataScope dataScope;
        return dataScope;
    }

    void setChannelNumber(uint8_t channel_number);
    void setData(float data,uint8_t channel);
    void send();
protected:
private:
    DataScope();
    ~DataScope();

    void floatToByte(float *target,unsigned char *buf,unsigned char beg);

    uint8_t m_channel_number;
    unsigned char m_buffer[42];
};

#endif //_TOOLS_DATA_SCOPE_H_
