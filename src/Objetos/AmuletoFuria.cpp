#include <iostream>
#include <cstdlib>
#include "AmuletoFuria.h"

using std::cout;
using std::endl;

/* Reutilizamos el constructor por defecto de ObjetoMagico */
AmuletoFuria::AmuletoFuria( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Amuleto de Furia";
    this -> descripcion = "Un objeto que aumenta el ataque entre 5 - 10 puntos, este efecto dura dos turnos. El efecto puede variar de forma aleatoria";
    this -> stockDisponible = stock;

    /* Valores por defecto de Ataque Max, Min y los turnos que dura */
    this -> aumentoAtaqueMax = 10;
    this -> aumentoAtaqueMin = 5;
    this -> turnos = 2;
}

int AmuletoFuria::calcularEfecto( ) {
     /* De esta forma se calcula el numero aleatorio entre la Furia Minima y la Furia Maxima */
    return this -> aumentoAtaqueMin + rand( ) % ( this -> aumentoAtaqueMax - this -> aumentoAtaqueMin + 1 );
}

void AmuletoFuria::aplicarEfecto( Personaje* usuario, vector<Personaje*> aliados, vector<Personaje*> enemigos ) {
    //El amuleto de furia solo afecta al usuario, ignora aliados y enemigos.

    int aumento = calcularEfecto();
    int ataqueAntes = usuario->getAtaque();

    usuario-> setAtaque( ataqueAntes + aumento);

    cout << endl << "========================================" << endl;
    cout << "         AMULETO DE FURIA" << endl;
    cout << "========================================" << endl;
    cout << usuario -> getNombre( ) << " activa el Amuleto de Furia!" << endl;
    cout << "Aumento de ataque: +" << aumento << " puntos." << endl;
    cout << "Ataque: " << ataqueAntes << " -> " << usuario -> getAtaque( ) << endl;
    cout << "Duracion: " << this -> turnos << " turnos." << endl;
    cout << "========================================" << endl;

    pausar(1500);

}

void AmuletoFuria::mostrarInformacion( ) {
    cout << "===== Amuleto de Furia =====" << endl;
    cout << this -> descripcion << endl;
    cout << "Aumento de ataque minimo: " << this -> aumentoAtaqueMin << endl;
    cout << "Aumento de ataque maximo: " << this -> aumentoAtaqueMax << endl;
    cout << "Stock Disponible: " << this -> stockDisponible << endl;
    cout << "============================" << endl;
}

/* Getters y Setters */

int AmuletoFuria::getAumentoAtaqueMin( ) {
    return this -> aumentoAtaqueMin;
}

int AmuletoFuria::getAumentoAtaqueMax( ) {
    return this -> aumentoAtaqueMax;
}

int AmuletoFuria::getTurnos( ) {
    return this -> turnos;
}

void AmuletoFuria::setAumentoAtaqueMin( int valor ) { 
    /* Verificamos que no se ingrese un valor menor a 5 o mayor-igual a 10, en tal caso
       por defecto se pone en 5, tambien se verifica que el valor de aumento de ataque
       Min no sea mas grande que el valor de aumento de ataque Max */
    if( valor < 5 || valor >= 10 || valor > this -> aumentoAtaqueMax ) {
        this -> aumentoAtaqueMin = 5;
    } else {
        this -> aumentoAtaqueMin = valor;
    }
}

void AmuletoFuria::setAumentoAtaqueMax( int valor ) {
    /* Verificamos que el valor de Furia no este fuera de los rangos permitidos, 
       ni que sea igual al valor minimo de aumento de ataque, ni que sea menor que
       el valor minimo de ataque, ya que eso no tendria sentido */
    if( valor <= 5 || valor < this -> aumentoAtaqueMin || valor > 10 ) {
        this -> aumentoAtaqueMax = 10;
    } else { 
        this -> aumentoAtaqueMax = valor;
    }
}

void AmuletoFuria::setTurnos( int turnos ) {
    /* Verificamos que el valor de turnos ingresado no este fuera de los 
       limites */
    if( turnos > 2 || turnos < 0 ) {
        this -> turnos = 2;
    } else {
        this -> turnos = turnos;
    }
}