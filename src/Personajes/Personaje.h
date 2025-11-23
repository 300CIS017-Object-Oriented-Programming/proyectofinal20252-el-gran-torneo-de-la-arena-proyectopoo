//
// Created by felip on 13/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H

//Librerias:
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>



//Declaracion adelantada sirve para evitar tener que implementar la clase objetos magicos por el momento.
//Cuando implementemos la clase ObjetoMagico esta clase lo necesitara, Entonces borraremos o comentaremos esta
//declaracion adelantada y descomentaremos el include .h.
class ObjetoAsignado;
// Usings para hacer la codificacion mas fluida.

using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::endl;
using std::setprecision;
using std::fixed;


class Personaje {

    protected:

        //Atributos basicos del personaje:
        string nombre;
        string rol;
        string bando;

        //Atributos para el combate:
        int nivel;
        int vida;
        int vidaMaxima; //Es el valor de vida maxima con la que empieza el personaje.
        // Se inicializa al igual que la vida.
        int ataque;
        int defensa;

        //Estados y obejtos magicos asignados:
        vector<ObjetoAsignado*> objetosEquipados;
        bool isEstaVivo; // True mientrar vida > 0.
        
    public:

        //Contructores y Destructores:
        Personaje( );
        Personaje( string nombre, string rol, string bando, int nivel, int vida, int ataque, int defensa );
        virtual ~Personaje( ); //Virtual por que de la clase Personaje manerja otros objetos de
        //Otra clases.
        
        //Gets:
        string getNombre( );
        string getRol( );
        string getBando( );
        int getVida( );
        int getVidaMaxima( );
        int getAtaque( );
        int getDefensa( );
        int getNivel( );
        bool getIsEstaVivo( );

        // Sets - solo ponemos sets de los atributos que queremos modificar (la de los objetos magicos) :
        void setVida( int vida );
        void setAtaque( int ataque );
        void setDefensa( int defensa );
        /* Agregado para cuando sea revivido */
        void setEstaVivo( bool );


        //Metodos abstractos que cuya definicion recae en las clases hijas:
        virtual void realizarAccion( Personaje* objetivo ) = 0;
        virtual void mostrarInformacion( ) = 0;

        //Metodos de combate, comunes a todos los personajes:
        void recibirDanio( int danio );//Reduce vida y verifica si muere.
        void equiparObjeto( ObjetoAsignado* objeto ); // Agrega objeto si hay espacio.
        void usarObjeto( int indice ); // Usa el objeto en la posicion indicada.
        void retirarObjeto( int indice ); //Quita un objeto equipado.
        bool isPuedeEquiparObjeto( );// Verificamos si tiene espacio. (en este caso un maximo de dos).
        ObjetoAsignado* getObjetoEquipado( int indice ); //Objeto el objeto en la posicion (indice).

        /*Metodo Para mostrar la informacion de los objetos equipado por el personaje. (Pipe)*/
        void mostrarObjetosEquipados();


};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H