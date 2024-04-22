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

// VARIABLES PRINCIPALES
double velocidad;
bool pulsado;
int puntuacion = 0;
double tiempo = 3;
double temp = 0;
int teclaAPulsar;
bool encontrado;
bool teclaAPulsarSeleccionada;

touchPosition pos_pantalla;

int teclaAlAzar();

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
	visualizarPantallaJugar();

			iprintf("\x1b[10;3HValor horizontal de pos_pantalla: %d", pos_pantalla.px);						
			iprintf("\x1b[14;3HValor vertical de pos_pantalla: %d", pos_pantalla.py);						

	touchRead(&pos_pantalla); // Primera lectura de la pantalla para establecer valores iniciales

	while(1)
	{	
		if (ESTADO==MENU) 
		{	
			// Encuestamos a la pantalla: No nos interesa abandonar esta encuesta hasta que se presione el botón.
			touchRead(&pos_pantalla); // lectura de la posición

			// Revisamos por encuesta que no se haya presionado el área del botón
 			while(!((55<=pos_pantalla.px && pos_pantalla.px<=205)) || !(99<=pos_pantalla.py && pos_pantalla.py<=161)) { // encuesta
				touchRead(&pos_pantalla); // lectura de la posición
				iprintf("\x1b[10;3HValor horizontal de pos_pantalla: %d", pos_pantalla.px);						
				iprintf("\x1b[14;3HValor vertical de pos_pantalla: %d", pos_pantalla.py);						
			}

			// Una vez se ha pulsado, nos mantenemos en este estado hasta que deje de pulsarse
			visualizarPantallaJugarPulsada();
			touchRead(&pos_pantalla);

 			while(((pos_pantalla.px!=0 && pos_pantalla.py!=0))) {
				touchRead(&pos_pantalla);
			}
			iprintf("\x1b[22;5HPASAMOS AL ESTADO JUEGO POR LOS VALORES %d y %d", pos_pantalla.px, pos_pantalla.py);						

			ESTADO=JUEGO;
			PonerEnMarchaTempo();
		}
		if (ESTADO==JUEGO)
		{
			encontrado = false;
			teclaAPulsarSeleccionada = false;
			visualizarFondoDos();
			if (teclaAPulsarSeleccionada== false){
				int teclaAPulsar= teclaAlAzar();
	
			teclaAPulsarSeleccionada=true;
			}	

			if(!(TeclaPulsada()==teclaAPulsar)){
				ESTADO=FIN;
			}

		}
		if (ESTADO==FIN){
			while (true) {

			}
			ESTADO=MENU;
		}
	}
	// Valorar si hay que inhibir las interrupciones
}

// Elige un valor al azar del 0 al 7
int teclaAlAzar() {
	int valorAzar = rand() % 8;
			switch (valorAzar){
				case 0:
					return A;
					break;
				case 1:
					return B;
					break;
				case 2:
					return DERECHA;
					break;
				case 3:
					return IZQUIERDA;
					break;
				case 4:
					return ARRIBA;
					break;
				case 5:
					return ABAJO;
					break;
				case 6:
					return R;
					break;
				case 7:
					return L;	
					break;
				default:
					break;
			}
}
