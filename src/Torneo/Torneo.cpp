//
// Created by felip on 17/11/2025.
//

#include "Torneo.h"

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
        cout << "Liberando Inventario...." << endl;
        delete this->inventario;
        this->inventario = nullptr;
    }

    //Libera la guild del jugador:
    if (this->guildJugador != nullptr) {
        cout << "Liberando la Guild del Jugador....." << endl;
        delete this-> guildJugador;
        this->guildJugador = nullptr;
    }

    cout << "Liberando la Arena del Torneo....." << endl;
    delete this -> arena;

    cout << "Torneo finalizado." << endl;
    cout << "=======================================" << endl;
}

//Metodos de inicializacion:

void Torneo::inicializarTorneo( ) {
    //Configura todo el torneo: Guilds inventario (pendiente) y arena (pendiente).
    // Nota: creo que cuando coloco, "Configura todo" automaticamente pone todas las letras en verde (ya lo confirme).
    cout << endl << "==========================================" << endl;
    cout << "   BIENVENIDO A: " << this -> nombreTorneo << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "En la ciudad de Lyrenhold, los gremios de aventureros" << endl;
    cout << "compiten por honor y gloria en el Gran Torneo de la Arena." << endl;
    cout << endl;

    //Inicializa las Guilds
    inicializarGuilds( );

    // Pendiente (Realizado): Inicializa la Guilds.
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
    cout << "Ahora creando rivales..." << endl << endl;

    // Crea 2 Guilds enemigas con personajes:
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
    enemiga2 -> agregarPersonaje( e3 );
    enemiga2 -> agregarPersonaje( e4 );
    this -> guildsEnemigas.push_back( enemiga2 );
    cout << "[2/3] Guild enemiga creada: Guardianes del Caos" << endl;

    Guild* enemiga3 = new Guild( "Demonios de Aura" );
    Personaje* e5 = new Guerrero( "Linie", "Enemigo", 4, 130, 38,  25 );
    Personaje* e6 = new Guerrero( "Draht", "Enemigo", 2, 100, 28,  15 );
    Personaje* e7 = new Mago( "Lugner", "Enemigo", 5, 180, 45, 20 );
    Personaje* e8 = new Mago( "Aura", "Enemigo", 10, 250, 60, 60 );
    enemiga3 -> agregarPersonaje( e5 );
    enemiga3 -> agregarPersonaje( e6 );
    enemiga3 -> agregarPersonaje( e7 );
    enemiga3 -> agregarPersonaje( e8 );
    this -> guildsEnemigas.push_back( enemiga3 );
    cout << "[3/3] Guild enemiga creada: Demonios de Aura" << endl;
    cout << "=== Guilds inicializadas ===" << endl;
}

