#include <stdio.h>
#include "TM4C129.h"                    // Device header
#include "Serial.h"
#include "LED.h"
#include "BTN.h"
#include "SYSTICK.h"
#include "CLOCK_HANDLER.h"
#include <inttypes.h>
#define MAX_TEST 3


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	int btn_prog = 0;
	int debounceSelector = 0;
	uint16_t selector = 0;
	uint32_t btns = 0;
	uint32_t cycle =0;
  SER_Initialize();
  LED_Initialize();
	//ENABLE_PORTA();
  BTN_Initialize();
	//inicializamos el manejador de systick en 1 ms
  initSysTick1ms();
	// corremos pruebas del tiempo n veces para medir el rendimiento de cada ciclo
	// los tiempos seran mostrados por medio del puerto serial
	//MultipleTest(2);
	// ahora evaluamos de forma normal
	initCycle();
	waitEndCycle();
	while(1){
		initCycle();
		cycle++;
		LED_Toggle(1); // parpadea cada ciclo scan
		if (exceeded_dead_time==1){
			LED_On(0); // se enciende si algun ciclo scan excede los 250 ms
		}
		btns = BTN_Get();
		if (btns==1){
			btn_prog++;
			if (btn_prog==2){
				btn_prog=0;
				LED_On(3);
				// salimos del ciclo scan
				
				while(1){
					initCycle();
					btns = BTN_Get();
					//Quiero salir del modo de programacion?
					if (btns==1){
						btn_prog--;
						// estoy completamente seguro
						if (btn_prog==0){
							break;
						}
					}else{
						// me equivoqué
						btn_prog=2;
					}
					if (btns==2){
						
						if (debounceSelector++==1){
							selector++;
							debounceSelector=0;
						}
						// btns % 3 nos da el selector deseado
					}else{
						debounceSelector=0;
					}
					if (btns==3){
						programarReloj(selector%3,0);
					}
					// cambiar hora del usuario
					waitEndCycle();
				}
				//Volvemos a entrar al ciclo scan, pero reiniciamos
				LED_Off(3);
				cycle=1;
				initCycle();
				waitEndCycle();
			}
		}else{
			btn_prog=0;
		}
		if (cycle %4 == 0){
			incrementarSegundo();
		}
		waitEndCycle();
		
		//actualizar 
	}

}
