//
// Created by felip on 27/11/2025.
//

#include "Arena.h"
#include "../Inventario/ObjetoAsignado.h"   // <- Incluimos aqui por que algunas funciones necesitan conocer
// a ObjetoAsignado.


//Contructores y Destructores

Arena::Arena() {
    //Constructor por defecto - Inicializa el estado del combate.
    this->turnoActual = 0;
    this->objetosUsados= 0;
    this->combateActivo = false;
    this->inventario = nullptr; //Se establece del Torneo antes de iniciar el combate .
    //Los vectores de heroes y enemigos se inicializan vacios automaticamente.
}

Arena::~Arena() {
    /*Destructor - La Arena no libera memoria de los personajes ni del inventario
     *Los Personajes pértencen a las Guilds, y el Inventario pertenece al Torneo
     * Solo limpiamos las referencias locales.
     */
    this->heroes.clear();
    this->enemigos.clear();
    this->inventario = nullptr;
    cout << "Arena cerrada. Los guerreros regresan a sus Guilds." << endl;
}

//Setter del Inventario:

void Arena::setInventario( Inventario* inv) {
    this->inventario = inv;
}

//Metodos auxiliares privados:

void Arena::pausar(int milisegundos) {
    sleep_for( milliseconds( milisegundos ) );
}

Personaje *Arena::seleccionarObjetivoAleatorio(vector<Personaje*> equipo) {

    /*Selecciona aleatoriamente un personaje Vivo del equipo dado.
     * Se usa para que los enemigos elijan a quien atacar.
     */

    vector<Personaje*> vivos;

    //Primero filtramos solo los personajes vivos:
    for ( int i = 0; i < equipo.size(); i++) {
        if (equipo[i]->getIsEstaVivo()) {
            vivos.push_back(equipo[i]);
        }
    }

    //Si no hay personajes vivos, retornamos nullptr:
    if (vivos.empty()) {
        return nullptr;
    }

    //Seleccionamos uno aleatorio de los vivos:

    int indice = rand() % vivos.size();

    return vivos[indice];

}

bool Arena::isEquipoDerrotado( vector<Personaje* > equipo) {
    /*Verifica si Todos los perosnajes del equipo estan derrotados.
     * Retorna true si el equipo perdio, false si aun tiene miembros vivos.
     */

    for (int i= 0; i < equipo.size();i++) {
        if (equipo[i]->getIsEstaVivo()) {
            return false; //Esto significa que hemos encontrado al menos un miembro vivo.
        }
    }

    return true; //Significa que todos estan muertos.
}

int Arena::contarVivos(vector<Personaje*> equipo) {

    //Cuenta cuantos personajes siguen vivos en el equipo:

    int contador = 0;

    for (int i = 0; i < equipo.size(); i++) {
        if (equipo[i] -> getIsEstaVivo()) {
            contador ++;
        }
    }

    return contador;
}

void Arena::mostrarListaObjetivos(vector<Personaje*> equipo, bool soloVivos) {
    /*Muestra una lista numerada de personajes del equipo.
     * Si soloVivos es true, solo muestra los que estan vivos.
     */

    int numero = 1;
    for (int i = 0; i < equipo.size() ; i++) {
        Personaje * p = equipo[i];
        if (soloVivos && !p->getIsEstaVivo()) {
            continue; //Saltamos los muertos si solo queremso los vivos.
        }

        cout << " " << numero << ". " << p->getNombre() << " (" <<  p->getRol() << ")-";
        cout << "Vida: " << p->getVida() << "/" << p->getVidaMaxima();

        if (!p->getIsEstaVivo()) {
            cout << "[DERROTADO]";
        }

        cout << endl;
        numero++;
    }
}

void Arena::ejecutarAccionEnemigo(Personaje* enemigo) {
    /*Implementa la "IA" basica de los enemigos.
     * El comportamiento varia segun el rol del enemigo.
     * -Guerreros y magos: Atacan al heroe con menos vida.
     * -Sanadores: solo curan aliados, no atacan directamente.
     */

    if ( ! enemigo->getIsEstaVivo()) {
        return; // los muertos no actuan.
    }

    //Llamamos al metodo de IA del enemigo.

    //El enemigo ve a "this-> heroe" como sus enemigos y a "this->enemigos" como sus aliados.
    enemigo ->realizarAccionIA( this->enemigos, this->heroes);

    pausar(1000);  //  Pausa después de que el enemigo actúe

}

