//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_MAGO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_MAGO_H

#include "Personaje.h"
#include "cstdlib" // Para numero aleatorios.

class Mago : public Personaje {
    // Atributos especiales del mago:
    private:
        int poderMagico;  // Poder magico adicional para los hechizos.
        double factorIgnorarDefensa;  // Porcentaje de defensa enemiga que ignora.

        // Metodo privado auxiliar (ver motivo de esto en Guerrero.h):
        int calcularDanioMagico( );

    public:
        //Constructores y destructores:
        Mago( );
        Mago( string nombre, string bando, int nivel, int vida, int ataque, int defensa );
        virtual ~Mago( ) = default;

        // Metodos Sobre escritos (override) de Personaje:
        void realizarAccion( Personaje* objetivo ) override;
        void mostrarInformacion( ) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_MAGO_H