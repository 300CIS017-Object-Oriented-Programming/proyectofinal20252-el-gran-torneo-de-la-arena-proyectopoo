#ifndef OBJETO_MAGICO
#define OBJETO_MAGICO

#include "../Inventario/ObjetoAsignado.h"

#include <string>
#include <vector>
#include <thread> // <- Para pausas.
#include <chrono> // <- Para medir los tiempos.




class Personaje; //Hacemos un forward declaration aqui para manjar la dependencia circular.
class ObjetoAsignado; // Forward declaration para evitar dependencia circular

using std::string;
using std::vector;
using std:: this_thread::sleep_for;
using std::chrono::milliseconds;

class ObjetoMagico {
    protected: 
        string nombre;
        string descripcion;
        int    stockDisponible;

       //Metodos auxiliares:
       void pausar(int milisegundos);
    public:
        ObjetoMagico( );
        ObjetoMagico( string nombre, string descripcion, int stockDisponible ); 
        virtual void aplicarEfecto( Personaje* usuario,
        vector<Personaje*> aliados, vector<Personaje*> enemigos, ObjetoAsignado* instancia ) = 0;
        /*Igualamos a 0 ya que el comportamiento lo definen
        las clases hijas.  */
        virtual void mostrarInformacion( ) = 0; /*Igualamos a 0 ya que el comportamiento lo definen
                                                las clases hijas.  */
        //Metodos para efectos temporales ( los objetos con efecto temporal lo sobreescriben).
        virtual int getTurnosEfecto();
        virtual void revertirEfecto( Personaje* personaje, ObjetoAsignado* instancia);

        void decrementarStock( );
        void incrementarStock( );
        // Getters.
        string getNombre( );
        string getDescription( );
        int getStock( );
        /* Se agrega Set Stock para manejarlo de manera mas eficiente en Inventario */
        void setStock( int stock );

        // Destrcuctor.
        virtual ~ObjetoMagico( ) = default;/*ya que la clase ObjetoMagico no tiene memoria dinamica
        propia ni punteros que liberar.  */
};

#endif