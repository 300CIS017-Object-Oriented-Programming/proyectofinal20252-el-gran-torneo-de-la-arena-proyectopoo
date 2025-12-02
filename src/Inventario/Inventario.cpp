#include "Inventario.h"
/*#include "../Personajes/Personaje.h"
#include "../Objetos/ObjetoMagico.h"
Nota (Pipe): en este caso no son necesarios, ya que no hay dependencia circular. Me corrigen.*/
#include "ObjetoAsignado.h"

using std::pair;

Inventario::Inventario() {
    cout << "===== INVENTARIO DEL TORNEO CREADO =====" << endl;
    // El unordered_map se inicializa automáticamente vacío
}

Inventario::~Inventario() {
    //Nota: Imlemente el destructor de Inventario (Pipe).
    cout << endl << "========================================" << endl;
    cout << "Destruyendo Inventario...."  << endl;
    cout << "Liberando " << this -> catalogoObjetos.size( ) << " objetos magicos..." << endl;

    for (pair<string, ObjetoMagico*> par: this->catalogoObjetos) {

        cout << "Liberadon memoria de: " << par.first << endl;//first es la clave (y en este caso el nombre).
        delete par.second;// par.second es el puntero a Objeto Magico.
    }

    this->catalogoObjetos.clear(); //Limpio el mapa.
    cout<< "Inventario Destruido" << endl;
    cout << "========================================" << endl;


}

/* Falta Implementar la carga de Objetos Iniciales, nose que objetos quieren que se carguen inicialmente
 * Nota (Pipe): Dos de cada tipo estaria bien, no se que piense Richi.
 */
void Inventario::cargarObjetosIniciales( ) {

    //Cargar los objetos iniciales del torneo con su stock predeterminado:

    cout << endl << "========================================" << endl;
    cout << "   CARGANDO INVENTARIO DEL TORNEO" << endl;
    cout << "========================================" << endl;

   //Pociones de Vida - Mas comunes:
    crearObjeto( new PocionVida(0), 20);


    //Amuletos de Furia - moderadamente comunes:
    crearObjeto( new AmuletoFuria(0), 3);

    //Escudo Benditos - moderadamente comunes:
    crearObjeto( new EscudoBendito(0), 3);

    //Pactos Sangrientos - raros:
    crearObjeto(new PactoSangriento(0), 2);

    //Caballas Legendarias - muy raras:
    crearObjeto( new CaballaLegendaria(0), 1);

    //Pociones de Resurreccion - rara:
    crearObjeto( new Revivir(0), 2 );

    cout << endl << "Inventario cargado exitosamente !!!!" << endl;
    cout << endl << "Total de tipos de objetos: " <<  this->catalogoObjetos.size() << endl;
    cout << "========================================" << endl;



}

void Inventario::crearObjeto( ObjetoMagico* objeto, int stockInicial ) {
    cout << "Se esta creando el objeto " << objeto -> getNombre( ) << "..." << endl;
    objeto -> setStock( stockInicial );
    this -> catalogoObjetos[ objeto -> getNombre( ) ] = objeto;
    cout << "Se han creado " << stockInicial << " " << objeto -> getNombre( ) << endl;
}

void Inventario::listarObjetos( ) {
    cout << "===== LISTA DE OBJETOS EN INVENTARIO =====" << endl;
    for( pair<string, ObjetoMagico*> par : this -> catalogoObjetos ) {
        cout << par.first << " x" << par.second -> getStock( ) << endl;
    }
    cout << "==========================================" << endl;
}

