//
// Created by Richi on 11/20/2025.
//

#include <iostream>
#include <cstdlib>
#include "PactoSangriento.h"

using std::cout;
using std::endl;

// Constructor
PactoSangriento::PactoSangriento( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Pacto Sangriento de los Caidos";
    this -> descripcion = "Un ritual oscuro grabado en pergamino de piel humana. Sacrifica parte de tu esencia vital a cambio de un poder devastador. El dolor es el precio del poder.";
    this -> stockDisponible = stock;

    this -> aumentoAtaqueMin = 25;
    this -> aumentoAtaqueMax = 40;
    this -> porcentajeVidaSacrificada = 30; // Pierde 30% de vida maxima
}

// Metodo auxiliar privado
int PactoSangriento::calcularAumentoAtaque( ) {
    // Calcula un aumento aleatorio entre el minimo y maximo
    return this -> aumentoAtaqueMin + rand( ) % ( this -> aumentoAtaqueMax - this -> aumentoAtaqueMin + 1 );
}

// Metodo principal - aplica el efecto del objeto
void PactoSangriento::aplicarEfecto( Personaje* personaje ) {
    cout << endl << "============================================" << endl;
    cout << "  " << personaje -> getNombre( ) << " invoca el PACTO SANGRIENTO DE LOS CAIDOS!" << endl;
    cout << "============================================" << endl;

    // Calcular la vida a sacrificar (30% de vida maxima)
    int vidaASacrificar = ( personaje -> getVidaMaxima( ) * this -> porcentajeVidaSacrificada ) / 100;
    int vidaActual = personaje -> getVida( );
    int nuevaVida = vidaActual - vidaASacrificar;

    // El pacto no puede matarte, minimo quedas con 1 de vida
    if( nuevaVida <= 0 ) {
        nuevaVida = 1;
        vidaASacrificar = vidaActual - 1;
        cout << "  ¡El pacto casi consume tu alma por completo!" << endl;
    }

    // Aplicar el sacrificio de vida
    personaje -> setVida( nuevaVida );
    cout << "  Sangre derramada: -" << vidaASacrificar << " puntos de vida" << endl;
    cout << "  Vida restante: " << nuevaVida << "/" << personaje -> getVidaMaxima( ) << endl;

    // Calcular y aplicar el aumento de ataque
    int aumento = calcularAumentoAtaque( );
    int ataqueAnterior = personaje -> getAtaque( );
    personaje -> setAtaque( ataqueAnterior + aumento );

    cout << endl << "  ¡El poder oscuro fluye por tus venas!" << endl;
    cout << "  Ataque aumentado: +" << aumento << " puntos" << endl;
    cout << "  Ataque anterior: " << ataqueAnterior << " -> Ataque actual: " << personaje -> getAtaque( ) << endl;
    cout << "============================================" << endl;
}

// Muestra informacion del objeto
void PactoSangriento::mostrarInformacion( ) {
    cout << endl << "=== PACTO SANGRIENTO DE LOS CAIDOS ===" << endl;
    cout << this -> descripcion << endl;
    cout << "Aumento de ataque: " << this -> aumentoAtaqueMin << " - " << this -> aumentoAtaqueMax << " puntos" << endl;
    cout << "Vida sacrificada: " << this -> porcentajeVidaSacrificada << "% de vida maxima" << endl;
    cout << "Stock disponible: " << this -> stockDisponible << endl;
    cout << "=======================================" << endl;
}

// Getters
int PactoSangriento::getAumentoAtaqueMin( ) {
    return this -> aumentoAtaqueMin;
}

int PactoSangriento::getAumentoAtaqueMax( ) {
    return this -> aumentoAtaqueMax;
}

int PactoSangriento::getPorcentajeVidaSacrificada( ) {
    return this -> porcentajeVidaSacrificada;
}

// Setters con validacion
void PactoSangriento::setAumentoAtaqueMin( int valor ) {
    // Validacion: minimo 15, no puede ser mayor o igual al maximo
    if( valor < 15 || valor >= this -> aumentoAtaqueMax ) {
        this -> aumentoAtaqueMin = 25;
    } else {
        this -> aumentoAtaqueMin = valor;
    }
}

void PactoSangriento::setAumentoAtaqueMax( int valor ) {
    // Validacion: no puede ser menor o igual al minimo, maximo 50
    if( valor <= this -> aumentoAtaqueMin || valor > 50 ) {
        this -> aumentoAtaqueMax = 40;
    } else {
        this -> aumentoAtaqueMax = valor;
    }
}

void PactoSangriento::setPorcentajeVidaSacrificada( int porcentaje ) {
    // Validacion: entre 10% y 50%
    if( porcentaje < 10 || porcentaje > 50 ) {
        this -> porcentajeVidaSacrificada = 30;
    } else {
        this -> porcentajeVidaSacrificada = porcentaje;
    }
}