#ifndef DECLARACIONES_H
#define DECLARACIONES_H
#include <string>
#include <vector>
#include <list>
using namespace std;

// Inicia el bucle infinito de la terminal con el indicador $
void iniciarConsola();

class Jugador;
class Territorio;
class Juego; 

// Funciones auxiliares
vector<string> separarPalabras(const string& linea);
void procesarEntrada(const vector<string>& palabras_comando, bool& ejecutando, Juego& juego);

// Funciones de validacion
bool esNumeroEntero(const string& cadena);
bool esNombreJugadorValido(const string& nombre);

//Se utilizan punteros para acceder directamente a los objetos y modificar sus atributos sin necesidad de crear copias
//es util porque se pueden realizar cambios en los objetos directamente

// Jugador* jugador = puede guardar una direccion de memoria de un objeto .
// Jugador* jugador = &nombre    con este apuntador ahora se pueden acceder directamente al dato de tipo jugador


class Jugador {
    private:
        string nombre; //Indica el nombre del jugador
        string color; //Indica el color del jugador
        int ejercito; //Indica la cantidad de ejercito que tiene el jugador
        list<Territorio*> territorios; //Indica los territorios que posee el jugador
        vector<string> cartas; // Indica las cartas que posee el jugador

    public:
        Jugador(const string& nombre, const string& color);
        void AgregarTerritorio(Territorio* territorio);
        void EliminarTerritorio(Territorio* territorio);
        void AgregarEjercito(int cantidad);
        void EliminarEjercito(int cantidad);
        //Getters
        const string& ObtenerNombre() const;
        const string& ObtenerColor() const;
        int ObtenerEjercito() const;
        const list<Territorio*>& ObtenerTerritorios() const;
        const vector<string>& ObtenerCartas() const;
};

class Territorio {
    private:
        string nombre; //Indica el nombre del territorio
        int codigo; //Indica el codigo del territorio
        string continente; //Indica el continente al que pertenece el territorio
        Jugador* dueño; //Indica el jugador que posee el territorio
        int unidades; //Indica la cantidad de unidades que estan en el territorio
        list<Territorio*> territoriosAdyacentes; //Indica los territorios que son vecinos del territorio actual, es decir, aquellos territorios a los que se puede atacar desde el territorio actual

    public:

        Territorio(const string& nombre, int codigo, const string& continente, Jugador* dueño, int unidades);
        void AgregarUnidades(int cantidad);
        void EliminarUnidades(int cantidad);
        void CambiarDueño(Jugador* nuevoDueño);
        void AgregarVecino(Territorio* vecino);
        bool VerificarVecino(Territorio* vecino) const;
        // Getters
        const string& ObtenerNombre() const;
        const string& ObtenerContinente() const;
        int ObtenerCodigo() const;
        int ObtenerUnidades() const;
        Jugador* ObtenerDueño() const;
        const list<Territorio*>& ObtenerVecinos() const;

};

class Juego {

    private:
        vector<Jugador*> jugadores; //Indica los jugadores en una partida
        list<Territorio*> territorios; //Indica los territorios en una partida
        Jugador* jugadorActual; // Indica que jugador tiene el turno actual

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