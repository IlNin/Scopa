#include "Carta.hpp"

using namespace std;
using namespace cv;

Carta::Carta(string directory) { // Costruttore in cui viene dato come parametro la directory della foto
 numero = -1;
 seme = "Invalida";
 this->directory = directory;
 fotoZoom = imread("Grafica/Pixel.jpg", IMREAD_COLOR); // Foto placeholder che contiene una carta pixellata
 if (fotoZoom.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Pixel.jpg"); }
 resize(fotoZoom, fotoZoom, Size(75, 130)); 
 fotoRettangolo = Mat::ones(160, 80, CV_32F); }

int Carta::getNumero() { // Permette di ottenere il numero della carta
 return numero; }
  
void Carta::setNumero(int numero) { // Cambia il numero della carta
 this->numero = numero; }

string Carta::getSeme() { // Permette di ottenere il seme della carta
 return seme; }
 
void Carta::setSeme(string seme) { // Cambia il seme della carta
 this->seme = seme; }

string Carta::getDirectory() { // Permette di ottenere la directory della foto
 return directory; }

void Carta::setDirectory(string directory) { // Cambia la directory della foto
 this->directory = directory; }

void Carta::mostraFotoZoom(string display) { // Mostra la carta estratta dalla foto
 imshow(display, fotoZoom);
 waitKey(2000);
 destroyWindow(display); } // Mostra la foto su schermo per due secondi

void Carta::mostraFotoRettangolo(string display) { // Mostra la foto originale con la carta segnalata da un rettangolo
 imshow(display, fotoRettangolo);
 waitKey(2000);
 destroyWindow(display); } 

Mat Carta::getFotoZoom() { // Ottiene la carta estratta dalla foto
 return fotoZoom; }

void Carta::setFotoZoom(Mat frame) { // Assegna la foto della carta estratta
 frame.copyTo(fotoZoom); }

void Carta::setFotoRettangolo(Mat frame) { // Assegna la foto originale con la carta segnalata da un rettangolo
 frame.copyTo(fotoRettangolo); }

void Carta::riconosci() { // Guarda la foto associata alla directory e riconosce la carta
 Mat image = imread(directory, IMREAD_COLOR); // Apre l'immagine nella directory 
 if (image.empty()) { // Errore durante la lettura dell'immagine
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory " + directory); }
 resize(image, image, Size(411, 411)); // Porta l'immagine alla dimensione adatta
 Mat grayImage;
 cvtColor(image, grayImage, CV_BGR2GRAY); // Converte l'immagine in bianco e nero e la salva in grayImage
 CascadeClassifier denaraCascade;
 vector<Rect> cards; // Vettore in cui vengono salvati i rettangoli con le features
 vector<Rect> cards2; // Crea un altro vettore per rettangoli
 string cascade = "CarteCascadeB.xml";
 if (!denaraCascade.load(cascade)) { // Carica il primo cascade
  throw std::invalid_argument("Non e' stato trovato il file " + cascade); }
 denaraCascade.detectMultiScale(grayImage, cards, 1.1, 500, 0|CV_HAAR_SCALE_IMAGE, Size(60, 50)); // Analizza l'immagine e salva i rettangoli
 denaraCascade.detectMultiScale(grayImage, cards2, 1.1, 500, 0|CV_HAAR_SCALE_IMAGE, Size(30, 40)); // Effettua la seconda analisi
 cards.insert(cards.end(), cards2.begin(), cards2.end()); // Unisce i due vettori in modo da comprendere tutti i risultati delle due analisi

 double distanzaMinima = 100000000000000; // Inizializza una distanza minima altissima
 Rect featureDefinitiva; // Contiene la feature migliore
 if (cards.size() != 0) {
  for (int j = 0; j < cards.size(); j++) { // Se il vettore non è vuoto, scorre tutti i rettangoli
   Mat currentImage = Mat(grayImage, cards[j]); // Apre quella parte di immagine che contiene il rettangolo/feature corrente
   // rectangle(image, cards[j], Scalar(255, 255, 255), 2, 8, 0); // Crea un rettangolo intorno alla feature trovata
   resize(currentImage, currentImage, Size(37, 70)); // Riduce la grandezza per renderla uguale a quella delle foto "target"
   for (int i = 1; i <= 40; i++) { // Scorre le foto "target"
    string directory = "Target/"; // Inizia a creare la directory corrente
    stringstream ss;
    ss << i;
    string contatore = ss.str();
    directory.append(contatore);
    directory.append(".png"); // Directory creata!
    Mat targetImage = imread(directory, IMREAD_GRAYSCALE); // Apre la foto "target" associata alla directory corrente
    if (image.empty()) { // Errore durante la lettura dell'immagine
     throw std::invalid_argument("Non e' stata trovata una foto associata alla directory " + directory); }
    equalizeHist(currentImage, currentImage); // Equalizza istogramma della foto con il rettangolo/feature corrente
    for (int x = 0; x <= 1; x++) { // Faccio due volte il confronto con target
     if (x == 0) { // Equalizza istogramma della foto "target"
      equalizeHist(targetImage, targetImage); } 
     else { // Ora faccio il paragone con l'immagine target rovesciata
      flip(targetImage, targetImage, -1); }
     double distanzaAttuale = norm(currentImage, targetImage); // Calcola la distanza Euclidea tra le due foto
     // cout << "Distanza da carta " << i << ", feature " << j << ": " << norm(image2, image3) << endl; 
     if (distanzaAttuale < distanzaMinima) { // Se la distanza e' inferiore a quella attuale, aggiorna le informazioni sulla carta.
      // rectangle(image, cards[j], Scalar(255, 255, 255), 2, 8, 0); // Crea un rettangolo intorno alla feature trovata
      distanzaMinima = distanzaAttuale; // Setta una nuova distanza minima
      featureDefinitiva = cards[j]; // La miglior feature viene conservata
      setFotoZoom(image(cards[j])); // Setta la foto che rappresenta la carta estratta
      if (i <= 10) { // Setta numero e seme
       setNumero(i);
       setSeme("Denara"); }
      else if (i > 10 && i <= 20) {
       setNumero(i-10);
       setSeme("Spade"); }
      else if (i > 20 && i <= 30) {
       setNumero(i-20);
       setSeme("Coppe"); }
      else {
       setNumero(i-30);
       setSeme("Bastoni"); } } } } }

  rectangle(image, featureDefinitiva, Scalar(255, 0, 0), 2, 8, 0); // Crea un rettangolo blu intorno alla feature definitiva
  int numero = getNumero(); // Ottiene numero e seme per scriverli sulla feature definitiva nella foto
  string seme = getSeme();
  stringstream ss;
  ss << numero;
  putText(image(featureDefinitiva), ss.str() + " " + seme, Point(5, 10), CV_FONT_HERSHEY_SIMPLEX, 0.3, Scalar(0, 0, 255), 1); // Scrittura foto!
  setFotoRettangolo(image); } // Setta la foto contenente la carta circondata da un rettangolo
 
 else {
  throw std::invalid_argument("Non e' stato possibile riconoscere la carta nella foto" + directory); } }
 
void Carta::stampaCarta() { // Stampa su schermo gli attributi della carta
 cout << "[" << getNumero() << ", " << getSeme() << "]"; }
