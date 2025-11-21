#include <iostream>
#include <cstdlib>
#include "PocionVida.h"


using std::cout;
using std::endl;

/* Reutilizando el constructor por defecto de ObjetoMagico */
PocionVida::PocionVida( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Pocion de Vida";
    this -> descripcion = "Un objeto que restaura 20 - 40 puntos de vida. El efecto puede variar de forma aleatoria";
    this -> stockDisponible = stock;

    /* Valores minimos y maximo por defecto de la Pocion de Vida */
    this -> curacionMaxima = 40;
    this -> curacionMinima = 20;
}

int PocionVida::calcularEfecto( ) {
    /* De esta forma se calcula el numero aleatorio entre la curacion Minima y la curacion Maxima */
    return this -> curacionMinima + rand( ) % ( this -> curacionMaxima - this -> curacionMinima + 1 );
}

void PocionVida::aplicarEfecto( Personaje* personaje ) {
    int curacion = calcularEfecto( );

    /* Validaciono para que el personaje que use la pocion de Vida no pueda 
       tener mas vida que la maxima posible */
    if( personaje -> getVida( ) + curacion > personaje -> getVidaMaxima( ) ) {
        personaje -> setVida( personaje -> getVidaMaxima( ) );
    } else {
        personaje -> setVida( personaje -> getVida( ) + curacion );
    }
}

void PocionVida::mostrarInformacion( ) {
    cout << "==== Pocion de Vida ====" << endl;
    cout << this -> descripcion << endl;
    cout << "Curacion Minima: " << this -> curacionMinima << endl;
    cout << "Curacion Maxima: " << this -> curacionMaxima << endl;
    cout << "Stock Disponible: " << this -> stockDisponible << endl;
    cout << "========================" << endl;
}

/* Getters y Setters */

int PocionVida::getCuracionMinima( ) {
    return this -> curacionMinima;
}

int PocionVida::getCuracionMaxima( ) {
    return this -> curacionMaxima;
}

void PocionVida::setCuracionMinima( int valor ) {
    /* Validacion para que el efecto no este fuera de los rangos permitidos,
       ademas si el efecto de curacion minima es 40, entoncespor defecto se pone 
       en 20, ademas se verifica que el valor de curacion Min no sea mayor que
       el valor de curacion Max */
    if( valor < 20 || valor >= 40 || valor > this -> curacionMaxima ) {
        this -> curacionMinima = 20;
    } else {
        this -> curacionMinima = valor;
    }
}

void PocionVida::setCuracionMaxima( int valor ) {
    /* Misma validacion de antes, solo que si pone 20 como curacion maxima,
       entonces por defecto se pondra en 40, ademas si la curacion maxima es 
       menor que la curacion minima, lo cual no tiene sentido, tambien se pone
       por defecto en 40 */
    if( valor <= 20 || valor > 40 || valor < this -> curacionMinima ) {
        this -> curacionMaxima = 40;
    } else {
        this -> curacionMaxima = valor;
    }
}

