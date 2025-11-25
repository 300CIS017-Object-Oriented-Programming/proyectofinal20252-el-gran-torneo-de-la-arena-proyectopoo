//
// Paladín - Rol adicional opcional
// Especializado en ataques moderados con defensa elevada y habilidades de protección
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PALADIN_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PALADIN_H

#include "Personaje.h"
#include <cstdlib>

class Paladin : public Personaje {
    private:
        // Atributos especiales del Paladín
        int poderDivino;                    // Poder de luz divina para ataques
        double probabilidadEscudoSagrado;   // Probabilidad de bloquear completamente un ataque
        bool escudoActivado;                // Estado del escudo sagrado
        int contadorTurnos;                 // Contador para cooldown de habilidades

        // Métodos auxiliares privados
        int calcularDanioDivino( );
        bool activarEscudoSagrado( );

    public:
        // Constructores y destructores
        Paladin( );
        Paladin( string nombre, string bando, int nivel, int vida, int ataque, int defensa );
        virtual ~Paladin( ) = default;

        // Métodos sobrescritos de Personaje
        void realizarAccion( Personaje* objetivo ) override;
        void mostrarInformacion( ) override;

        // Método especial del Paladín
        void protegerAliado( Personaje* aliado );
        void bendiccionDivina( Personaje* aliado );  // Aumenta defensa temporalmente

        // Getters
        int getPoderDivino( );
        double getProbabilidadEscudoSagrado( );
        bool getEscudoActivado( );
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PALADIN_H