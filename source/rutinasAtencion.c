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
	if (ESTADO != FIN) {
		if (TeclaPulsada() == SELECT && ESTADO != ESPERA) {
			ocultarSpritesTeclas();
			ESTADO = MENU;
		}
		if (ESTADO == JUEGO && TeclaPulsada() == START) {
			consoleClear();
			printf("JUEGO PAUSADO: PULSA \nSTART PARA CONTINUAR");
			while (TeclaDetectada()) {
				;
			}
			ESTADO = PAUSA;
			PararTempo();
			InhibirIntTempo();
		}
		if (ESTADO == PAUSA && TeclaPulsada() == START){
			consoleClear();
			while (TeclaDetectada()) {
				;
			}
			ESTADO = JUEGO;
			PonerEnMarchaTempo();
			HabilitarIntTempo();
		}
	}

	if (ESTADO == FIN) {
		if (TeclaPulsada() == START) {
			ESTADO = JUEGO;
			PonerEnMarchaTempo();
			HabilitarIntTempo();
			inicializarValores();
		}

		if (TeclaPulsada() == SELECT) {
			ESTADO = MENU;
		}

	}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	if (ESTADO==JUEGO || ESTADO==ESPERA)
	{
		tick++;
		temp=temp+0.005;
	}		
}	


void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS,RutAtencionTeclado);
	irqSet(IRQ_TIMER0,RutAtencionTempo);
}