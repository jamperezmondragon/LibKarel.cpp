#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cassert>
#include <set>

class MundoKarel {
  /*
   * Gracias a César Cepeda por la documentación:
   * https://github.com/ComiteMexicanoDeInformatica/OMI-2023/blob/main/documentacion_mundos_karel.md
   *
   * width = Ancho del mundo. Por default el ancho es 100.
   * height = Altura del mundo. Por default el ancho es 100.
   * Estos dos parámetros se inicializan al declarar una variable de tipo MundoKarel, con el constructor de la clase.
   *
   * xKarel = Coordenada x de karel. Por default es 1.
   * yKarel = Coordenada y de karel. Por default es 1.
   * direccionKarel = Direccion a la que apunta karel, tiene un valor entero entre 1 y 4. Por default es 0, es decir Norte.
   * mochilakarel = Cantidad de zumbadores en la mochila de karel al iniciar el mundo. -1 representa infinito.
   *
   * posicionDump = Set de arrays, cuyos valores representan las coordenadas que se quiere regresar al evaluador.
   * instruccionesMaximasAEjecutar = Las instrucciones máximas a ejecutar. Por default es 10 millones.
   * longitudDeStack = La longitud del stack. Por default es 65000.
   * nombre = El nombre del mundo. Por default es "mundo_0".
   * tipo = Es un índice que representa el tipo de despliegue. Por default es 0, es decir el tipo default es "MUNDO".
   * Tipos = las strings correspondientes al arreglo anterior.
   *
   * Hay una matriz de width * height, llamada Beepers, donde Beepers[x][y] representa la cantidad de beepers en la posición (x, y).
   * Se puede controlar dicha matriz más fácilmente mediante la función addBeeper(x, y).
   *
   * Función setWall(x, y, t): Lo que hace es agregar una pared a la posición (x, y).
   * t = 0 indica la pared norte, y los valores continuan en orden anti horario.
   *
   * Función unsetWall(x, y, t): Lo que hace es quitar una pared a la posición (x, y).
   * t = 0 indica la pared norte, y los valores continuan en orden anti horario.
   *
   *
   * Variables privadas:
   *
   * beepers = Cada elemento del vector es una celda que contiene zumbadores.
   * Los primeros dos valores son las coordenadas, y el tercero la cantidad de zumbadores.
   * paredes = Sean {x, y, z} los valores de un elemento del vector. 
   * Cada elemento del vector representa una celda con coordenadas (x, y),
   * que tiene una pared a la derecha si z tiene el bit 0 encendido y una pared a la arriba si z tiene el bit 1 encendido.
   *
   * Estos dos vectores los usa la función de print_to_file() para controlar la información de una manera más sencilla.
   *
   */

  public:
    int xKarel = 1;
    int yKarel = 1;
    int direccionKarel = 0;
    std::string direciones[4] = {"NORTE", "ESTE", "SUR", "OESTE"};
    int mochilaKarel = 0;
    int width = 100, height = 100;

    std::vector<std::vector<int>> Beepers;
    std::set<std::array<int, 2>> posicionDump;

    int instruccionesMaximasAEjecutar = 1e7;
    int longitudDeStack = 65e3;
    std::string nombre = "mundo_0";
    int tipo = 0;
    std::string Tipos[9] = {"MUNDO", "UNIVERSO", "ORIENTACION", "POSICION", "MOCHILA", "AVANZA", "GIRA_IZQUIERDA", "COGE_ZUMBADOR", "DEJA_ZUMBADOR"};

