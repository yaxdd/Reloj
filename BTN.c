// 0 1 2 3 4 5 6 7
// 1 2 3 4 5 6 7 8
/*----------------------------------------------------------------------------
 * Name:    BTN.c
 * Purpose: low Level Push Button functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2014 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

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
