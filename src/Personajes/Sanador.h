//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_SANADOR_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_SANADOR_H

#include "Personaje.h"
#include <cstdlib> //Para rand() y numeros aleatorios

class Sanador : public Personaje {
    private:
        //Atributos especiales del Sanador:
        int poderCuracion; // poder de curacion base.
        double efectividadCuracion;  // Variacion en la efectividad ( entre 0 y 1.0).

        // Metodo privador Auxiliar (ver razon de esto en Guerrero.h):
        int calcularCuracion( );

    public:
        Sanador( );
        Sanador( string nombre, string bando, int nivel, int vida, int defensa );
        virtual ~Sanador( ) = default;

        // Metodos sobreescritos de Personaje :

        void realizarAccion( Personaje* objetivo ) override;
        void mostrarInformacion( ) override;

       //Metodo para la IA:
        void realizarAccionIA( vector<Personaje*> aliados, vector <Personaje*> enemigos) override;

       //Para las acciones del jugador:
        bool realizarAccionJugador( vector<Personaje*> aliados, vector <Personaje*> enemigos) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_SANADOR_H