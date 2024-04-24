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
	// En esta función vamos a tratar las posibilidades de presionar la tecla correcta o la tecla incorrecta en el ciclo de juego
	if(ESTADO == JUEGO && TeclaPulsada() == START){
			ESTADO=PAUSA;
			PararTempo();
	}
	else if (ESTADO==JUEGO && TeclaPulsada()==teclaAPulsar) {
		printf("VICTORIA");
	}
	else if (ESTADO == JUEGO && TeclaPulsada()!=teclaAPulsar) {
			ESTADO=MENU;
	}

	if(ESTADO == PAUSA && TeclaPulsada == START){

			ESTADO=JUEGO;
			PonerEnMarchaTempo();
	}

	}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	if (ESTADO==JUEGO)
	{
		printf("\x1b[6;3HTEMP_PRESUM: %f", &temp);	
		temp=temp+0.005;
		printf("\x1b[8;3HTEMP_POSTSUM: %f", &temp);	

		if (temp>=tiempo && !(TeclaDetectada() && (TeclaPulsada()==teclaAPulsar))){
			ESTADO=MENU;
		printf("\x1b[8;3HjejejejejeTEMP_POSTSUM: %f", &temp);	
			PararTempo();
			temp = 0;
			tiempo =tiempo * 0.95;
		}
		
	}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS,RutAtencionTeclado);
	irqSet(IRQ_TIMER0,RutAtencionTempo);
}