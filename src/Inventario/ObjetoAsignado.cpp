//
// Created by Richi on 11/18/2025.
//


#include "ObjetoAsignado.h"
#include "../Personajes/Personaje.h"
// Cuando implementes ObjetoMagico, asegúrate de que esta ruta sea correcta:
#include "ObjetoMagico.h"
// =======================
// Constructores y destructor
// =======================

ObjetoAsignado::ObjetoAsignado( ObjetoMagico* tipo ) {
    // Recibe el tipo de objeto que se está asignando al héroe.
    this -> tipoObjeto = tipo;
    this -> usado = false;   // Por defecto, el objeto recién asignado no está usado.
}

ObjetoAsignado::~ObjetoAsignado( ) {
    delete this -> tipoObjeto; //<- Se agrega esta linea, sino tenemos memory leak.
    this -> tipoObjeto = nullptr;
}

// =======================
// Métodos públicos
// =======================

void ObjetoAsignado::aplicarEfecto( Personaje* personaje ) {
    // Verifica que haya un tipo de objeto asociado.
    if( this -> tipoObjeto == nullptr ) {
        cout << "No hay ningun objeto asignado para usar." << endl;
        return;
    }

    // Verifica si el objeto ya fue consumido en este combate.
    if( this -> usado ) {
        cout << "El objeto " << this -> tipoObjeto -> getNombre( )
             << " ya fue usado en este combate y no puede reutilizarse." << endl;
        return;
    }

    // Aplica el efecto concreto (poción, amuleto, escudo, etc.).
    // La lógica específica vive en las clases hijas de ObjetoMagico.
    this -> tipoObjeto -> aplicarEfecto( personaje );

    // Después de aplicarlo se marca como usado.
    marcarUsado( );
}

void ObjetoAsignado::marcarUsado( ) {
    this -> usado = true;
}

bool ObjetoAsignado::estaUsado( ) {
    return this -> usado;
}

ObjetoMagico* ObjetoAsignado::getTipoObjeto( ) {
    return this -> tipoObjeto;
}

string ObjetoAsignado::getNombre( ) {
    if( this -> tipoObjeto != nullptr ) {
        return this -> tipoObjeto -> getNombre( );
    }
    return "Sin objeto";
}