void Torneo::inicializarInventario() {

    cout << endl << "=== Inicializando Inventario ===" << endl;

    //Crear el inventario :
    this->inventario = new Inventario();

    //Usar el metodo de inicializacion de inventario. <- Pendiente de implementar:
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

void Torneo::crearNuevoHeroe( ) {
    // Metodo auxiliar que encapsula toda la logica de creacion de heroes.
    // Hace que el menu de gestionarGuild sea mas limpio.

    string nombre;
    int tipoRol, nivel, vida, ataque, defensa;
    cout << endl << "=== Crear nuevo heroe ===" << endl;
    cout << "Nombre: " ;
    getline( cin, nombre );

    //Verificamos que el nombre no este vacio
    if( nombre.empty( ) ) {
        cout << "Error: el nombre no puede esta vacio." << endl;
        return;
    }

    //Verificamos que no exista ya un heroe con ese nombre:

    if( guildJugador -> buscarPersonaje( nombre ) != nullptr ) {
        cout << "Error: ya existe un heroe llamado " << nombre << "." << endl;
        return;
    }

    cout << "Tipo de rol:" << endl;
    cout << "1. Guerrero." << endl;
    cout << "2. Mago." << endl;
    cout << "3. Sanador" << endl;
    cout << "4. Paladin" << endl;
    cout << "5. Hechicero Oscuro" << endl;
    cout << "Seleccione: ";
    cin >> tipoRol;

    // Crea el personaje segun el tipo Seleccionado
    Personaje* nuevoHeroe = nullptr;

    switch( tipoRol ) {

        case 1: {
            //Guerrero:
            cout << "Nivel: ";
            cin >> nivel;

            cout <<  "Vida: ";
            cin >> vida;

            cout << "Ataque: ";
            cin >> ataque;

            cout << "Defensa: ";
            cin >> defensa;


            nuevoHeroe = new Guerrero ( nombre, "Jugador", nivel, vida , ataque, defensa );
            break;
        }
        case 2: {
            //Mago;
            cout << "Nivel: ";
            cin >> nivel;

            cout <<  "Vida: ";
            cin >> vida;

            cout << "Ataque: ";
            cin >> ataque;

            cout << "Defensa: ";
            cin >> defensa;

            nuevoHeroe = new Mago ( nombre, "Jugador", nivel, vida, ataque, defensa );
            break;
        }
        case 3: {
            //Sanador:
            cout << "Nivel: ";
            cin >> nivel;

            cout <<  "Vida: ";
            cin >> vida;

            cout << "Defensa: ";
            cin >> defensa;
            nuevoHeroe = new Sanador ( nombre, "Jugador", nivel, vida, defensa);
            break;
        }

        case 4: {
            //Paladin;
            cout << "Nivel: ";
            cin >> nivel;

            cout <<  "Vida: ";
            cin >> vida;

            cout << "Ataque: ";
            cin >> ataque;

            cout << "Defensa: ";
            cin >> defensa;

            nuevoHeroe = new Paladin (  nombre, "Jugador", nivel,  vida,  ataque, defensa );
            break;
        }
        case 5: {
            //Paladin;
            cout << "Nivel: ";
            cin >> nivel;

            cout <<  "Vida: ";
            cin >> vida;

            cout << "Ataque: ";
            cin >> ataque;

            cout << "Defensa: ";
            cin >> defensa;

            nuevoHeroe = new HechiceroOscuro( nombre, "Jugador",  nivel, vida, ataque,  defensa );
            break;
            break;
        }
        default: {
            cout << "Opcion invalida. Heroe no creado." << endl;
            return;
        }
    }

    //Si se creo exitosamente se agrega a la Guild:

    if( nuevoHeroe != nullptr ) {
        this -> guildJugador -> agregarPersonaje( nuevoHeroe );
    }
}

void Torneo::consultarHeroeTorneo( ) {
    //Metodos auxiliar para consultar un heroe.
    //Separa la logica con la interaccion con el usuario.

    string nombre;
    cout << "Ingrese el nombre del heroe: " ;
    getline( cin, nombre );
    if( nombre.empty( ) ) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }
    this -> guildJugador -> consultarPersonaje( nombre );
}


void Torneo::retirarHeroeTorneo( ) {
    // Metodo auxiliar para retirar un heroe.
    // Encapsula la logica del retiro con confirmacion.

    string nombre;
    cout << "Ingrese el nombre del heroe a retirar: ";
    getline( cin, nombre );

    if( nombre.empty( ) ) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    //Verifica que el heroe existe antes de retirar:

    if( this -> guildJugador -> buscarPersonaje( nombre ) != nullptr ) {
        //Pedir confirmacion:
        char confirmacion;

        cout << "Estas Seguro de retirar a " << nombre << "? (s/n): ";
        cin >> confirmacion;
        cin.ignore( );

        if( confirmacion == 's' || confirmacion == 'S' ) {
            guildJugador -> retirarPersonaje( nombre );
        }
        else {
            cout << "Operacion cancelada." << endl;
        }
    }
    else {
        cout << "No se encontro ningun heroe con ese nombre." << endl;
    }

}



