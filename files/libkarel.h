#include <fstream>
#include <string>
#include <vector>
#include <array>
using namespace std;

class MundoKarel {
  /*
   * Gracias a César Cepeda y la documentación:
   * https://github.com/ComiteMexicanoDeInformatica/OMI-2023/blob/main/documentacion_mundos_karel.md
   *
   * xKarel = Coordenada x de karel. Por default es 1.
   * yKarel = Coordenada y de karel. Por default es 1.
   * direccionKarel = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4.
   * mochilakarel = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
   * width = Ancho del mundo. Por default el ancho es 100.
   * height = Altura del mundo. Por default el ancho es 100.
   * beepers = Cada elemento del vector es una celda que contiene zumbadores.
   * Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
   * paredes = Sean {x, y, z} los valores de un elemento del vector. 
   * Cada elemento del vector representa una celda con coordenadas (x, y),
   * que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
   * posicionDump = Vector de arrays, cuyos valores representan las coordenadas que se quiere regresar al evaluador.
   * instruccionesMaximasAEjecutar = Las instrucciones máximas a ejecutar. Por default es 10 millones.
   * longitudDeStack = La longitud del stack. Por default es 65000.
   * nombre = El nombre del mundo. Por default es "mundo_0".
   * tipo = Es un índice que representa el tipo de despliegue. Por default es 0, es decir el tipo default es "MUNDO".
   * Tipos = las strings correspondientes al arreglo anterior.
   *
   */
  public:
    int xKarel = 1;
    int yKarel = 1;
    int direccionKarel;
    string direciones[4] = {"NORTE", "ESTE", "SUR", "OESTE"};
    int mochilaKarel = 0;
    int width = 100, height = 100;
    vector<array<int, 3>> beepers, paredes; 
    vector<array<int, 2>> posicionDump;
    int instruccionesMaximasAEjecutar = 1e7;
    int longitudDeStack = 65e3;
    string nombre = "mundo_0";
    int tipo = 0;
    string Tipos[9] = {"MUNDO", "UNIVERSO", "ORIENTACION", "POSICION", "MOCHILA", "AVANZA", "GIRA_IZQUIERDA", "COGE_ZUMBADOR", "DEJA_ZUMBADOR"};


    // Imprime el mundo en formato XML.
    void print_to_file(string file_name) {
      ofstream file_output;
      file_output.open(file_name);

      file_output << "<ejecucion>\n";
      file_output << "\t<condiciones instruccionesMaximasAEjecutar=\"" << instruccionesMaximasAEjecutar << "\" longitudStack=\"" << longitudDeStack << "\"></condiciones>\n";
      file_output << "\t<mundos>\n";
      file_output << "\t\t<mundo nombre=\"" << nombre << "\" ancho=\"" << width <<"\" alto=\"" << height << "\">\n";

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

      for (auto [y, x] : posicionDump) {
        file_output << "\t\t\t<posicionDump " << "x=\"" << x << "\" y=\"" << y << "\"/>\n";
      }

      file_output << "\t\t</mundo>\n";
      file_output << "\t</mundos>\n";
      file_output << "\t<programas tipoEjecucion=\"CONTINUA\" intruccionesCambioContexto=\"1\" milisegundosParaPasoAutomatico=\"0\">\n";
      file_output << "\t\t<programa nombre=\"p1\" ruta=\"{$2$}\" mundoDeEjecucion=\"mundo_0\" xKarel=\"" << xKarel;
      assert(direccionKarel < 4 && direccionKarel > -1);
      file_output << "\" yKarel=\"" << yKarel << "\" direccionKarel=\"" << direciones[direccionKarel];
      file_output << "\" mochilaKarel=\"" << ((mochilaKarel == -1) ? "INFINITO" : to_string(mochilaKarel)) << "\">\n";
      assert(tipo < 9 && tipo > -1);
      file_output << "\t\t\t<despliega" << " tipo=\"" << Tipos[tipo] << "\"" << "/>\n";

      file_output << "\t\t</programa>\n";
      file_output << "\t</programas>\n";
      file_output << "</ejecucion>";

      file_output.close();
    }
};
