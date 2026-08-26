#ifndef CONSOLA_H
#define CONSOLA_H

#include <string>
#include <vector>

using namespace std;

class Juego; //La necesitamos porque aca tenemos una funcion que recibe el objeto como parametro

void iniciarConsola();

vector<string> separarPalabras(const string& linea);

void procesarEntrada(const vector<string>& palabras_comando, bool& ejecutando, Juego& juego);

bool esNumeroEntero(const string& cadena);

bool esNombreJugadorValido(const string& nombre);

#endif