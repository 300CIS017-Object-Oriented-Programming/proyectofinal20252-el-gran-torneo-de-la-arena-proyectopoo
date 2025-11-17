```mermaid

classDiagram
    %% Clase principal
    class Main{
        +main() int
    }

    %% Controlador principal del torneo
    class Torneo{
        -string nombreTorneo
        -Guild* guildJugador
        -vector< Guild* > guildsEnemigas  
        -Inventario* inventario
        -Arena* arena
        
        +Torneo(string nombre)
        +~Torneo()
        
        +void inicializarTorneo()
        +void inicializarGuilds()
        +void inicializarInventario()
        
        +void gestionarGuild()
        +void gestionarInventario()
        +void iniciarArena()
        
        +void menuPrincipal()
    }

    %% Gestiona personajes de un equipo
    class Guild{
        -string nombreGuild
        -unordered_map< string, Personaje* > personajes
        
        +Guild(string nombre)
        +~Guild()
        
        +void cargarPersonajesIniciales()
        +void agregarPersonaje(Personaje* personaje)
        +void consultarPersonaje(string nombre)
        +void listarPersonajes()
        +void retirarPersonaje(string nombre)
        +Personaje* buscarPersonaje(string nombre)
        
        +vector<Personaje*> getPersonajesVivos()
        +int getCantidadPersonajes()
    }

    %% Clase base para personajes
    class Personaje{
        #string nombre
        #string rol
        #string bando
        #int nivel
        #int vida
        #int vidaMaxima
        #int ataque
        #int defensa
        #vector<ObjetoAsignado*> objetosEquipados
        #bool estaVivo
        
        +Personaje(string nombre, string rol, string bando, int nivel, int vida, int ataque, int defensa)
        +virtual ~Personaje()
        
        +virtual void realizarAccion(Personaje* objetivo) 
        +virtual void mostrarInformacion()
        
        +void recibirDanio(int danio)
        +void equiparObjeto(ObjetoAsignado* objeto)
        +void usarObjeto(int indice)
        +bool puedeEquiparObjeto()
        +ObjetoAsignado* getObjetoEquipado(int indice)
        +void retirarObjeto(int indice)
        
        +string getNombre()
        +string getRol()
        +string getBando()
        +int getVida()
        +int getAtaque()
        +int getDefensa()
        +bool getEstaVivo()
        
        +void setVida(int vida)
        +void setAtaque(int ataque)
        +void setDefensa(int defensa)
    }

    %% Especializado en ataques físicos
    class Guerrero{
        -double probabilidadCritico
        
        +Guerrero(string nombre, string bando, int nivel, int vida, int ataque, int defensa)
        +~Guerrero()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularDanioCritico(int danioBase)
        -bool esCritico()
    }

    %% Especializado en magia
    class Mago{
        -int poderMagico
        -double factorIgnorarDefensa
        
        +Mago(string nombre, string bando, int nivel, int vida, int ataque, int defensa)
        +~Mago()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularDanioMagico()
    }

    %% Especializado en curación
    class Sanador{
        -int poderCuracion
        -double efectividadCuracion
        
        +Sanador(string nombre, string bando, int nivel, int vida, int defensa)
        +~Sanador()
        
        +void realizarAccion(Personaje* objetivo) override
        +void mostrarInformacion() override
        
        -int calcularCuracion()
    }

    %% Gestiona objetos mágicos del torneo
    class Inventario{
        -unordered_map< string, ObjetoMagico* > catalogoObjetos
        
        +Inventario()
        +~Inventario()
        
        +void cargarObjetosIniciales()
        +void crearObjeto(ObjetoMagico* objeto, int stockInicial)
        +void listarObjetos()
        +void consultarObjeto(string nombre)
        +void actualizarStock(string nombre, int nuevoStock)
        +void eliminarObjeto(string nombre)
        +void asignarObjetoAPersonaje(string nombre, Personaje* personaje)
        +void retirarObjetoDePersonaje(Personaje* personaje, int indice)
        
        +ObjetoMagico* buscarObjeto(string nombre)
        +int getStock(string nombre)
        +int getStockTotal()
    }

    %% Clase base para objetos mágicos (tipo con stock)
    class ObjetoMagico{
        #string nombre
        #string descripcion
        #int stockDisponible
        
        +ObjetoMagico(string nombre, string descripcion, int stock)
        +virtual ~ObjetoMagico()
        
        +virtual void aplicarEfecto(Personaje* personaje) = 0
        +virtual void mostrarInformacion()
        
        +void decrementarStock()
        +void incrementarStock()
        
        +string getNombre()
        +string getDescripcion()
        +int getStock()
    }

    %% Representa una instancia asignada a un personaje
    class ObjetoAsignado{
        -ObjetoMagico* tipoObjeto
        -bool usado
        
        +ObjetoAsignado(ObjetoMagico* tipo)
        +~ObjetoAsignado()
        
        +void aplicarEfecto(Personaje* personaje)
        +void marcarUsado()
        +bool estaUsado()
        +ObjetoMagico* getTipoObjeto()
        +string getNombre()
    }

    %% Restaura puntos de vida
    class PocionVida{
        -int curacionMinima
        -int curacionMaxima
        
        +PocionVida(int stock)
        +~PocionVida()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
        
        +int getCuracionMinima()
        +int getCuracionMaxima()
        +void setCuracionMinima(int valor)
        +void setCuracionMaxima(int valor)
    }

    %% Aumenta el ataque temporalmente
    class AmuletoFuria{
        -int aumentoAtaqueMin
        -int aumentoAtaqueMax
        -int duracionTurnos
        
        +AmuletoFuria(int stock)
        +~AmuletoFuria()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
        
        +int getAumentoAtaqueMin()
        +int getAumentoAtaqueMax()
        +int getDuracionTurnos()
        +void setAumentoAtaqueMin(int valor)
        +void setAumentoAtaqueMax(int valor)
        +void setDuracionTurnos(int turnos)
    }

    %% Aumenta la defensa temporalmente
    class EscudoBendito{
        -int aumentoDefensaMin
        -int aumentoDefensaMax
        -int duracionTurnos
        
        +EscudoBendito(int stock)
        +~EscudoBendito()
        
        +void aplicarEfecto(Personaje* personaje) override
        +void mostrarInformacion() override
        
        +int getAumentoDefensaMin()
        +int getAumentoDefensaMax()
        +int getDuracionTurnos()
        +void setAumentoDefensaMin(int valor)
        +void setAumentoDefensaMax(int valor)
        +void setDuracionTurnos(int turnos)
    }

    %% Controla los combates por turnos
    class Arena{
        -vector< Personaje* > personajesEnCombate
        -int turnoActual
        
        +Arena()
        +~Arena()
        
        +void iniciarCombate(vector<Personaje*> heroes, vector<Personaje*> enemigos)
        +void ejecutarTurno()
        +bool verificarFinCombate()
        +void mostrarEstadoCombate()
        +void mostrarResumenFinal()
        +void procesarObjetosPostCombate()
    }

    %% Relaciones entre clases
    Main ..> Torneo : Usa
    
    Torneo --> Guild : Tiene
    Torneo o--  Guild : guilds rivales
    Torneo o-- Inventario : Tiene
    Torneo o-- Arena : Tiene
    
    Guild o-- Personaje : Tiene muchos
    
    Personaje <|-- Guerrero : Es
    Personaje <|-- Mago : Es
    Personaje <|-- Sanador : Es
    
    Personaje o-- ObjetoAsignado : Equipa hasta 2
    
    ObjetoAsignado --> ObjetoMagico : Referencia al tipo
    
    Inventario o-- ObjetoMagico : Gestiona catálogo
    
    ObjetoMagico <|-- PocionVida : Es
    ObjetoMagico <|-- AmuletoFuria : Es
    ObjetoMagico <|-- EscudoBendito : Es
    
    Arena ..> Personaje : Usa
    Arena ..> Inventario : Procesa objetos
    Inventario ..> Personaje : Asigna objetos

```