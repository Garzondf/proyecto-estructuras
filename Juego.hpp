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

    vector<DatosTerritorio> baseTerritorios = { //Este vector nos va a permitir encontrar los datos a partir del codigo del archivo, funciona como una base
        {"1.1", "Alaska", "America del Norte"}, {"1.2", "Alberta", "America del Norte"}, 
        {"1.3", "America Central", "America del Norte"}, {"1.4", "Estados Unidos Orientales", "America del Norte"}, 
        {"1.5", "Groenlandia", "America del Norte"}, {"1.6", "Territorio Noroccidental", "America del Norte"}, 
        {"1.7", "Ontario", "America del Norte"}, {"1.8", "Quebec", "America del Norte"}, 
        {"1.9", "Estados Unidos Occidentales", "America del Norte"},
        
        {"2.1", "Argentina", "America del Sur"}, {"2.2", "Brasil", "America del Sur"}, 
        {"2.3", "Peru", "America del Sur"}, {"2.4", "Venezuela", "America del Sur"},
        
        {"3.1", "Gran Bretana", "Europa"}, {"3.2", "Islandia", "Europa"}, 
        {"3.3", "Europa del Norte", "Europa"}, {"3.4", "Escandinavia", "Europa"}, 
        {"3.5", "Europa del Sur", "Europa"}, {"3.6", "Ucrania", "Europa"}, 
        {"3.7", "Europa Occidental", "Europa"},
        
        {"4.1", "Congo", "Africa"}, {"4.2", "Africa Oriental", "Africa"}, 
        {"4.3", "Egipto", "Africa"}, {"4.4", "Madagascar", "Africa"}, 
        {"4.5", "Africa del Norte", "Africa"}, {"4.6", "Africa del Sur", "Africa"},
        
        {"5.1", "Afghanistan", "Asia"}, {"5.2", "China", "Asia"}, 
        {"5.3", "India", "Asia"}, {"5.4", "Irkutsk", "Asia"}, 
        {"5.5", "Japon", "Asia"}, {"5.6", "Kamchatka", "Asia"}, 
        {"5.7", "Medio Oriente", "Asia"}, {"5.8", "Mongolia", "Asia"}, 
        {"5.9", "Siam", "Asia"}, {"5.10", "Siberia", "Asia"}, 
        {"5.11", "Ural", "Asia"}, {"5.12", "Yakutsk", "Asia"},
        
        {"6.1", "Australia Oriental", "Australia"}, {"6.2", "Indonesia", "Australia"}, 
        {"6.3", "Nueva Guinea", "Australia"}, {"6.4", "Australia Occidental", "Australia"}
    };

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

    for (int i = 0; i < cantidadJugadores; i++) { //Crear jugadores

        string nombreJugador;
        string colorJugador;

        if (!(archivoEntrada >> nombreJugador >> colorJugador)) { //Condicion para saber si no hay nada de info
            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        Jugador* jugador = new Jugador(nombreJugador, colorJugador);
        jugadores.push_back(jugador); // Se agrega el jugador a la lista de los jugadores de juego

    }

    // Leer territorios y asociarlos a partir de su codigo

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
                dueño->AgregarEjercito(unidades); //Revisamos que si hubiese un control
                break;
            }
        }

        if (dueño == nullptr) {

            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        string nombreContinente; // Comparacion para asignar el continente al territorio segun su codigo
        string nombreTerritorio;
        bool bandera = false; 

        for (vector<DatosTerritorio>:: iterator it = baseTerritorios.begin(); bandera == false && it != baseTerritorios.end(); it++ ){
            //A partir de la base que tenemos podemos identificar los territorios y se sale de forma segura POR SI EN ALGUN CASO no se encuentra

            if (it -> codigo == codigoTerritorio){

                nombreContinente = it -> continente;
                nombreTerritorio = it -> nombre;
                bandera = true;
            }
        }
        

        Territorio* territorio = new Territorio(nombreTerritorio, codigoTerritorio, nombreContinente, dueño, unidades);
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

