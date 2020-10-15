#include <TM4C129.h>
#include <stdio.h>
#include "CLOCK_HANDLER.h"
volatile uint16_t segundos;
volatile uint16_t minutos;
volatile uint16_t horas;
void incrementarHora(){
	horas++;
	if(horas==24){
		horas = 0;
	}
}
void incrementarMinuto(){
	minutos++;
	if (minutos == 60){
		minutos=0;
		incrementarHora();
	}
}
void incrementarSegundo(){
	segundos++;
	if (segundos == 60){
		segundos=0;
		incrementarMinuto();
	}
}

