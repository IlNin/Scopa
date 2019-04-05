#include "Mazzo.hpp"

using namespace std;

Mazzo::Mazzo() { // Crea un mazzo vuoto
 begin = new node;
 begin->carta = 0;
 begin->next = 0;
 end = begin; } 

void Mazzo::riempiCarte() { // Riempe il mazzo con tutte le 40 carte
 srand(time(NULL)); // Questo permette la randomizzazione di rand
 int random = (rand() % 3);
 for (int i = 1; i <= 40; i++) {
  string directory; // Inizia a creare la directory contenente la foto della carta
  if (random == 0) { 
   directory = "CarteA/"; }
  else if (random == 1) {
   directory = "CarteB/"; }
  else if (random == 2) {
   directory = "CarteC/"; }
  stringstream ss;
  ss << i;
  string contatore = ss.str();
  directory.append(contatore);
  directory.append(".jpg"); // Directory creata
  Carta* carta = new Carta(directory); // Crea un oggetto carta e gli associa la directory
  aggiungiCarta(carta); } }

void Mazzo::mischiaCarte() { // Mischia le carte presenti nel mazzo
 srand(time(NULL)); // Questo comando permette la randomizzazione di rand
 for (int i = 0; i < 120; i++) {
  Carta* attuale = rimuoviCarta(40); // Toglie l'ultima carta dal mazzo
  int random = (rand() % numeroCarte())+1; // Scegli un int tra 1 e 39
  aggiungiCarta(attuale, random); } }
  
void Mazzo::svuota() { // Svuota un mazzo
 begin = new node;
 begin->carta = 0;
 begin->next = 0;
 end = begin; }

bool Mazzo::vuoto() { // Controlla se il mazzo e' vuoto
 if (begin->carta == 0) // Basta controllare se la primo puntatore punta ad una carta valida
  return true;
 return false; }

int Mazzo::numeroCarte() { // Riporta il numero di carte attualmente presenti nel mazzo
 if (vuoto() == true) {
  return 0; }
 else {
  int contatore = 0; // Inizializza un contatore
  node* current = begin;
  while (current != 0) { // current scorre tutte le carte e aggiorna di conseguenza il contatore
   contatore = contatore+1;
   current = current->next; }
  return contatore; } }

Carta* Mazzo::getCarta(int i) { // Ottiene la carta alla posizione indicata da int
 if (vuoto() == true) {
  return new Carta(""); }
 else if (i > numeroCarte()) { // Ovviamente la ricerca fallisce se i e' maggiore del numero di carte presenti nel mazzo
  return new Carta(""); }
 else {
  int contatore = 1;
  node* current = begin;
  while (current != 0) { // Scorre le carte, aggiornando il contatore, finche' non trova quella cercata dall'int i
   if (contatore == i) {
    return current->carta; }
   else {
    contatore = contatore+1;
    current = current->next; } } } }

void Mazzo::aggiungiCarta(Carta* carta) { // Aggiunge una carta specifica in coda al mazzo
 if (vuoto() == true) { // Se il mazzo e' vuoto, assegna la carta direttamente al nodo begin...
  begin->carta = carta; }
 else { //... altrimenti lo aggiunge direttamente dopo il nodo end, che puntera' poi a quest'ultima carta
  end->next = new node;
  end = end->next;
  end->carta = carta;
  end->next = 0; } }

void Mazzo::aggiungiCarta(Carta* carta, int n) { // Aggiunge una carta specifica nella posizione n del mazzo
 if (n < 1) { // Controlla se l'int n e' compatibile con le dimensioni del mazzo attuale
  return; }
 else if (n >= (numeroCarte()+1)) { // Aggiunge la carta in fondo al mazzo
  aggiungiCarta(carta); }
 else { // Aggiunge la carta in qualsiasi altra posizione
  int contatore = 1;
  node* current = begin;
  while (current != 0) { // Itera le carte del mazzo
   if (contatore == n) { // Viene raggiunga la posizione in cui inserire la carta
    Carta* vecchiaCarta = current->carta; // Vengono salvate le informazioni sulla carta che occupava precedentemente questa posizione
    node* vecchioCurrent = new node; // Viene creato un nuovo nodo che contiene le stesse informazioni del nodo current che stiamo modificando
    vecchioCurrent->carta = vecchiaCarta; // La vecchia carta viene assegnata a vecchioCurrent
    vecchioCurrent->next = current->next; // Il next di current viene assegnato al next di vecchioCurrent
    current->carta = carta; // Viene cambiata la carta con quella attuale
    current->next = vecchioCurrent; // Ora la lista e' di nuovo continua
    if (current == end) { // Aggiorna il puntatore di end se stiamo a fine coda
     end = vecchioCurrent; }
    return; }
   contatore = contatore + 1;
   current = current->next; } } }
    
