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
int teclaAPulsar; // Almacena la tecla que se debe pulsar en cada ronda
int teclaInputteada; // Cuando en una ronda se recibe un input válido, se almacena en esta variable
bool teclaAPulsarSeleccionada; // Booleano que vale TRUE si en una ronda ya se ha escogido al azar una nueva tecla
int globo = 0; // Valor para el movimiento del globo, en 3 posiciones diferentes
// Coordenadas para imprimir los sprites de las teclas a pulsar
int x = 105;
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

			// Realizamos una encuesta a la pantalla hasta que se presione el área del botón para jugar
 			while(!((55<=pos_pantalla.px && pos_pantalla.px<=205)) || !(99<=pos_pantalla.py && pos_pantalla.py<=161)) {
				touchRead(&pos_pantalla);
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
			}

			// Perdemos si ha pasado el tiempo sin presionar el botón
			if (temp >= tiempo) {
				visualizarPresionaBotonIncorrecto();
                dormir();
				perder();
            }

			// Si se detecta el primer input de la ronda (es decir, teclaInputteada=-1), se revisa si es la opción correcta
			if (TeclaDetectada() && temp < tiempo && teclaInputteada==-1) {
				teclaInputteada = TeclaPulsada();

				// Si la tecla pulsada es START o SELECT, debemos ignorarla
				if (teclaInputteada != START && teclaInputteada != SELECT) {
					// En función de si se ha pulsado la tecla correcta, se pasa a la siguiente ronda o se pierde el juego
					if (teclaInputteada != teclaAPulsar) {
                        visualizarPresionaBotonIncorrecto();
                        dormir();
						perder();
					}
					else {
                        visualizarPresionaBotonCorrecto();
                        dormir();
						siguienteRonda();
					}
				}
				// Si se han detectado START o SELECT, consideramos que no se ha inputteado nada de cara al bucle de juego
				else {
					teclaInputteada = -1;
				}
			}
		

		}

		if (ESTADO==FIN){
			// En el estado FIN, estamos a la espera de los inputs de START o SELECT. Por tanto, para evitar un if vacío, imprimimos un carácter vacío: si no, el juego no funciona correctamente.
			iprintf("\x1b[20;4 ");
		}
	}
}

// Ejecuta las funciones correspondientes a finalizar una partida
void perder() {
	// Se ejecuta un cooldown antes de pasar al estado de FIN
	dormir();
	ESTADO = FIN;
	// Se limpia la pantalla, eliminando tanto texto como sprites.
	consoleClear();
	ocultarSpritesTeclas();
	visualizarEstateFin();
	// Se detienen las interrupciones de temporizador hasta la siguiente ronda
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

// Dado un valor de tecla, devuelve el nombre de la tecla en un string (función con fines de debugging)
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
	teclaAPulsarSeleccionada = false;
	tiempo = tiempo * 0.95; // Reducimos el tiempo
}

// Selecciona la siguiente tecla aleatoria para el juego, y la imprime en pantalla
void seleccionarTecla() {
	teclaInputteada = -1;
	teclaAPulsar = teclaAlAzar();
	char* nombreNuevaTecla = nombreTecla(teclaAPulsar);
	consoleClear();
	teclaAPulsarSeleccionada = true;
}

// Imprime las instrucciones de juego en la pantalla
void imprimirInstruccionesPantalla() {
		consoleClear();
		iprintf("\x1b[2;3HINSTRUCCIONES DE JUEGO");
		iprintf("\x1b[6;0HPresiona las teclas que se te ");
        iprintf("\x1b[8;0Hindiquen, pero hazlo a tiempo!");
		iprintf("\x1b[10;0HSi te equivocas de tecla, o");
        iprintf("\x1b[12;0Hpasa el tiempo y no");
        iprintf("\x1b[14;0has acertado, perderas.");
		iprintf("\x1b[16;0HCada tecla te dara un punto, pero...");
		iprintf("\x1b[18;0HCuidado, entre rondas el tiempo se disminuye!");
}

// Hace un "cooldown" de unos instantes entre ronda y ronda, gracias al que se puede ver si se ha acertado o fallado con la tecla pulsada
void dormir() {
    int tiempoDormido = 2;
    temp = 0;
    while (temp <= tiempoDormido) {
		printf(" ");
    }
    temp = 0;
}

// Toma la tecla a pulsar en el momento de la llamada, y muestra su correspondiente sprite en pantalla.
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

// Oculta los sprites de todas las teclas.
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