void Torneo::mostrarGuildsRivales( ) {
    //Metodo auxiliar, permite ver a las guilds enemigas:
    //Permite reutilizar esta funcionalidad desde otros lugares de ser necesario.
    int personajesVivos;
    int personajesTotales;

    cout << endl << "=== GUILDS RIVALES ===" << endl;

    //Validacion: Verifica si hay Guilds enemigas registradas.
    if( this -> guildsEnemigas.empty( ) ) {
        cout << "No hay Guilds enemigas registradas."<< endl;
        return;
    }

    //Itera sobre todas la Guilds enemigas.
    for( int i = 0; i < this -> guildsEnemigas.size( ); i++ ) {
        //Muestra el numero y nombre de cada Guild

        cout << endl << "Guild " << ( i + 1 ) << ": "
        << this -> guildsEnemigas[ i ] -> getNombreGuild( ) << endl;

        //delegar a la Guild el mostrar sus propios personajes:
        this -> guildsEnemigas[ i ] -> listarPersonajes( );

        //Mostramos estadisticas adiccionales:
        personajesVivos = this -> guildsEnemigas[ i ] -> getPersonajesVivos( ).size( ); /*
        Verificar esto cuando lo corran*/
        personajesTotales = this -> guildsEnemigas[ i ] -> getCantidadPersonajes( );
        cout << " ##### Personajes activos: " << personajesVivos << "/" << personajesTotales << endl ;
    }

       // Resumen al final:
    cout << endl << "Total de Guilds Rivales : " << this -> guildsEnemigas.size( ) << "." <<endl;
}

//Metodos de gestion (Menus):