void Inventario::consultarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        iter -> second -> mostrarInformacion( );
    } else {
        cout << "El objeto consultado no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::actualizarStock( string objeto, int nuevoStock ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        iter -> second -> setStock( nuevoStock );
        cout << "El stock del objeto " << iter -> first << " se ha actualizado, ahora dispone de " 
             << nuevoStock << " unidades!" << endl;
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::eliminarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        this -> catalogoObjetos.erase( objeto );
        cout << "El objeto " << objeto << " se ha eliminado del Inventario!" << endl;
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::asignarObjetoAPersonaje( string objeto, Personaje* personaje ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        ObjetoAsignado* asignar = new ObjetoAsignado( iter -> second );
        personaje -> equiparObjeto( asignar );
        cout << personaje -> getNombre( ) << " ha equipado [ " << objeto << " ]" << endl; 
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::retirarObjetoDePersonaje( Personaje* personaje, int indice ) {
    ObjetoAsignado* objeto = personaje -> getObjetoEquipado( indice );

    //Validacion:
    if ( objeto == nullptr ) {
        cout << "No hay ningun objeto equipado en ese slot." << endl;
        return;
    }

    //Si el objeto no fue usado, devolver el stock al inventario

    // Despues de verificar que el objeto no fue usado
    if (!objeto->estaUsado()) {
        string nombreObjeto = objeto->getNombre();
        ObjetoMagico* tipoObjeto = buscarObjeto(nombreObjeto);

        if (tipoObjeto != nullptr) {
            tipoObjeto->incrementarStock();
            cout << "Stock de '" << nombreObjeto << "' devuelto al inventario." << endl;
        }
        else {
            // El tipo de objeto fue eliminado del inventario
            cout << "Advertencia: El tipo '" << nombreObjeto << "' ya no existe en el inventario." << endl;
            cout << "El objeto se retira pero no se puede devolver al stock." << endl;
        }
    }

    else {
        // El objeto ya fue usado, no devolver stock
        cout << "EL objeto ya fue usado y no puede devolverse al Stock. " << endl;
    }

        //Retirarn el objeto del persoaje (este usado o no).
        personaje->retirarObjeto(indice);
        cout << "Objeto retirado exitosamente del personaje." << endl;

}

ObjetoMagico* Inventario::buscarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        return iter -> second;
    }

    return nullptr;
}

int Inventario::getStock( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        return iter -> second -> getStock( );
    }

    return 0;
}

int Inventario::getStockTotal( ) {
    int total = 0;
    for( pair<string, ObjetoMagico*> par : this -> catalogoObjetos ) {
        total += par.second -> getStock( );
    }

    return total;
}

/*Nuevo Metodo de Gestion, para mejorar el encapsulamiento (los estoy dejando al final por si no funciona
 * asi puedo saber facilmente que eliminar):*/

void Inventario::asignarObjetoInteractivo(Guild* guildJugador) {
    // Metodo que encapsula toda la logica de asignacion de objetos:

    if (guildJugador == nullptr) {
        cout << "Error: No hay guild del jugador." << endl;
        return;
    }

    string nombreHeroe;
    string nombreObjeto;

    cout << endl << "=== Asignar objeto a heroe ===" << endl;

    // Mostrar inventario disponible
    listarObjetos();

    cout << endl << "Ingrese el nombre del objeto: ";
    getline(cin, nombreObjeto);

    if (nombreObjeto.empty()) {
        cout << "Error: Debe ingresar un nombre de objeto." << endl;
        return;
    }

    // Verificar que el objeto exista
    ObjetoMagico* objeto = buscarObjeto(nombreObjeto);

    if (objeto == nullptr) {
        cout << "Error: El objeto '" << nombreObjeto << "' no existe." << endl;
        return;
    }

    // Verificar stock
    if (objeto->getStock() <= 0) {
        cout << "Error: No hay stock disponible de '" << nombreObjeto << "'." << endl;
        return;
    }
    if (nombreObjeto == "Pocion Vida"){
        if (objeto -> getStock() >= 5)
        {

        }
    }

    // Mostrar héroes disponibles
    cout << endl << "Heroes Disponibles:" << endl;
    guildJugador->listarPersonajes();

    cout << endl << "Ingrese el nombre del heroe: ";
    getline(cin, nombreHeroe);

    if (nombreHeroe.empty()) {
        cout << "Error: Debe ingresar un nombre de heroe." << endl;
        return;
    }

    // Buscar el heroe
    Personaje* heroe = guildJugador->buscarPersonaje(nombreHeroe);

    if (heroe == nullptr) {
        cout << "Error: No se encontro ningún heroe con el nombre '" << nombreHeroe << "'." << endl;
        return;
    }

    // Verificar que el heroe pueda equipar más objetos
    if (!heroe->isPuedeEquiparObjeto()) {
        cout << "Error: " << nombreHeroe << " ya tiene el maximo de objetos equipados (2/2)." << endl;
        return;
    }

    // Asignar el objeto
    asignarObjetoAPersonaje(nombreObjeto, heroe);

    // Decrementar stock
    objeto->decrementarStock();

    cout << "Objeto asignado exitosamente!!!!" << endl;
    cout << "Stock restante de '" << nombreObjeto << "': " << objeto->getStock() << endl;
}

