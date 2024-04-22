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
	if(ESTADO == JUEGO && TeclaPulsada == START){

			ESTADO=PAUSA;
			PararTempo();
	if(ESTADO == PAUSA && TeclaPulsada == START){

			ESTADO=JUEGO;
			PonerEnMarchaTempo();
	}
//if (ESTADO == CERRADA)
//{	
//	if (TeclaPulsada()==A)
//	{
//		ESTADO=ABIERTA;
//		visualizarPuertaAbierta();
//		seg3=0;
//		MostrarRombo(1, 5, 5);
//		MostrarRomboGrande(2, 100, 100);
//	}
//}

	}}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	

if (ESTADO==JUEGO)
{
	temp=temp+0.05; 
	if (temp==tiempo && !(TeclaPulsada()==teclaAPulsar)){
		ESTADO=FIN;
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