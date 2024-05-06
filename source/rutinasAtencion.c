/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"
#include "juego.h"

int ESTADO; // Para controlar el estado del autómata en que esté
int seg3;   // Para ver si pasan tres segundos

void RutAtencionTeclado ()
{
	if (ESTADO == JUEGO) {
		printf("jejeje");
		if (TeclaPulsada()==START) {
			printf("UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUF");
			ESTADO = MENU;
			PararTempo();
			InhibirIntTempo();
		}
	}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	if (ESTADO==JUEGO)
	{
		tick++;
		iprintf("\x1b[2;3H%d", tick);	

		//printf("\x1b[6;3HTEMP_PRESUM: %f", &temp);
		// Si estamos en una nueva ronda, actualizamos el funcionamiento del tiempo
		if (!teclaAPulsarSeleccionada) {
			temp = 0;
			tiempo = tiempo * 0.95;

		}
		else {
			temp=temp+0.005;
		}
		//printf("\x1b[8;3HTEMP_POSTSUM: %f", &temp);	


		// if (temp>=tiempo && !(TeclaDetectada() && (TeclaPulsada()==teclaAPulsar))){
		// 	ESTADO=MENU;
		// 	PararTempo();
		// 	InhibirIntTempo();
		// 	temp = 0;
		// 	tiempo =tiempo * 0.95;
		// }
		
	}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS,RutAtencionTeclado);
	irqSet(IRQ_TIMER0,RutAtencionTempo);
}