void Mazzo::rimuoviCarta(Carta* carta) { // Rimuove una specifica carta dal mazzo
 if (vuoto() == true) { // Non rimuove nulla se il mazzo è vuoto
  return; }
 
 Carta* attuale = begin->carta; // Controllo la prima carta
 if (attuale->getNumero() == carta->getNumero() && attuale->getSeme().compare(carta->getSeme()) == 0) { // Guarda se le due carte sono uguali
  if (numeroCarte() == 1) { // Se c'e' solo una carta, svuota il mazzo
   svuota();
   return; }
  else { // Altrimenti il puntatore all'elemento iniziale passa al secondo
   begin = begin->next; } }
 
 else { // La prima carta e' diversa. Scorro quindi tutte le altre
  node* current = begin->next;
  node* previous = begin; // Puntatore che punta al nodo precedente di quello current
  while (current != 0) {
   Carta* attuale = current->carta;
   if (attuale->getNumero() == carta->getNumero() && attuale->getSeme().compare(carta->getSeme()) == 0) { // Guarda se le due carte sono uguali
    previous->next = current->next; // Il nodo precedente non punta piu' a questa carta
    if (current == end) { // Controlla se il nodo corrente e' anche l'ultimo
     end = previous; }
    return; } 
   else { // Scorre di un elemento entrambi i puntatori
    previous = current;
    current = current->next; } } } }

Carta* Mazzo::rimuoviCarta(int n) { // Rimuove e restituisce una specifica carta nella posizione n del mazzo
 if (vuoto() == true || n < 1 || n > numeroCarte()) { // Non rimuove nulla se il mazzo e' vuoto o se n e' incompatibile
  return new Carta(""); }

 else if (n == 1) { // La carta da togliere e' la prima
  Carta* carta = begin->carta;
  if (numeroCarte() == 1) { // Se il mazzo contiene solo quella carta, lo svuota
   Carta* carta = begin->carta;
   svuota();
   return carta; }
  else { // Altrimenti begin inizia dalla carta successiva
   begin = begin->next;
   return carta; } }
 
 else { // La carta si trova in mezzo al mazzo
  int contatore = 2;
  node* current = begin->next;
  node* previous = begin; // Puntatore che punta al nodo precedente di quello current
  while (current != 0) { // Itera le carte presenti nel mazzo
   if (contatore == n) { // Viene raggiunta la carta da eliminare
    previous->next = current->next; // Il nodo precedente non punta piu' a questa carta
    if (current == end) { // Controlla se il nodo corrente e' anche l'ultimo
     end = previous; }
    return current->carta; } 
   else { // Scorre di un elemento entrambi i puntatori
    contatore = contatore + 1;
    previous = current;
    current = current->next; } } } }

void Mazzo::aggiungiMazzo(Mazzo* mazzo) { // Aggiunge un altro mazzo in coda a quello corrente
 for (int i = 1; i <= mazzo->numeroCarte(); i++) {
  Carta* attuale = mazzo->getCarta(i);
  aggiungiCarta(attuale); } }
 
bool Mazzo::confrontaMazzi(Mazzo* mazzo) { // Controlla se i due mazzi sono uguali
 if (numeroCarte() != mazzo->numeroCarte()) { // Se la lunghezza e' diversa, sono automaticamente diversi
  return false; }
 int contatore = 0; // Indica il numero di carte uguali
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  for (int j = 1; j <= mazzo->numeroCarte(); j++) {
   Carta* confronto = mazzo->getCarta(j);
   if (attuale->getNumero() == confronto->getNumero() && attuale->getSeme().compare(confronto->getSeme()) == 0) { // Le carte sono uguali
    contatore++; } } } 
 if (contatore == numeroCarte()) { // Guarda se tutte le carte sono uguali
  return true; }
 return false; }

