| Fecha       | Qué decidí | Por qué lo hice así | Responsable |
|-------------|------------|---------------------|-------------|
| 12/nov/2025 | Crear clase base Heroe con subclases Guerrero, Mago y Sanador | Para poder usar herencia y que cada tipo de héroe tenga su propio comportamiento | Juan Felipe |
| 13/nov/2025 | Usar unordered_map para almacenar héroes en Guild | Permite buscar héroes por nombre de forma más eficiente | Juan Felipe |
| 13/nov/2025 | Usar unordered_map para el inventario | Facilita buscar y gestionar objetos por nombre | Juan Felipe |
| 13/nov/2025 | Dejar Heroe y Oponente como clases separadas | Los héroes pueden equipar objetos pero los oponentes no, así que es mejor mantenerlos separados | Juan Felipe |
| 17/nov/2024 | Crear jerarquía Personaje → Guerrero/Mago/Sanador | Cada rol ataca diferente: Guerrero hace críticos, Mago ignora defensa, Sanador cura. Usar herencia permite que cada uno tenga su propia lógica de combate. | Juan Felipe |
| 17/nov/2024 | Usar unordered_map en Guild | Buscar por nombre es rápido y evita personajes duplicados automáticamente. | Juan Felipe |
| 17/nov/2024 | Separar menús en métodos auxiliares | Los switch quedaban muy largos. Extraer métodos hace el código más limpio y fácil de entender. | Juan Felipe |
| 17/nov/2024 | Validar nombre antes de crear con new | Si creo primero y luego falla, pierdo memoria. Validar antes es más seguro. | Juan Felipe |
| 26/nov/2025 | Corregir retirarObjetoDePersonaje y completar el manejo de personajes vivos/muertos | Había errores al retirar objetos y al listar personajes; ajustar estas funciones evita inconsistencias y personajes repetidos en los vectores. | Juan Felipe |
| 27/nov/2025 | Integrar Paladin y ajustar HechiceroOscuro | Era necesario que el nuevo rol adicional y el hechicero oscuro compilaran bien y se integraran con el sistema de combate y de objetos. | Juan Felipe |
| 27/nov/2025 | Implementar la clase Arena para los combates | La Arena centraliza el flujo de los turnos y permite conectar Guild, Inventario y Personaje para cumplir la fase final del proyecto. | Juan Felipe |
| 30/nov/2025 | Agregar realizarAccionIA y mover lógica de acciones/IA a los héroes (incluyendo daño AOE) | Reducir la responsabilidad de la Arena y usar mejor el polimorfismo, haciendo que cada Personaje defina su propia IA y ataques especiales. | Juan Felipe |
| 30/nov/2025 | Unificar y extender la interfaz de los objetos mágicos | Modificar las firmas de aplicarEfecto y los métodos relacionados permite que los objetos actúen sobre aliados o enemigos y soporten efectos por turnos. | Juan Felipe |
| 30/nov/2025 | Ajustar la carga y el formato del JSON de héroes | Richi implementó el guardado y yo la carga; luego corregí el formato para que fuera una sola línea y que al leer se actualizaran los héroes existentes con los datos del JSON. | Juan Felipe |
| 01/dic/2025 | Reorganizar responsabilidades de Torneo hacia Guild e Inventario | Mover la carga y gestión de héroes/archivos mejora el encapsulamiento y respeta mejor el principio de responsabilidad única. | Juan Felipe |
| 01/dic/2025 | Simplificar el formato de guardado JSON y guardar también héroes muertos | Un formato más compacto es más fácil de leer y mantener, y guardar todos los héroes (vivos y muertos) deja el torneo en un estado consistente. | Juan Felipe |
| 01/dic/2025 | Añadir validaciones al eliminar objetos del inventario | Evita borrar objetos que estén equipados por cualquier personaje y protege la integridad del sistema de equipamiento. | Juan Felipe |
| 01/dic/2025 | Actualizar README y documentación final del proyecto | La documentación debía reflejar la versión final del código, los nuevos diagramas UML y el funcionamiento real del sistema. | Juan Felipe |
