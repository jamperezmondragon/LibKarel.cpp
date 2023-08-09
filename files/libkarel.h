#include <fstream>
#include <string>
#include <vector>
#include <array>
using namespace std;

class Mundo {
  /*
   * xKarel = Coordenada x de karel.
   * yKarel = Coordenada y de karel.
   * direccionKarel = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4.
   * mochilakarel = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
   * width = Ancho del mundo.
   * height = Altura del mundo.
   * beepers = Cada elemento del vector es una celda que contiene zumbadores.
   * Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
   * paredes = Sean {x, y, z} los valores de un elemento del vector. 
   * Cada elemento del vector representa una celda con coordenadas (x, y),
   * que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
   */
  public:
    int xKarel;
    int yKarel;
    int direccionKarel;
    string direciones[4] = {"NORTE", "ESTE", "SUR", "OESTE"};
    int mochilaKarel;
    int width, height;
    vector<array<int, 3>> beepers, paredes; 

    // Imprime el mundo en formato XML.
    void print_to_file(string file_name) {
      ofstream file_output;
      file_output.open(file_name);

      file_output << "<ejecucion>\n";
      file_output << "\t<condiciones instruccionesMaximasAEjecutar=\"10000000\" longitudStack=\"65000\"></condiciones>\n";
      file_output << "\t<mundos>\n";
      file_output << "\t\t<mundo nombre=\"mundo_0\" ancho=\"" << width <<"\" alto=\"" << height << "\">\n";
      for (auto [y, x, z] : beepers) {
        file_output << "\t\t\t<monton x=\"" << x << "\" y=\"" << y << "\" zumbadores=\"" << z << "\"></monton>\n";
      }
      for (auto [y, x, z] : paredes) {
          if ((z>>0)&1) {
            file_output << "\t\t\t<pared x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x + 1 << "\"></pared>\n";
          }
          if ((z>>1)&1) {
            file_output << "\t\t\t<pared x1=\"" << x << "\" y1=\"" << y << "\" y2=\"" << y + 1 << "\"></pared>\n";
          }
      }
      file_output << "\t\t</mundo>\n";
      file_output << "\t</mundos>\n";
      file_output << "\t<programas tipoEjecucion=\"CONTINUA\" intruccionesCambioContexto=\"1\" milisegundosParaPasoAutomatico=\"0\">\n";
      file_output << "\t\t<programa nombre=\"p1\" ruta=\"{$2$}\" mundoDeEjecucion=\"mundo_0\" xKarel=\"" << xKarel;
      file_output << "\" yKarel=\"" << yKarel << "\" direccionKarel=\"" << direciones[direccionKarel];
      file_output << "\" mochilaKarel=\"" << ((mochilaKarel == -1) ? "INFINITO" : to_string(mochilaKarel)) << "\">\n";
      file_output << "\t\t\t<despliega tipo=\"MUNDO\"/>\n";
      file_output << "\t\t</programa>\n";
      file_output << "\t</programas>\n";
      file_output << "</ejecucion>";

      file_output.close();
    }
};
