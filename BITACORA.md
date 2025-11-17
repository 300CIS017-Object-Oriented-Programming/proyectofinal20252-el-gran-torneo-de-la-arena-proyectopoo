| Fecha       | Qué decidí | Por qué lo hice así | Responsable |
|-------------|------------|---------------------|-------------|
| 12/nov/2025 | Crear clase base Heroe con subclases Guerrero, Mago y Sanador | Para poder usar herencia y que cada tipo de héroe tenga su propio comportamiento | Juan Felipe |
| 13/nov/2025 | Usar unordered_map para almacenar héroes en Guild | Permite buscar héroes por nombre de forma más eficiente | Juan Felipe |
| 13/nov/2025 | Usar unordered_map para el inventario | Facilita buscar y gestionar objetos por nombre | Juan Felipe |
| 13/nov/2025 | Dejar Heroe y Oponente como clases separadas | Los héroes pueden equipar objetos pero los oponentes no, así que es mejor mantenerlos separados | Juan Felipe |
| 17/Nov/2024 | Crear jerarquía Personaje → Guerrero/Mago/Sanador | Cada rol ataca diferente: Guerrero hace críticos, Mago ignora defensa, Sanador cura. Usar herencia permite que cada uno tenga su propia lógica de combate. | Juan Felipe |
| 17/Nov/2024 | Usar unordered_map en Guild | Buscar por nombre es rápido y evita personajes duplicados automáticamente. | Juan Felipe |
| 17/Nov/2024 | Separar menús en métodos auxiliares | Los switch quedaban muy largos. Extraer métodos hace el código más limpio y fácil de entender. | Juan Felipe |
| 17/Nov/2024 | Validar nombre antes de crear con new | Si creo primero y luego falla, pierdo memoria. Validar antes es más seguro. | Juan Felipe |