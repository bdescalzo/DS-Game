/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;
touchPosition pos_pantalla;
void juego()
{	
	// Definiciones de variables
	int i=9;
	int tecla=0;;

	ESTADO=MENU;
	
	// Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HProbando la pantalla de texto");						

/* Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas */
	iprintf("\x1b[23;5HProbando la escritura con variable. Valor=%d", i);
	visualizarFondoUno();


	while(1)
	{	
		if (ESTADO==MENU) 
		{	
			// Encuestamos a la pantalla: No nos interesa abandonar esta encuesta hasta que se presione el botón.
			// TODO: limitar la pulsación válida al área del botón.
			touchRead(&pos_pantalla); // lectura de la posición
 			while(pos_pantalla.px==0 && pos_pantalla.py==0) // encuesta
				touchRead(&pos_pantalla); // lectura de la posición
			ESTADO=JUEGO;
		}
		if (ESTADO==JUEGO)
		{
			visualizarFondoDos();
		}
	}
	// Valorar si hay que inhibir las interrupciones
}



