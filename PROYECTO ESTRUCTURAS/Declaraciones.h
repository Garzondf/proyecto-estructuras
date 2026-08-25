#ifndef DECLARACIONES_H
#define DECLARACIONES_H
#include <string>
#include <vector>
#include <list>
using namespace std;

// Inicia el bucle infinito de la terminal con el indicador $
void iniciarConsola();

// Funciones auxiliares para la interfaz
vector<string> separarPalabras(const string& linea);
void procesarEntrada(const vector<string>& palabras_comando, bool& ejecutando);

// Funciones de validacion
bool esNumeroEntero(const string& cadena);
bool esNombreJugadorValido(const string& nombre);

//Se utilizan punteros para acceder directamente a los objetos y modificar sus atributos sin necesidad de crear copias
//es util porque se pueden realizar cambios en los objetos directamente

// Jugador* jugador = puede guardar una direccion de memoria de un objeto .
// Jugador* jugador = &nombre    con este apuntador ahora se pueden acceder directamente al dato de tipo jugador


class Jugador;
class Territorio;

class Jugador {
    private:
        string nombre;
        string color;
        int ejercito;
        list<Territorio*> territorios;
        vector<string> cartas;

    public:
        Jugador(const string& nombre, const string& color);
        void AgregarTerritorio(Territorio* territorio);
        void EliminarTerritorio(Territorio* territorio);
        const list<Territorio*>& ObtenerTerritorios() const;
        const vector<string>& ObtenerCartas() const;
        int ObtenerEjercito() const;
        void AgregarEjercito(int cantidad);
        void EliminarEjercito(int cantidad);
};

class Territorio {
    private:
        string nombre;
        int codigo;
        string continente;
        Jugador* dueño;
        int ejercitoPorTerritorio;
        list<Territorio*> territoriosAdyacentes;

    public:

        Territorio(const string& nombre, int codigo, const string& continente);
        void AgregarUnidades(int cantidad);
        void EliminarUnidades(int cantidad);
        int ObtenerUnidades() const;
        Jugador* ObtenerDueño() const;
        const string& ObtenerContinente() const;
        void CambiarDueño(Jugador* nuevoDueño);
        void AgregarVecino(Territorio* vecino);
        bool VerificarVecino(Territorio* vecino) const;

};

class Juego {

    private:
        vector<Jugador*> jugadores; //Indica los jugadores en una partida
        list<Territorio*> territorios; //Indica los territorios en una partida
        Jugador* jugadorActual; // Indica que jugador tiene el turno actual

    public: //Los atributos estan sujetos a cambios
        Juego(); //Constructor por defecto
        void InicializarJuego(const vector<string>& jugadores, const list<string>& territorios);
        void AtacarTerritorio(const string& jugador, const string& territorio);
        void FortificarTerritorio(const string& jugador, const string& territorio);
        void CambiarTurno(const string& jugador);
        void EstadoJuego();
        bool VerificarGanador();

};



#endif