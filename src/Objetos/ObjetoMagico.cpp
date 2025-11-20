#include "ObjetoMagico.h"
//<- No es necesario incluir Personaje.h aqui ya que no hay una implementacion que requiera a personaje.


ObjetoMagico::ObjetoMagico( ) {
    this -> nombre = "Sin nombre";
    this -> descripcion = "Sin descripcion";
    this -> stockDisponible = 0;
}

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