#include <iostream>
#include <ctime>
#include "Torneo/Torneo.h" //Para poder acceder al directorio donde estan los archivos.

using std::cout;
using std:: cin;

int main() {
    //Inicializa la semilla aleatoria para los numero aleatorios .
    //Es necesario para los golpes criticos, curaciones variables, etc.
    srand(time(0));

    cout << "========================================" << endl;
    cout << "   PROYECTO LYRENHOLD - TORNEO" << endl;
    cout << "========================================" << endl;

    //Crea el Torneo
    Torneo torneo ("Gran Torneo de la Arena de Lyrenhold");

    //Inicializa todo el sistema (otra vez se puso en verde)
    torneo.inicializarTorneo();

    //Ejecuta el menu principal:
    torneo.menuPrincipal();

    cout << endl << "=== Programa finalizado ===" << endl;

    return 0;
}