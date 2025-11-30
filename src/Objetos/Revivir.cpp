#include <iostream>
#include "Revivir.h"

using std::cout;
using std::endl;

Revivir::Revivir( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Pocion de Resurrecion";
    this -> descripcion = "Un objeto que revive a un companero caido en combate con el 50% de su vida maxima.";
    this -> stockDisponible = stock;

}

void Revivir::aplicarEfecto( Personaje* usuario, vector<Personaje*> aliados, vector<Personaje*> enemigos ) {
     // La pocion de resurreccion requiere seleccionar a un aliado Muerto.

    cout << endl << "========================================" << endl;
    cout << "       POCION DE RESURRECCION" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione un aliado caido para revivir:" << endl;
    cout << "----------------------------------------" << endl;

    pausar(1000);

    //Mostrar lista de aliados muertos.

    int contador = 1;

    for (int i = 0; i < aliados.size(); i++) {

        if ( !aliados[i]-> getIsEstaVivo() ) {
            cout << " " << contador << "." << aliados[i]->getNombre() << " ("
            << aliados[i]->getRol() << ") " << "[DERROTADO] - Vida maxima: " << aliados[i]->getVidaMaxima() <<
                endl;
            contador ++;
        }
    }

    if (contador == 1) {
        cout << "No hay aliados caidos para revivir." << endl;
        cout << "La pocion se conserva para otro momento." << endl;
        return;
    }

     cout << "0. Cancelar (Conservar la pocion)." << endl;
     cout << "----------------------------------------" << endl;
     cout << "Opcion: ";

    int seleccion;
    cin >> seleccion;


    if (seleccion == 0) {
        cout << "Decides guardar la pocion para un momento mas critico." << endl;
        return;
    }

    //Buscar Aliado muerto seleccionado:

    Personaje * aliado = nullptr;
    contador = 1;

    for (int i = 0; i < aliados.size(); i++) {
        if ( !aliados[i]->getIsEstaVivo() ) {
            if (contador == seleccion) {
                aliado = aliados[i];
                break;
            }
            contador ++;
        }
    }

    if (aliado == nullptr) {
        cout << "Seleccion invalida. La pocion se conserva." << endl;
        return;
    }

    //Aplicar el efecto de resurrecion:

    cout << endl << usuario->getNombre() << " usa la Pocion de Resurreccion en " <<
        aliado->getNombre() << "!!!!!" << endl;
    pausar(1000);

    int vidaResucitado = aliado->getVidaMaxima()/2;
    aliado ->setVida( vidaResucitado);
    aliado->setEstaVivo(true);

    cout << "Una luz celestial envuelve a " << aliado->getNombre() << "....." << endl;
    //No hagan drogas.
    pausar(1500);
    cout << aliado->getNombre() << " ha Sido REVIVIDO con " << vidaResucitado << "/" <<
        aliado->getVidaMaxima() << " puntos de vida!!!" << endl;
    pausar(1000);
    cout << "========================================" << endl;

    /*Nota (Pipe): Todas las pausan que vean son o para efectos dramaticos, o para que el jugador lea el texto. */

}

void Revivir::mostrarInformacion( ) {
    cout << "==== Pocion de Resurreccion ====" << endl;
    cout << this -> descripcion << endl;
    cout << "Stock Disponible: " << this -> stockDisponible << endl;
    cout << "================================" << endl;
}