void Arena::mostrarMenuAcciones(Personaje * heroe) {
    //Muestra las opciones disponibles para el heroe (El jugador):

    cout << endl << "=== Turno de " << heroe->getNombre() << " (" << heroe->getRol() << ") ===" << endl;
    cout << "Vida: " << heroe->getVida() << "/" << heroe -> getVidaMaxima() << endl;
    cout << "1. Realizar accion principal (atacar/curar segun rol)." << endl;
    cout << "2. Usar objeto equipado." << endl;
    cout << "3. Ver estado del combate." << endl;
    cout << "Selecciones una opcion: ";

}

void Arena:: ejecutarAccionHeroe(Personaje* heroe) {
    //Permite al jugador elegir que hace su heroe en este turno.

    if (!heroe->getIsEstaVivo()) {
        cout << heroe->getNombre() << " esta derrotado y no puede actuar. " << endl;
        return;
    }

    int opcion = 0;
    bool accionRealizada = false;

    while (!accionRealizada ) {
        mostrarMenuAcciones(heroe);
        cin >> opcion;

        switch (opcion) {

            case 1: {
                //Accion principal segun el rol del heroe:
                string rol = heroe->getRol();

                if (rol == "Sanador") {
                    //El sanador cura aliados:
                    cout << endl << "Seleccione un aliado para curar: " << endl;
                    mostrarListaObjetivos(this->heroes, true);
                    cout << "Opcion: ";

                    int seleccion;
                    cin>> seleccion;

                    //Buscamos el aliado seleccionado (solo entre los vivos):
                    int contador = 1;

                    for (int i = 0; i < this->heroes.size(); i++) {
                        if (this->heroes[i]->getIsEstaVivo()) {
                            if ( contador == seleccion){
                                heroe -> realizarAccion(this->heroes[i]);
                                accionRealizada = true;
                                break;
                            }
                            contador ++;
                        }
                    }
                    if (!accionRealizada) {
                        cout << "Seleccion invalida. intente de nuevo.";
                    }
                }
                else {

                    //Guerrero, Mago, etc atacan enemigos:

                    cout << endl << "Seleccione un enemigo para atacar: " << endl;
                    mostrarListaObjetivos(this->enemigos, true);
                    cout << "Opcion: ";

                    int seleccion;
                    cin >>seleccion;

                    //Buscamos el enemigo seleccionado (solo entre vivos):

                    int contador = 1;
                    for (int i = 0; i < this->enemigos.size(); i++) {
                        if (this-> enemigos[i]-> getIsEstaVivo()) {
                            if (contador == seleccion) {
                                heroe->realizarAccion(this->enemigos[i]);
                                accionRealizada = true;
                                break;
                            }
                            contador++;
                        }
                    }
                    if (!accionRealizada) {
                        cout << "Seleccion invalida. intente de nuevo." << endl ;
                    }
                }
                break;
            }
            case 2: {
                //Usar objeto equipado:
                cout << endl << "Objeto equipados de " << heroe ->getNombre() << ":"<< endl;
                heroe->mostrarObjetosEquipados();

                cout << "Seleccione el slot del objeto (1 o 2), 0 para cancelar: ";
                int slot;
                cin >> slot;

                if (slot == 1 || slot == 2) {
                    //Verificamos que haya un objeto en ese slot:
                    ObjetoAsignado * objeto = heroe->getObjetoEquipado(slot-1);

                    if (objeto == nullptr) {
                        cout << "No hay objeto en ese slot." << endl;
                    }

                    else if (objeto ->estaUsado()) {
                        cout << "Ese objeto ya fue usado en este combate." << endl;
                    }
                    else {
                        //usarObjeto usa indices 0 y 1, ajustamos:
                        heroe->usarObjeto(slot-1);
                        this->objetosUsados++;
                        accionRealizada = true;
                    }
                }
                else if (slot == 0) {
                    cout << "Uso de objeto cancelado." << endl;
                    //No marcamos accion realizada, vuelve al menu.
                }
                else {
                    cout << "Slot invalido." << endl;
                }
                break;
            }
            case 3: {
                //Ver estado del combate(no consume turno):
                mostrarEstadoCombate();

                //No marcamos accion realizada, vuelve al menu.
                break;
            }
            default: {
                cout << "Opcion Invalida. Intente de nuevo." << endl;
                break;
            }
        }
    }
}

