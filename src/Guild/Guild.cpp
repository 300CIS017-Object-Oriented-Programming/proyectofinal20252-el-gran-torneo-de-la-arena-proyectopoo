//
// Created by felip on 17/11/2025.
//

#include "Guild.h"

// Constructores y destrucotres:

Guild::Guild( ) {
    //Contructor por defecto:
    this -> nombreGuild = "Guild sin nombre";
}

Guild::Guild( string nombre ) {
    // Contructor parametrizado:
    this -> nombreGuild = nombre;
}

Guild:: ~Guild( ) {
    // El destructor - debe liberar la memoria de todos los personajes:
    cout << endl << "========================================" << endl;
    cout << "Destruyendo Guild: " << this -> nombreGuild << endl;
    cout << "Liberando " << this -> personajes.size( ) << " personajes..." << endl;

    // Personajes es la colección que se va a recorrer.
    // En cada iteración, par representa un elemento de esa colección.
    for( pair<string, Personaje*> par : this -> personajes ) {
        // Es un for basado en rango.
        // pair: Para el tipo de dato.

        cout << "Liberando memoria de : " << par.first << endl; //first es la clave (y en este caso el nombre).
        delete par.second; // par.second es el puntero al Personaje.
    }
    this -> personajes.clear( ); //limpio el mapa.
    cout << "Guild destruida." << endl;
    cout << "========================================" << endl;
}

// gets
string Guild:: getNombreGuild( ) {
    return this -> nombreGuild;
}



// Metodos para la gestion de personajes:

void Guild::cargarPersonajesIniciales( ) {
    // Carga un conjunto de peronajes para la Guild.
    // Esto permite que el juego funciones sin que el usuario tenga que crear personajes.

    cout << endl << "===========================================" << endl;
    cout << "Cargando personajes iniciales para  " << this -> nombreGuild << "...." << endl;

    //Creamos 3 personajes iniciales: 1 de cada tipo:

    Personaje* heroe1= new Guerrero( "Stark", "Jugador", 2, 150, 35, 15 );
    cout << "[1/5] Guerrero creado: Stark." << endl;

    Personaje* heroe2 = new Mago( "Fern", "Jugador", 1, 80, 45, 5 );
    cout << "[2/5] Mago creado: Fern." << endl;

    Personaje* heroe3 = new Sanador( "Sein", "Jugador", 1, 90, 10 );
    cout << "[3/5] Sanador creado: Sein." << endl;

    Personaje* heroe4= new Paladin( "Himmel", "Jugador", 50, 300, 80, 80 );
    cout << "[4/5] Paladin creado: Himmel." << endl;

    Personaje* heroe5= new HechiceroOscuro( "Ubel", "Jugador", 5, 100, 40, 10 );
    cout << "[4/5] Hechicero Oscuro creado: Ubel." << endl;

    //Los agregamos al mapa de personajes:
    personajes[ heroe1 -> getNombre( ) ] = heroe1; //Usamos el get para esta seguros que estamos usando el nombre
    // verdadero del personaje.
    personajes[ heroe2 -> getNombre( ) ] = heroe2;
    personajes[ heroe3 -> getNombre( ) ] = heroe3;
    personajes[ heroe4 -> getNombre( ) ] = heroe4;
    personajes[ heroe5 -> getNombre( ) ] = heroe5;

    cout << "Personajes iniciales cargados exitosamente." << endl;
    cout << "===========================================" << endl;

}

void Guild::agregarPersonaje( Personaje* personaje ) {
    // Agrega un nuevo personaje a la Guild:
    if( personaje == nullptr ) {
        cout << "Error: No se puede agregar un personaje nulo. "<<  endl;
        return;
    }

    string nombre = personaje -> getNombre( );

    // Verifica que no exita ya un personaje con ese nombre :

    if( this -> personajes.find( nombre ) != this -> personajes.end( ) ) {
        // Si personajes si llega a end se asume que no existe un personaje con ese nombre.
        // Pero si no llega se asume que existe.
        cout << "Error: Ya existe un personaje llamado " << nombre << " en la Guild." << endl;
        return;
    }

    //Agregar el personaje al mapa:

    personajes[ nombre ] = personaje;
    cout << endl << personaje -> getRol( ) << " " << nombre << " se ha unido a " << this -> nombreGuild << "!!!!!" << endl;
}