void Inventario::mostrarInventarioDetallado() {
    //Muestra el inventario con detalles (movido de Torneo)

    cout << endl << "===== Inventario de Objetos Magicos ===" << endl;

    if (this->getStockTotal() == 0) {
        cout << "El inventario esta vacio." << endl;
        return;
    }

    listarObjetos();

    cout << "Stock total Disponible: " << this->getStockTotal() << endl;
    cout << "=====================================" << endl;


}

void Inventario::consultarObjetoInteractivo() {
    //Consulta un objeto en especifico con interaccion (movido de Torneo):

    string nombreObjeto;

    cout << endl << "==== Consultar Objeto Especifico ===" << endl;
    listarObjetos();

    cout << "Ingrese el nombre del objeto: " ;
    getline(cin, nombreObjeto);

    if (nombreObjeto.empty()) {
        cout << "Error: Debe ingresar el nombre de un objeto." << endl;
        return;
    }

    consultarObjeto( nombreObjeto);

}

void Inventario::actualizarStockInteractivo() {
    //Actualiza el stock de un objeto con interaccion:

    string nombreObjeto;
    int nuevoStock;

    cout << endl << "===== Actualizar Stock de Objeto =====" << endl;
    listarObjetos();

    cout << "Ingrese el nombre del objeto: " << endl;
    getline(cin ,nombreObjeto);

    if  ( nombreObjeto.empty() ) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    ObjetoMagico * objeto = buscarObjeto( nombreObjeto);

    if ( objeto == nullptr) {
        cout << "Error: El objeto '" << nombreObjeto << "' no existe." << endl;
        return;
    }

    cout << "Stock actual: " << objeto->getStock() << endl;
    cout << "Ingrese el nuevo stock: ";
    cin >> nuevoStock;
    cin.ignore();

    if ( nuevoStock < 0 ) {
        cout << "Error: El stock no puede ser negativo." << endl;
        return;
    }

    actualizarStock(nombreObjeto , nuevoStock);

}


