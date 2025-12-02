

#include <iostream>
#include <cstdlib>
#include "CaballaLegendaria.h"

using std::cout;
using std::endl;

// Constructor
CaballaLegendaria::CaballaLegendaria( int stock ) : ObjetoMagico( ) {
    this -> nombre = "Caballa Legendaria del Destino";
    this -> descripcion = "Un pez mistico de tiempos ancestrales. Al consumirlo, el destino decide: 50% de probabilidad de eliminar instantaneamente al enemigo, 50% de que el usuario muera en el acto. Solo los mas valientes se atreven a usarla.";
    this -> stockDisponible = stock;
    this -> probabilidadExito = 0.5;

}

// Metodo auxiliar privado
bool CaballaLegendaria::calcularExito( ) {
    // Genera numero aleatorio entre 0 y 1
    // Si es menor a 0.5 (probabilidadExito) es exito
    double random = ( double ) rand( ) / RAND_MAX;
    return random < this -> probabilidadExito;
}

// Metodo principal - aplica el efecto del objeto
void CaballaLegendaria::aplicarEfecto( Personaje* usuario, vector<Personaje*> aliados, vector<Personaje *> enemigos,
    ObjetoAsignado* instancia )  {

    //La Caballa Legendaria requiere seleccionar un enemigo objetivo:
    cout << endl << "============================================" << endl;
    cout << "    CABALLA LEGENDARIA DEL DESTINO" << endl;
    cout << "============================================" << endl;
    cout << "ADVERTENCIA: 50% de matar al enemigo, 50% de morir tu!" << endl;
    cout << endl << "Seleccione un enemigo objetivo:" << endl;
    cout << "----------------------------------------" << endl;

    pausar(2000);

    //Mostrar lista de enemigos vivos:

    int contador = 1;

    for (int i = 0; i < enemigos.size(); i++) {
        if ( enemigos[i] -> getIsEstaVivo() ) {
            cout << " " << contador << ". " << enemigos[i]->getNombre()
            << " (" << enemigos[i]->getRol() << ") " << "- Vida: " <<
                enemigos[i]->getVida() << "/" << enemigos[i]-> getVidaMaxima() << endl;
            contador ++;
        }
    }

    if (contador == 1) {
        cout << "No hay enemigos vivos para atacar." << endl;
        cout << "La Caballa se conserva para otro momento." << endl;
        return;
    }

    cout << " 0. Cancelar (conservar la Caballa). " << endl;
    cout  << "----------------------------------------" << endl;
    cout <<"Opcion: ";

    int seleccion;
    cin >> seleccion;

    if (seleccion == 0) {
        cout << "Decides guardar la Caballa para un momento mas desesperado." << endl;
        pausar(1500);
        return;
    }

    //Buscar el enemigo seleccionado.
    Personaje * objetivo = nullptr;
    contador = 1;

    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] -> getIsEstaVivo() ) {
            if ( contador == seleccion) {
                objetivo = enemigos[i];
                break;
            }
            contador++ ;
        }
    }

    if (objetivo == nullptr) {
        cout << "Seleccion invalida. La Caballa se conserva." << endl;
        pausar(1500);
        return;
    }

    //Ahora ejecutamos el efecto de la caballa:

    cout << endl << usuario->getNombre() << " consume la CABALLA LEGENDARIA!!!!!!" << endl;
    cout << "El aire se congela... el destino se decide...." << endl;

    pausar(3000);

    if ( calcularExito( ) ) {
        //Exito: El enemigo muere instantanemente.
        cout << endl << "*~~* EL DESTINO FAVORECE A LOS VALIENTES !!!!!!!! *~~*" << endl;
        cout << objetivo -> getNombre() << " es fulminado por el poder ancestral!!!!" << endl;
        objetivo->setVida(0);
        objetivo->setEstaVivo(false);
        cout << objetivo->getNombre() << "ha sido ELIMINADO instantaneamente!!!!!!" << endl;

    }
    else {
        //Fracaso: el usuario muere:
        cout << endl << "*~~* EL DESTINO ES CRUEL!!!! *~~*" << endl;
        cout << "La Caballa estaba maldita.....O "<< usuario->getNombre() << " era alergico a los pescados "
            <<", no hay forma de saberlo..... " <<" igualmente "<< usuario->getNombre() <<  " cae FULMINADO." << endl;
        pausar(2500);

        usuario->setVida(0);
        usuario->setEstaVivo(false);

        cout << usuario->getNombre() << " ha MUERTO por su propia osadia !!!!... O alergia a los pescados." << endl;

    }
    cout << "============================================" << endl;
    pausar(1500);
}

// Muestra informacion del objeto
void CaballaLegendaria::mostrarInformacion( ) {
    cout << endl << "=== CABALLA LEGENDARIA DEL DESTINO ===" << endl;
    cout << this -> descripcion << endl;
    cout << "Probabilidad de exito: " << ( this -> probabilidadExito * 100 ) << "%" << endl;
    cout << "Probabilidad de muerte propia: " << ( ( 1 - this -> probabilidadExito ) * 100 ) << "%" << endl;
    cout << "Stock disponible: " << this -> stockDisponible << endl;
    cout << "=======================================" << endl;
}



// Getters


double CaballaLegendaria::getProbabilidadExito( ) {
    return this -> probabilidadExito;
}