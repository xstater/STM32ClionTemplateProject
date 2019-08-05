#include "data_scope.h"

DataScope::DataScope()
    :m_channel_number(4),
     m_buffer{0}{}

DataScope::~DataScope() = default;

void DataScope::setData(float data,uint8_t channel){
    if((channel > 10) || (channel == 0)){
        return; //通道个数大于10或等于0，直接跳出，不执行函数
    }else{
        switch(channel){
            case 1:
                floatToByte(&data,m_buffer,1);
                break;
            case 2:
                floatToByte(&data,m_buffer,5);
                break;
            case 3:
                floatToByte(&data,m_buffer,9);
                break;
            case 4:
                floatToByte(&data,m_buffer,13);
                break;
            case 5:
                floatToByte(&data,m_buffer,17);
                break;
            case 6:
                floatToByte(&data,m_buffer,21);
                break;
            case 7:
                floatToByte(&data,m_buffer,25);
                break;
            case 8:
                floatToByte(&data,m_buffer,29);
                break;
            case 9:
                floatToByte(&data,m_buffer,33);
                break;
            case 10:
                floatToByte(&data,m_buffer,37);
                break;
        }
    }
}

void DataScope::send(){
    auto &usart = USART::instance();
    m_buffer[0] = '$'; //帧头
    uint32_t length = 0;
    switch(m_channel_number){
        case 1:
            m_buffer[5] = 5;
            length = 6;
            break;
        case 2:
            m_buffer[9] = 9;
            length = 10;
            break;
        case 3:
            m_buffer[13] = 13;
            length = 14;
            break;
        case 4:
            m_buffer[17] = 17;
            length = 18;
            break;
        case 5:
            m_buffer[21] = 21;
            length = 22;
            break;
        case 6:
            m_buffer[25] = 25;
            length = 26;
            break;
        case 7:
            m_buffer[29] = 29;
            length = 30;
            break;
        case 8:
            m_buffer[33] = 33;
            length = 34;
            break;
        case 9:
            m_buffer[37] = 37;
            length = 38;
            break;
        case 10:
            m_buffer[41] = 41;
            length = 42;
            break;
        default:
            m_buffer[5] = 5;
            length = 6;
            break;
    }
    for(uint32_t i = 0;i < length;++i){
        usart << static_cast<char>(m_buffer[i]);
    }
}

void DataScope::floatToByte(float *target,unsigned char *buf,unsigned char beg){
    unsigned char *point;
    point = (unsigned char *)target; //得到float的地址
    buf[beg] = point[0];
    buf[beg + 1] = point[1];
    buf[beg + 2] = point[2];
    buf[beg + 3] = point[3];
}

void DataScope::setChannelNumber(uint8_t channel_number){
    if((channel_number > 10)||(channel_number == 0))
        return;
    m_channel_number = channel_number;
}
