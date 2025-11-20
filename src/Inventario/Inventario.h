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
        void consultarObjeto( string nombre );
        void actualizarStock( string nombre, int nuevoStock );
        void eliminarObjeto( string nombre );
        void asignarObjetoAPersonaje( string nombre, Personaje* personaje );
        void retirarObjetoDePersonaje( Personaje* personaje, int indice );
        ObjetoMagico* buscarObjeto( string nombre );
        int getStock( string nombre );
        int getStockTotal( );

};

#endif