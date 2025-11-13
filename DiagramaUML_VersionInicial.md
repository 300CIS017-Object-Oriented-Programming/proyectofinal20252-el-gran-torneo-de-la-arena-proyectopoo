```mermaid

classDiagram
    %% Clase principal
    class Main{
        +main() int
    }

    %% Controlador principal del torneo
    class Torneo{
        -string nombreTorneo
        -Guild* guild
        -unordered_map< string, Personaje* > personajes
        -Inventario* inventario
        -Arena* arena
        
        +Torneo(string nombre)
        +~Torneo()
        
        +void inicializarTorneo()
        +void inicializarGuild()
        +void inicializarGuildEnemiga() 
        +void inicializarInventario()
        
        +void gestionarGuild()
        +void gestionarInventario()
        +void iniciarArena()
        
        +void menuPrincipal()
    }

    %% Gestiona los héroes del jugador
    class Guild{
        -string nombreGuild
        -unordered_map < string, Personaje* > personajes
        
        +Guild(string nombre)
        +~Guild()
        
        +void cargarPersonajeIniciales()
        +void agregarPersonaje(Personaje* personajes)
        +void consultarPersonaje(string nombre)
        +void listarPersonaje()
        +void retirarPersonaje(string nombre)
        +Personaje* buscarPersonaje(string nombre)
        
        +vector< Personaje* > getPersonajeVivos()
        +int getCantidadPersonajes()
    }

    %% Clase base para todos los héroes
    class Personaje{
        #string nombre
        #string rol
        #int nivel
        #int vida
        #int vidaMaxima
        #int ataque
        #int defensa
        #vector < ObjetoMagico*> objetosEquipados
        #bool estaVivo
        
        +Personaje(string nombre, string rol, int nivel, int vida, int ataque, int defensa)
        +virtual ~Personaje()
        
        +virtual void realizarAccion(Personaje* objetivo) 
        +virtual void mostrarInformacion()
        
        +void recibirDanio(int danio)
        +void equiparObjeto(ObjetoMagico* objeto)
        +void usarObjeto(int indice)
        +bool puedeEquiparObjeto()
        
        +string getNombre()
        +string getRol()
        +int getVida()
        +int getAtaque()
        +int getDefensa()
        +bool getEstaVivo()
        
        +void setVida(int vida)
        +void setAtaque(int ataque)
        +void setDefensa(int defensa)
    }

    %% Héroe especializado en ataques físicos
    class Guerrero{
        -double probabilidadCritico
        
        +Guerrero(string nombre, int nivel, int vida, int ataque, int defensa)
        +~Guerrero()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularDanioCritico(int danioBase)
        -bool esCritico()
    }

    %% Héroe especializado en magia
    class Mago{
        -int poderMagico
        -double factorIgnorarDefensa
        
        +Mago(string nombre, int nivel, int vida, int ataque, int defensa)
        +~Mago()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularDanioMagico()
    }

    %% Héroe especializado en curación
    class Sanador{
        -int poderCuracion
        -double efectividadCuracion
        
        +Sanador(string nombre, int nivel, int vida, int ataque, int defensa)
        +~Sanador()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularCuracion()
    }


    %% Gestiona los objetos mágicos del torneo
    class Inventario{
        -unordered_map < string, ObjetoMagico* > objetosDisponibles
        
        +Inventario()
        +~Inventario()
        
        +void cargarObjetosIniciales()
        +void crearObjeto()
        +void listarObjetos()
        +void consultarObjeto(string nombre)
        +void actualizarStock(string nombre, int nuevoStock)
        +void eliminarObjeto(string nombre)
        +void asignarObjetoAPersonaje(Personaje* personaje)
        +void retirarObjetoDePersonaje(Personaje* personaje, int indice)
        
        +ObjetoMagico* buscarObjeto(string nombre)
        +int getStockTotal()
    }

    %% Clase base para objetos mágicos
    class ObjetoMagico{
        #string nombre
        #string descripcion
        #int stockDisponible
        #bool fueUsado
        
        +ObjetoMagico(string nombre, string descripcion, int stock)
        +virtual ~ObjetoMagico()
        
        +virtual void aplicarEfecto(Personaje* personaje)
        +virtual void mostrarInformacion()
        
        +void decrementarStock()
        +void incrementarStock()
        
        +string getNombre()
        +int getStock()
        +bool getFueUsado()
        +void setFueUsado(bool usado)
    }

    %% Restaura puntos de vida
    class PocionVida{
        -int curacionMinima
        -int curacionMaxima
        
        +PocionVida()
        +~PocionVida()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
    }

    %% Aumenta el ataque temporalmente
    class AmuletoFuria{
        -int aumentoAtaqueMin
        -int aumentoAtaqueMax
        -int duracionTurnos
        
        +AmuletoFuria()
        +~AmuletoFuria()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
    }

    %% Aumenta la defensa temporalmente
    class EscudoBendito{
        -int aumentoDefensaMin
        -int aumentoDefensaMax
        -int duracionTurnos
        
        +EscudoBendito()
        +~EscudoBendito()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
    }

    %% Controla los combates por turnos
    class Arena{
        -vector < Personaje* > equipoGuild
        -int turnoActual
        
        +Arena()
        +~Arena()
        
        +void iniciarCombate(vector < Personaje* > personajes)
        +void ejecutarTurno()
        +bool verificarFinCombate()
        +void mostrarEstadoCombate()
        +void mostrarResumenFinal()
    }

    %% Relaciones entre clases
    Main ..> Torneo : Usa
    
    Torneo "Compone" o-- Guild 
    Torneo "Compone" <-- Inventario 
    Torneo "Compone" <-- Arena 
    
    Guild o-- Personaje : Tiene muchos
    
    Personaje <|-- "Es" Guerrero 
   Personaje <|-- "Es" Mago 
    Personaje <|--  "Es" Sanador 
    
    Personaje o-- ObjetoMagico : Usa
    
    Inventario "Gestiona" o-- ObjetoMagico 
    
    ObjetoMagico <|-- "Es" PocionVida 
    ObjetoMagico <|-- "Es" AmuletoFuria 
    ObjetoMagico <|-- "Es" EscudoBendito 
    
    Arena "Usa"..> Personaje

    Inventario "Usa"..> Personaje
```