void Torneo::gestionarGuild( ) {
    //Menu para gestionar la Guild del jugador :
    int opcion;

    do {
        cout << endl << "=== GESTION DE GUILD ===" << endl;
        cout << "Guild: " << this -> guildJugador -> getNombreGuild( ) << endl;
        cout << "1. Listar heroes." << endl;
        cout << "2. Consultar heroe." << endl;
        cout << "3. Agregar heroe." << endl;
        cout << "4. Retirar heroe." << endl;
        cout << "5. Volver al menu principal" << endl;
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
                consultarHeroeTorneo( );
                break;
            }
            case 3: {
                crearNuevoHeroe( );
                // Agregar un nuevo heroe:
                break;
            }
            case 4: { 
                retirarHeroeTorneo( );
                break;
            }
            case 5: {
                cout << "Volviendo al menu principal..." << endl;
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

void Torneo:: menuPrincipal() {
    int opcion;

    do {
        cout << endl << "========================================" << endl;
        cout << "     " << this -> nombreTorneo << endl;
        cout << "========================================" << endl;
        cout << "1, Gestionar Guild." << endl;
        cout << "2. Gestionar inventario . " << endl;
        cout << "3. Iniciar Arena (combates)." << endl;
        cout << "4. Ver Guilds enemigas." << endl;
        cout << "0. Salir del torneo." << endl;
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
                mostrarGuildsRivales( );
                break;
            }
            case 0: {
                cout << endl << "Saliendo del Torneo..." << endl;
                cout << "¡Gracias por participar en " << this -> nombreTorneo << "!!!!!" <<endl;
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

//Metodo de Gestion del inventario:

void Torneo::listarInventarioDetallado() {

    //Para mostrar los detalles del inventario:

    cout << endl << "=== INVENTARIO DE OBJETOS MAGICOS ===" << endl;

    if ( this->inventario->getStockTotal( )  == 0) {
        cout << "El inventario esta vacio. " << endl;
        return;
    }

    this -> inventario -> listarObjetos();

    cout << "Stock total disponible: " << this -> inventario -> getStockTotal( ) << endl;
    cout << "=====================================" << endl;

}

void Torneo:: asignarObjetoHeroe() {
    //Metodo que contiene la logica para asignar los objetos a los heroes:

    string nombreHeroe;
    string nombreObjeto;

    cout << endl << "=== Asignar objeto a heroe ===" << endl;

    //Mostrar el inventario disponible:

    this -> inventario->listarObjetos();

    cout << endl << "Ingrese el nombre del objeto: ";
    getline( cin, nombreObjeto);

    if (nombreObjeto.empty()) {
        cout << " Error: Debe ingresar un nombre de objeto." << endl;
        return;
    }

    //Verificamos que el objeto exista:

    ObjetoMagico * objeto = this -> inventario -> buscarObjeto( nombreObjeto);

    if ( objeto == nullptr) {
        cout << "Error: No hay stock disponible de '" << nombreObjeto << "'. " <<endl;
        return;
    }

    //Mostrar heroes disponibles:
    cout << endl << "Heroes Disponibles: " << endl;
    this-> guildJugador -> listarPersonajes();

    cout << endl << "Ingrese el nombre del heroe: " ;
    getline(cin, nombreHeroe);

    if (nombreHeroe.empty()) {
        cout << "Error: Debe ingresar un nombre de heroe." << endl;
        return;
    }

    //Buscar el heroe:

    Personaje * heroe = this -> guildJugador -> buscarPersonaje(nombreHeroe);

    if ( heroe == nullptr) {
        cout << "Error: No se encontro ningun heroe con el nombre '" << nombreHeroe << "'.";
        return;
    }

    //Verificar que el Heroe puede equipar mas objetos:

    if ( !heroe -> isPuedeEquiparObjeto( ) ) {
        cout << "Error: " << nombreHeroe << " ya tiene el maximo de objetos equipados (2/2). " << endl;
        return;
    }

    //Asignar el objeto:

    this -> inventario ->asignarObjetoAPersonaje( nombreObjeto, heroe);

    //Decrementar stock:
    objeto->decrementarStock();

    cout << "Objeto aignado exitosamente!!!!!!!!" << endl;
    cout << "Stock restante de '" << nombreObjeto << "': " << objeto ->getStock() << endl;

}

void Torneo::buscarObjetoEspecifico() {
    //Metodo auxiliar para buscar un objeto especifico.
    string nombreObjeto;

    cout << "Ingrese el nombre del objeto: ";
    getline(cin, nombreObjeto);

    if (nombreObjeto.empty()) {
        cout << "Error: Debe de ingresar el nombre de un objeto." << endl;
        return;
    }

    this-> inventario -> consultarObjeto(nombreObjeto);
}

void Torneo::listarObjetosEquipadosHeroes() {
    //Metodo para ver los objetos equipados por los heroes:

    char respuesta;

    cout << endl << "=== Objetos equipados por heroes ===" << endl;
    this -> guildJugador -> listarPersonajes( );
    cout << "Desea ver los detalles de un heroe? (S/N)" << endl;

    cin >> respuesta;
    cin.ignore();

    if ( respuesta == 's' || respuesta == 'S' ) {
        consultarHeroeTorneo();
    }

}

//Metodo de gestionar inventario:

void Torneo::gestionarInventario() {
    int opcion;

    do {
        cout << endl << "=== GESTION DE INVENTARIO ===" << endl;
        cout << "Stock total: " << this->inventario->getStockTotal() << " Objetos." << endl;
        cout << "1. Listar objetos disponible." << endl;
        cout << "2. Consultar objeto especifico." << endl;
        cout << "3. Asignar objeto a heroe." << endl;
        cout << "4. Ver objetos equipado por heroes. " << endl;
        cout << "0. Volvel al menu principal." << endl;
        cout << "Selecciones una opcion: ";
        cin >> opcion;
        cin.ignore();



        switch (opcion) {
            case 1: {
                listarInventarioDetallado();
                break;
            }
            case 2: {
                buscarObjetoEspecifico();
                break;
            }
            case 3: {
                asignarObjetoHeroe();
                break;
            }
            case 4: {
                listarObjetosEquipadosHeroes();
                break;
            }
            case 0: {
                cout << "Volviendo al menu principal......" << endl;
                break;
            }
            default: {
                cout << "Error: opcion invalida, intente de nuevo." << endl;
                break;
            }
        }
    }
    while (opcion!=0);
}