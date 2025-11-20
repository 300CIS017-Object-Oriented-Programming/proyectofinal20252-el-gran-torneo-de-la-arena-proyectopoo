#include "ObjetoMagico.h"

ObjetoMagico::ObjetoMagico( string nombre, string descripcion, int stockDisponible ) {
    this -> nombre = nombre;
    this -> descripcion = descripcion;
    this -> stockDisponible = stockDisponible;
}

void ObjetoMagico::decrementarStock( ) {
    this -> stockDisponible--;
}

void ObjetoMagico::incrementarStock( ) {
    this -> stockDisponible++;
}

string ObjetoMagico::getNombre( ) {
    return this -> nombre;
}

string ObjetoMagico::getDescription( ) {
    return this -> descripcion;
}

int ObjetoMagico::getStock( ) {
    return this -> stockDisponible;
}