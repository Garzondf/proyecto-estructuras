#include "Territorio.h"
#include "Jugador.h"

using namespace std;

Territorio::Territorio(const string& nombre, const string& codigo, const string& continente, Jugador* dueño, int unidades) {
    this->nombre = nombre;
    this->codigo = codigo;
    this->continente = continente;
    this->dueño = dueño;
    this->unidades = unidades;
}

void Territorio::AgregarUnidades(int cantidad) { 
    unidades += cantidad; 
}

void Territorio::EliminarUnidades(int cantidad) { 
    unidades -= cantidad; 
}

void Territorio::CambiarDueño(Jugador* nuevoDueño) { 
    dueño = nuevoDueño; 
}

const string& Territorio::ObtenerNombre() const { 
    return nombre; 
}

const string& Territorio::ObtenerContinente() const { 
    return continente; 
}

const string& Territorio::ObtenerCodigo() const { 
    return codigo; 
}

int Territorio::ObtenerUnidades() const { 
    return unidades; 
}

Jugador* Territorio::ObtenerDueño() const { 
    return dueño; 
}

const list<Territorio*>& Territorio::ObtenerVecinos() const { 
    return territoriosAdyacentes; 
}

void Territorio::AgregarVecino(Territorio* vecino) {
        // Verificamos que el vecino no se agregue dos veces (opcional pero seguro)
    for (Territorio* t : territoriosAdyacentes) {
        if (t->ObtenerCodigo() == vecino->ObtenerCodigo()) {
            return; 
        }
    }
    territoriosAdyacentes.push_back(vecino);
}

bool Territorio::VerificarVecino(Territorio* vecino) const {
    for (Territorio* t : territoriosAdyacentes) {
        if (t->ObtenerCodigo() == vecino->ObtenerCodigo()) {
            return true;
        }
    }
    return false;
}

void Territorio::AgregarUnidades(int cantidad) {
    this->unidades += cantidad;
}

void Territorio::EliminarUnidades(int cantidad) {
    this->unidades -= cantidad;
    if (this->unidades < 0) {
        this->unidades = 0;
    }
}

void Territorio::CambiarDueño(Jugador* nuevoDueño) {
    this->dueño = nuevoDueño;
}

const list<Territorio*>& Territorio::ObtenerTerritoriosAdyacentes() const {
    return territoriosAdyacentes;
}

int Territorio::ObtenerUnidades() const {
    return unidades;
}

Jugador* Territorio::ObtenerDueño() const {
    return dueño;
}

const string& Territorio::ObtenerContinente() const {
    return continente;
}

const string& Territorio::ObtenerCodigo() const {
    return codigo;
}

const string& Territorio::ObtenerNombre() const {
    return nombre;
}