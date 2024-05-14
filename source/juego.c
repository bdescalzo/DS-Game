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
#include "sprites.h"

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
int x = 100;
int y = 100;

touchPosition pos_pantalla;


// DECLARACIÓN DE FUNCIONES
int teclaAlAzar();
char* nombreTecla();
void inicializarValores();
void siguienteRonda();
void imprimirInstruccionesPantalla();
void dormir();
void mostrarSpriteTecla();
void perder();

void juego()
{	
	// Definiciones de variables
	//int i=9;
	//int tecla=0;

	ESTADO=MENU;

	touchRead(&pos_pantalla); // Primera lectura de la pantalla para establecer valores iniciales

	// BUCLE PRINCIPAL DE JUEGO: Controla la máquina de estados
	while(1)
	{	
		if (ESTADO==MENU) 
		{	
			visualizarPantallaJugar();

			imprimirInstruccionesPantalla();
			// SECCION: Botón de jugar.

			// La pantalla MENÚ incluye un solo botón, el de jugar. Se encuentra entre los píxeles (55, 205) y (99, 161), por lo que encuestamos a la pantalla continuamente hasta que se presione dicho botón.
			touchRead(&pos_pantalla);

			// Revisamos por encuesta que no se haya presionado el área del botón
 			while(!((55<=pos_pantalla.px && pos_pantalla.px<=205)) || !(99<=pos_pantalla.py && pos_pantalla.py<=161)) { // encuesta
				touchRead(&pos_pantalla); // lectura de la posición
			}
			// Una vez pulsado el botón, cambiamos al fondo de botón presionado, que se va a mantener mientras el lápiz esté en la pantalla.
			visualizarPantallaJugarPulsada();
			touchRead(&pos_pantalla);

			// Nos mantenemos en este estado hasta que el lápiz deje de presionar la pantalla.
 			while(((pos_pantalla.px!=0 && pos_pantalla.py!=0))) {
				touchRead(&pos_pantalla);
			}

			// Habilitamos el temporizador para el juego, establecemos los valores iniciales de partida y comenzamos.
			HabilitarIntTeclado();
			HabilitarIntTempo();
			PonerEnMarchaTempo();
			inicializarValores();
			ESTADO=JUEGO;
			
		}
		if (ESTADO==JUEGO)
		{
			visualizarPresionaBotonSinPulsar();

			if (!teclaAPulsarSeleccionada) { // Si estamos en una nueva ronda en la que aún no hay elección de nueva tecla, se hace la elección.
				ocultarSpritesTeclas();
                seleccionarTecla();
				mostrarSpriteTecla();
				printf("CAE NUEVA: %s", nombreTecla(teclaAPulsar));
			}

			// Perdemos si ha pasado el tiempo sin presionar el botón
			if (temp >= tiempo && !encontrado) {
				printf("Hemos perdido por no encontrar la tecla fuera de tiempo");
				visualizarPresionaBotonIncorrecto();
                dormir();
				perder();
            }

			// TODO: Migrar (parte de) este bloque, si es posible / aporta ventajas, a la rutina de atención de tiempo.
			// Si se detecta el primer input de la ronda (es decir, teclaInputteada=-1), se revisa si es la opción correcta
			if (TeclaDetectada() && temp < tiempo && teclaInputteada==-1) {
				teclaInputteada = TeclaPulsada();

				// Si la tecla pulsada es START o SELECT, debemos ignorarla
				if (teclaInputteada != START && teclaInputteada != SELECT) {
					printf("SE ESPERABA LA TECLA %d\n", teclaAPulsar);
					printf("SE HA RECIBIDO LA TECLA %d\n", teclaInputteada);

					// En función de si se ha pulsado la tecla correcta, se pasa a la siguiente ronda o se pierde el juego
					if (teclaInputteada != teclaAPulsar) {
                        visualizarPresionaBotonIncorrecto();
                        dormir();
						//consoleClear();
						//printf("SE ESPERABA LA TECLA %d", teclaAPulsar);
						//printf("SE HA RECIBIDO LA TECLA %d", teclaInputteada);
						perder();

                        //InhibirIntTeclado();
						InhibirIntTempo();
						PararTempo();
					}
					else {
                        visualizarPresionaBotonCorrecto();
                        dormir();
						printf("Se ha encontrado la tecla a tiempo.");
						siguienteRonda();
					}
				}
				else {
					teclaInputteada = -1;
				}
			}
		

		}

		if (ESTADO==FIN){
			iprintf("\x1b[20;4 ");
		}
	}
}

