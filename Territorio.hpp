#include "Territorio.h"
#include "Jugador.h"

using namespace std;

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