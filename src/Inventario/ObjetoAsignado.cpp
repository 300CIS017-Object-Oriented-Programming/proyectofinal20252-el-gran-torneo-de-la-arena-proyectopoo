//
// Created by Richi on 11/18/2025.
//


#include "ObjetoAsignado.h"
#include "../Personajes/Personaje.h"
// Cuando implementes ObjetoMagico, asegúrate de que esta ruta sea correcta:
#include "../Objetos/ObjetoMagico.h"
// =======================
// Constructores y destructor
// =======================

ObjetoAsignado::ObjetoAsignado( ObjetoMagico* tipo ) {
    // Recibe el tipo de objeto que se está asignando al héroe.
    this -> tipoObjeto = tipo;
    this -> usado = false;   // Por defecto, el objeto recién asignado no está usado.

    //Inicializar atributos de efectos temporales.
    this-> personajeAfectado = nullptr;
    this-> turnosRestantes = 0;
    this-> ultimoAumento = 0;  // ← Nuevo
}

ObjetoAsignado::~ObjetoAsignado( ) {
    // delete this -> tipoObjeto; //<- Se agrega esta linea, sino tenemos memory leak.
    /*Nota: El delete no es necesario, ObjetoAsignado es un puntero a objeto magico, pero no es su dueño.
    El dueño de ObjetoMagico es Inventario, por eso basta con hacer el puntero a ObjetoMagico nulo. (Pipe)*/
    this -> tipoObjeto = nullptr;
}

//Gets:
string ObjetoAsignado::getNombre( ) {
    if( this -> tipoObjeto != nullptr ) {
        return this -> tipoObjeto -> getNombre( );
    }
    return "Sin objeto";
}

// Nuevo: getter y setter
int ObjetoAsignado::getUltimoAumento() {
    return this->ultimoAumento;
}

//Setters: setter
void ObjetoAsignado::setUltimoAumento(int aumento) {
    this->ultimoAumento = aumento;
}
// =======================
// Métodos públicos
// =======================

void ObjetoAsignado::aplicarEfecto( Personaje* usuario, vector<Personaje*> aliados, vector<Personaje*> enemigos ) {
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
    // Cada objeto decide que hacer con los vectores de aliados y enemigos.


    this -> tipoObjeto -> aplicarEfecto( usuario, aliados, enemigos, this );

    //Verificar si el objeto tiene efecto temporal y registrarlo:
    int turnos = this->tipoObjeto->getTurnosEfecto();
    if ( turnos > 0 ) {
        this->personajeAfectado = usuario;
        this->turnosRestantes = turnos;
    }

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

void ObjetoAsignado::procesarFinTurno() {
    //Procesa el efecto temporal al final del turno:

    if (this-> turnosRestantes <= 0) {
        return; //No hay efecto temporal activo.
    }

    //Decrementar turnos restantes.

    this->turnosRestantes--;

    if ( this->turnosRestantes <= 0 ) {
        //El efecto ha expirado, el objeto se encarga de revertirse.
        if ( this->personajeAfectado != nullptr  && this-> personajeAfectado-> getIsEstaVivo() ) {
            this->tipoObjeto ->revertirEfecto( this->personajeAfectado, this);
        }
        this->personajeAfectado = nullptr;
    }

    else {
        //El efecto sigue activo, mostrar turnos restantes:
        if (this -> personajeAfectado != nullptr) {
            cout << " >> [" << this->getNombre() << "] en " << this->personajeAfectado->getNombre()
            << ": " << this-> turnosRestantes << " turno(s) restnate(s)." << endl;
        }
    }
}

bool ObjetoAsignado::tieneEfectoActivo() {
    return this-> turnosRestantes > 0; //Envia true si lo cumple, false si no.
}

int ObjetoAsignado::getTurnosRestantes() {
    return this->turnosRestantes;
}