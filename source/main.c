/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto

#include "graficos.h"		
#include "definiciones.h"
#include "sprites.h"
#include "juego.h"


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	inicializarGraficosSprites();
	HabilitarInterrupciones();
	ConfigurarTemporizador(37942,1);
	ConfigurarTeclado(0x0C);
	// Llamada al juego que vosotros programaréis
	juego();

	return(0);

}
