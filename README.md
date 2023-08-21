# LibKarel.cpp
Librería en C++ para generar y procesar casos de Karel.
Gracias a la ayuda de Cesar Cépeda por la [documentación](https://github.com/ComiteMexicanoDeInformatica/OMI-2023/blob/main/documentacion_mundos_karel.md
) del formato, y a [LeoT121](https://github.com/LeoT121) por ayudarme con el esqueleto del programa.

Basta con descargar el repositorio, e incluir el archivo libkarel.h en su código. Esto le da acceso a la clase `Mundo`, donde fácilmente puede editar las carácterísticas de un mundo de karel en c++. 
También, le permite imprimir el mundo en formato XML a cualquier archivo, para ser usado en karel.js, omegaup u otras plataformas.
Estas son las propiedades que te permite modificar la librería (por ahora):
- `width` = Ancho del mundo. Por default el ancho es 100.
- `height` = Altura del mundo. Por default el ancho es 100.

  Estos dos parámetros se inicializan al declarar una variable de tipo MundoKarel, con el constructor de la clase.
- `xKarel` = Coordenada x de karel. Por default es 1.
- `yKarel` = Coordenada y de karel. Por default es 1.
- `direccionKarel` = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4. Por default es 0, es decir Norte.
- `mochilakarel` = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
- `posicionDump` = Set de arrays, cuyos valores representan las coordenadas que se quiere regresar al evaluador.
- `instruccionesMaximasAEjecutar` = Las instrucciones máximas a ejecutar. Por default es 10 millones.
- `longitudDeStack` = La longitud del stack. Por default es 65000.
- `nombre` = El nombre del mundo. Por default es "mundo_0".
- `tipo` = Es un índice que representa el tipo de despliegue. Por default es 0, es decir el tipo default es "MUNDO".
- `Tipos` = las strings correspondientes al arreglo anterior.
- Hay una matriz de `width * height`, llamada `Beepers`, donde `Beepers[x][y]` representa la cantidad de beepers en la posición (x, y).
- Se puede controlar dicha matriz más fácilmente mediante la función `addBeeper(x, y)`.
- Función `setWall(x, y, t)`: Lo que hace es agregar una pared a la posición (x, y).
  `t = 0` indica la pared norte, y los valores continuan en orden anti horario.
- Función `unsetWall(x, y, t)`: Lo que hace es quitar una pared a la posición (x, y).
  `t = 0` indica la pared norte, y los valores continuan en orden anti horario.
- Función `print_to_file(string file_name)`: Lo que hace es imprimir el caso con la información dada, en el formato XML, en un archivo llamado `file_name`.
- Variables privadas:
   - `beepers` = Cada elemento del vector es una celda que contiene zumbadores.
     Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
   - `paredes` = Sean `{x, y, z}` los valores de un elemento del vector. 
     Cada elemento del vector representa una celda con coordenadas (x, y),
     que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
     Estos dos vectores los usa la función de `print_to_file()` para controlar la información de una manera más sencilla.
