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
int teclaInputteada;
bool encontrado;
bool teclaAPulsarSeleccionada;

touchPosition pos_pantalla;

int teclaAlAzar();
char* nombreTecla();
void inicializarValores();
void siguienteRonda();

void juego()
{	
	// Definiciones de variables
	int i=9;
	int tecla=0;

	ESTADO=MENU;
	
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
			HabilitarIntTeclado();
			HabilitarIntTempo();
			PonerEnMarchaTempo();
			inicializarValores();
			ESTADO=JUEGO;

		}
		if (ESTADO==JUEGO)
		{
			// Inicializamos las variables del salto de estado
			visualizarFondoDos();
			// Si estamos en un ciclo de juego que ya ha comenzado
			if (teclaAPulsarSeleccionada) {
				// Perdemos si ha pasado el tiempo sin presionar el botón
				if (temp >= tiempo && !encontrado) {
					printf("Hemos perdido por no encontrar la tecla fuera de tiempo");
					ESTADO = MENU;
				}

				// Si se detecta el primer input de la ronda (es decir, teclaInputteada=-1), se almacena
				if (TeclaDetectada() && temp < tiempo && teclaInputteada==-1) {
					teclaInputteada = TeclaPulsada();

					// Si la tecla pulsada es START o SELECT, la ignoramos en el bucle de juego
					if (teclaInputteada != START && teclaInputteada != SELECT) {
						teclaAPulsarSeleccionada = false;
												printf("SE uwu ESPERABA LA TECLA %d", teclaAPulsar);
							printf("SE uwu HA RECIBIDO LA TECLA %d", teclaInputteada);

						// En función de si se ha pulsado la tecla correcta, se pasa a la siguiente ronda o se pierde el juego
						if (teclaInputteada != teclaAPulsar) {
							//consoleClear();
							//printf("SE ESPERABA LA TECLA %d", teclaAPulsar);
							//printf("SE HA RECIBIDO LA TECLA %d", teclaInputteada);
							InhibirIntTeclado();
							InhibirIntTempo();
							PararTempo();
							ESTADO = MENU;
						}
						else {
							printf("Se ha encontrado la tecla a tiempo.");
							siguienteRonda();
						}
					}
					else {
						teclaInputteada = -1;
					}
				}
			}
			else if (!teclaAPulsarSeleccionada) {
				seleccionarTecla();
				printf("CAE NUEVA: %s", nombreTecla(teclaAPulsar));
			}


			//if (ESTADO==JUEGO) {
			//	teclaAPulsar= teclaAlAzar();
			//	printf("NUEVA TECLA ELEGIDA:%d", &teclaAPulsar);
			//	teclaAPulsarSeleccionada=true;
			//}	
		}

			//printf("%s", nombreTecla(teclaAPulsar));

		if (ESTADO==FIN){
			ESTADO=MENU;
		}
	}
}
// Elige una tecla al azar
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
			return "INCORRECTA";
			break;
	}
};

// Restablece los valores de la partida a su estado inicial
void inicializarValores() {
	velocidad = 1;
	encontrado = false;
	puntuacion = 0;
	tiempo = 3.0;
	temp = 0.0;
	teclaAPulsarSeleccionada = false;
}

// Actualiza los valores al saltar en una ronda satisfactoria
void siguienteRonda() {
	printf("AAAAAAAAAAAAAAAAAAPIOARJGOPERIGHOERIGNEORFIGKEORFIGKEORFGJIKEROFGIJEROFPIJGEORPDFJEGRPDJOGERPODFJ");
	puntuacion++;
	printf("Puntuacion: %d", puntuacion);
	teclaInputteada = -1;
	encontrado = false;
}

// Selecciona la siguiente tecla aleatoria para el juego, y la imprime en pantalla
void seleccionarTecla() {
	teclaInputteada = -1;
	teclaAPulsar = teclaAlAzar();
	char* nombreNuevaTecla = nombreTecla(teclaAPulsar);
	iprintf("\x1b[22;5HTECLA NUEVA: %s, de valor %d", nombreNuevaTecla, teclaAPulsar);
	teclaAPulsarSeleccionada = true;
}