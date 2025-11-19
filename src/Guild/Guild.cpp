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
        // pair: Para es el tipo de dato.

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

    cout << endl << "========================================" << endl;
    cout << "Cargando personajes iniciales para  " << this -> nombreGuild << "...." << endl;

    //Creamos 3 personajes iniciales: 1 de cada tipo:

    Personaje* heroe1= new Guerrero( "Stark", "Jugador", 2, 150, 35, 15 );
    cout << "[1/3] Guerrero creado: Stark." << endl;

    Personaje* heroe2 = new Mago( "Fern", "Jugador", 1, 80, 45, 5 );
    cout << "[2/3] Mago creado: Fern." << endl;

    Personaje* heroe3 = new Sanador( "Sein", "Jugador", 1, 90, 10 );
    cout << "[3/3] Sanador creado: Sein." << endl;

    //Los agregamos al mapa de personajes:
    personajes[ heroe1 -> getNombre( ) ] = heroe1; //Usamos el get para esta seguros que estamos usando el nombre
    // verdadero del personaje.
    personajes[ heroe2 -> getNombre( ) ] = heroe2;
    personajes[ heroe3 -> getNombre( ) ] = heroe3;

    cout << "Personajes iniciales cargados exitosamente." << endl;
    cout << "========================================" << endl;

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
        }
    }

    return vivos;
}

int Guild::getCantidadPersonajes( ) {
    // Retorna el numero total de personajes en la Guild

    return this -> personajes.size( ); // Tambine retorna el numero total, no solo los vivos.
}