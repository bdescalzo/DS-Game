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
int save;	// Para guardar el temporizador;

void RutAtencionTeclado ()
{
	if (ESTADO == JUEGO || ESTADO == PAUSA) {
		printf("jejeje");
		if (TeclaPulsada() == SELECT) {
			printf("UUUUF");
			ESTADO = MENU;
			PararTempo();
			InhibirIntTempo();
		}
		if (ESTADO == JUEGO && TeclaPulsada() == START) {
			ESTADO = PAUSA;
			PararTempo();
		}
		if (ESTADO == PAUSA && TeclaPulsada() == START){
			ESTADO = JUEGO;
			PonerEnMarchaTempo();
		}
	}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	if (ESTADO==JUEGO)
	{	
		temp=temp+0.05;
		if (temp>=tiempo){
			ESTADO=MENU;
			inhibirIntTempo();
			inhibirIntTeclado();
			temp=0;
			pararTempo();
		}
	}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS,RutAtencionTeclado);
	irqSet(IRQ_TIMER0,RutAtencionTempo);
}