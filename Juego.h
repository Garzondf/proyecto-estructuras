
#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Territorio.h"
#include <string>
#include <vector>
#include <list>
using namespace std;

class Juego {

    private:
        vector<Jugador*> jugadores; //Indica los jugadores en una partida
        list<Territorio*> territorios; //Indica los territorios en una partida
        Jugador* jugadorActual; // Indica que jugador tiene el turno actual
        bool juegoInicializado; //Esta variable la vamos a usar para saber si el juego ya fue iniciado

    public:
        Juego(); //Constructor por defecto
        void InicializarJuego(const string& archivo);
        void AtacarTerritorio(const string& jugador, const string& territorio);
        void FortificarTerritorio(const string& jugador, const string& territorio);
        void CambiarTurno(const string& jugador);
        void EstadoJuego();
        bool VerificarGanador();
        Jugador* BuscarJugador(const string& nombre);
        Territorio* BuscarTerritorio(const string& nombre);

};

#endif