int Mazzo::numeroDenara() { // Ritorna il numero di carte "denara" nel mazzo
 int contatore = 0;
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  if (attuale->getSeme().compare("Denara") == 0) {
   contatore = contatore + 1; } }
 return contatore; }

bool Mazzo::setteBello() { // Controlla se il 7 Bello e' presente nel mazzo
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  if (attuale->getNumero() == 7 && attuale->getSeme().compare("Denara") == 0) {
   return true; } }
 return false; }

int Mazzo::primiera() { // Calcola la primiera
 int punteggioCarta = 0; // Punteggio della carta attuale
 int punteggioDenara = 0; // Ogni seme di carta contiene un suo punteggio massimo
 int punteggioSpade = 0;
 int punteggioCoppe = 0;
 int punteggioBastoni = 0;

 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  if (attuale->getNumero() == 7) { // Assegno un punteggio in base al numero della carta
   punteggioCarta = 21; }
  else if (attuale->getNumero() == 6) {
   punteggioCarta = 18; }
  else if (attuale->getNumero() == 1) {
   punteggioCarta = 16; }
  else if (attuale->getNumero() == 5) {
   punteggioCarta = 15; }
  else if (attuale->getNumero() == 4) {
   punteggioCarta = 14; }
  else if (attuale->getNumero() == 3) {
   punteggioCarta = 13; }
  else if (attuale->getNumero() == 2) {
   punteggioCarta = 12; }
  else {
   punteggioCarta = 10; }
  
  if (attuale->getSeme().compare("Denara") == 0 && punteggioCarta > punteggioDenara) { // Controllo il seme e aggiorno il punteggio giusto
   punteggioDenara = punteggioCarta; }
  else if (attuale->getSeme().compare("Spade") == 0 && punteggioCarta > punteggioSpade) {
   punteggioSpade = punteggioCarta; }
  else if (attuale->getSeme().compare("Coppe") == 0 && punteggioCarta > punteggioCoppe) {
   punteggioCoppe = punteggioCarta; }
  else if (attuale->getSeme().compare("Bastoni") == 0 && punteggioCarta > punteggioBastoni) {
   punteggioBastoni = punteggioCarta; } }
 
 // cout << punteggioDenara << " " << punteggioSpade << " " << punteggioCoppe << " " << punteggioBastoni << endl;
 return punteggioDenara + punteggioSpade + punteggioCoppe + punteggioBastoni; } // Ritorna la somma dei punteggi massimi per seme

int Mazzo::somma() { // Calcola la somma delle carte all'interno del mazzo
 int somma = 0;
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  somma = somma + attuale->getNumero(); }
 return somma; }

void Mazzo::mostraFotoCarteZoom(string display) { // Mostra le foto associate alle carte zoomate
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  attuale->mostraFotoZoom(display); } }

void Mazzo::mostraFotoCarteRettangolo(string display) { // Mostra le foto con le carte circondate da rettangoli
 for (int i = 1; i <= numeroCarte(); i++) {
  Carta* attuale = getCarta(i);
  attuale->mostraFotoRettangolo(display); } }

Mat Mazzo::concatenaCarte(bool small) { // Restituisce una foto che mostra le carte concatenate
 // SETTAGGIO DIMENSIONE DI UNA CARTA CONCATENATA
 int y;
 int x;
 if (small == true) {
  y = 80;
  x = 40; }
 else {
  y = 130;
  x = 75; }

 // CONCATENAZIONE CARTE
 Mat concatenata;
 if (numeroCarte() == 0) {
  concatenata = Mat::ones(y, x, CV_8UC3); }
 else {
  Carta* attuale = getCarta(1);
  concatenata = attuale->getFotoZoom();
  resize(concatenata, concatenata, Size(x, y));
  for (int i = 2; i <= numeroCarte(); i++) { // Scorre le carte e le concatena una ad una
   attuale = getCarta(i);
   Mat image = attuale->getFotoZoom();
   resize(image, image, Size(x, y));
   hconcat(concatenata, image, concatenata); }  }
 return concatenata; }
  