// Ejecuta las funciones correspondientes a finalizar una partida
void perder() {
	dormir();
	ESTADO = FIN;
	consoleClear();
	ocultarSpritesTeclas();
	printf("PUNTUACION: %d", puntuacion);
	visualizarEstateFin();
	consoleClear();
	PararTempo();
	InhibirIntTempo();
	iprintf("PUNTUACION: %d", puntuacion);
}
// Devuelve una tecla al azar (entre: A, B, Arriba, Abajo, Izquierda, Derecha, L, R)
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

// Restablece los valores de la partida a su estado inicial, para comenzar un nuevo juego.
void inicializarValores() {
	velocidad = 1;
	encontrado = false;
	puntuacion = 0;
	tiempo = 3.0;
	temp = 0.0;
	teclaAPulsarSeleccionada = false;
}

// Actualiza los valores del juego, tras una ronda satisfactoria
void siguienteRonda() {
	puntuacion++;

	// Permitimos un timeout a la lectura de teclas: si no, la siguiente ronda podría tomar erroneamente el input de la ronda actual
	while (TeclaDetectada()) {
		;
	}
	printf("Puntuacion: %d", puntuacion);

	// Actualizamos todos los valores de control
	temp = 0;
	teclaInputteada = -1;
	encontrado = false;
	teclaAPulsarSeleccionada = false;
	tiempo = tiempo * 0.95; // Reducimos el tiempo
}

// Selecciona la siguiente tecla aleatoria para el juego, y la imprime en pantalla
void seleccionarTecla() {
	teclaInputteada = -1;
	teclaAPulsar = teclaAlAzar();
	char* nombreNuevaTecla = nombreTecla(teclaAPulsar);
	consoleClear();
	iprintf("\x1b[22;5HTECLA NUEVA: %s, de valor %d\n", nombreNuevaTecla, teclaAPulsar);
	teclaAPulsarSeleccionada = true;
}

// Imprime las instrucciones de juego en la pantalla
void imprimirInstruccionesPantalla() {
		consoleClear();
		iprintf("\x1b[2;3HINSTRUCCIONES DE JUEGO");
		iprintf("\x1b[6;0HPresiona las teclas que se te, ");
        iprintf("\x1b[8;0Hindiquen, pero hazlo a tiempo!");
		iprintf("\x1b[10;0HSi te equivocas de tecla, o");
        iprintf("\x1b[12;0Hpasa el tiempo y no");
        iprintf("\x1b[14;0has acertado, perderas.");
		iprintf("\x1b[16;0HCada tecla te dara un punto, pero...");
		iprintf("\x1b[18;0HCuidado, entre rondas el tiempo se disminuye!");
}

void dormir() {
    int tiempoDormido = 2;
    temp = 0;
    while (temp <= tiempoDormido) {
		printf("%f\n\n", temp);
    }
    temp = 0;
}

void mostrarSpriteTecla() {
	switch (teclaAPulsar) {
        case A:
            MostrarA(0, x, y);
            break;
        case B:
            MostrarB(1, x, y);
            break;
        case ARRIBA:
            MostrarArriba(2, x, y);
            break;
        case ABAJO:
            MostrarAbajo(3, x, y);
            break;
        case IZQUIERDA:
            MostrarIzda(4, x, y);
            break;
        case DERECHA:
            MostrarDcha(5, x, y);
            break;
        case L:
            MostrarL(6, x, y);
            break;
        case R:
            MostrarR(7, x, y);
            break;
    }
}

void ocultarSpritesTeclas() {
    BorrarA(0, x, y);
    BorrarB(1, x, y);
    BorrarArriba(2, x, y);
    BorrarAbajo(3, x, y);
    BorrarIzda(4, x, y);
    BorrarDcha(5, x, y);
    BorrarL(6, x, y);
    BorrarR(7, x, y);
}