#include <iostream>
#include <ctime>
#include "Torneo/Torneo.h" //Para poder acceder al directorio donde estan los archivos.

#include <windows.h> // Error en Linux/Mac

using std::cout;
using std::cin;

int main( ) {
    //Inicializa la semilla aleatoria para los numero aleatorios .
    //Es necesario para los golpes criticos, curaciones variables, etc.
    // Configurar consola para UTF-8 (solo Windows)
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    srand( time( 0 ) );

    cout << "========================================" << endl;
    cout << "   PROYECTO LYRENHOLD - TORNEO" << endl;
    cout << "========================================" << endl;

    //Crea el Torneo
    Torneo torneo ( "Gran Torneo de la Arena de Lyrenhold" );

    //Inicializa todo el sistema (otra vez se puso en verde)
    torneo.inicializarTorneo( );

    //Nota: cuando implementen el pacto sangriento verifiquen que esto compile.
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                  ║" << endl;
    cout << "║    ██╗  ██╗   ██╗██████╗ ███████╗███╗   ██╗██╗  ██╗ ██████╗      ║" << endl;
    cout << "║    ██║  ╚██╗ ██╔╝██╔══██╗██╔════╝████╗  ██║██║  ██║██╔═══██╗     ║" << endl;
    cout << "║    ██║   ╚████╔╝ ██████╔╝█████╗  ██╔██╗ ██║███████║██║   ██║     ║" << endl;
    cout << "║    ██║    ╚██╔╝  ██╔══██╗██╔══╝  ██║╚██╗██║██╔══██║██║   ██║     ║" << endl;
    cout << "║    ███████╗██║   ██║  ██║███████╗██║ ╚████║██║  ██║╚██████╔╝     ║" << endl;
    cout << "║    ╚══════╝╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝      ║" << endl;
    cout << "║                                                                  ║" << endl;
    cout << "║              ⚔  EL GRAN TORNEO DE LA ARENA  ⚔                    ║" << endl;
    cout << "║         En Lyrenhold, donde los heroes escriben leyendas         ║" << endl;
    cout << "║                                                                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    //Ejecuta el menu principal:
    torneo.menuPrincipal( );

    cout << endl << "=== Programa finalizado ===" << endl;

    return 0;
}