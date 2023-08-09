# LibKarel.cpp
Librería en C++ para generar y procesar casos de Karel.
Basta con descargar el repositorio, e incluir el archivo libkarel.h en su código. Esto le da acceso a la clase `Mundo`, donde fácilmente puede editar las carácterísticas de un mundo de karel en c++. 
También, le permite imprimr el mundo en formato XML, para ser usado en karel.js, omegaup u otras plataformas.
Estas son las propiedades que te permite modificar la librería (por ahora):
- xKarel = Coordenada x de karel.
- yKarel = Coordenada y de karel.
- direccionKarel = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4.
- mochilakarel = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
- width = Ancho del mundo.
- height = Altura del mundo.
- beepers = Cada elemento del vector es una celda que contiene zumbadores.
- Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
- paredes = Sean {x, y, z} los valores de un elemento del vector. 
- Cada elemento del vector representa una celda con coordenadas (x, y),
- que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
