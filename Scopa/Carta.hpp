#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <unistd.h> // ESCLUSIVAMENTE LINUX

using namespace std;
using namespace cv;

class Carta {
 private:
  int numero; // Numero della carta
  string seme; // Seme della carta
  string directory; // Directory della foto associata alla carta
  Mat fotoZoom; // Contiene la carta estratta dalla foto
  Mat fotoRettangolo; // Contiene la foto originale con la carta segnalata da un rettangolo
 
 public:
  Carta(string); // Costruttore in cui viene dato come parametro la directory della foto
  int getNumero(); // Permette di ottenere il numero della carta
  void setNumero(int); // Cambia il numero della carta
  string getSeme(); // Permette di ottenere il seme della carta
  void setSeme(string); // Cambia il seme della carta
  string getDirectory(); // Permette di ottenere la directory della foto
  void setDirectory(string); // Cambia la directory della foto
  void mostraFotoZoom(string); // Mostra la carta estratta dalla foto
  void mostraFotoRettangolo(string); // Mostra la foto originale con la carta segnalata da un rettangolo
  Mat getFotoZoom(); // Ottiene la carta estratta dalla foto
  void setFotoZoom(Mat); // Assegna la foto della carta estratta
  void setFotoRettangolo(Mat); // Assegna la foto originale con la carta segnalata da un rettangolo
  void riconosci(); // Guarda la foto associata alla directory e riconosce la carta
  void stampaCarta(); // Stampa su schermo gli attributi della carta
};
