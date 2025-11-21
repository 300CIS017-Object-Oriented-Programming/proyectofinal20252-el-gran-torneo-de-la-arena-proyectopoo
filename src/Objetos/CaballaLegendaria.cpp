//
// Created by Richi on 11/20/2025.
//

#include <iostream>
#include <cstdlib>
#include "CaballaLegendaria.h"

using std::cout;
using std::endl;

// Constructor
CaballaLegendaria::CaballaLegendaria( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Caballa Legendaria del Destino";
    this -> descripcion = "Un pez mistico de tiempos ancestrales. Al consumirlo, el destino decide: 50% de probabilidad de eliminar instantaneamente al enemigo, 50% de que el usuario muera en el acto. Solo los mas valientes se atreven a usarla.";
    this -> stockDisponible = stock;
    this -> probabilidadExito = 0.5;
    this -> objetivoEnemigo = nullptr;
}

// Metodo auxiliar privado
bool CaballaLegendaria::calcularExito( ) {
    // Genera numero aleatorio entre 0 y 1
    // Si es menor a 0.5 (probabilidadExito) es exito
    double random = ( double ) rand( ) / RAND_MAX;
    return random < this -> probabilidadExito;
}

// Metodo principal - aplica el efecto del objeto
void CaballaLegendaria::aplicarEfecto( Personaje* personaje ) {
    cout << endl << "============================================" << endl;
    cout << "  " << personaje -> getNombre( ) << " consume la CABALLA LEGENDARIA DEL DESTINO!" << endl;
    cout << "  El aire se congela... el destino decide..." << endl;
    cout << "============================================" << endl;

    /* Agrego Validacion: */
    if ( this->objetivoEnemigo == nullptr) {
        cout << "Error: No hay objetivo enemigo establecido." << endl;
        return;
    }

    if( calcularExito( ) ) {
        // EXITO: El enemigo muere instantaneamente
        cout << endl << "*** ¡EL DESTINO FAVORECE AL VALIENTE! ***" << endl;

        if( this -> objetivoEnemigo != nullptr && this -> objetivoEnemigo -> getIsEstaVivo( ) ) {
            cout << this -> objetivoEnemigo -> getNombre( ) << " es fulminado por el poder ancestral!" << endl;
            this -> objetivoEnemigo -> setVida( 0 );
            cout << "¡" << this -> objetivoEnemigo -> getNombre( ) << " ha sido ELIMINADO instantaneamente!" << endl;
        } else {
            cout << "No hay enemigo objetivo establecido o ya esta derrotado." << endl;
            cout << "El poder de la caballa se disipa en el viento..." << endl;
        }
    } else {
        // FRACASO: El usuario muere
        cout << endl << "*** ¡EL DESTINO ES CRUEL! ***" << endl;
        cout << "La caballa estaba maldita... " << personaje -> getNombre( ) << " cae fulminado!" << endl;
        personaje -> setVida( 0 );
        cout << "¡" << personaje -> getNombre( ) << " ha MUERTO por su propia osadia!" << endl;
    }

    cout << "============================================" << endl;
}

// Muestra informacion del objeto
void CaballaLegendaria::mostrarInformacion( ) {
    cout << endl << "=== CABALLA LEGENDARIA DEL DESTINO ===" << endl;
    cout << this -> descripcion << endl;
    cout << "Probabilidad de exito: " << ( this -> probabilidadExito * 100 ) << "%" << endl;
    cout << "Probabilidad de muerte propia: " << ( ( 1 - this -> probabilidadExito ) * 100 ) << "%" << endl;
    cout << "Stock disponible: " << this -> stockDisponible << endl;
    cout << "=======================================" << endl;
}

// Setter para establecer el enemigo objetivo antes de usar la caballa
void CaballaLegendaria::setObjetivoEnemigo( Personaje* enemigo ) {
    this -> objetivoEnemigo = enemigo;
}

// Getters
Personaje* CaballaLegendaria::getObjetivoEnemigo( ) {
    return this -> objetivoEnemigo;
}

double CaballaLegendaria::getProbabilidadExito( ) {
    return this -> probabilidadExito;
}