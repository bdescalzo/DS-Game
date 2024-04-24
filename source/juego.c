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
char* nombreTecla();

void juego()
{	
	// Definiciones de variables
	int i=9;
	int tecla=0;

	ESTADO=MENU;
	
	// Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HProbando la pantalla de texto");						

	touchRead(&pos_pantalla); // Primera lectura de la pantalla para establecer valores iniciales

	while(1)
	{	
		if (ESTADO==MENU) 
		{	
			visualizarPantallaJugar();

			// La pantalla MENÚ incluye un solo botón, el de jugar. Se encuentra entre los píxeles (55, 205) y (99, 161), por lo que encuestamos a la pantalla continuamente hasta que se presione dicho botón.
			touchRead(&pos_pantalla);
			// Revisamos por encuesta que no se haya presionado el área del botón
 			while(!((55<=pos_pantalla.px && pos_pantalla.px<=205)) || !(99<=pos_pantalla.py && pos_pantalla.py<=161)) { // encuesta
				touchRead(&pos_pantalla); // lectura de la posición
			}


			// Una vez pulsado el botón, cambiamos al fondo de botón presionado, que se va a mantener mientras el lápiz esté en la pantalla.
			visualizarPantallaJugarPulsada();
			touchRead(&pos_pantalla);

 			while(((pos_pantalla.px!=0 && pos_pantalla.py!=0))) {
				touchRead(&pos_pantalla);
			}

			// Habilitamos el temporizador para el juego y comenzamos.
			HabilitarIntTempo();
			PonerEnMarchaTempo();
			ESTADO=JUEGO;
		}
		if (ESTADO==JUEGO)
		{
			encontrado = false;
			visualizarFondoDos();
			// Si aún no se ha elegido una tecla (que será el caso al comenzar cada ronda) cogemos una al azar, y la dejamos fija. De ahí en adelante, el estado se trata en rutinasAtencion.
			if (teclaAPulsarSeleccionada== false){
				teclaAPulsar= teclaAlAzar();
				printf("NUEVA TECLA ELEGIDA: %d", &teclaAPulsar);
				teclaAPulsarSeleccionada=true;
			}	

			printf("%s", nombreTecla(teclaAPulsar));
		}

		if (ESTADO==FIN){
			ESTADO=MENU;
		}
	}
	// Valorar si hay que inhibir las interrupciones
}

// Elige un valor al azar del 0 al 7, y devuelve la tecla correspondiente entre las posibilidades para el juego
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

// Dado un valor de tecla, devuelve el nombre de la tecla en un string
char* nombreTecla(int tecla) {
	switch(tecla) {
		case A:
			return "A";
			break;
		case B:
			return "B";
			break;
		case DERECHA:
			return "Derecha";
			break;
		case IZQUIERDA:
			return "Izquierda";
			break;
		case ARRIBA:
			return "Arriba";
			break;
		case ABAJO:
			return "Abajo";
			break;
		case R:
			return "R";
			break;
		case L:
			return "L";
			break;
		default:
			break;
	}
};
