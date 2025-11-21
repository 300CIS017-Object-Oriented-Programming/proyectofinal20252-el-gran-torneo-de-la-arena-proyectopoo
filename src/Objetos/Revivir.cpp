#include <iostream>
#include "Revivir.h"

using std::cout;
using std::endl;

Revivir::Revivir( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Pocion de Resurrecion";
    this -> descripcion = "Un objeto que revive un compañero caido en combate. El personaje que sea revivido solo lo hara con el 50% de su vida maxima";
    this -> stockDisponible = stock;
}

void Revivir::aplicarEfecto( Personaje* usuario, Personaje* objetivo ) {
    
}