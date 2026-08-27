#include "Juego.h"
#include "Jugador.h"
#include "Territorio.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

Juego::Juego()
{

    juegoInicializado = false; // Conecta con el TAD asi sabemos que el juego no se ha iniciado
    jugadorActual = nullptr;
}

// Estructura lineal auxiliar exclusivamente para definir las fronteras del tablero
struct ConexionFrontera
{
    string territorio1;
    string territorio2;
};

// validar existencia de jugador
Jugador *Juego::BuscarJugador(const string &nombre)
{
    for (Jugador *j : jugadores)
    {
        if (j->ObtenerNombre() == nombre)
        {
            return j;
        }
    }
    return nullptr;
}
// validar existencia de territorio
Territorio *Juego::BuscarTerritorio(const string &busqueda)
{
    for (Territorio *t : territorios)
    {
        if (t->ObtenerCodigo() == busqueda || t->ObtenerNombre() == busqueda)
        {
            return t;
        }
    }
    return nullptr;
}
void Juego::ConfigurarFronteras()
{ // Los jugadores no se agregan dos veces porque el metodo agregar vecino revisa que no existe otro antes
    vector<ConexionFrontera> fronteras_del_mundo = {

        // 1. AMÉRICA DEL NORTE
        // 1.1 Alaska
        {"1.1", "1.6"},
        {"1.1", "1.2"},
        {"1.1", "5.6"},
        // 1.2 Alberta
        {"1.2", "1.6"},
        {"1.2", "1.7"},
        {"1.2", "1.9"},
        // 1.3 América Central
        {"1.3", "1.9"},
        {"1.3", "1.4"},
        {"1.3", "2.4"},
        // 1.4 Estados Unidos Orientales
        {"1.4", "1.9"},
        {"1.4", "1.7"},
        {"1.4", "1.8"},
        {"1.4", "1.3"},
        // 1.5 Groenlandia
        {"1.5", "1.6"},
        {"1.5", "1.7"},
        {"1.5", "1.8"},
        {"1.5", "3.2"},
        // 1.6 Territorio Noroccidental
        {"1.6", "1.7"},
        {"1.6", "1.5"},
        // 1.7 Ontario
        {"1.7", "1.6"},
        {"1.7", "1.2"},
        {"1.7", "1.9"},
        {"1.7", "1.4"},
        {"1.7", "1.8"},
        {"1.7", "1.5"},
        // 1.8 Quebec
        {"1.8", "1.7"},
        {"1.8", "1.4"},
        {"1.8", "1.5"},
        // 1.9 Estados Unidos Occidentales
        {"1.9", "1.2"},
        {"1.9", "1.7"},
        {"1.9", "1.4"},
        {"1.9", "1.3"},

        // 2. AMÉRICA DEL SUR
        // 2.1 Argentina
        {"2.1", "2.2"},
        {"2.1", "2.3"},
        // 2.2 Brasil
        {"2.2", "2.3"},
        {"2.2", "2.4"},
        {"2.2", "2.1"},
        {"2.2", "4.5"},
        // 2.3 Perú
        {"2.3", "2.4"},
        {"2.3", "2.2"},
        {"2.3", "2.1"},
        // 2.4 Venezuela
        {"2.4", "1.3"},
        {"2.4", "2.2"},
        {"2.4", "2.3"},

        // 3. EUROPA
        // 3.1 Gran Bretaña
        {"3.1", "3.2"},
        {"3.1", "3.4"},
        {"3.1", "3.3"},
        {"3.1", "3.7"},
        // 3.2 Islandia
        {"3.2", "1.5"},
        {"3.2", "3.1"},
        {"3.2", "3.4"},
        // 3.3 Europa del Norte
        {"3.3", "3.1"},
        {"3.3", "3.7"},
        {"3.3", "3.5"},
        {"3.3", "3.6"},
        {"3.3", "3.4"},
        // 3.4 Escandinavia
        {"3.4", "3.2"},
        {"3.4", "3.1"},
        {"3.4", "3.3"},
        {"3.4", "3.6"},
        // 3.5 Europa del Sur
        {"3.5", "3.7"},
        {"3.5", "3.3"},
        {"3.5", "3.6"},
        {"3.5", "4.3"},
        {"3.5", "5.7"},
        {"3.5", "3.1" /* Nota: Italia conecta con Western Europe, manejado aparte */},
        // 3.6 Ucrania
        {"3.6", "3.4"},
        {"3.6", "3.3"},
        {"3.6", "3.5"},
        {"3.6", "5.1"},
        {"3.6", "5.7"},
        {"3.6", "5.11"},
        // 3.7 Europa Occidental
        {"3.7", "3.1"},
        {"3.7", "3.3"},
        {"3.7", "3.5"},
        {"3.7", "4.5"},

        // 4. ÁFRICA
        // 4.1 Congo
        {"4.1", "4.5"},
        {"4.1", "4.2"},
        {"4.1", "4.6"},
        // 4.2 África Oriental
        {"4.2", "4.5"},
        {"4.2", "4.3"},
        {"4.2", "5.7"},
        {"4.2", "4.1"},
        {"4.2", "4.6"},
        {"4.2", "4.4"},
        // 4.3 Egipto
        {"4.3", "4.5"},
        {"4.3", "5.7"},
        {"4.3", "3.5"},
        {"4.3", "4.2"},
        // 4.4 Madagascar
        {"4.4", "4.2"},
        {"4.4", "4.6"},
        // 4.5 África del Norte
        {"4.5", "3.7"},
        {"4.5", "4.3"},
        {"4.5", "4.2"},
        {"4.5", "4.1"},
        {"4.5", "2.2"},
        // 4.6 África del Sur
        {"4.6", "4.1"},
        {"4.6", "4.2"},
        {"4.6", "4.4"},

        // 5. ASIA
        // 5.1 Afganistán
        {"5.1", "5.11"},
        {"5.1", "5.7"},
        {"5.1", "5.3"},
        {"5.1", "5.2"},
        {"5.1", "3.6"},
        // 5.2 China
        {"5.2", "5.11"},
        {"5.2", "5.10"},
        {"5.2", "5.8"},
        {"5.2", "5.9"},
        {"5.2", "5.3"},
        {"5.2", "5.1"},
        // 5.3 India
        {"5.3", "5.7"},
        {"5.3", "5.1"},
        {"5.3", "5.2"},
        {"5.3", "5.9"},
        // 5.4 Irkutsk
        {"5.4", "5.10"},
        {"5.4", "5.12"},
        {"5.4", "5.6"},
        {"5.4", "5.8"},
        // 5.5 Japón
        {"5.5", "5.6"},
        {"5.5", "5.8"},
        // 5.6 Kamchatka
        {"5.6", "1.1"},
        {"5.6", "5.12"},
        {"5.6", "5.4"},
        {"5.6", "5.8"},
        {"5.6", "5.5"},
        // 5.7 Medio Oriente
        {"5.7", "3.6"},
        {"5.7", "3.5"},
        {"5.7", "4.3"},
        {"5.7", "4.2"},
        {"5.7", "5.3"},
        {"5.7", "5.1"},
        // 5.8 Mongolia
        {"5.8", "5.10"},
        {"5.8", "5.4"},
        {"5.8", "5.6"},
        {"5.8", "5.5"},
        {"5.8", "5.2"},
        // 5.9 Siam
        {"5.9", "5.2"},
        {"5.9", "5.3"},
        {"5.9", "6.2"},
        // 5.10 Siberia
        {"5.10", "5.11"},
        {"5.10", "5.12"},
        {"5.10", "5.4"},
        {"5.10", "5.8"},
        {"5.10", "5.2"},
        // 5.11 Ural
        {"5.11", "3.6"},
        {"5.11", "5.1"},
        {"5.11", "5.2"},
        {"5.11", "5.10"},
        // 5.12 Yakutsk
        {"5.12", "5.10"},
        {"5.12", "5.4"},
        {"5.12", "5.6"},

        // 6. AUSTRALIA
        // 6.1 Australia Oriental
        {"6.1", "6.4"},
        {"6.1", "6.3"},
        // 6.2 Indonesia
        {"6.2", "5.9"},
        {"6.2", "6.4"},
        {"6.2", "6.3"},
        // 6.3 Nueva Guinea
        {"6.3", "6.2"},
        {"6.3", "6.1"},
        // 6.4 Australia Occidental
        {"6.4", "6.2"},
        {"6.4", "6.1"}};

    // Recorrido estrictamente lineal para establecer la relación bidireccional
    for (size_t i = 0; i < fronteras_del_mundo.size(); i++)
    {
        Territorio *t1 = BuscarTerritorio(fronteras_del_mundo[i].territorio1);
        Territorio *t2 = BuscarTerritorio(fronteras_del_mundo[i].territorio2);

        if (t1 != nullptr && t2 != nullptr)
        {
            t1->AgregarVecino(t2);
            t2->AgregarVecino(t1); // Relación bidireccional automática
        }
    }
}

