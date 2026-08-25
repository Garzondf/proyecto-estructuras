#include "Declaraciones.h"
#include <iostream>
#include <sstream>
#include <cctype> 

using namespace std;

bool esNumeroEntero(const string& cadena) {
    if (cadena.empty()) return false;
    for (char const &c : cadena) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}


bool esNombreJugadorValido(const string& nombre) {
    return (nombre.length() > 0 && nombre.length() <= 8);
}

vector<string> separarPalabras(const string& linea) {
    vector<string> palabras_comando;
    string palabra_individual;
    stringstream ss(linea);

    while (ss >> palabra_individual) {
        palabras_comando.push_back(palabra_individual);
    }
    return palabras_comando;
}


void procesarEntrada(const vector<string>& palabras_comando, bool& ejecutando) {
    if (palabras_comando.empty()) {
        return;
    }

    string comando_principal = palabras_comando[0];
    int cantidad_palabras = palabras_comando.size();

    if (comando_principal == "ayuda") {

        if (cantidad_palabras == 1) { 
            cout << "Lista de comandos disponibles:" << endl;
            //comandos parte 1
            cout << "  - Inicializar" << endl;
            cout << "  - Obtener_unidades" << endl;
            cout << "  - Atacar" << endl;
            cout << "  - Fortificar" << endl;
            cout << "  - Estado_juego" << endl;
            //comandos parte 2
            cout << "  - Guardar" << endl;
            cout << "  - Guardar_comprimido" << endl;
            //comados parte 3
            cout << "  - Costo_conquista" << endl;
            cout << "  - Conquista_mas_barata" << endl;
            //comando salida
            cout << "  -Salir" << endl;
            cout << "\nPara ver el uso de un comando especifico, escribe: ayuda <comando>" << endl;
        } 
        else if (cantidad_palabras == 2) {

            string subcomando = palabras_comando[1];
            
            if (subcomando == "Inicializar" || subcomando == "inicializar") {  // Tambien debe aceptar "inicializar" en minusculas?
                cout << "Uso: Inicializar <archivo_inicio.txt>" << endl;
                cout << "Inicializa el juego a partir de la información contenida en el archivo \"archivo_inicio.txt\" dejando la interfaz del juego lista para recibir los turnos de cada jugador" << endl;
            } 
            else if (subcomando == "Obtener_unidades" || subcomando == "obtener_unidades") {
                cout << "Uso: Obtener_unidades <nombre_jugador>" << endl;
                cout << "El comando primero informar al jugador cuántas unidades adicionales puede reclamar y luego le pregunta en cuáles de sus territorios las quiere asignar y en qué cantidad." << endl;
            } 
            else if (subcomando == "Atacar" || subcomando == "atacar") {
                cout << "Uso: Atacar <nombre_jugador>" << endl;
                cout << "El comando primero pregunta desde cuál territorio quiere atacar (que contiene actualmente unidades del jugador) y hacia cuál territorio dirigirá el ataque. Luego informa los valores obtenidos con los dados, y la cantidad de unidades que se ganan o pierden. Este proceso se repite hasta que alguno de los dos territorios se quede sin unidades, o hasta que el atacante decida detenerse." << endl;
            } 
            else if (subcomando == "Fortificar" || subcomando == "fortificar") {
                cout << "Uso: Fortificar <nombre_jugador>" << endl;
                cout << "El comando pregunta al jugador los territorios vecinos que desea seleccionar para la fortificación y la cantidad de unidades que se trasladarán de uno al otro." << endl;
            } 
            else if (subcomando == "Estado_juego" || subcomando == "estado_juego") {
                cout << "Uso: Estado_juego" << endl;
                cout << "Presenta en pantalla un resumen de la situacion actual del juego mostrando: " << endl;
                cout << "número de jugadores, nombres y colores de cada uno, jugador con el turno actual y lista de los territorios con el color del jugador que lo controla con la cantidad de unidades que hay ubicadas en cada uno" << endl;
            } 
            else if (subcomando == "Guardar" || subcomando == "guardar") {
                cout << "Uso: Guardar <nombre_archivo>" << endl;
                cout << "Guarda el estado actual del juego en un archivo de texto plano." << endl;
            } 
            else if (subcomando == "Guardar_comprimido" || subcomando == "guardar_comprimido") {
                cout << "Uso: Guardar_comprimido <nombre_archivo>" << endl;
                cout << "Guarda el estado actual del juego en un archivo binario comprimido (.bin)." << endl;
            } 
            else if (subcomando == "Costo_conquista" || subcomando == "costo_conquista") {
                cout << "Uso: Costo_conquista <nombre_jugador> <territorio>" << endl;
                cout << "Calcula el costo y la secuencia de territorios a conquistar para llegar al territorio objetivo dado por el usuario." << endl;
            } 
            else if (subcomando == "Conquista_mas_barata" || subcomando == "conquista_mas_barata") {
                cout << "Uso: Conquista_mas_barata <nombre_jugador>" << endl;
                cout << "De todos los territorios posibles, calcula aquel que pueda implicar un menor número de unidades de ejército perdidas." << endl;
            } 
            else if (subcomando == "Salir" || subcomando == "salir") {
                cout << "Uso: Salir" << endl;
                cout << "Termina la ejecucion de la aplicacion." << endl;
            } 
            else {
                cout << "Error: El comando '" << subcomando << "' no existe." << endl;
            }
        } 
        else {
            cout << "Error en formato. Uso correcto: ayuda o ayuda <comando>" << endl;
        }
    } 
    // ==========================================
    // LOGICA DE LOS DEMAS COMANDOS Y VALIDACION
    // ==========================================


  else if (comando_principal == "Inicializar" || comando_principal == "inicializar") {
        if (cantidad_palabras == 2) {
            string nombre_archivo = palabras_comando[1];
            bool es_txt = (nombre_archivo.length() >= 4 && nombre_archivo.substr(nombre_archivo.length() - 4) == ".txt");
            bool es_bin = (nombre_archivo.length() >= 4 && nombre_archivo.substr(nombre_archivo.length() - 4) == ".bin");
            
            // Validamos que termine en .txt o .bin
            if (es_txt || es_bin) {
                cout << "(simulacion!!!!) Comando inicializar ejecutado con archivo: " << nombre_archivo << endl;
            } else {
                cout << "(Archivo sin formato) El archivo debe tener extension .txt o .bin" << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: Inicializar <archivo_inicio.txt o binario>" << endl;
        }
    }
    else if (comando_principal == "Obtener_unidades" || comando_principal == "obtener_unidades") {
        if (cantidad_palabras == 2) {
            //editar para entrega 1 detectar si nombre de jugador existe en partida, si no existe mostrar mensaje de error
            if (esNombreJugadorValido(palabras_comando[1])) {
                cout << "(simulacion!!!!) Comando obtener_unidades dando unidades a jugador: " << palabras_comando[1] << endl;
            } else {
                cout << "(Jugador no valido) El nombre debe tener maximo 8 caracteres." << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: obtener_unidades <nombre_jugador>" << endl;
        }
    }
    else if (comando_principal == "Atacar" || comando_principal == "atacar") {
        if (cantidad_palabras == 2) {
            //editar para entrega 1 detectar si nombre de jugador existe en partida, si no existe mostrar mensaje de error
            if (esNombreJugadorValido(palabras_comando[1])) {
                cout << "(simulacion!!!!) Comando atacar ejecutado para jugador: " << palabras_comando[1] << endl;
                cout << "(simulacion!!!!) preguntando y recibiendo respuesta" << endl;
                cout << "(Simulacion!!!!) Ataque desde territorio A hacia territorio B. Resultado: Jugador " << palabras_comando[1] << " gana el ataque." << endl;
            } else {
                cout << "(Jugador no valido) El nombre debe tener maximo 8 caracteres." << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: atacar <nombre_jugador>" << endl;
        }
    }
    else if (comando_principal == "Fortificar" || comando_principal == "fortificar") {
        if (cantidad_palabras == 2) {
            //editar para entrega 1 detectar si nombre de jugador existe en partida, si no existe mostrar mensaje de error
            if (esNombreJugadorValido(palabras_comando[1])) {
                cout << "(simulacion!!!!) Comando fortificar validado para: " << palabras_comando[1] << endl;
                cout << "(simulacion!!!!) preguntando y recibiendo respuesta" << endl;
                cout << "(Simulacion!!!!) Fortificacion de territorio A hacia territorio B. Resultado: Jugador " << palabras_comando[1] << " ha fortificado exitosamente." << endl;
            } else {
                cout << "(Jugador no valido) El nombre debe tener maximo 8 caracteres." << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: fortificar <nombre_jugador>" << endl;
        }
    }
    else if (comando_principal == "Estado_juego" || comando_principal == "estado_juego") {
        if (cantidad_palabras == 1) {
            cout << "(simulacion!!!!) Mostrando estado del juego." << endl;
            cout << "(simulacion!!!!) Numero de jugadores: 2" << endl;
            cout << "(simulacion!!!!) Jugador 1: Alice (Rojo)" << endl;
            cout << "(simulacion!!!!) Jugador 2: Bob (Azul)" << endl;
            cout << "(simulacion!!!!) Territorios: 25" << endl;
            cout << "(simulacion!!!!) Turno actual: Alice" << endl;
            cout << "(simulacion!!!!) Territorios y unidades:" << endl;
            cout << "(simulacion!!!!)   - Territorio A: Alice (Rojo) - 5 unidades" << endl;
            cout << "(simulacion!!!!)   - Territorio B: Bob (Azul) - 3 unidades" << endl;
            
        } else {
            cout << "Uso incorrecto. Sintaxis: estado_juego (no recibe parametros)" << endl;
        }
    }
    else if (comando_principal == "Guardar" || comando_principal == "guardar") {
        if (cantidad_palabras == 2) {
            cout << "(simulacion!!!!) Comando guardar actualizando en archivo: " << palabras_comando[1] << endl;
        } else {
            cout << "Uso incorrecto. Sintaxis: guardar <nombre_archivo>" << endl;
        }
    }
    else if (comando_principal == "Guardar_comprimido" || comando_principal == "guardar_comprimido") {
        if (cantidad_palabras == 2) {
            cout << "(simulacion!!!!) Comando guardar_comprimido actualizando en archivo: " << palabras_comando[1] << endl;
        } else {
            cout << "Uso incorrecto. Sintaxis: guardar_comprimido <nombre_archivo>" << endl;
        }
    }
    else if (comando_principal == "Costo_conquista" || comando_principal == "costo_conquista") {
        if (cantidad_palabras == 3) {
            //editar para entrega 1 detectar si nombre de jugador existe en partida, si no existe mostrar mensaje de error
            if (esNombreJugadorValido(palabras_comando[1])) {
                cout << "(simulacion!!!!) Comando costo_conquista validado para " << palabras_comando[1] << " hacia " << palabras_comando[2] << endl;
            } else {
                cout << "(Jugador no valido) El nombre debe tener maximo 8 caracteres." << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: costo_conquista <nombre_jugador> <territorio>" << endl;
        }
    }
    else if (comando_principal == "Conquista_mas_barata" || comando_principal == "conquista_mas_barata") {
        if (cantidad_palabras == 2) {
            //editar para entrega 1 detectar si nombre de jugador existe en partida, si no existe mostrar mensaje de error
            if (esNombreJugadorValido(palabras_comando[1])) {
                cout << "(simulacion!!!!) Comando conquista_mas_barata validado para: " << palabras_comando[1] << endl;
            } else {
                cout << "(Jugador no valido) El nombre debe tener maximo 8 caracteres." << endl;
            }
        } else {
            cout << "Uso incorrecto. Sintaxis: conquista_mas_barata <nombre_jugador>" << endl;
        }
    }
    else if (comando_principal == "Salir" || comando_principal == "salir") {
        if (cantidad_palabras == 1) {
            ejecutando = false;
        } else {
             cout << "Uso incorrecto. Sintaxis: salir (no recibe parametros)" << endl;
        }
    } 
    else {
        cout << "Comando no reconocido. Escribe 'ayuda' para ver la lista de comandos." << endl;
    }
}


void iniciarConsola() {
    string entrada;
    bool ejecutando = true;

    cout << "Bienvenido. Escribe 'ayuda' para ver los comandos disponibles." << endl;

    while (ejecutando) {
        cout << "$ "; // Indicador de linea de comando exigido
        getline(cin, entrada);
        
        vector<string> palabras_comando = separarPalabras(entrada);
        procesarEntrada(palabras_comando, ejecutando);
    }
}