//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H

#include "../Personajes/Personaje.h" // Los puntos hacen que Guild.h suba a la cabecera (src)
//y desde ahi entra al directorio Personajes.

# include "../Personajes/Guerrero.h"
# include "../Personajes/Mago.h"
# include "../Personajes/Sanador.h"

//Librerias:
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <iomanip>

// Usings para hacer la codificacion mas fluida.
using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::endl;
using std::setprecision;
using std::fixed;
using std::unordered_map;
using std::pair;


class Guild {
    private:
        string nombreGuild;
        //unordered_map permite busqueda rapida por nombre (Clave-valor).
        // La clave es el nombre del personaje, el valor es el puntero al personaje.
        unordered_map<string, Personaje*> personajes;

    public:
        //Contructores y destructores:
        Guild( );
        Guild( string nombre );
        virtual ~Guild( );

        // Metodos para controlar los personajes:

        void cargarPersonajesIniciales( ); // Carga heroes predeterminados.
        void agregarPersonaje( Personaje* personajes ); // Añade un nuevo personaje.
        void consultarPersonaje( string nombre ); // Muestra informacion de los personajes.
        void listarPersonajes( ); // Lista a todos los personajes.
        void retirarPersonaje( string nombre ); // Elimina un personaje.
        Personaje* buscarPersonaje( string nombre ); // Busca y retorna un personaje.

        //Metodos auxiliares (metodos necesarios para la implementacion del codigo):

        vector<Personaje*> getPersonajesVivos( );// Retorna solo personajes vivos.
        int getCantidadPersonajes( ); // Cuenta el total de personajes.

        // Gets:
        string getNombreGuild( );

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H