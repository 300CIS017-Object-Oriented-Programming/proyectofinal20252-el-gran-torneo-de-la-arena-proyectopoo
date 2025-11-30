//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUERRERO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUERRERO_H

#include "Personaje.h"
#include <cstdlib> // Para rand() y numero aleatorios.
#include <ctime> // Para inicializar la semilla aleatoria.


class Guerrero: public Personaje{
    private:
        // Atributo especial del Guerrero: probabilidad de golpe critico.
        double probabilidadCritico; // Este valor es un porcentaje (entre 0 y 1.0 ).


        //Metodos auxiliares para el combate( son privados ya que hacen parte de la logica interna del
        //Guerrero, se usan para hacer el ataque de este, desde afuera solo nos importa que ataque(), no como lo haga):
        bool isEsCritico( ); // Este metodo no va esta en el diagrama UML inicial, se agrego
        // para hacer mas facil la implementacion de otros metodos, no se agrega al UML inicial sino al segundo
        // que se piden en documento del proyecto.
        int calcularDanioCritico( int danioBase );

    public:
        // Constructores y destructores:
        Guerrero( );
        Guerrero( string nombre, string bando, int nivel, int vida, int ataque, int defensa );
        virtual ~Guerrero( ) = default; // Destructor por defecto, Personaje se escarga de liberar los objetos asignados.

        //Metodos sobrescritos (override) de Personaje:

        void realizarAccion( Personaje* objetivo ) override;
        void mostrarInformacion( ) override;
        void realizarAccionIA( vector<Personaje * > aliados, vector <Personaje *> enemigos) override;

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUERRERO_H