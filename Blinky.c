/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
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

#include <stdio.h>
#include "TM4C129.h"                    // Device header
#include "Serial.h"
#include "LED.h"
#include "BTN.h"
#include "SYSTICK.h"




/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
    SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */

  SER_Initialize();
  LED_Initialize();
  //BTN_Initialize();
  SysTick_Config(SystemCoreClock / 1000ul);     /* Setup SysTick for 1 msec   */
	test_time();
	while(1){
		delay(1000);
		LED_Toggle(0);
		delay(1000);
		LED_Toggle(0);
	}
 

}