//Metodos publicos principales:

void Arena::iniciarCombate( vector <Personaje*> equipoHeroes, vector<Personaje*> equipoEnemigos) {

    //Inicializa el combate con los dos equipos.

    cout << endl;
    cout << "===============================================" << endl;
    cout << "    BIENVENIDOS A LA ARENA DE LYRENHOLD" << endl;
    cout << "===============================================" << endl;

    pausar(1000);  //  Pausa dramática

    //Guardamos las referencias al equipo:

    this->heroes = equipoHeroes;
    this->enemigos = equipoEnemigos;

    //Reiniciamos los contadores:

    this->  turnoActual = 0;
    this->  objetosUsados = 0;
    this->  combateActivo = true;

    cout << endl << "Equipo del Jugador (" << this->heroes.size() << "heroes):" << endl;
    for (int i = 0; i < this-> heroes.size(); i++) {
        cout << " -"  << this->heroes[i]->getNombre() << " (" << this->heroes[i] -> getRol() << ")" << endl;
    }

    pausar(800);  // Pausa

    cout << endl << "Equipo Enemigo (" << this->enemigos.size() << "Oponentes):" << endl;
    for (int i = 0; i < this-> enemigos.size(); i++) {
        cout << " -"  << this->enemigos[i]->getNombre() << " (" << this->enemigos[i] -> getRol() << ")" << endl;
    }

    pausar(1000);  // Pausa antes del combate

    cout << endl << "===============================================" << endl;
    cout << "          QUE COMIENCE EL COMBATE!" << endl;
    cout << "===============================================" << endl;

    pausar(1500);  //  Pausa dramática final
}

void Arena::ejecutarTurno ( ) {
    /*Ejecuta un turno completo del combate.
     *Primero actuan todos los heroes vivos, luego todos los enemigos vivos.
     */

    this->turnoActual ++ ;

    cout << endl;
    cout << "================================================" << endl;
    cout << "              TURNO " << this -> turnoActual << endl;
    cout << "================================================" << endl;


    pausar(800);  // Pausa al inicio del turno
    //-- Fase de los heroes --

    cout << endl << "--- FASE DE LOS HEROES ---" << endl;

    pausar(500);  //  Pausa breve
    for ( int i = 0; i < this->heroes.size(); i++) {
        Personaje * heroe = this->heroes[i];

        if (heroe->getIsEstaVivo()) {
            ejecutarAccionHeroe(heroe);


            //Verificamos si el combate termino despues de cada accion:

            if ( isEquipoDerrotado(this->enemigos) ) {
                cout << endl << "Todos los enemigos han sido derrotados!!!!" << endl;
                return;
            }
        }
    }

    //Fase de los enemigos:

    cout << endl << "--- FASE DE LOS ENEMIGOS ---" << endl;

    pausar(1000);  // Pausa antes de que actúen los enemigos

    for (int i = 0 ; i < this->enemigos.size() ; i++) {
        Personaje * enemigo  = this-> enemigos[i];

        if (enemigo->getIsEstaVivo() ) {
            ejecutarAccionEnemigo(enemigo);

            //Verificamos si el combate termino despues de cada accion:
            if (isEquipoDerrotado(this->heroes)) {
                cout << endl << "Todos los Heroes han caido..." << endl;
                return;
            }
        }
    }

    cout << endl << "--- Fin del Turno" << this ->turnoActual << " ---" << endl;
    pausar(600);  // Pausa al final del turno
}

bool Arena::verificarFinCombate() {
    /*Verifica si el combate debe continuar.
     * Retorna true si debe continuar, false si ya termino.
     */

    if ( isEquipoDerrotado(this->heroes) ) {
        this->combateActivo = false;
        return false;//Perdieron los heroes.
    }

    if ( isEquipoDerrotado(this->enemigos) ) {
        this->combateActivo = false;
        return false;//Perdieron los enemigos.
    }

    return true; // El combate continua.
}

