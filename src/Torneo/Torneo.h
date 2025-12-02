//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H

#include "../Guild/Guild.h" // Los puntos hacen que Guild.h suba a la cabecera (src)
//y desde ahi entra al directorio Guild.

//->Pendiente: Cuando implementemos Inventario y Arena, descomentar:
#include "../Inventario/Inventario.h" //<-Nota: Implementado (Por Angel).
#include "../Arena/Arena.h"

//Librerias:

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>  // <- Para pausas.
#include <chrono>  // <- Para medir los tiempos.


// Usings para hacer la codificacion mas fluida.
using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::endl;
using std::setprecision;
using std::fixed;
using std::unordered_map;
using std::getline;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;


class Torneo {
    private:
        string nombreTorneo;
        Guild* guildJugador;             // Guild controlada por el jugador.
        vector<Guild*> guildsEnemigas;   // Guilds enemigas (rivales).
        // Inventario global de objetos mágicos. <- Nota: Implementado (Por Angel).
        Inventario* inventario;
        // Sistema de combate.
        Arena* arena;

        // Metodos privados auxiliares para organizar el codigo:
        void mostrarGuildsRivales( );     // Muestra a las Guilds Enemigas.
        void pausar( int milisegundos );
    public:
        // Constructores y destructores:
        Torneo( );
        Torneo( string nombre );
        virtual ~Torneo( );

        // Metodos de Inicializacion:

        void inicializarTorneo( );     // Configura todo el torneo.
        void inicializarGuilds( );     // Crea la Guild del jugador y enemigas.
        void inicializarInventario( ); // Carga objetos magicos iniciales.
        void iniciarArena( );          // Inicia el sistema de combate.

        // Metodos de gestion (menus):
        void gestionarGuild( );        // Menu para administrar la Guild del jugador.
        void gestionarInventario( );   // Menu para objetos magicos.
        void menuPrincipal( );         // Menu Principal del torneo.

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H
