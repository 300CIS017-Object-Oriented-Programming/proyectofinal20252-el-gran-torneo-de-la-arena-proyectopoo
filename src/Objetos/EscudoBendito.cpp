#include <cstdlib>
#include "EscudoBendito.h"

/* Reutilizamos el constructor por defecto de ObjetoMagico */
EscudoBendito::EscudoBendito( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Escudo Bendito";
    this -> descripcion = "Un objeto que aumenta la defensa entre 10 - 20 puntos, este efecto dura un turno. El efecto puede variar de forma aleatoria";
    this -> stockDisponible = stock;

    /* Valores por defecto de Defensa Max, Min y los turnos que dura */
    this -> aumentoDefensaMin = 10;
    this -> aumentoDefensaMax = 20;
    this -> turnos = 1;
}

int EscudoBendito::calcularEfecto( ) {
    return this -> aumentoDefensaMin + rand( ) % ( this -> aumentoDefensaMax - this -> aumentoDefensaMin + 1 );
}

void EscudoBendito::aplicarEfecto( Personaje* usuario, vector <Personaje*> aliados, vector<Personaje*> enemigos ) {

   //El escudo bendito solo afecta al usuario, ignora a aliados y enemigos.

    int aumento = calcularEfecto();
    int defensaAntes = usuario->getDefensa();

    usuario -> setDefensa( defensaAntes + aumento);

    cout << endl << "========================================" << endl;
    cout << "         ESCUDO BENDITO" << endl;
    cout << "========================================" << endl;
    cout << usuario -> getNombre( ) << " activa el Escudo Bendito!" << endl;
    cout << "Aumento de defensa: +" << aumento << " puntos." << endl;
    cout << "Defensa: " << defensaAntes << " -> " << usuario -> getDefensa( ) << endl;
    cout << "Duracion: " << this -> turnos << " turno(s)." << endl;
    cout << "========================================" << endl;

    pausar(1500);

}

void EscudoBendito::mostrarInformacion( ) {
    cout << "===== Escudo Bendito =====" << endl;
    cout << this -> descripcion << endl;
    cout << "Aumento de Defensa Min: " << this -> aumentoDefensaMin << endl;
    cout << "Aumento de Defensa Max: " << this -> aumentoDefensaMax << endl;
    cout << "Stock Disponible: " << this -> stockDisponible << endl;
    cout << "==========================" << endl;
}

/* Getters y Setters */

int EscudoBendito::getAumentoDefensaMin( ) {
    return this -> aumentoDefensaMin;
}

int EscudoBendito::getAumentoDefensaMax( ) {
    return this -> aumentoDefensaMax;
}

int EscudoBendito::getTurnos( ) {
    return this -> turnos;
}

void EscudoBendito::setDefensaMin( int valor ) { 
    /* Verificamos que no se ingrese un valor menor a 10 o mayor-igual a 20, en tal caso
       por defecto se pone en 10, tambien se verifica que el valor de aumento de defensa
       Min no sea mas grande que el valor de aumento de defensa Max */
    if( valor < 10 || valor >= 20 || valor > this -> aumentoDefensaMax ) {
        this -> aumentoDefensaMin = 10;
    } else {
        this -> aumentoDefensaMin = valor;
    }
}

void EscudoBendito::setDefensaMax( int valor ) {
    /* Verificamos que el valor de Defensa no este fuera de los rangos permitidos, 
       ni que sea igual al valor minimo de aumento de defensa, ni que sea menor que
       el valor minimo de defensa, ya que eso no tendria sentido */
    if( valor <= 10 || valor < this -> aumentoDefensaMin || valor > 20 ) {
        this -> aumentoDefensaMax = 20;
    } else { 
        this -> aumentoDefensaMax = valor;
    }
}

void EscudoBendito::setTurnos( int turnos ) {
    /* Verificamos que el valor de turnos ingresado no este fuera de los 
       limites */
    if( turnos > 1 || turnos < 0 ) {
        this -> turnos = 1;
    } else {
        this -> turnos = turnos;
    }
}