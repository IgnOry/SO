#include <stdlib.h>
#include <stdio.h>

#define N_PARADAS 5 
#define EN_RUTA 0
#define EN_PARADA 1
#define MAX_USUARIOS 40
#define USUARIOS 4

// estado inicial
int estado = EN_RUTA;
int parada_actual = 0; // parada en la que se encuentra el autobus
int n_ocupantes = 0; // ocupantes que tiene el autob�s

int esperando_parada[N_PARADAS]; //= {0,0,...0};

int esperando_bajar[N_PARADAS]; //= {0,0,...0};
// Otras definiciones globales (comunicaci�n y sincronizaci�n)

void Autobus_En_Parada() {
	/* Ajustar el estado y bloquear al autob�s hasta que no haya pasajeros que
	quieran bajar y/o subir la parada actual. Despu�s se pone en marcha */
}
void Conducir_Hasta_Siguiente_Parada() {
	/* Establecer un Retardo que simule el trayecto y actualizar numero de parada */
}
void Subir_Autobus(int id_usuario, int origen) {
	/* El usuario indicar� que quiere subir en la parada �origen�, esperar� a que
	el autob�s se pare en dicha parada y subir�. El id_usuario puede utilizarse para
	proporcionar informaci�n de depuraci�n */
}
void Bajar_Autobus(int id_usuario, int destino) {
	/* El usuario indicar� que quiere bajar en la parada �destino�, esperar� a que
	el autob�s se pare en dicha parada y bajar�. El id_usuario puede utilizarse para
	proporcionar informaci�n de depuraci�n */
}


void* thread_autobus(void* args) {
	while (/*condicion*/) {
		// esperar a que los viajeros suban y bajen
		Autobus_En_Parada();
		// conducir hasta siguiente parada
		Conducir_Hasta_Siguiente_Parada();
	}
}
void* thread_usuario(void* arg) {
	int id_usuario;
	// obtener el id del usario
	while (/*condicion*/) {
		a = rand() % N_PARADAS;
		do {
			b = rand() % N_PARADAS;
		} while (a == b);
		Usuario(id_usuario, a, b);
	}
}
void Usuario(int id_usuario, int origen, int destino) {
	// Esperar a que el autobus est� en parada origen para subir
	Subir_Autobus(id_usuario, origen);
	// Bajarme en estaci�n destino
	Bajar_Autobus(id_usuario, destino);
}

int main(int argc, char* argv[]) {
	int i;
	// Definici�n de variables locales a main
	// Opcional: obtener de los argumentos del programa la capacidad del
	// autobus, el numero de usuarios y el numero de paradas
	// Crear el thread Autobus
	for (i = 0; ...) {
		// Crear thread para el usuario i
		// Esperar terminaci�n de los hilos
		return 0;
	}
}