    MundoKarel(int W = 1, int H = 1) { 
      width = W;
      height = H;
      Paredes.assign(W + 1, std::vector<int>(H + 1, 0));
      Beepers.assign(W + 1, std::vector<int>(H + 1, 0));
    }
    // top left bottom right. 
    std::array<int, 3> foo[4] = {{-1, 0, 1}, {-1, -1, 2}, {-1, -1, 1}, {0, -1, 2}};
    // Agrega la pared en la dirección direccion[t] de la celda (x, y).
    void setWall(int x, int y, int t) {
      auto [a, b, c] = foo[t];
      assert(0 < x + a && x + a <= width && 0 < y + b && y + b <= height);
      if (!(Paredes[x + a][y + b]&c)) Paredes[x + a][y + b] += c;
    }
    // Quita la pared en la dirección direccion[t] de la celda (x, y).
    void unsetWall(int x, int y, int t) {
      auto [a, b, c] = foo[t];
      assert(0 < x + a && x + a <= width && 0 < y + b && y + b <= height);
      if (Paredes[x + a][y + b]&c) Paredes[x + a][y + b] -= c;
    }
    // Agrega c zumbadores en la posición (x, y).
    void addBeepers(int x, int y, int c) {
      assert(y > 0 && x <= width && x > 0 && y <= height);
      Beepers[x][y] += c;
    }

    // Imprime el mundo en formato XML.
    void print_to_file(std::string file_name) {
      std::ofstream file_output;
      file_output.open(file_name);

      file_output << "<ejecucion>\n";
      file_output << "\t<condiciones instruccionesMaximasAEjecutar=\"" << instruccionesMaximasAEjecutar << "\" longitudStack=\"" << longitudDeStack << "\"></condiciones>\n";
      file_output << "\t<mundos>\n";
      file_output << "\t\t<mundo nombre=\"" << nombre << "\" ancho=\"" << width <<"\" alto=\"" << height << "\">\n";

      beepers.clear(); paredes.clear();
      for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
          if (Beepers[i][j] != 0) beepers.push_back({i, j, Beepers[i][j]});
          assert(Beepers[i][j] >= 0);
          if (Paredes[i][j] != 0) paredes.push_back({i, j, Paredes[i][j]});
        }
      }

      for (auto [x, y, z] : beepers) {
        file_output << "\t\t\t<monton x=\"" << x << "\" y=\"" << y << "\" zumbadores=\"" << z << "\"></monton>\n";
      }
      
      for (auto [x, y, z] : paredes) {
          if ((z>>0)&1) {
            file_output << "\t\t\t<pared x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x + 1 << "\"></pared>\n";
          }
          if ((z>>1)&1) {
            file_output << "\t\t\t<pared x1=\"" << x << "\" y1=\"" << y << "\" y2=\"" << y + 1 << "\"></pared>\n";
          }
      }

      for (auto [x, y] : posicionDump) {
        file_output << "\t\t\t<posicionDump " << "x=\"" << x << "\" y=\"" << y << "\"/>\n";
      }

      file_output << "\t\t</mundo>\n";
      file_output << "\t</mundos>\n";
      file_output << "\t<programas tipoEjecucion=\"CONTINUA\" intruccionesCambioContexto=\"1\" milisegundosParaPasoAutomatico=\"0\">\n";
      file_output << "\t\t<programa nombre=\"p1\" ruta=\"{$2$}\" mundoDeEjecucion=\"mundo_0\" xKarel=\"" << xKarel;
      assert(direccionKarel < 4 && direccionKarel > -1);
      file_output << "\" yKarel=\"" << yKarel << "\" direccionKarel=\"" << direciones[direccionKarel];
      file_output << "\" mochilaKarel=\"" << ((mochilaKarel == -1) ? "INFINITO" : std::to_string(mochilaKarel)) << "\">\n";
      assert(tipo < 9 && tipo > -1);
      file_output << "\t\t\t<despliega" << " tipo=\"" << Tipos[tipo] << "\"" << "/>\n";

      file_output << "\t\t</programa>\n";
      file_output << "\t</programas>\n";
      file_output << "</ejecucion>";

      file_output.close();
    }
  private:
    std::vector<std::vector<int>> Paredes;
    std::vector<std::array<int, 3>> beepers, paredes; 
};
