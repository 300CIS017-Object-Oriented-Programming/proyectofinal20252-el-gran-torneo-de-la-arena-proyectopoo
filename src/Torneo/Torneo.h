//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H

#include "../Guild/Guild.h" // Los puntos hacen que Guild.h suba a la cabecera (src)
//y desde ahi entra al directorio Guild.

//->Pendiente: Cuando implementemos Inventario y Arena, descomentar:
//#include "../Inventario/Inventario.h"
//#include "../Arena/Arena.h"

//Librearias:

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

// Usings para hacer la codificacion mas fluida.
using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::endl;
using std::setprecision;
using std::fixed;
using std::unordered_map;
using std::cin;
using std::getline;


class Torneo {

    private:
        string nombreTorneo;
        Guild* guildJugador;// Guild controlada por el jugador.
        vector<Guild*> guildsEnemigas; //Guilds enemigas (rivales).

        //Pendiente: Cuando implementemos Inventario y Arena, descomentar:
        // Inventario * inventario; // Inventario global de objetos magicos.
        // Arena* arena //Sistema de combate.

        //Metodos privados auxiliares para organizar el codigo:
        void crearNuevoHeroe( ); // Logica para la creacion de heroes.
        void consultarHeroeTorneo( ); // Logica para la consulta.
        void retirarHeroeTorneo( ); // Logica de retiro.
        void mostrarGuildsRivales( ); //Muestra a las Guilds Enemigas.

    public:
        //Constructores y destructores:
        Torneo( );
        Torneo( string nombre );
        virtual ~Torneo( );

        // Metodos de Inicializacion:

        void inicializarTorneo( ); // Configura todo el torneo (Por alguna razon todo lo escribo aqui queda en verde)
        void inicializarGuilds( ); // Crea la Guild del jugador y enemigas.
        //Pendiente: void inicializarInventario(); // Carga objetos magicos iniciales.


        // Metodos de gestion (menus):

        void gestionarGuild( ); // Menu para administrar la Guild del jugador.
        // Pendiente: void gestionarInventario(); // Menu para objetos magicos.
        // Pendiente: void iniciarArena() // inicia el sistema de combate.

        void menuPrincipal( ); // Menu Principal del torneo.

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_TORNEO_H