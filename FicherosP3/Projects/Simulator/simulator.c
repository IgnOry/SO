#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N_PARADAS 5 
#define EN_RUTA 0
#define EN_PARADA 1
#define MAX_USUARIOS 40
#define USUARIOS 4

// estado inicial
int estado = EN_RUTA;
int parada_actual = 0; // parada en la que se encuentra el autobus
int n_ocupantes = 0; // ocupantes que tiene el autobús

int esperando_parada[N_PARADAS]; //= {0,0,...0};

int esperando_bajar[N_PARADAS]; //= {0,0,...0};

pthread_t usuarios[USUARIOS];
pthread_t bus;
// Otras definiciones globales (comunicación y sincronización)

void Autobus_En_Parada() {
	/* Ajustar el estado y bloquear al autobús hasta que no haya pasajeros que
	quieran bajar y/o subir la parada actual. Después se pone en marcha */


	estado = EN_PARADA;

	while (esperando_parada[parada_actual] != 0 && esperando_bajar[parada_actual] != 0) {
		sleep(random() % 5);
	}

	estado = EN_RUTA;
}
void Conducir_Hasta_Siguiente_Parada() {
	/* Establecer un Retardo que simule el trayecto y actualizar numero de parada */
	parada_actual = (parada_actual == N_PARADAS - 1) ? 0 : parada_actual + 1;

	printf("Siguiente parada: %d\n", i);
	sleep(random() % 10);

	estado = EN_PARADA;
}
void Subir_Autobus(int id_usuario, int origen) {
	/* El usuario indicará que quiere subir en la parada ’origen’, esperará a que
	el autobús se pare en dicha parada y subirá. El id_usuario puede utilizarse para
	proporcionar información de depuración */

	esperando_parada[origen] += 1;

	//mutex lock?
	while (estado != EN_PARADA && parada_actual != origen) {
		//cond wait?
	}
	//mutex unlock?

	esperando_parada[origen] -= 1;
}
void Bajar_Autobus(int id_usuario, int destino) {
	/* El usuario indicará que quiere bajar en la parada ’destino’, esperará a que
	el autobús se pare en dicha parada y bajará. El id_usuario puede utilizarse para
	proporcionar información de depuración */
	esperando_bajar[destino] += 1;

	//mutex lock?
	while (estado != EN_PARADA && parada_actual != destino) {
		//cond wait?
	}
	//mutex unlock?

	esperando_bajar[destino] -= 1;
}


void* thread_autobus(void* args) {
	while (1) {
		// esperar a que los viajeros suban y bajen
		Autobus_En_Parada();

		// conducir hasta siguiente parada
		Conducir_Hasta_Siguiente_Parada();
	}
}
void* thread_usuario(void* arg) {
	int id_usuario = (int)arg;

	while (true) {
		a = rand() % N_PARADAS;
		do {
			b = rand() % N_PARADAS;
		} while (a == b);
		Usuario(id_usuario, a, b);
	}
}
void Usuario(int id_usuario, int origen, int destino) {
	// Esperar a que el autobus esté en parada origen para subir
	Subir_Autobus(id_usuario, origen);


	// Bajarme en estación destino
	Bajar_Autobus(id_usuario, destino);
}

int main(int argc, char* argv[]) {
	int i;
	// Definición de variables locales a main
	// Opcional: obtener de los argumentos del programa la capacidad del
	// autobus, el numero de usuarios y el numero de paradas

	// Crear el thread Autobus
	pthread_create(&bus, NULL, thread_autobus, NULL);


	for (i = 0; i < USUARIOS) {
		pthread_create(&usuarios[i], NULL, thread_usuario, (void*)i);
	}


	for (i = 0; i < USUARIOS) {
		pthread_join(usuarios[i], NULL);
	}

	return 0;
}