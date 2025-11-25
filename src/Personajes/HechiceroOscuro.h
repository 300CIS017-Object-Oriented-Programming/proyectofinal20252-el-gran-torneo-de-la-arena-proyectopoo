//
// Hechicero Oscuro - Rol adicional opcional
// Especializado en magia oscura que daña tanto a enemigos como a aliados
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HECHICEROOSCURO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HECHICEROOSCURO_H

#include "Personaje.h"
#include <cstdlib>
#include <vector>

class HechiceroOscuro : public Personaje {
private:
    // Atributos especiales del Hechicero Oscuro
    int poderOscuro;                    // Poder de magia oscura base
    double porcentajeDanioAOE;          // % del daño que se aplica como AoE (Area of Effect)
    int radioAOE;                       // Número de objetivos adicionales afectados

    // Métodos auxiliares privados
    int calcularDanioOscuro( );
    int calcularDanioColateral( int danioBase );

public:
    // Constructores y destructores
    HechiceroOscuro( );
    HechiceroOscuro( string nombre, string bando, int nivel, int vida, int ataque, int defensa );
    virtual ~HechiceroOscuro( ) = default;

    // Métodos sobrescritos de Personaje
    void realizarAccion( Personaje* objetivo ) override;
    void realizarAccionAOE( Personaje* objetivo, vector<Personaje*> objetivosAdicionales );
    void mostrarInformacion( ) override;

    // Getters
    int getPoderOscuro( );
    double getPorcentajeDanioAOE( );
    int getRadioAOE( );
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HECHICEROOSCURO_H