#include <iostream>
#include "Revivir.h"

using std::cout;
using std::endl;

Revivir::Revivir( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Pocion de Resurrecion";
    this -> descripcion = "Un objeto que revive un compañero caido en combate. El personaje que sea revivido solo lo hara con el 50% de su vida maxima";
    this -> stockDisponible = stock;

    /*Agrego inicializacion Explicita:*/
    this ->aliado =nullptr;
}

void Revivir::aplicarEfecto( Personaje* personaje ) {

    /*Verificamos que haya un aliado establecido.*/
    if (this->aliado == nullptr) {
        cout << "Error: No se ha establecido un aliado para revivir." << endl;
        return;
    }

    /* Verificamos que el aliado efectivamente este muerto */
    if( !aliado -> getIsEstaVivo( ) ) {
        cout << "¡" << personaje -> getNombre( ) << " ha decidido revivir a su compañero" << 
        this -> aliado -> getNombre( ) << endl;

        this -> aliado -> setVida( this -> aliado -> getVidaMaxima( ) / 2 );
        this -> aliado -> setEstaVivo( true );
        cout << "El personaje " << this -> aliado -> getNombre( ) << " ha sido revivido!!!" << endl;
    } else {
        cout << "El aliado seleccionado no esta muerto!!" << endl;
    }
}

void Revivir::mostrarInformacion( ) {
    cout << "==== Pocion de Resurreccion ====" << endl;
    cout << this -> descripcion << endl;
    cout << "Stock Disponible: " << this -> stockDisponible << endl;
    cout << "================================" << endl;
}

void Revivir::setAliado( Personaje* aliado ) {
    this -> aliado = aliado;
}

Personaje* Revivir::getAliado( ) {
    return this -> aliado;
}