void Juego::InicializarJuego(const string &archivo)
{

    vector<DatosTerritorio> baseTerritorios = {// Este vector nos va a permitir encontrar los datos a partir del codigo del archivo, funciona como una base
                                               {"1.1", "Alaska", "America del Norte"},
                                               {"1.2", "Alberta", "America del Norte"},
                                               {"1.3", "America Central", "America del Norte"},
                                               {"1.4", "Estados Unidos Orientales", "America del Norte"},
                                               {"1.5", "Groenlandia", "America del Norte"},
                                               {"1.6", "Territorio Noroccidental", "America del Norte"},
                                               {"1.7", "Ontario", "America del Norte"},
                                               {"1.8", "Quebec", "America del Norte"},
                                               {"1.9", "Estados Unidos Occidentales", "America del Norte"},

                                               {"2.1", "Argentina", "America del Sur"},
                                               {"2.2", "Brasil", "America del Sur"},
                                               {"2.3", "Peru", "America del Sur"},
                                               {"2.4", "Venezuela", "America del Sur"},

                                               {"3.1", "Gran Bretana", "Europa"},
                                               {"3.2", "Islandia", "Europa"},
                                               {"3.3", "Europa del Norte", "Europa"},
                                               {"3.4", "Escandinavia", "Europa"},
                                               {"3.5", "Europa del Sur", "Europa"},
                                               {"3.6", "Ucrania", "Europa"},
                                               {"3.7", "Europa Occidental", "Europa"},

                                               {"4.1", "Congo", "Africa"},
                                               {"4.2", "Africa Oriental", "Africa"},
                                               {"4.3", "Egipto", "Africa"},
                                               {"4.4", "Madagascar", "Africa"},
                                               {"4.5", "Africa del Norte", "Africa"},
                                               {"4.6", "Africa del Sur", "Africa"},

                                               {"5.1", "Afghanistan", "Asia"},
                                               {"5.2", "China", "Asia"},
                                               {"5.3", "India", "Asia"},
                                               {"5.4", "Irkutsk", "Asia"},
                                               {"5.5", "Japon", "Asia"},
                                               {"5.6", "Kamchatka", "Asia"},
                                               {"5.7", "Medio Oriente", "Asia"},
                                               {"5.8", "Mongolia", "Asia"},
                                               {"5.9", "Siam", "Asia"},
                                               {"5.10", "Siberia", "Asia"},
                                               {"5.11", "Ural", "Asia"},
                                               {"5.12", "Yakutsk", "Asia"},

                                               {"6.1", "Australia Oriental", "Australia"},
                                               {"6.2", "Indonesia", "Australia"},
                                               {"6.3", "Nueva Guinea", "Australia"},
                                               {"6.4", "Australia Occidental", "Australia"}};

    if (juegoInicializado)
    {
        cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
        return;
    }

    ifstream archivoEntrada(archivo);

    if (!archivoEntrada.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    if (archivoEntrada.peek() == ifstream::traits_type::eof())
    { // Revisamos que si tenga info el archivo
        cout << "(Archivo vacío) " << archivo << " no contiene información." << endl;
        return;
    }

    int cantidadJugadores;

    if (!(archivoEntrada >> cantidadJugadores))
    {
        cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
        return;
    }

    int unidadesPermitidas = 0; // Nos va a servir para cumplir la condicion de saber cuantas unidades puede tener un jugador

    if (cantidadJugadores == 3)
    {
        unidadesPermitidas = 35;
    }
    else if (cantidadJugadores == 4)
    {
        unidadesPermitidas = 30;
    }
    else if (cantidadJugadores == 5)
    {
        unidadesPermitidas = 25;
    }
    else if (cantidadJugadores == 6)
    {
        unidadesPermitidas = 20;
    }
    else
    {
        cout << "(Cantidad de jugadores inválida) El juego solo puede ser jugado por 3, 4, 5 o 6 jugadores." << endl;
        return;
    }

    for (int i = 0; i < cantidadJugadores; i++)
    { // Crear jugadores

        string nombreJugador;
        string colorJugador;

        if (!(archivoEntrada >> nombreJugador >> colorJugador))
        { // Condicion para saber si no hay nada de info
            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        Jugador *jugador = new Jugador(nombreJugador, colorJugador);
        jugadores.push_back(jugador); // Se agrega el jugador a la lista de los jugadores de juego
    }

    // Leer territorios y asociarlos a partir de su codigo

    string codigoTerritorio;
    string color;
    int unidades;
    int conteoTerritorios = 0;

    while (archivoEntrada >> codigoTerritorio >> color >> unidades)
    { // Va a leer toda la info

        conteoTerritorios++;      // Va a contar la cantidad de territorios que hay en el archivo
        Jugador *dueño = nullptr; // Hay que declararlo dentro para que no se quede con la direccion del jugador anterior

        for (Jugador *jugador : jugadores)
        {
            if (jugador->ObtenerColor() == color)
            { // Va a asociar el color del jugador con el color de ese territorio para saber quien es el dueño
                dueño = jugador;
                dueño->AgregarEjercito(unidades); // Revisamos que si hubiese un control
                break;
            }
        }

        if (dueño == nullptr)
        {

            cout << "(Archivo sin formato) " << archivo << " no contiene información en el formato esperado." << endl;
            return;
        }

        string nombreContinente; // Comparacion para asignar el continente al territorio segun su codigo
        string nombreTerritorio;
        bool bandera = false;

        for (vector<DatosTerritorio>::iterator it = baseTerritorios.begin(); bandera == false && it != baseTerritorios.end(); it++)
        {
            // A partir de la base que tenemos podemos identificar los territorios y se sale de forma segura POR SI EN ALGUN CASO no se encuentra

            if (it->codigo == codigoTerritorio)
            {

                nombreContinente = it->continente;
                nombreTerritorio = it->nombre;
                bandera = true;
            }
        }

        Territorio *territorio = new Territorio(nombreTerritorio, codigoTerritorio, nombreContinente, dueño, unidades);
        territorios.push_back(territorio); // Se agrega el territorio a la lista de territorios de juego
        if (dueño != nullptr)
        {
            dueño->AgregarTerritorio(territorio); // Se agrega el territorio a la lista de territorios del jugador dueño
        }
    }

    if (conteoTerritorios != 42)
    { // Revisamos que sean solo los 42 territorios
        cout << "(Cantidad de territorios inválida) El juego debe contener exactamente 42 territorios." << endl;
        return;
    }

    for (Jugador *jugador : jugadores)
    {

        if (jugador->ObtenerEjercito() != unidadesPermitidas)
        {

            cout << "(Cantidad de unidades invalida) El jugador " << jugador->ObtenerNombre() << " tiene una cantidad de unidades diferente a la permitida." << endl;
            return;
        }
    }

    ConfigurarFronteras();             // Se llama a la funcion para configurar las fronteras del juego
    juegoInicializado = true;          // Si todo esta bien, el juego se inicializa
    jugadorActual = jugadores.front(); // El primer jugador de la lista va a ser el que tenga el turno inicial
    srand(time(0));                    // Inicializa la semilla para la generación de números aleatorios basada en el tiempo actual
    cout << "(Juego inicializado) El juego ha sido inicializado correctamente." << endl;
}

void Juego::EliminarJugadorDeJuego(Jugador *jugadorAEliminar)
{
    if (jugadorAEliminar == nullptr)
        return;

    for (int iteliminar = 0; iteliminar < jugadores.size(); iteliminar++)
    {
        if (jugadores[iteliminar] == jugadorAEliminar)
        {
            jugadores.erase(jugadores.begin() + iteliminar);
            delete jugadorAEliminar;
            break;
        }
    }
}

void Juego::AtacarTerritorio(const string &jugador, const string &territorio)
{
    // Inicio verificar casos error para validar que el jugador y territorio sean validos, que el juego este inicializado y que sea el turno del jugador
    if (!juegoInicializado)
    {
        cout << "(Juego no inicializado) El juego debe ser inicializado antes de realizar un ataque." << endl;
        return;
    }

    Jugador *jugadorActualPtr = BuscarJugador(jugador);
    if (jugadorActualPtr == nullptr)
    {
        cout << "(Jugador no válido) El jugador " << jugador << " no existe en la partida." << endl;
        return;
    }

    if (jugadorActual != jugadorActualPtr)
    {
        cout << "(Turno inválido) No es el turno del jugador " << jugador << "." << endl;
        return;
    }

    string nombreOrigen, nombreDestino;

    cout << "Ingrese el nombre del territorio desde el cual desea atacar: ";
    getline(cin, nombreOrigen);

    Territorio *origen = BuscarTerritorio(nombreOrigen);
    if (origen == nullptr)
    {
        cout << "(Territorio no válido) El territorio " << nombreOrigen << " no existe." << endl;
        return;
    }

    if (origen->ObtenerDueño() != jugadorActualPtr)
    {
        cout << "(Territorio no válido) El territorio " << nombreOrigen << " no pertenece al jugador " << jugador << "." << endl;
        return;
    }

    if (origen->ObtenerUnidades() <= 1)
    {
        cout << "(Unidades insuficientes) El territorio " << nombreOrigen << " no tiene suficientes unidades para atacar." << endl;
        return;
    }
    // Para dar continuidad al juego, si el territorio no se pasa como argumento, se le pide al jugador que lo ingrese por consola
    if (territorio.empty())
    {
        cout << "Ingrese el nombre del territorio al cual desea atacar: ";
        getline(cin, nombreDestino);
    }
    else
    {
        nombreDestino = territorio;
    }

    Territorio *destino = BuscarTerritorio(nombreDestino);
    if (destino == nullptr)
    {
        cout << "(Territorio no valido) El territorio " << nombreDestino << " no existe." << endl;
        return;
    }

    if (destino->ObtenerDueño() == jugadorActualPtr)
    {
        cout << "(Territorio no valido) El territorio " << nombreDestino << " ya pertenece al jugador " << jugador << "." << endl;
        return;
    }

    if (!origen->VerificarVecino(destino))
    {
        cout << "(Territorios no adyacentes) El territorio " << destino->ObtenerNombre() << " no es vecino de " << origen->ObtenerNombre() << "." << endl;
        return;
    }
    // fin casos error

    // muestra por consola que se va a realizar el ataque y de quien es el territorio que se va a atacar
    Jugador *defensor = destino->ObtenerDueño();
    cout << "Comienza el ataque de " << origen->ObtenerNombre() << " contra " << destino->ObtenerNombre() << " (" << defensor->ObtenerNombre() << ")" << endl;

    bool continuarAtacando = true;

    while (continuarAtacando && origen->ObtenerUnidades() > 1 && destino->ObtenerUnidades() > 0)
    {
        int dadosAtacanteNum = min(3, origen->ObtenerUnidades() - 1); // El atacante puede lanzar hasta 3 dados, pero debe dejar al menos 1 unidad en el territorio
        int dadosDefensorNum = min(2, destino->ObtenerUnidades());    // El defensor puede lanzar hasta 2 dados, pero no más de las unidades que tiene

        vector<int> dadosAtacante(dadosAtacanteNum);
        vector<int> dadosDefensor(dadosDefensorNum);

        for (int i = 0; i < dadosAtacanteNum; i++)
            dadosAtacante.push_back((rand() % 6) + 1);
        for (int i = 0; i < dadosDefensorNum; i++)
            dadosDefensor.push_back((rand() % 6) + 1);

        sort(dadosAtacante.rbegin(), dadosAtacante.rend());
        sort(dadosDefensor.rbegin(), dadosDefensor.rend());

        cout << "Resultado de los dados: " << endl;
        cout << "Atacante (" << jugadorActualPtr->ObtenerNombre() << "): ";
        for (int d : dadosAtacante)
            cout << d << " ";
        cout << endl;
        cout << "Defensor (" << defensor->ObtenerNombre() << "): ";
        for (int d : dadosDefensor)
            cout << d << " ";
        cout << endl;

        int comparaciones = min(dadosAtacanteNum, dadosDefensorNum);
        int perdidasAtacante = 0;
        int perdidasDefensor = 0;

        for (int i = 0; i < comparaciones; i++)
        {
            if (dadosAtacante[i] > dadosDefensor[i])
            {
                perdidasDefensor++;
            }
            else
            {
                perdidasAtacante++;
            }
        }

        // Actualizacion de las unidades de los territorios y los ejércitos de los jugadores
        origen->EliminarUnidades(perdidasAtacante);
        jugadorActualPtr->EliminarEjercito(perdidasAtacante);
        destino->EliminarUnidades(perdidasDefensor);
        defensor->EliminarEjercito(perdidasDefensor);

        cout << "Unidades perdidas en esta ronda - Atacante: " << perdidasAtacante << ", Defensor: " << perdidasDefensor << endl;
        cout << "Unidades restantes - " << origen->ObtenerNombre() << ": " << origen->ObtenerUnidades() << ", " << destino->ObtenerNombre() << ": " << destino->ObtenerUnidades() << endl;

        if (destino->ObtenerUnidades() == 0)
        {
            cout << jugadorActualPtr->ObtenerNombre() << "!!! ha conquistado " << destino->ObtenerNombre() << endl;
            // Transferencia de propiedad del territorio
            defensor->EliminarTerritorio(destino);
            destino->CambiarDueño(jugadorActualPtr);
            jugadorActualPtr->AgregarTerritorio(destino);
            // El atacante debe mover al menos tantas unidades como dados lanzó pero tambien debe dejar al menos 1 unidad en el territorio de origen
            int tropasParaMover = min(dadosAtacanteNum, origen->ObtenerUnidades() - 1);
            origen->EliminarUnidades(tropasParaMover);
            destino->AgregarUnidades(tropasParaMover);

            cout << "Se han movido " << tropasParaMover << " unidades a " << destino->ObtenerNombre() << endl;

            if (defensor->ObtenerTerritorios().empty())
            {
                cout << "El jugador " << defensor->ObtenerNombre() << " ha sido eliminado del juego." << endl;
                EliminarJugadorDeJuego(defensor); // Elimina al jugadro de la lista
            }

            if (jugadorActualPtr->ObtenerTerritorios().size() == 42)
            {
                cout << "El jugador " << jugadorActualPtr->ObtenerNombre() << " ha conquistado todos los territorios y ha ganado el juego!" << endl;
                juegoInicializado = false; // Finaliza el juego
                return;
            }
            break; // Sale del bucle de ataque
        }

        string respuesta;
        cout << "¿Desea continuar atacando (s/n)? ";
        getline(cin, respuesta);
        if (respuesta != "s" && respuesta != "S")
        {
            continuarAtacando = false;
        }
    }
}
