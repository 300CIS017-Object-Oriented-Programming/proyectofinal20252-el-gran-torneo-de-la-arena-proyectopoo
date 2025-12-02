//
// Created by felip on 17/11/2025.
//

#include "Torneo.h"
#include <fstream>

// Constructores y destructores:

Torneo::Torneo( ) { //Constructor por defecto:
    this -> nombreTorneo = "Gran Torneo de Lyrenhold";
    this -> guildJugador = nullptr;
    this-> inventario = nullptr; //Agregar Inicializacion.
    this-> arena = new Arena();
}

Torneo::Torneo( string nombre ) {
    //Constructor parametrizado:
    this -> nombreTorneo = nombre;
    this -> guildJugador = nullptr;
    this-> inventario = nullptr;//Agregar Inicializacion.
    this-> arena = new Arena();
}

Torneo::~Torneo( ) {
    // Destructor libera el espacio de memoria de todas la Guilds:
    cout << endl << "=======================================" << endl;
    cout << "Finalizando torneo: " << this -> nombreTorneo << endl;

    // Libera las Guilds enemigas:
    cout << "Liberando " << this -> guildsEnemigas.size( ) << " Guilds enemigas..." << endl;
    for( int i = 0; i < this -> guildsEnemigas.size( ); i++ ) {
        delete this->guildsEnemigas[ i ];
    }
    guildsEnemigas.clear( );

    //Libera el inventario:
    if (this->inventario != nullptr) {
        cout << "Liberando Inventario." << endl;
        delete this->inventario;
        this->inventario = nullptr;
    }

    //Libera la guild del jugador:
    if (this->guildJugador != nullptr) {
        cout << "Liberando la Guild del Jugador." << endl;
        delete this-> guildJugador;
        this->guildJugador = nullptr;
    }

    cout << "Liberando la Arena del Torneo." << endl;
    delete this -> arena;

    cout << "Torneo finalizado." << endl;
    cout << "=======================================" << endl;
}

//Metodos de inicializacion:

void Torneo::inicializarTorneo( ) {
    //Configura todo el torneo: Guilds inventario (pendiente) y arena (pendiente).
    cout << endl << "==========================================" << endl;
    cout << "   BIENVENIDO A: " << this -> nombreTorneo << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "En la ciudad de Lyrenhold, los gremios de aventureros" << endl;
    cout << "compiten por honor y gloria en el Gran Torneo de la Arena." << endl;
    cout << endl;

    //Inicializa las Guilds
    inicializarGuilds( );

    // Inicializa el inventario global
    inicializarInventario();

    cout << "El torneo esta listo para comenzar!!!!!" << endl;
    cout << "==========================================" << endl;

}

void Torneo::inicializarGuilds( ) {
    //Crea la Guild del jugador y las Guilds enemigas:
    cout << endl << "=== Inicializando Guilds ===" << endl;

    // Crea la Guild del jugador:
    guildJugador = new Guild( "Heroes de Lyrenhold" );
    guildJugador -> cargarPersonajesIniciales( );

    cout << endl << "Tu Guild ha sido creada." << endl;
    cout << "Ahora creando rivales." << endl << endl;

    // Crea 3 Guilds enemigas con personajes:
    Guild* enemiga1 = new Guild( "Mercenarios Oscuros" );
    Personaje* e1 = new Guerrero( "Dravos", "Enemigo" , 2, 140, 30,  12 );
    Personaje* e2 = new Mago( "Selene", "Enemigo", 1, 75, 40, 3 );
    enemiga1 -> agregarPersonaje( e1 );
    enemiga1 -> agregarPersonaje( e2 );
    this -> guildsEnemigas.push_back( enemiga1 );
    cout << "[1/3] Guild enemiga creada: Mercenarios Oscuros" << endl;

    Guild* enemiga2 = new Guild( "Guardianes del Caos" );
    Personaje* e3 = new Guerrero( "Korgath", "Enemigo" , 3, 160, 38,  15 );
    Personaje* e4 = new Sanador( "Miriel", "Enemigo", 2, 95, 12 );
    Personaje* e5 = new Paladin( "Shalltear", "Enemigo" , 10 , 160, 20, 50);
    Personaje* e6 = new HechiceroOscuro( "Momonga", "Enemigo" , 20 , 200, 30, 20);
    enemiga2 -> agregarPersonaje( e3 );
    enemiga2 -> agregarPersonaje( e4 );
    enemiga2 -> agregarPersonaje( e5 );
    enemiga2 -> agregarPersonaje( e6 );
    this -> guildsEnemigas.push_back( enemiga2 );
    cout << "[2/3] Guild enemiga creada: Guardianes del Caos" << endl;

    Guild* enemiga3 = new Guild( "Demonios de Aura" );
    Personaje* e7 = new Guerrero( "Linie", "Enemigo", 4, 130, 38,  25 );
    Personaje* e8 = new Guerrero( "Draht", "Enemigo", 2, 100, 28,  15 );
    Personaje* e9 = new Mago( "Lugner", "Enemigo", 5, 180, 45, 20 );
    Personaje* e10 = new Mago( "Aura", "Enemigo", 10, 250, 60, 60 );
    enemiga3 -> agregarPersonaje( e7 );
    enemiga3 -> agregarPersonaje( e8 );
    enemiga3 -> agregarPersonaje( e9 );
    enemiga3 -> agregarPersonaje( e10 );
    this -> guildsEnemigas.push_back( enemiga3 );
    cout << "[3/3] Guild enemiga creada: Demonios de Aura" << endl;
    cout << "=== Guilds inicializadas ===" << endl;
}

