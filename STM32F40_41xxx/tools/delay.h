#ifndef _DELAY_H_
#define _DELAY_H_

#ifdef STM32F407xx

#define TIME_COUNT_5us 16
#define TIME_COUNT_10us 41
#define TIME_COUNT_50us 233
#define TIME_COUNT_100us 480
#define TIME_COUNT_500us 2400
#define TIME_COUNT_1ms 4850
#define TIME_COUNT_5ms 24250
#define TIME_COUNT_10ms 48500
#define TIME_COUNT_50ms 242500
#define TIME_COUNT_100ms 485000
#define TIME_COUNT_500ms 2425000
#define TIME_COUNT_1s 4850000

#define delay_5us() delay_simple(TIME_COUNT_5us)
#define delay_10us() delay_simple(TIME_COUNT_10us)
#define delay_50us() delay_simple(TIME_COUNT_50us)
#define delay_100us() delay_simple(TIME_COUNT_100us)
#define delay_500us() delay_simple(TIME_COUNT_500us)
#define delay_1ms() delay_simple(TIME_COUNT_1ms)
#define delay_5ms() delay_simple(TIME_COUNT_5ms)
#define delay_10ms() delay_simple(TIME_COUNT_10ms)
#define delay_50ms() delay_simple(TIME_COUNT_50ms)
#define delay_100ms() delay_simple(TIME_COUNT_100ms)
#define delay_500ms() delay_simple(TIME_COUNT_500ms)
#define delay_1s() delay_simple(TIME_COUNT_1s)

#define delay_second(Time) delay_simple(TIME_COUNT_1s * (Time))

#endif //STM32F407xx

void delay_simple(volatile unsigned int count);

#endif //_DELAY_H_