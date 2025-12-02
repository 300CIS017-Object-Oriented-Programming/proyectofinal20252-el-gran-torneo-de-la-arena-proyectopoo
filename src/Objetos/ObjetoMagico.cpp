#include "ObjetoMagico.h"

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

//Metodos virtuales:

int ObjetoMagico:: getTurnosEfecto( ) {
    //Por defecto, los objetos no tienen efecto temporal.
    return 0;
}

void ObjetoMagico::revertirEfecto( Personaje * personaje, ObjetoAsignado* instancia ){
    //Por defect, los objetos no tienen efecto que revertir.
    //Las clases hijas con efectos temporales sobreescriben este metodo.
}

//Metodos auxiliares:

void ObjetoMagico::pausar(int milisegundos) {
    sleep_for( milliseconds( milisegundos ) );
}


void ObjetoMagico::decrementarStock( ) {
    //Solo decrementar si hau StockDisponible
    if ( this-> stockDisponible >0) {
        this -> stockDisponible--;
    }
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

void ObjetoMagico::setStock( int stock ) {
    this -> stockDisponible = stock;
}