void Inventario::eliminarObjetoInteractivo( Guild* guildJugador, vector<Guild*> guildsEnemigas ) {
    //Elimina un objeto del inventario con interaccion (movido de Torneo):

    string nombreObjeto;

    cout << endl << "===== Eliminar Objeto del Inventario =====" << endl;
    listarObjetos();

    cout << "Ingrese el nombre de los objetos a eliminar: " ;
    getline(cin, nombreObjeto);

    if ( nombreObjeto.empty() ) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    ObjetoMagico * objeto = buscarObjeto( nombreObjeto );

    if ( objeto == nullptr) {
        cout << "Error: El objeto '" << nombreObjeto << "' No existe." << endl;
        return;
    }

    if ( objeto->getStock() > 0 ) {
        cout << "Error: Solo se pueden eliminar objetos con Stock = 0." << endl;
        cout << "Stock actual de '" << nombreObjeto << "': " << objeto->getStock() << endl;
        return;
    }

    // Nueva validacion: Verificar si algun personaje tiene este objeto equipado
    cout << endl << "Verificando si algun personaje tiene este objeto equipado..." << endl;
    pausar( 800 );

    vector<string> personajesConObjeto;

    // Verificar heroes de la guild del jugador
    if ( guildJugador != nullptr ) {
        vector<Personaje*> heroes = guildJugador->getPersonajesVivos();
        vector<Personaje*> muertos = guildJugador->getPersonajesMuertos();

        // Agregar muertos al vector para revisarlos tambien
        for ( int i = 0; i < muertos.size(); i++ ) {
            heroes.push_back( muertos[i] );
        }

        // Revisar cada heroe
        for ( int i = 0; i < heroes.size(); i++ ) {
            Personaje* heroe = heroes[i];

            // Revisar ambos slots
            for ( int slot = 0; slot < 2; slot++ ) {
                ObjetoAsignado* objAsignado = heroe->getObjetoEquipado( slot );

                if ( objAsignado != nullptr && objAsignado->getNombre() == nombreObjeto ) {
                    personajesConObjeto.push_back( heroe->getNombre() + " (Jugador)" );
                    break; // No revisar el otro slot de este heroe
                }
            }
        }
    }

    // Verificar enemigos de todas las guilds enemigas
    for ( int g = 0; g < guildsEnemigas.size(); g++ ) {
        Guild* guildEnemiga = guildsEnemigas[g];

        if ( guildEnemiga != nullptr ) {
            vector<Personaje*> enemigos = guildEnemiga->getPersonajesVivos();
            vector<Personaje*> muertosEnemigos = guildEnemiga->getPersonajesMuertos();

            // Agregar muertos
            for ( int i = 0; i < muertosEnemigos.size(); i++ ) {
                enemigos.push_back( muertosEnemigos[i] );
            }

            // Revisar cada enemigo
            for ( int i = 0; i < enemigos.size(); i++ ) {
                Personaje* enemigo = enemigos[i];

                // Revisar ambos slots
                for ( int slot = 0; slot < 2; slot++ ) {
                    ObjetoAsignado* objAsignado = enemigo->getObjetoEquipado( slot );

                    if ( objAsignado != nullptr && objAsignado->getNombre() == nombreObjeto ) {
                        personajesConObjeto.push_back( enemigo->getNombre() + " (" + guildEnemiga->getNombreGuild() + ")" );
                        break;
                    }
                }
            }
        }
    }

    // Si hay personajes con el objeto, NO permitir eliminarlo (es un parche, pero sirve para evitar errores.
    if ( !personajesConObjeto.empty() ) {
        cout << endl << "ERROR: No se puede eliminar '" << nombreObjeto << "'" << endl;
        cout << "Los siguientes personajes tienen este objeto equipado:" << endl;

        for ( int i = 0; i < personajesConObjeto.size(); i++ ) {
            cout << "  - " << personajesConObjeto[i] << endl;
        }

        cout << endl << "Debes retirar el objeto de estos personajes antes de eliminarlo." << endl;
        cout << "Usa 'Retirar objeto de heroe' o espera a que se use en combate." << endl;
        return;
    }

    cout << "Ningun personaje tiene este objeto equipado." << endl;
    pausar( 500 );

    cout << endl << "ADVERTENCIA: Si eliminas este objeto, el tipo sera" << endl;
    cout << "removido permanentemente del inventario." << endl;

    char confirmacion;

    cout << "Seguro que desea eliminar '" << nombreObjeto << "' ? (s/n): ";
    cin >> confirmacion;
    cin.ignore();

    if (confirmacion == 's' || confirmacion == 'S') {
        eliminarObjeto(nombreObjeto);
    }
    else {
        cout << "Operacion Cancelada." << endl;
    }
}

void Inventario:: retirarObjetoInteractivo( Guild * guildJugador) {
    //Retira un objeto de un heroe con interaccion (movido de Torno):

    if ( guildJugador == nullptr) {
        cout << "Error: No hay Guild del jugador." << endl;
        return;
    }

    string nombreHeroe;

    cout << endl << "======= Retirar Objeto del Heroe ====== " << endl;
    guildJugador -> listarPersonajes();

    cout << "Ingrese el nombre del Heroe: " << endl;
    getline(cin , nombreHeroe);

    if ( nombreHeroe.empty() ) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    Personaje * heroe = guildJugador->buscarPersonaje( nombreHeroe);


    if ( heroe == nullptr) {
        cout << "Error: No se encontro al Heroe '" << nombreHeroe << "'." << endl;
        return;
    }

    cout << endl << "Objetos equipado por " << nombreHeroe << ": " << endl;
    heroe-> mostrarObjetosEquipados();

    cout << "Seleccione el slot a retirar ( 1 o 2 ), 0 para cancelar: " ;
    int slot;
    cin >> slot;
    cin.ignore();

    if (slot == 0) {
        cout << "Operacion Cancelada." << endl;
        return;
    }

    if ( slot < 1 || slot > 2 ) {
        cout << "Error: Slot invalido." << endl;
        return;
    }

    retirarObjetoDePersonaje( heroe, slot-1);

}