void Guild::matarPersonaje( Personaje* personaje ) {
    /* Validamos que efectivamente el personaje este muerto */
    if( !personaje -> getIsEstaVivo( ) ) {
        this -> muertos[ personaje -> getNombre( ) ] = personaje;
    } else {
        cout << "El personaje " << personaje -> getNombre( ) << " no ha muerto!" << endl;
    }
}

void Guild::consultarPersonaje( string nombre ) {

    // Busca y muestra la informacion de un personaje especifico:
    Personaje* personaje = buscarPersonaje( nombre );//esta funcion se implementa mas abajo.

    if( personaje != nullptr ) { // Si se entraga un nullptr no se muestra la informacion por que no existe.
        personaje -> mostrarInformacion( );
    }
    else {
        cout << "No se encuentra ningun personaje llamado " << nombre << "." << endl;
    }
}

void Guild::listarPersonajes( ) {
    // Muestra a todos los personajes de la Guild
    cout << endl << "======== Miembros de " << this -> nombreGuild << " ========" << endl;

    if( personajes.empty( ) ) {
        cout << "La Guild no tiene ningun miembro." << endl;
    }

    else {
        int contador = 1;
        for( pair<string, Personaje*> par : this -> personajes ) {
            Personaje* p = par.second;
            cout << contador << ". " << p -> getRol( ) << " - " << p -> getNombre( ) <<
                " (Nivel " << p -> getNivel( ) << ") - " << ( p-> getIsEstaVivo( ) ? "Vivo" : "Derrotado") << endl;
            contador++;
        }
    }
    cout << "Total de personajes: " << personajes.size( ) << endl;
    cout << "========================================" << endl;

}

void Guild::retirarPersonaje( string nombre ) {
    // Elimina un personaje de la Guild:

    Personaje* personaje = buscarPersonaje( nombre );

    if( personaje != nullptr ) {
        cout << personaje -> getRol( ) << " " << nombre
        << " ha dejado " << this -> getNombreGuild( ) << "." << endl;


        //Libera la memoria del personaje:
        delete personaje;

        //Lo elimina del mapa:
        personajes.erase( nombre );
    }

    else {
        cout << "No se encontro ningun personaje llamado " << nombre << endl;
    }
}

Personaje* Guild::buscarPersonaje( string nombre ) {
    //Busca un personaje por su nombre y retorna su puntero.
    //Retorna un nullptr si no lo encuentra:

    unordered_map<string, Personaje*>::iterator it = this -> personajes.find( nombre );
    // Busca en el mapa la clave "nombre"
    // si no encuentra la clave, retorna personajes.end().

    if( it != this -> personajes.end( ) ) {
        return it -> second; //Retorna el puntero al Personaje
    }

    return nullptr; // No encontrado.
}

// Metodos para el combate:

vector<Personaje*> Guild::getPersonajesVivos( ) {
    // Retorna un vector con solo los personajes vivos.
    // Esto sera util para la Arena cuando necesitemos saber quien puede pelear.

    vector<Personaje*> vivos;

    for( pair<string, Personaje*> par : this -> personajes ) {

        if( par.second -> getIsEstaVivo( ) ) { // Esto es true si estan vivos los personajes y si lo estan ejecuta
            //lo de adentro del if.
            
            vivos.push_back( par.second );
        } else {
            /* Aprovechamos este metodo para agregar los personajes que vayan cayendo en combate al map
               de personajes muertos */
            /*Mover automaticamente a  muertos si no esta ya. Para verificacion.*/
           if (this->muertos.find(par.first)== this->muertos.end()) {
               matarPersonaje( par.second );
           }
        }
    }
    return vivos;
}

int Guild::getCantidadPersonajes( ) {
    // Retorna el numero total de personajes en la Guild

    return this -> personajes.size( ); // Tambine retorna el numero total, no solo los vivos.
}

vector<Personaje * > Guild::getPersonajesMuertos() {
    //Retorna el vector con todos los personajes muertos:
    vector<Personaje*> fallecidos;

    for (pair<string, Personaje *> par: this->muertos) {
        fallecidos.push_back(par.second); /* Hacemos push_back al vector de perosnajes muertos.*/
    }
    return fallecidos;
}

//Metodos de gestion para mejora r el encapsulamiento:

void Guild::crearNuevoPersonaje() {
    // Metodo que encapsula toda la lógica de creación de personajes (SIgue en verde)

    string nombre;
    int tipoRol, nivel, vida, ataque, defensa;

    cout << endl << "=== Crear nuevo héroe ===" << endl;
    cout << "Nombre: ";
    getline(cin, nombre);

    // Validar nombre no vacío
    if (nombre.empty()) {
        cout << "Error: el nombre no puede estar vacío." << endl;
        return;
    }

    // Verificar que no exista
    if (buscarPersonaje(nombre) != nullptr) {
        cout << "Error: ya existe un heroe llamado " << nombre << "." << endl;
        return;
    }

    cout << "Tipo de rol:" << endl;
    cout << "1. Guerrero" << endl;
    cout << "2. Mago" << endl;
    cout << "3. Sanador" << endl;
    cout << "4. Paladin" << endl;
    cout << "5. Hechicero Oscuro" << endl;
    cout << "Seleccione: ";
    cin >> tipoRol;

    Personaje* nuevoHeroe = nullptr;

    switch(tipoRol) {
        case 1: {
            cout << "Nivel: "; cin >> nivel;
            cout << "Vida: "; cin >> vida;
            cout << "Ataque: "; cin >> ataque;
            cout << "Defensa: "; cin >> defensa;
            nuevoHeroe = new Guerrero(nombre, "Jugador", nivel, vida, ataque, defensa);
            break;
        }
        case 2: {
            cout << "Nivel: "; cin >> nivel;
            cout << "Vida: "; cin >> vida;
            cout << "Ataque: "; cin >> ataque;
            cout << "Defensa: "; cin >> defensa;
            nuevoHeroe = new Mago(nombre, "Jugador", nivel, vida, ataque, defensa);
            break;
        }
        case 3: {
            cout << "Nivel: "; cin >> nivel;
            cout << "Vida: "; cin >> vida;
            cout << "Defensa: "; cin >> defensa;
            nuevoHeroe = new Sanador(nombre, "Jugador", nivel, vida, defensa);
            break;
        }
        case 4: {
            cout << "Nivel: "; cin >> nivel;
            cout << "Vida: "; cin >> vida;
            cout << "Ataque: "; cin >> ataque;
            cout << "Defensa: "; cin >> defensa;
            nuevoHeroe = new Paladin(nombre, "Jugador", nivel, vida, ataque, defensa);
            break;
        }
        case 5: {
            cout << "Nivel: "; cin >> nivel;
            cout << "Vida: "; cin >> vida;
            cout << "Ataque: "; cin >> ataque;
            cout << "Defensa: "; cin >> defensa;
            nuevoHeroe = new HechiceroOscuro(nombre, "Jugador", nivel, vida, ataque, defensa);
            break;
        }
        default: {
            cout << "Opcion invalida. Heroe no creado." << endl;
            return;
        }
    }

    if (nuevoHeroe != nullptr) {
        agregarPersonaje(nuevoHeroe);
    }
}

void Guild::consultarPersonajeInteractivo() {
    // Método que encapsula la consulta interactiva (Verde)

    string nombre;
    cout << "Ingrese el nombre del heroe: ";
    getline(cin, nombre);

    if (nombre.empty()) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    consultarPersonaje(nombre);
}

