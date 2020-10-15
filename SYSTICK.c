#include <TM4C129.h>
#include "SYSTICK.h"
volatile uint32_t msTicks;
volatile uint32_t curTicks;
const uint32_t MAX_TICKS = 250;
void SysTick_Handler(void) {
  msTicks++;
}
void delay (uint32_t time) {
  uint32_t curTicks;
  curTicks = msTicks;
  while ((msTicks - curTicks) < time) { __NOP(); }	
}
uint32_t init_cycle(void){
	curTicks = msTicks;
	return curTicks;
	//printf("Inicia ciclo\n");
}
void wait_end_cycle (void) {
  while ((msTicks - curTicks) < MAX_TICKS) { __NOP(); }
}