void Inventario::crearObjetoDesdeMenu() {
    //Crea el tipo de objeto que no existe actualmente

    cout << endl << "=== CREAR OBJETO MAGICO ===" << endl;
    cout << "NOTA: Los efectos son aleatorios segun el tipo." << endl;
    cout << "Solo puedes elegir el stock inicial." << endl;
    cout << endl;

    //Lista de tipos disponibles;

    vector<string> tiposDisponibles;
    tiposDisponibles.push_back("Pocion de Vida");
    tiposDisponibles.push_back("Amuleto de Furia");
    tiposDisponibles.push_back("Escudo Bendito");
    tiposDisponibles.push_back("Pacto Sangriento de los Caidos");
    tiposDisponibles.push_back("Caballa Legendaria del Destino");
    tiposDisponibles.push_back("Pocion de Resurrecion");


    //filtrar solo los que NO  existen en el inventario:


    vector <string> tiposFaltantes;

    for (int i = 0; i < tiposDisponibles.size(); i++) {
        if ( buscarObjeto( tiposDisponibles[i]) == nullptr ) {
            tiposFaltantes.push_back( tiposDisponibles[i] );
        }
    }

    if ( tiposFaltantes.empty() ){
        cout << "Todos los tipos de objeto ya existen en el inventario." << endl;
        cout << "Si deseas mas unidades, usa 'Actualizar Stock'." << endl;
        return;
    }


    cout << "Tipos Disponibles para crear: " << endl;
    cout << "----------------------------------------" << endl;

    for ( int i = 0; i < tiposFaltantes.size(); i++ ) {
        cout << " " << (i+1) << ". " << tiposFaltantes[i] << endl;

    }


    cout << " 0. Cancelar." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Seleccione el tipo: " ;

    int seleccion;
    cin >> seleccion;
    cin.ignore();

    if ( seleccion == 0) {
        cout << "Operacion cancelada." << endl;
        return;
    }

    if (seleccion < 1 || seleccion > tiposFaltantes.size() ) {
        cout << "Error: Seleccion invalida." << endl;
        return;
    }


    string tipoSeleccionado= tiposFaltantes[ seleccion -1 ];


    cout << "Ingrese el stock inicial para '" << tipoSeleccionado << "': ";

    int stockInicial;
    cin >>stockInicial;
    cin.ignore();

    if ( stockInicial <= 0) {
        cout << "Error: El stock debe ser mayor a 0. " << endl;
        return;
    }


    //Crear el objeto segun el tipo

    ObjetoMagico* nuevoObjeto = nullptr;

    if ( tipoSeleccionado == "Pocion de Vida") {
        nuevoObjeto = new PocionVida(0);
    }

    else if (tipoSeleccionado == "Amuleto de Furia" ) {
        nuevoObjeto = new AmuletoFuria(0);
    }
    else if (tipoSeleccionado == "Escudo Bendito" ) {
        nuevoObjeto = new EscudoBendito(0);
    }
    else if (tipoSeleccionado == "Pacto Sangriento de los Caidos" ) {
        nuevoObjeto = new PactoSangriento(0);
    }
    else if (tipoSeleccionado == "Caballa Legendaria del Destino" ) {
        nuevoObjeto = new CaballaLegendaria(0);
    }
    else if (tipoSeleccionado == "Pocion de Resurrecion" ) {
        nuevoObjeto = new AmuletoFuria(0);
    }


    if ( nuevoObjeto != nullptr) {
        crearObjeto( nuevoObjeto, stockInicial);
        cout << endl << "Objeto '" << tipoSeleccionado << "' creado con "
        << stockInicial << " unidades!!!!" << endl;
    }

}

//Metodo auxiliar para parar el tiempo.

void Inventario::pausar( int milisegundos ) {
    sleep_for( milliseconds( milisegundos ) );
}