void Guild::retirarPersonajeInteractivo(Inventario* inventario) {
    // Metodo que encapsula el retiro con devolucion de objetos (No entiendo por que me sale en verde).

    listarPersonajes();

    string nombre;
    cout << "Ingrese el nombre del heroe a retirar: ";
    getline(cin, nombre);

    if (nombre.empty()) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    Personaje* heroe = buscarPersonaje(nombre);

    if (heroe == nullptr) {
        cout << "No se encontro ningun heroe con ese nombre." << endl;
        return;
    }

    // Mostrar objetos equipados
    bool tieneObjetos = false;
    cout << endl << "=== Objetos Equipados por " << nombre << " ===" << endl;

    for (int slot = 0; slot < 2; slot++) {
        ObjetoAsignado* objeto = heroe->getObjetoEquipado(slot);
        if (objeto != nullptr) {
            tieneObjetos = true;
            cout << "  [" << (slot + 1) << "] " << objeto->getNombre();
            if (objeto->estaUsado()) {
                cout << " (Usado - Se perdera)";
            } else {
                cout << " (No usado - Volvera al inventario)";
            }
            cout << endl;
        }
    }

    if (!tieneObjetos) {
        cout << " [Ningún Objeto equipado]" << endl;
    }

    // Pedir confirmación
    char confirmacion;
    cout << "Estas seguro de retirar a " << nombre << "? (s/n): ";
    cin >> confirmacion;
    cin.ignore();

    if (confirmacion == 's' || confirmacion == 'S') {
        // Devolver objetos no usados al inventario
        if (inventario != nullptr) {
            for (int slot = 1; slot >= 0; slot--) {
                ObjetoAsignado* objeto = heroe->getObjetoEquipado(slot);
                if (objeto != nullptr) {
                    if (!objeto->estaUsado()) {
                        string nombreObjeto = objeto->getNombre();
                        ObjetoMagico* tipoObjeto = inventario->buscarObjeto(nombreObjeto);

                        if (tipoObjeto != nullptr) {
                            tipoObjeto->incrementarStock();
                            cout << "'" << nombreObjeto << "' devuelto al inventario." << endl;
                        }
                    } else {
                        cout << "'" << objeto->getNombre() << "' fue usado y se pierde." << endl;
                    }
                    heroe->retirarObjeto(slot);
                }
            }
        }

        // Retirar el heroe
        retirarPersonaje(nombre);
    } else {
        cout << "Operación cancelada." << endl;
    }
}

void Guild::mostrarDetallesGuild() {
    // Método que encapsula la visualización completa de la guild (otra vez sale verde).

    int personajesVivos = getPersonajesVivos().size();
    int personajesTotales = getCantidadPersonajes();

    cout << endl << "=== " << nombreGuild << " ===" << endl;
    listarPersonajes();
    cout << " ##### Personajes activos: " << personajesVivos << "/"
         << personajesTotales << endl;
}

void Guild:: mostrarObjetosEquipadosHeroes() {
    //Muestra los objetos Equipados por todos los heroes (movido de Torneo)

    cout << endl << " ===== Objetos Equipados por heroes ===== " << endl;

    listarPersonajes();

    char respuesta;

    cout << "Desea ver los detalles de un heroe? (S/N): ";
    cin >> respuesta;
    cin.ignore();

    if ( respuesta == 's' || respuesta == 'S') {
        consultarPersonajeInteractivo();
    }

}

//Para la Carga y Descarga de Archivos JSON