void Mazzo::mostraFotoCarteConcatenate(string display, string nome, int x, int y, bool small) { // Mostra le carte concatenate tra loro
 namedWindow(display, CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL); // Da' il nome alla finestra
 /* PARAMETRI:
 CV_WINDOW_AUTOSIZE: le dimensioni della finestra si adattano automaticamente a quelle dell'immagine
 CV_WINDOW_KEEPRATIO: le dimensioni della finestra mantengono la stessa ratio altezza/larghezza di quella dell'immagine
 CV_GUI_NORMAL: la finestra viene mostrata SENZA la barra degli strumenti */
 moveWindow(display, x, y); // Sposta la finestra nelle coordinate x e y desiderate
 Mat concatenata = concatenaCarte(small); // Concatena le carte alla dimensione desiderata

 // CARICAMENTO TAGLIANDO
 string directory; // Il tagliando contiene una frase che precede le carte concatenate
 if (display.compare("Mano " + nome) == 0) {
  directory = "Grafica/TagliandoGiocatore.jpg"; }
 else if (display.compare("Tavolo") == 0) {
  directory = "Grafica/TagliandoTavolo.jpg"; }
 else if (display.compare("Mano CPU") == 0) {
  directory = "Grafica/TagliandoCPU.jpg"; }
 else if (display.compare("Carte Pescate " + nome) == 0) {
  directory = "Grafica/TagliandoPescateGiocatore.jpg"; }
 else if (display.compare("Carte Pescate CPU") == 0) {
  directory = "Grafica/TagliandoPescateCPU.jpg"; }
 else {
  directory = "Grafica/TagliandoChePeschi.jpg"; }
 Mat tagliando = imread(directory, IMREAD_COLOR);
 if (tagliando.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory " + directory); }
 hconcat(tagliando, concatenata, concatenata);

 imshow(display, concatenata); // Mostra le carte concatenate
 waitKey(200); } // Il waitKey(200) e' essenziale per evitare alcuni glitch grafici...

void Mazzo::mostraFotoCarteConcatenateCoperte(string display, int scoperto) { // Mostra il RETRO delle carte concatenate
 Mat retro = imread("Grafica/Retro.jpg", IMREAD_COLOR);
 if (retro.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Retro.jpg"); }
 resize(retro, retro, Size(75, 130));
 Mazzo* mazzo = new Mazzo();
 for (int i = 1; i <= numeroCarte(); i++) { // Crea un nuovo mazzo di carte coperte
  Carta* attuale;
  if (i == scoperto) { // scoperto indica il numero della carta che a differenza delle altre DEVE essere mostrata
   attuale = getCarta(i); }
  else {
   attuale = new Carta(""); 
   attuale->setFotoZoom(retro); }
  mazzo->aggiungiCarta(attuale); }
 mazzo->mostraFotoCarteConcatenate(display, "", 80, 420, false);
 if (scoperto != 0) { // Se una carta e' mostrata, prolunga leggermente l'animazione
  waitKey(200); } }
   
void Mazzo::stampaCarte() { // Stampa su schermo tutte le carte presenti nel mazzo
 if (vuoto() == true) {
  cout << "Mazzo vuoto." << endl; }
 else {
  node* current = begin;
  int contatore = 1;
  while (current != 0) {
   Carta* attuale = current->carta;
   cout << contatore << ": ";
   attuale->stampaCarta();
   cout << endl;
   contatore = contatore + 1;
   current = current->next; } } }

void Mazzo::stampaCarteCoperte() { // Stampa su schermo le carte, ma senza dire nulla su numero e seme
 if (vuoto() == true) {
  cout << "Mazzo vuoto." << endl; }
 else {
  node* current = begin;
  int contatore = 1;
  while (current != 0) {
   cout << contatore << ": [?]" << endl;
   contatore = contatore + 1;
   current = current->next; } } }
