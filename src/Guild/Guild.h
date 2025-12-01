//
// Created by felip on 17/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H

#include "../Inventario/Inventario.h"
#include <fstream>  // Para ifstream y ofstream
#include "../Personajes/Personaje.h" // Los puntos hacen que Guild.h suba a la cabecera (src)
//y desde ahi entra al directorio Personajes.

# include "../Personajes/Guerrero.h"
# include "../Personajes/Mago.h"
# include "../Personajes/Sanador.h"
# include "../Personajes/Paladin.h"
# include "../Personajes/HechiceroOscuro.h"

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

class Inventario;

class Guild {
    private:
        string nombreGuild;
        //unordered_map permite busqueda rapida por nombre (Clave-valor).
        // La clave es el nombre del personaje, el valor es el puntero al personaje.
        unordered_map<string, Personaje*> personajes;
        /* Mapa para guardar los personajes que han ido muriendo en la batalla */
        unordered_map<string, Personaje*> muertos;

    public:
        //Contructores y destructores:
        Guild( );
        Guild( string nombre );
        virtual ~Guild( );

        //Metodos:
        // Métodos de gestion delegada (mejora de encapsulamiento para depesjar el cpp de Torneo):

        void crearNuevoPersonaje();  // Maneja toda la logica de creacion
        void consultarPersonajeInteractivo();  // Maneja la consulta con interaccion
        void retirarPersonajeInteractivo(Inventario* inventario);  // Maneja el retiro con devolucion de objetos
        void mostrarDetallesGuild();  // Muestra informacion completa de la guild
        void mostrarObjetosEquipadosHeroes();

        // Metodos para controlar los personajes:

        void cargarPersonajesIniciales( ); // Carga heroes predeterminados.
        void agregarPersonaje( Personaje* personajes ); // Añade un nuevo personaje.
        void matarPersonaje( Personaje* personaje ); // Para agregar los personajes que vayan muriendo al map de muertos.
        void consultarPersonaje( string nombre ); // Muestra informacion de los personajes.
        void listarPersonajes( ); // Lista a todos los personajes.
        void retirarPersonaje( string nombre ); // Elimina un personaje.
        Personaje* buscarPersonaje( string nombre ); // Busca y retorna un personaje.

      // Persistencia JSON
         void guardarHeroesEnJSON( const string& nombreArchivo );
         void cargarHeroesDesdeJSON( const string& nombreArchivo );

        //Metodos auxiliares (metodos necesarios para la implementacion del codigo):

        vector<Personaje*> getPersonajesVivos( ); // Retorna solo personajes vivos.
        vector<Personaje*> getPersonajesMuertos( ); //Retorna solo Personajes Muertos.
        int getCantidadPersonajes( ); // Cuenta el total de personajes.

        // Gets:
        string getNombreGuild( );

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_GUILD_H