void Torneo::inicializarInventario() {

    cout << endl << "=== Inicializando Inventario ===" << endl;

    //Crear el inventario :
    this->inventario = new Inventario();

    //Usar el metodo de inicializacion de inventario.
    this->inventario-> cargarObjetosIniciales();

    cout << "=== Inventario inicializado ===" << endl;

}


void Torneo::iniciarArena() {

    //Verifica que haya heroes vivos antes de iniciar:

    vector<Personaje*> heroesVivos = this->guildJugador->getPersonajesVivos();

    if ( heroesVivos.empty() ) {
        cout << "No tienes heroes vivos para combatir!!!" << endl;
        return;
    }

    //Seleccionar una Guild enemiga para combatir:
    cout << endl << "=== SELECCIONAR OPONENTE ===" << endl;
    mostrarGuildsRivales();

    cout << "Seleccione la guild enemiga (1-" << this->guildsEnemigas.size() << "): " ;
    int seleccion;
    cin >> seleccion;

    if ( seleccion < 1 || seleccion > this -> guildsEnemigas.size() ) {

        cout << "Seleccion invalida." << endl;
        return;
    }

    Guild * guildEnemiga = this -> guildsEnemigas[ seleccion - 1 ];
    vector <Personaje*> enemigosVivos = guildEnemiga ->getPersonajesVivos();

    if ( enemigosVivos.empty() ) {
        cout << "La Guild " << guildEnemiga -> getNombreGuild() << " ya fue derrotada!!!!" << endl;
        return;
    }

    //Pasamos el inventario a la Arena para que pueda procesar objetos:
    this-> arena -> setInventario(this-> inventario);

    //iniciar Combate:

    this-> arena -> iniciarCombate(heroesVivos, enemigosVivos );

    //Bucle principal del combate:

    while ( this -> arena -> verificarFinCombate() ) {
        this-> arena -> ejecutarTurno();
    }

    //Mostrar Resultados:

    this -> arena -> mostrarResumenFinal();
    this -> arena -> procesarObjetosPostCombate();
}

// Metodos auxialiares privados:

void Torneo::pausar(int milisegundos) {
    sleep_for( milliseconds( milisegundos ) );
}

//Nuevos (Pipe): -->

void Torneo::mostrarGuildsRivales() {
    // Metodo simpiflicado, usando el nuevo metodo de guild.

    cout << endl << "=== GUILDS RIVALES ===" << endl;

    if (this->guildsEnemigas.empty()) {
        cout << "No hay Guilds enemigas registradas." << endl;
        return;
    }

    for (int i = 0; i < this->guildsEnemigas.size(); i++) {
        cout << endl << "Guild " << (i + 1) << ": ";
        this->guildsEnemigas[i]->mostrarDetallesGuild();
        pausar(2000);
    }

    cout << endl << "Total de Guilds Rivales: " << this->guildsEnemigas.size() << "." << endl;
}

// <--Hasta aqui


//Metodos de gestion (Menus):

void Torneo::gestionarGuild( ) {
    //Menu para gestionar la Guild del jugador :
    int opcion;
   if (this->guildJugador != nullptr) {
       do {
           cout << endl << "===========[-_-] GESTION DE GUILD [-_-]============" << endl;
           cout << "Guild: " << this -> guildJugador -> getNombreGuild( ) << endl;
           cout << "1) Listar heroes." << endl;
           cout << "2) Consultar heroe." << endl;
           cout << "3) Agregar heroe." << endl;
           cout << "4) Retirar heroe." << endl;
           cout << "5) Volver al menu principal" << endl;
           cout << "========================================" << endl;
           cout << "Seleccione una opcion: ";
           cin >> opcion;

           cin.ignore( );

           switch( opcion ) {

               case 1: {
                   //Listar todos los heroes:
                   this -> guildJugador -> listarPersonajes( );
                   break;
               }

               case 2: {
                   //Consultar un heroe especifico:
                   this->guildJugador->consultarPersonajeInteractivo();
                   break;
               }
               case 3: {
                   this->guildJugador->crearNuevoPersonaje();
                   // Agregar un nuevo heroe:
                   break;
               }
               case 4: {
                   this->guildJugador->retirarPersonajeInteractivo(this->inventario);
                   break;
               }
               case 5: {
                   cout << "Volviendo al menu principal." << endl;
                   break;
               }
               default: {
                   cout << "Opcion invalida. Intente de nuevo." << endl;
                   break;
               }
           }
       }
       while( opcion != 5 );
   }
    else {
        cout << "Error: No se ha inicializado la Guild del jugador." << endl;
    }

}

