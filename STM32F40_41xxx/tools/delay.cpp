#include "delay.h"

void delay_simple(volatile unsigned int count){
    for(;count > 0;--count);
}