#ifndef INVENTARIO
#define INVENTARIO

#include <string>
#include <unordered_map>

/* Forward Declarations */
class ObjetoMagico;
class Personaje;

using std::string;
using std::unordered_map;

class Inventario {
    private:
        unordered_map<string, ObjetoMagico*> catalogoObjetos;
    
    public:
        Inventario( );
        ~Inventario( );

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