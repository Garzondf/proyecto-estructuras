#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <string>
#include <vector>

// Inicia el bucle infinito de la terminal con el indicador $
void iniciarConsola();

// Funciones auxiliares para la interfaz
std::vector<std::string> separarPalabras(const std::string& linea);
void procesarEntrada(const std::vector<std::string>& palabras_comando, bool& ejecutando);

// Funciones de validacion
bool esNumeroEntero(const std::string& cadena);
bool esNombreJugadorValido(const std::string& nombre);

#endif