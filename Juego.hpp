#include "Juego.h"
#include "Jugador.h"
#include "Territorio.h"
#include <iostream>
#include <fstream>

using namespace std;

void Juego::InicializarJuego(const string& archivo) {

    ifstream archivoEntrada(archivo);

    if (!archivoEntrada.is_open()) {
        cerr << "Error: No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    int cantidadJugadores;
    archivoEntrada >> cantidadJugadores;

    for (int i = 0; i < cantidadJugadores; i++) {

        string nombreJugador;
        string colorJugador;
        archivoEntrada >> nombreJugador >> colorJugador;

        Jugador* jugador = new Jugador(nombreJugador, colorJugador);
        jugadores.push_back(jugador); // Se agrega el jugador a la lista de los jugadores de juego

    }

    float codigoTerritorio;
    string color;
    int unidades;
    Jugador* dueño = nullptr;

    while (archivoEntrada >> codigoTerritorio >> color >> unidades) { //Va a leer toda la info 

        for (Jugador* jugador : jugadores) {
            if (jugador->ObtenerColor() == color) { //Va a asociar el color del jugador con el color de ese territorio para saber quien es el dueño
                dueño = jugador;
                break;
            }
        }

        string continente;

        if (codigoTerritorio > 1 && codigoTerritorio < 2){

            continente = "America del Norte";

        }
        else if (codigoTerritorio > 2 && codigoTerritorio < 3){

            continente = "America del Sur";

        }
        else if (codigoTerritorio > 3 && codigoTerritorio < 4){

            continente = "Europa";

        }
        else if (codigoTerritorio > 4 && codigoTerritorio < 5){

            continente = "Africa";

        }
        else if (codigoTerritorio > 5 && codigoTerritorio < 6){

            continente = "Asia";

        }
        else if (codigoTerritorio > 6 && codigoTerritorio < 7){

            continente = "Australia";

        }

        Territorio* territorio = new Territorio("Territorio" + to_string(codigoTerritorio), codigoTerritorio, continente, dueño, unidades);
        territorios.push_back(territorio); // Se agrega el territorio a la lista de territorios de juego
        if (dueño != nullptr) {
            dueño->AgregarTerritorio(territorio); // Se agrega el territorio a la lista de territorios del jugador dueño
        }
    }
}