void Arena::mostrarEstadoCombate() {
    //Muestra el estado actual del combate:


    cout << endl;
    cout << "================ ESTADO DEL COMBATE ================" << endl;
    cout << "Turno actual: " << this -> turnoActual << endl;
    cout << endl;

    cout << "--- HEROES (" << contarVivos(this->heroes) << " vivos) ---" << endl;

    for (int i = 0; i < this->heroes.size(); i++) {
        Personaje * h = heroes[i];
        cout << " " << h->getNombre() << " (" << h->getRol() <<") :" ;
        cout << h->getVida() << "/" << h->getVidaMaxima() << " HP ";
        if (!h -> getIsEstaVivo()) {
            cout << "[DERROTADO]";
        }
        cout << endl;
    }

    cout << "--- ENEMIGOS (" << contarVivos(this->enemigos) << " vivos) ---" << endl;

    for (int i = 0; i < this->enemigos.size(); i++) {
        Personaje * e = enemigos[i];
        cout << " " << e->getNombre() << " (" << e->getRol() <<") :" ;
        cout << e->getVida() << "/" << e->getVidaMaxima() << " HP ";
        if (!e -> getIsEstaVivo()) {
            cout << "[DERROTADO]";
        }
        cout << endl;
    }

    cout << "====================================================" << endl;
}

void Arena:: mostrarResumenFinal() {
    /* Muestra el resumen al finalizar el combate
     * Incluye: ganador, supervivientes, turnos y objetos usados:
     */

    cout << endl;
    cout << "===============================================" << endl;
    cout << "            FIN DEL COMBATE" << endl;
    cout << "===============================================" << endl;

    //Determinamos el ganador:

    pausar(1000);  //  Pausa dramática

    bool ganaronHeroes = !isEquipoDerrotado(this->heroes);

    if (ganaronHeroes) {
        cout << endl << "*** VICTORIA PARA LA GUILD DEL JUGADOR! ***" << endl;
        cout << "Motivo: Todos los oponentes han sido derrotados." << endl;
    }
    else {
        cout << endl << "*** DERROTA... LA GUILD ENEMIGA HA TRIUNFADO ***" << endl;
        cout << "Motivo: Todos los heroes han caido en combate." << endl;
    }

    pausar(800);  // Pausa

    //Heroes supervivientes:
    cout << endl << "Heroes supervivientes: " ;
    bool primero = true;
    for (int i = 0 ; i < this-> heroes.size(); i++) {
        if (this->heroes[i] -> getIsEstaVivo()) {
            if (!primero) {
                cout << ", ";
            }
            cout << this->heroes[i]->getNombre();
            primero = false;
        }
    }
    if (primero ) {
        cout << "Ninguno.";
    }

    cout << endl;

    //Estadisticas:

    cout << "Duracion del combate: " << this-> turnoActual << " turnos" << endl;
    cout << "Objetos magicos usados: " << this->objetosUsados << endl;

    cout << "===============================================" << endl;

}

void Arena::procesarObjetosPostCombate() {
    /*Procesa los objetos despues del combate.
     * Los objetos usados ya fueron marcados durante el combate.
     * Ahora debemos descontar el stock del inventario global.
     */

    cout << endl << "Procesando objetos post-combate..." << endl;

    if (this->inventario == nullptr) {
        cout << "Advertencia: No hay inventario asignado a la Arena." << endl;
        return;
    }

    //Recorremos los heroes para verificar sus objetos equipados:

    for ( int i = 0; i < this->heroes.size(); i++ ) {
        Personaje * heroe = this->heroes[i];

        //Verificamos los 2 slots de obejtos:

        for (int slot = 0; slot < 2; slot ++) {
            ObjetoAsignado* objeto = heroe -> getObjetoEquipado(slot);

            if ( objeto != nullptr && objeto -> estaUsado()) {
                //El objeto fue usado, descontamos del stock global:
                string nombreObjeto = objeto->getNombre();
                ObjetoMagico * tipoObjeto = this-> inventario->buscarObjeto(nombreObjeto);

                if (tipoObjeto != nullptr) {
                    tipoObjeto->decrementarStock();
                    cout << " -- " << nombreObjeto << " consumido (Stock restante: " <<
                        tipoObjeto->getStock() <<") " << endl;
                }
            }
        }
    }

    cout << "Total de Objetos consumidos en este combate: " << this->objetosUsados << endl;
}

//Getters:

int Arena::getTurnoActual() {
    return this->turnoActual;
}

int Arena::getObjetoUsados() {
    return this-> objetosUsados;
}

bool Arena:: isCombateActivo() {
    return this-> combateActivo;
}