#include "interfaz.h"
#include <iostream>
#include <sstream>
#include <cctype> 

using namespace std;

// Verifica si todos los caracteres de un string son numeros
bool esNumeroEntero(const string& cadena) {
    if (cadena.empty()) return false;
    for (char const &c : cadena) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

// Verifica que el nombre tenga entre 1 y 8 caracteres
bool esNombreJugadorValido(const string& nombre) {
    return (nombre.length() > 0 && nombre.length() <= 8);
}

// Divide el texto ingresado separandolo por los espacios
vector<string> separarPalabras(const string& linea) {
    vector<string> palabras_comando;
    string palabra_individual;
    stringstream ss(linea);
    
    // Lee palabra por palabra y la guarda en el vector
    while (ss >> palabra_individual) {
        palabras_comando.push_back(palabra_individual);
    }
    return palabras_comando;
}

// Analiza el vector de palabras ingresadas por el usuario
void procesarEntrada(const vector<string>& palabras_comando, bool& ejecutando) {
    if (palabras_comando.empty()) {
        return; // El usuario solo presiono Enter, seguir esperando la entrada
    }

    string comando_principal = palabras_comando[0];
    int cantidad_palabras = palabras_comando.size();

    // ==========================================
    // LOGICA DEL COMANDO: ayuda
    // ==========================================
    if (comando_principal == "ayuda") {
        if (cantidad_palabras == 1) {
            cout << "Lista de comandos disponibles:" << endl;
            //comandos parte 1
            cout << "  - inicializar" << endl;
            cout << "  - obtener_unidades" << endl;
            cout << "  - atacar" << endl;
            cout << "  - fortificar" << endl;
            cout << "  - estado_juego" << endl;
            //comandos parte 2
            cout << "  - guardar" << endl;
            cout << "  - guardar_comprimido" << endl;
            //comados parte 3
            cout << "  - costo_conquista" << endl;
            cout << "  - conquista_mas_barata" << endl;
            //comando salida
            cout << "  - salir" << endl;
            cout << "\nPara ver el uso de un comando especifico, escribe: ayuda <comando>" << endl;
        } 
        else if (cantidad_palabras == 2) {
            string subcomando = palabras_comando[1];
            
            if (subcomando == "inicializar") {
                cout << "Uso: inicializar <archivo_inicio.txt>" << endl;
                cout << "Inicializa el juego a partir de la información contenida en el archivo \"archivo_inicio.txt\" dejando la interfaz del juego lista para recibir los turnos de cada jugador" << endl;
            } 
            else if (subcomando == "obtener_unidades") {
                cout << "Uso: obtener_unidades <nombre_jugador>" << endl;
                cout << "El comando primero informar al jugador cuántas unidades adicionales puede reclamar y luego le pregunta en cuáles de sus territorios las quiere asignar y en qué cantidad." << endl;
            } 
            else if (subcomando == "atacar") {
                cout << "Uso: atacar <nombre_jugador>" << endl;
                cout << "El comando primero pregunta desde cuál territorio quiere atacar (que contiene actualmente unidades del jugador) y hacia cuál territorio dirigirá el ataque. Luego informa los valores obtenidos con los dados, y la cantidad de unidades que se ganan o pierden. Este proceso se repite hasta que alguno de los dos territorios se quede sin unidades, o hasta que el atacante decida detenerse." << endl;
            } 
            else if (subcomando == "fortificar") {
                cout << "Uso: fortificar <nombre_jugador>" << endl;
                cout << "El comando pregunta al jugador los territorios vecinos que desea seleccionar para la fortificación y la cantidad de unidades que se trasladarán de uno al otro." << endl;
            } 
            else if (subcomando == "estado_juego") {
                cout << "Uso: estado_juego" << endl;
                cout << "Presenta en pantalla un resumen de la situacion actual del juego mostrando: " << endl;
                cout << "número de jugadores, nombres y colores de cada uno, jugador con el turno actual y lista de los territorios con el color del jugador que lo controla con la cantidad de unidades que hay ubicadas en cada uno" << endl;
            } 
            else if (subcomando == "guardar") {
                cout << "Uso: guardar <nombre_archivo>" << endl;
                cout << "Guarda el estado actual del juego en un archivo de texto plano." << endl;
            } 
            else if (subcomando == "guardar_comprimido") {
                cout << "Uso: guardar_comprimido <nombre_archivo>" << endl;
                cout << "Guarda el estado actual del juego en un archivo binario comprimido (.bin)." << endl;
            } 
            else if (subcomando == "costo_conquista") {
                cout << "Uso: costo_conquista <nombre_jugador> <territorio>" << endl;
                cout << "Calcula el costo y la secuencia de territorios a conquistar para llegar al territorio objetivo dado por el usuario." << endl;
            } 
            else if (subcomando == "conquista_mas_barata") {
                cout << "Uso: conquista_mas_barata <nombre_jugador>" << endl;
                cout << "De todos los territorios posibles, calcula aquel que pueda implicar un menor número de unidades de ejército perdidas." << endl;
            } 
            else if (subcomando == "salir") {
                cout << "Uso: salir" << endl;
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

    //Implementaciones por ahcer solo muestar simulaciones de los comandos y la logica de la salida que deberia mostrar el juego en consola

  else if (comando_principal == "inicializar") {
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
            cout << "Uso incorrecto. Sintaxis: inicializar <archivo_inicio.txt o binario>" << endl;
        }
    }
    else if (comando_principal == "obtener_unidades") {
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
    else if (comando_principal == "atacar") {
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
    else if (comando_principal == "fortificar") {
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
    else if (comando_principal == "estado_juego") {
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
    else if (comando_principal == "guardar") {
        if (cantidad_palabras == 2) {
            cout << "(simulacion!!!!) Comando guardar actualizando en archivo: " << palabras_comando[1] << endl;
        } else {
            cout << "Uso incorrecto. Sintaxis: guardar <nombre_archivo>" << endl;
        }
    }
    else if (comando_principal == "guardar_comprimido") {
        if (cantidad_palabras == 2) {
            cout << "(simulacion!!!!) Comando guardar_comprimido actualizando en archivo: " << palabras_comando[1] << endl;
        } else {
            cout << "Uso incorrecto. Sintaxis: guardar_comprimido <nombre_archivo>" << endl;
        }
    }
    else if (comando_principal == "costo_conquista") {
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
    else if (comando_principal == "conquista_mas_barata") {
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
    else if (comando_principal == "salir") {
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

// Bucle principal para la consola 
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