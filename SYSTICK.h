#ifndef SYSTICK_H
#define SYSTICK_H
extern volatile uint32_t msTicks;
extern volatile uint32_t curTicks;;
extern void SysTick_Handler(void);
extern void delay(uint32_t );
extern uint32_t  init_cycle(void);
extern void wait_end_cycle(void);
extern void test_time(void);
#endif
