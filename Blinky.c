#include <stdio.h>
#include "TM4C129.h"                    // Device header
#include "Serial.h"
#include "LED.h"
#include "BTN.h"
#include "SYSTICK.h"
#include "CLOCK_HANDLER.h"
#include "LCD.h"
#include <inttypes.h>

#define MAX_TEST 3
void intToTimeString(uint32_t n, char *pt){
	char result[2];
	if (n<10){
		pt[0]='0';
		pt[1]=n+'0';
	}else{
		pt[0]=n/10+'0';
		pt[1] = n%10+'0';
	}
}
/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	int btn_prog = 0;
	int debounceSelector = 0;
	char timeTemp[2];
	
	uint16_t selector = 0;
	uint32_t btns = 0;
	uint32_t cycle =0;
  SER_Initialize();
  LED_Initialize();
  BTN_Initialize();
	initSysTick1ms();
	LCD_Init();
	LCD_Clear();
	LCD_OutString("12:00:00");
	// corremos pruebas del tiempo n veces para medir el rendimiento de cada ciclo
	// los tiempos seran mostrados por medio del puerto serial
	//MultipleTest(2);
	// ahora evaluamos de forma normal
	initCycle();
	waitEndCycle();
	//LCD_OutString("Test LCD");
	while(1){
		initCycle();
		if (++cycle %4 == 0){
			incrementarSegundo();
			//printf("Hora:%d Minutos:%d Segundos:%d\n",horas,minutos,segundos);
		}
		LCD_Clear();
			//LCD_OutUTime(textLCD,horas,0);
			intToTimeString(horas,timeTemp);
			textLCD[0]=timeTemp[0];
			textLCD[1]=timeTemp[1];
			textLCD[2]=':';
			intToTimeString(minutos,timeTemp);
			textLCD[3]=timeTemp[0];
			textLCD[4]=timeTemp[1];
			textLCD[5]=':';
			intToTimeString(segundos, timeTemp);
			textLCD[6]=timeTemp[0];
			textLCD[7]=timeTemp[1];
			LCD_OutString(textLCD); 
		LED_Toggle(1); // parpadea cada ciclo scan
		if (exceeded_dead_time==1){
			LED_On(0); // se enciende si algun ciclo scan excede los 250 ms
		}
		btns = BTN_Get();
		if (btns==1){
			btn_prog++;
			if (btn_prog==2){
				cycle=0;
				btn_prog=0;
				LED_On(3);
				// salimos del ciclo scan
				curTicks = msTicks;
				while(1){
					btns = BTN_Get();
					initCycle();
					if (cycle%4==2){
						LCD_Clear();
						//LCD_OutUTime(textLCD,horas,0);
						if (selector%3==0){
							textLCD[0]=' ';
							textLCD[1]=' ';	
						}
						textLCD[2]=':';
						if (selector%3==1){
							textLCD[3]=' ';
							textLCD[4]=' ';
						}
						textLCD[5]=':';
						if (selector%3==2){
							textLCD[6]=' ';
							textLCD[7]=' ';
						}
						LCD_OutString(textLCD);
					}else if (cycle%4==0){
						LCD_Clear();
						intToTimeString(horas,timeTemp);
						textLCD[0]=timeTemp[0];
						textLCD[1]=timeTemp[1];	
						textLCD[2]=':';
						intToTimeString(minutos,timeTemp);
						textLCD[3]=timeTemp[0];
						textLCD[4]=timeTemp[1];
						textLCD[5]=':';
						intToTimeString(segundos, timeTemp);
						textLCD[6]=timeTemp[0];
						textLCD[7]=timeTemp[1];
						LCD_OutString(textLCD);
					}
					cycle++;
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
							printf("Selecionando %d\n",selector);
						}
						// btns % 3 nos da el selector deseado
					}else{
						debounceSelector=0;
					}
					if (btns==4){
						programarReloj(selector%3,0);
						printf("Hora:%d Minutos:%d Segundos:%d\n",horas,minutos,segundos);
					}
					if (btns==8){
						programarReloj(selector%3,1);
						printf("Hora:%d Minutos:%d Segundos:%d\n",horas,minutos,segundos);
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
		waitEndCycle();
	}

}
