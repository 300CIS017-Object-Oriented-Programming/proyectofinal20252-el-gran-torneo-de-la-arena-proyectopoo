#ifndef INVENTARIO
#define INVENTARIO


/*Realmente no hay dependencia circular en este caso, por lo que, para mantenernos dentro de lo
 * enseñado en clase, las incluyo aqui y no en el cpp.
 */
#include "../Guild/Guild.h" //<- Mejorar el encapsulamiento
#include "../Personajes/Personaje.h"
#include "../Objetos/ObjetoMagico.h"

// Agregar los objetos específicos:
#include "../Objetos/PocionVida.h"
#include "../Objetos/AmuletoFuria.h"
#include "../Objetos/EscudoBendito.h"
#include "../Objetos/PactoSangriento.h"
#include "../Objetos/CaballaLegendaria.h"
#include "../Objetos/Revivir.h"

#include <string>
#include <unordered_map>
#include <thread> // <- Para pausas.
#include <chrono> // <- Para medir los tiempos.

/* Forward Declarations */
//class ObjetoMagico;
//class Personaje; Nota (Pipe): en este caso no son necesarios, ya que no hay dependencia circular. Me corrigen.


class Guild; //<-- Para mejorar el encapsulamiento.

using std::string;
using std::unordered_map;
using std:: this_thread::sleep_for;
using std::chrono::milliseconds;

class Inventario {
    private:
        unordered_map<string, ObjetoMagico*> catalogoObjetos;

    //Metodo auxiliar para pausar el tiempo:

    // Metodo auxiliar para pausar
    void pausar( int milisegundos );
    public:
        Inventario( );
        virtual ~Inventario( );

       // Metodod de gestion, mejora la logica del encapsulamiento:
        void asignarObjetoInteractivo(Guild* guildJugador);  // Maneja toda la lógica de asignación
        void retirarObjetoInteractivo( Guild* guildJugador );  // Nuevo
        void consultarObjetoInteractivo();                      // Nuevo
        void actualizarStockInteractivo();                      // Nuevo

        void eliminarObjetoInteractivo( Guild* guildJugador, vector<Guild*> guildsEnemigas);                       // Nuevo

        void crearObjetoDesdeMenu();                            // Nuevo
        void mostrarInventarioDetallado();                      // Nuevo

        void cargarObjetosIniciales( );
        void crearObjeto( ObjetoMagico* objeto, int stockInicial );
        void listarObjetos( );
        void consultarObjeto( string objeto );
        void actualizarStock( string objeto, int nuevoStock );
        void eliminarObjeto( string objeto );
        void asignarObjetoAPersonaje( string objeto, Personaje* personaje );
        void retirarObjetoDePersonaje( Personaje* personaje, int indice );
        ObjetoMagico* buscarObjeto( string objeto );
        int getStock( string objeto );
        int getStockTotal( );

};

#endif