void Torneo:: menuPrincipal() {
    int opcion;

    do {
        cout << endl << "========================================" << endl;
        cout << "     " << this -> nombreTorneo << endl;
        cout << "========================================" << endl;
        cout << "1) Gestionar Guild." << endl;
        cout << "2) Gestionar inventario . " << endl;
        cout << "3) Iniciar Arena (combates)." << endl;
        cout << "4) Ver Guilds enemigas." << endl;
        cout << "5) Guardar heroes de la Guild en JSON." << endl;
        cout << "6) Cargar heroes desde JSON." << endl;
        cout << "0) Salir del torneo." << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore( );

        switch( opcion ) {
            case 1: {
                gestionarGuild( );
                break;
            }
            case 2: {
                gestionarInventario();
                break;
            }
            case 3: {
                iniciarArena();
                break;
            }
            case 4: {
                mostrarGuildsRivales( ); //<-- A esta no le vi la necesidad de encapsular.
                break;
            }
            case 5: {
                string nombreArchivo = "../src/ArchivosJson/heroes.json";
                this->guildJugador->guardarHeroesEnJSON( nombreArchivo );
                break;
            }
            case 6: {
                string nombreArchivo = "../src/ArchivosJson/heroes.json";
                this->guildJugador->cargarHeroesDesdeJSON( nombreArchivo );
                break;
            }
            case 0: {
                cout << endl << "Saliendo del Torneo..." << endl;
                cout << "¡Gracias por participar en " << this -> nombreTorneo << "!!!!!" << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. intente de nuevo."  << endl;
                break;
            }
        }

    }
    while( opcion != 0 );
}

//Metodo de gestionar inventario:

void Torneo::gestionarInventario() {
    int opcion;

    if (this->inventario != nullptr) {
        do {
            cout << endl << "=======$ GESTION DE INVENTARIO $======== " << endl;
            cout << "Stock total: " << this->inventario->getStockTotal() << " objetos." << endl;
            cout << "1) Crear objeto magico." << endl;
            cout << "2) Listar objetos disponibles." << endl;
            cout << "3) Consultar objeto especifico." << endl;
            cout << "4) Actualizar stock de objeto." << endl;
            cout << "5) Eliminar objeto (si stock = 0)." << endl;
            cout << "========== ~~~~~~~~~~~~~~~~~~~~~~~~ ======== " << endl;
            cout << "6) Asignar objeto a heroe." << endl;
            cout << "7) Retirar objeto de heroe." << endl;
            cout << "8) Ver objetos equipados por heroes." << endl;
            cout << "0) Volver al menu principal." << endl;
            cout << "========================================" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch ( opcion ) {
                case 1: {
                        this->inventario->crearObjetoDesdeMenu();
                    break;
                }
                case 2: {

                        this->inventario->mostrarInventarioDetallado();

                    break;
                }
                case 3: {
                        this->inventario->consultarObjetoInteractivo();
                    break;
                }
                case 4: {
                        this->inventario->actualizarStockInteractivo();
                    break;
                }
                case 5: {
                        this->inventario->eliminarObjetoInteractivo( this->guildJugador, this->guildsEnemigas );
                    break;
                }
                case 6: {
                        this->inventario->asignarObjetoInteractivo( this->guildJugador );
                    break;
                }
                case 7: {
                        this->inventario->retirarObjetoInteractivo( this->guildJugador );
                    break;
                }
                case 8: {
                    if (this->guildJugador != nullptr) {
                        this->guildJugador->mostrarObjetosEquipadosHeroes();
                    }
                    else {
                        cout << "Error: No hay Guild del jugador Inicializada." << endl;
                    }

                    break;
                }
                case 0: {
                    cout << "Volviendo al menu principal..." << endl;
                    break;
                }
                default: {
                    cout << "Error: opcion invalida." << endl;
                    break;
                }
            }
        }
        while ( opcion != 0 );
    }
    else {
        cout << "Error: Inventario del Torneo no ha sido inicializado." << endl;
    }
}

