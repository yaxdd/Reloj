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
	int i=0;
	uint32_t cycle =0;
  SER_Initialize();
  LED_Initialize();
  //BTN_Initialize();
	//inicializamos el manejador de systick en 1 ms
  initSysTick1ms();
	// corremos pruebas del tiempo n veces para medir el rendimiento de cada ciclo
	// los tiempos seran mostrados por medio del puerto serial
	//MultipleTest(2);
	//primer segundo del sistema
	while(cycle<4){
		initCycle();
		waitEndCycle();
		cycle++;
		//actualizar 
	}
	// ahora evaluamos de forma normal
	while(1){
		initCycle();
		LED_Toggle(0);
		if (cycle %4 == 0){
			incrementarSegundo();
		}
		waitEndCycle();
		cycle++;
		//actualizar 
	}

}
