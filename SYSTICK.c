#include <TM4C129.h>
#include <stdio.h>
#include "SYSTICK.h"
#include <inttypes.h>
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

void test_time(){
	uint32_t array[11];
	uint64_t promedio = 0;
	int cycle = 0;
	int i;
	while(cycle<=11){
		array[cycle]=init_cycle();
		printf("%d--%d\n",cycle,array[cycle]);
		delay(200);
		wait_end_cycle();
		cycle++;
	};
	for(i=11;i>1;i--){
		promedio+=array[i]-array[i-1];
		printf("%" PRIu32 "\n"  ,array[i]-array[i-1]);
	}
	promedio/=10;
	printf("Promedio:%" PRIu64 "\n",promedio);
}
