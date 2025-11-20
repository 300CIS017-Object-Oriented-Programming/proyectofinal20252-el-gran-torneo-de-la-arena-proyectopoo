#ifndef OBJETO_MAGICO
#define OBJETO_MAGICO

#include <string>

class Personaje; //Hacemos un forward declaration aqui para manjar la dependencia circular.

using std::string;

class ObjetoMagico {
    protected: 
        string nombre;
        string descripcion;
        int    stockDisponible;
    public:
        ObjetoMagico( );
        ObjetoMagico( string nombre, string descripcion, int stockDisponible ); 
        virtual void aplicarEfecto( Personaje* personaje ) = 0; /*Igualamos a 0 ya que el comportamiento lo definen
                                                                las clases hijas.  */
        virtual void mostrarInformacion( ) = 0; /*Igualamos a 0 ya que el comportamiento lo definen
                                                las clases hijas.  */
        void decrementarStock( );
        void incrementarStock( );
        
        // Getters.
        string getNombre( );
        string getDescription( );
        int getStock( );

        // Destrcuctor.
        virtual ~ObjetoMagico( ) = default;/*ya que la clase ObjetoMagico no tiene memoria dinamica
        propia ni punteros que liberar.  */
};

#endif