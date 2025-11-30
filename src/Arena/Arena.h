//
// Created by felip on 27/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_ARENA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_ARENA_H
//Otras clase:
#include "../Guild/Guild.h"
#include "../Inventario/Inventario.h"
#include "../Personajes/Personaje.h"

#include <vector>
#include<iostream>
#include<string>
#include <thread> // <- Para pausas.
#include <chrono> // <- Para medir los tiempos.
#include<cstdlib>
#include<ctime> //Para rand() y numero aleatoriosen la "IA" del enemigo.


//Using para hacer la codificacion mas fluida

using std::cout;
using std::cin;
using std:: endl;
using std::vector;
using std:: string;
using std:: this_thread::sleep_for;
using std::chrono::milliseconds;

class Arena {
private:
    /*Vectores que almacena los personajes de cada equipo durante el combate.
    Se copian desde la Guilds al iniciar el combate.*/

    vector <Personaje*> heroes;
    vector <Personaje*> enemigos;

    /* Puntero al Inventario global del torneo.
     * La Arena no es dueña del inventario, solo lo usa para gestionar obejetos.
     */

    Inventario * inventario;

    //Control del estado del combate:

    int turnoActual; //Contador de turnos transcurridos.
    int objetosUsados; // Contador de objetos magicos utilizados.
    bool combateActivo; // True mientras el combate este en curso.

    //Metodos auxiliares privados para organizar la logica del combate:

    //Selecciona un objetivo aleatorio del equipo contrario que este vivo:
    Personaje* seleccionarObjetivoAleatorio( vector<Personaje*> equipo);

    //Determinar la accion que realizara un enemigo ( "IA" basica):
    //El comportamiento varia segun el rol del enemigo.
    void ejecutarAccionEnemigo(Personaje* enemigo);

    //Permite al jugador elegir la accion de un heroe.
    void ejecutarAccionHeroe( Personaje* heroe);

    //Muestra el menu de acciones disponibles para un heroe:
    void mostrarMenuAcciones(Personaje * );

    //Verifica que el equipo completo ha sido derrotado:
    bool isEquipoDerrotado( vector <Personaje*> equipo);

    //Cuenta los personajes vivos en un equipo:
    int contarVivos( vector<Personaje*> equipo);

    // Muestra una lista de personajes de un equipo (para seleccion de objetivo).
    void mostrarListaObjetivos( vector<Personaje*> equipo, bool soloVivos);

    /*Metodo que permite pausar el combate temporalmente.
     *(Para darle al jugador tiempo de ver los cambios en el juego.)*/

    void pausar(int millisegundos);

    //Para procesar efectos temporales:
    void procesarEfectosTemporales();

public:
//Contrustores y Destructores:
    Arena();
    virtual ~Arena();

    //Setters para el inventario (se establece desde el Torneo antes de iniciar combate:
    void setInventario( Inventario* inv);

    //Metodos principales del sistema de combate:

    /* Inicializa el combate por equipos de heroes y enemigos.
     * Recibe los vectores de personajes de cada Guild.
     */
    void iniciarCombate( vector <Personaje*> heroes, vector<Personaje*> enemigos);

    //Ejecuta un turno completo: Primero actuan los heroes luego los enemigos:
    void ejecutarTurno();

    /*Verifica si el combate ha terminado (un equiposin personajes vivos):
     *Retorna True sie le combate debe continuar, false si termino.
    */
    bool verificarFinCombate();

    //Muestra el estado actual del combate (vida de todos los personajes).
    void mostrarEstadoCombate();

    //Muestra el resumen final del combate (vida de todos los personajes):
    void mostrarResumenFinal();

    /* Procesa los objetos despues del combate:
     * Los objetos usados se eliminar del inventario global
     */
    void procesarObjetosPostCombate();

    //Getter:
    int getTurnoActual();
    int getObjetoUsados();
    bool isCombateActivo();



};




#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_ARENA_H