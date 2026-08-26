#include "Juego.h"
#include "Jugador.h"
#include "Territorio.h"
#include <iostream>
#include <fstream>

using namespace std;

Juego::Juego() {

    juegoInicializado = false; //Conecta con el TAD asi sabemos que el juego no se ha iniciado 
    jugadorActual = nullptr;
}

void Juego::InicializarJuego(const string& archivo) {

    if (juegoInicializado) {
        cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
        return;
    }

    ifstream archivoEntrada(archivo);

    if (!archivoEntrada.is_open()) {
        cerr << "Error: No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    if (archivoEntrada.peek() == ifstream::traits_type::eof()) { //Revisamos que si tenga info el archivo
        cout << "(Archivo vacío) " << archivo << " no contiene información." << endl;
        return;
    }

    int cantidadJugadores;

    if (!(archivoEntrada >> cantidadJugadores)) {
        cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
        return;
    }

    int unidadesPermitidas = 0; //Nos va a servir para cumplir la condicion de saber cuantas unidades puede tener un jugador

    if (cantidadJugadores == 3) {
        unidadesPermitidas = 35;
    }
    else if (cantidadJugadores == 4) {
        unidadesPermitidas = 30;
    }
    else if (cantidadJugadores == 5) {
        unidadesPermitidas = 25;
    }
    else if (cantidadJugadores == 6) {
        unidadesPermitidas = 20;
    }
    else {
        cout << "(Cantidad de jugadores inválida) El juego solo puede ser jugado por 3, 4, 5 o 6 jugadores." << endl;
        return;
    }

    for (int i = 0; i < cantidadJugadores; i++) {

        string nombreJugador;
        string colorJugador;

        if (!(archivoEntrada >> nombreJugador >> colorJugador)) { //Condicion para saber si no hay nada de info
            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        Jugador* jugador = new Jugador(nombreJugador, colorJugador);
        jugadores.push_back(jugador); // Se agrega el jugador a la lista de los jugadores de juego

    }

    string codigoTerritorio;
    string color;
    int unidades;
    int conteoTerritorios =0;

    while (archivoEntrada >> codigoTerritorio >> color >> unidades) { //Va a leer toda la info

        conteoTerritorios++; //Va a contar la cantidad de territorios que hay en el archivo
        Jugador* dueño = nullptr; // Hay que declararlo dentro para que no se quede con la direccion del jugador anterior

        for (Jugador* jugador : jugadores) {
            if (jugador->ObtenerColor() == color) { //Va a asociar el color del jugador con el color de ese territorio para saber quien es el dueño
                dueño = jugador;
                dueño->AgregarEjercito(unidades); //Revisamos que si haya un control
                break;
            }
        }

        if (dueño == nullptr) {

            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        string continente; // Comparacion para asignar el continente al territorio segun su codigo

        if ( codigoTerritorio[0] == '1' ){ 

            continente = "America del Norte";

        }
        else if (codigoTerritorio[0] == '2'){

            continente = "America del Sur";

        }
        else if (codigoTerritorio[0] == '3'){

            continente = "Europa";

        }
        else if (codigoTerritorio[0] == '4'){

            continente = "Africa";

        }
        else if (codigoTerritorio[0] == '5'){

            continente = "Asia";

        }
        else if (codigoTerritorio[0] == '6'){

            continente = "Australia";

        }

        Territorio* territorio = new Territorio("Territorio" + codigoTerritorio, codigoTerritorio, continente, dueño, unidades);
        territorios.push_back(territorio); // Se agrega el territorio a la lista de territorios de juego
        if (dueño != nullptr) {
            dueño->AgregarTerritorio(territorio); // Se agrega el territorio a la lista de territorios del jugador dueño
        }
    }

    if (conteoTerritorios != 42) { //Revisamos que sean solo los 42 territorios
        cout << "(Cantidad de territorios inválida) El juego debe contener exactamente 42 territorios." << endl;
        return;
    }

    for (Jugador* jugador : jugadores) {

        if (jugador->ObtenerEjercito() != unidadesPermitidas) {

            cout << "(Cantidad de unidades invalida) El jugador " << jugador->ObtenerNombre() << " tiene una cantidad de unidades diferente a la permitida." << endl;
            return;
        }
    }

    juegoInicializado = true; //Si todo esta bien, el juego se inicializa
    jugadorActual = jugadores.front(); //El primer jugador de la lista va a ser el que tenga el turno inicial
    cout << "(Juego inicializado) El juego ha sido inicializado correctamente." << endl;

}