void Guild::guardarHeroesEnJSON( const string& nombreArchivo ) {
    // Guarda los heroes vivos de la guild en formato JSON

    vector<Personaje*> heroesVivos = getPersonajesVivos();

    if ( heroesVivos.empty() ) {
        cout << "No hay heroes vivos para guardar." << endl;
        return;
    }

    std::ofstream archivo( nombreArchivo );

    if ( !archivo.is_open() ) {
        cout << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    archivo << "{\n";
    archivo << "  \"guild\": \"" << this->nombreGuild << "\",\n";
    archivo << "  \"heroes\": [\n";

    for ( int i = 0; i < heroesVivos.size(); i++ ) {
        Personaje* h = heroesVivos[i];

        archivo << "    {\n";
        archivo << "      \"nombre\": \"" << h->getNombre() << "\",\n";
        archivo << "      \"rol\": \"" << h->getRol() << "\",\n";
        archivo << "      \"nivel\": " << h->getNivel() << ",\n";
        archivo << "      \"vida\": " << h->getVida() << ",\n";
        archivo << "      \"vidaMaxima\": " << h->getVidaMaxima() << ",\n";
        archivo << "      \"ataque\": " << h->getAtaque() << ",\n";
        archivo << "      \"defensa\": " << h->getDefensa() << "\n";
        archivo << "    }";

        if ( i + 1 < heroesVivos.size() ) {
            archivo << ",";
        }
        archivo << "\n";
    }

    archivo << "  ]\n";
    archivo << "}\n";

    archivo.close();

    cout << endl << "========================================" << endl;
    cout << "Heroes guardados en '" << nombreArchivo << "'." << endl;
    cout << "Total: " << heroesVivos.size() << " heroes." << endl;
    cout << "========================================" << endl;
}

void Guild::cargarHeroesDesdeJSON( const string& nombreArchivo ) {
    // Carga heroes desde un archivo JSON

    std::ifstream archivo( nombreArchivo );

    if ( !archivo.is_open() ) {
        cout << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    cout << endl << "========================================" << endl;
    cout << "Cargando heroes desde '" << nombreArchivo << "'..." << endl;

    // Leer todo el contenido del archivo (todo vuelve las letras verdes)
    string contenido( ( std::istreambuf_iterator<char>( archivo ) ),
                       std::istreambuf_iterator<char>() );
    archivo.close();

    // Parseo manual simple del JSON
    int heroesActualizados = 0;
    int heroesCreados = 0;

    size_t pos = 0;
    while ( ( pos = contenido.find( "\"nombre\":", pos ) ) != string::npos ) {
        // Extraer nombre
        size_t inicioNombre = contenido.find( "\"", pos + 9 ) + 1;
        size_t finNombre = contenido.find( "\"", inicioNombre );
        string nombre = contenido.substr( inicioNombre, finNombre - inicioNombre );

        // Extraer rol
        size_t posRol = contenido.find( "\"rol\":", finNombre );
        size_t inicioRol = contenido.find( "\"", posRol + 6 ) + 1;
        size_t finRol = contenido.find( "\"", inicioRol );
        string rol = contenido.substr( inicioRol, finRol - inicioRol );

        // Extraer nivel
        size_t posNivel = contenido.find( "\"nivel\":", finRol );
        size_t inicioNivel = posNivel + 8;
        size_t finNivel = contenido.find_first_of( ",\n", inicioNivel );
        int nivel = stoi( contenido.substr( inicioNivel, finNivel - inicioNivel ) );

        // Extraer vida
        size_t posVida = contenido.find( "\"vida\":", finNivel );
        size_t inicioVida = posVida + 7;
        size_t finVida = contenido.find_first_of( ",\n", inicioVida );
        int vida = stoi( contenido.substr( inicioVida, finVida - inicioVida ) );

        // Extraer ataque
        size_t posAtaque = contenido.find( "\"ataque\":", finVida );
        size_t inicioAtaque = posAtaque + 9;
        size_t finAtaque = contenido.find_first_of( ",\n", inicioAtaque );
        int ataque = stoi( contenido.substr( inicioAtaque, finAtaque - inicioAtaque ) );

        // Extraer defensa
        size_t posDefensa = contenido.find( "\"defensa\":", finAtaque );
        size_t inicioDefensa = posDefensa + 10;
        size_t finDefensa = contenido.find_first_of( ",\n }", inicioDefensa );
        int defensa = stoi( contenido.substr( inicioDefensa, finDefensa - inicioDefensa ) );

        // Verificar si el heroe ya existe
        Personaje* existente = buscarPersonaje( nombre );

        if ( existente != nullptr ) {
            // Actualizar stats
            existente->setVida( vida );
            existente->setAtaque( ataque );
            existente->setDefensa( defensa );
            cout << "Actualizado: " << nombre << endl;
            heroesActualizados++;
        }
        else {
            // Crear nuevo heroe segun el rol
            Personaje* nuevoHeroe = nullptr;

            if ( rol == "Guerrero" ) {
                nuevoHeroe = new Guerrero( nombre, "Jugador", nivel, vida, ataque, defensa );
            }
            else if ( rol == "Mago" ) {
                nuevoHeroe = new Mago( nombre, "Jugador", nivel, vida, ataque, defensa );
            }
            else if ( rol == "Sanador" ) {
                nuevoHeroe = new Sanador( nombre, "Jugador", nivel, vida, defensa );
            }
            else if ( rol == "Paladin" ) {
                nuevoHeroe = new Paladin( nombre, "Jugador", nivel, vida, ataque, defensa );
            }
            else if ( rol == "Hechicero Oscuro" ) {
                nuevoHeroe = new HechiceroOscuro( nombre, "Jugador", nivel, vida, ataque, defensa );
            }

            if ( nuevoHeroe != nullptr ) {
                agregarPersonaje( nuevoHeroe );
                cout << "Creado: " << nombre << " (" << rol << ")" << endl;
                heroesCreados++;
            }
        }

        pos = finDefensa;
    }

    cout << "========================================" << endl;
    cout << "Heroes actualizados: " << heroesActualizados << endl;
    cout << "Heroes nuevos: " << heroesCreados << endl;
    cout << "========================================" << endl;
}