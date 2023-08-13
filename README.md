# LibKarel.cpp
Librería en C++ para generar y procesar casos de Karel.
Gracias a la ayuda de [LeoT121](https://github.com/LeoT121) y a Cesar Cépeda por la [documentación](https://github.com/ComiteMexicanoDeInformatica/OMI-2023/blob/main/documentacion_mundos_karel.md
) del formato.

Basta con descargar el repositorio, e incluir el archivo libkarel.h en su código. Esto le da acceso a la clase `Mundo`, donde fácilmente puede editar las carácterísticas de un mundo de karel en c++. 
También, le permite imprimir el mundo en formato XML a cualquier archivo, para ser usado en karel.js, omegaup u otras plataformas.
Estas son las propiedades que te permite modificar la librería (por ahora):
- xKarel = Coordenada x de karel.
- yKarel = Coordenada y de karel.
- direccionKarel = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4.
- mochilaKarel = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
- width = Ancho del mundo.
- height = Altura del mundo.
- beepers = Es un vector de arrays que te permite determinar los zumbadores en el mundo. Cada elemento del vector es una celda que contiene zumbadores. Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
- paredes = Es un vector de arrays que te permite determinar las paredes en el mundo. Sean {x, y, z} los valores de un elemento del vector. Cada elemento del vector representa una celda con coordenadas (x, y), que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
-  posicionDump = Vector de arrays, cuyos valores representan las coordenadas que se quiere regresar al evaluador.
- instruccionesMaximasAEjecutar = Las instrucciones máximas a ejecutar. Por default es 10 millones.
- longitudDeStack = La longitud del stack. Por default es 65000.
- nombre = El nombre del mundo. Por default es "mundo_0".
- tipo = Es un índice que representa el tipo de despliegue. Por default es 0, es decir el tipo default es "MUNDO".
