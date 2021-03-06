// Inicializamos los botones de la tiva y 2 externos mas
// Se utilizan los puertos A y J
// pines J0, J1, A4, A5

#include <TM4C129.h>
#include <inttypes.h>
#include "Serial.h"
#include <stdio.h>
/*----------------------------------------------------------------------------
  initialize Push Button Pins (PJ0, PJ1)
 *----------------------------------------------------------------------------*/
void BTN_Initialize (void) {

  SYSCTL->RCGCGPIO |= (1ul << 8) | (1UL << 0);                /* enable clock for GPIOs    */
  GPIOJ_AHB->DR2R |=  ((1ul << 0) | (1ul << 1)); /* PJ0, PJ1 2-mA Drive       */
  GPIOJ_AHB->PUR  |=  ((1ul << 0) | (1ul << 1)); /* PJ0, PJ1 pull-down          */
  GPIOJ_AHB->DIR  &= ~((1ul << 0) | (1ul << 1)); /* PJ0, PJ1 is intput        */
  GPIOJ_AHB->DEN  |=  ((1ul << 0) | (1ul << 1)); /* PJ0, PJ1 is digital func. */
	GPIOA_AHB->DR2R |=  ((1ul << 4) | (1ul << 5)); 
 
  GPIOA_AHB->PDR  |=  ((1ul << 4) | (1ul << 5)); 
	GPIOJ_AHB->DR2R |=  ((1ul << 4) | (1ul << 5)); /* PJ0, PJ1 2-mA Drive       */
  GPIOA_AHB->DIR  &=  ~((1ul << 4) | (1ul << 5)); 
  GPIOA_AHB->DEN  |= ((1ul << 4) | (1ul << 5)); 
}


/*----------------------------------------------------------------------------
  Get Push Button status
 *----------------------------------------------------------------------------*/
uint32_t BTN_Get (void) {
	uint32_t pressed = 0;
	pressed|=~(GPIOJ_AHB->DATA)& (1ul << 0);
	pressed|=~(GPIOJ_AHB->DATA)& (1ul << 1);
	pressed|=(((GPIOA_AHB->DATA)& (1ul << 4))>>(2));
	pressed|=(((GPIOA_AHB->DATA)& (1ul << 5))>>(2));
	return pressed;
}
