#ifndef INVENTARIO
#define INVENTARIO


/*Realmente no hay dependencia circular en este caso, por lo que, para mantenernos dentro de lo
 * enseñado en clase, las incluyo aqui y no en el cpp.
 */
#include "../Personajes/Personaje.h"
#include "../Objetos/ObjetoMagico.h"

#include <string>
#include <unordered_map>

/* Forward Declarations */
//class ObjetoMagico;
//class Personaje; Nota (Pipe): en este caso no son necesarios, ya que no hay dependencia circular. Me corrigen.

using std::string;
using std::unordered_map;

class Inventario {
    private:
        unordered_map<string, ObjetoMagico*> catalogoObjetos;
    
    public:
        Inventario( );
        virtual ~Inventario( );

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