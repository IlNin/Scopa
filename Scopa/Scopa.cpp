#include "ScopaUtil.hpp"

using namespace std;

#define TIMER 1 // Timer usato per creare le pause artificiali nel gioco

int main() {
 // MENU PRINCIPALE
 int inputMenu;
 try {
  inputMenu = menu(); }
 catch(const std::invalid_argument& e) { 
  cout << e.what() << endl;
  return 1; }
 bool coperto;
 if (inputMenu == 0) {
  sleep(1); // Per qualche motivo, questo sleep(1) evita un raro problema di segmentation fault al termine del programma...
  return 1; }
 else if (inputMenu == 1) {
  coperto = false; }
 else if (inputMenu == 2) {
  coperto = true; }

 // STAMPA LOGO
 cout << "-----------------------------------" << endl;
 cout << "|   ___   ___   ___   ___   ___   |" << endl;
 cout << "|  |   | |   | |   | |   | |   |  |" << endl;
 cout << "|  |___  |     |   | |___| |___|  |" << endl;
 cout << "|      | |     |   | |     |   |  |" << endl;
 cout << "|  |___| |___| |___| |     |   |  |" << endl;
 cout << "|                                 |" << endl;
 cout << "-----------------------------------" << endl;
 cout << "|--------- LOG DI GIOCO ----------|" << endl;
 cout << "-----------------------------------" << endl;
 cout << endl;

 // INSERIMENTO NOME
 cout << "Questo e' il log di gioco, dove verrano mostrati su schermo tutti i dati" << endl;
 cout << "attinenti alla partita in corso! Ma prima di iniziare..." << endl;
 string nome = inserisciNome();
 cout << endl;

 // CREAZIONE GIOCATORI E DICHIARAZIONE VARIABILI
 Utente* utente = new Utente(nome);
 CPU* cpu = new CPU(coperto);
 Mazzo* mazzo = new Mazzo;
 Mazzo* tavolo = new Mazzo;
 Carta* cartaTirata; // Indica l'ultima carta tirata
 bool pescato = false; // Indica se chi ha tirato la carta ha pescato qualcosa
 bool giocatoreHaPescatoPerUltimo = false; // Sapere chi ha pescato per ultimo e' fondamentale per assegnare le carte sul tavolo a fine partita
 bool giocatoreIniziaPerPrimo = true; // Indica se il giocatore inizia per primo
 int punteggio[2] = {0, 0};
 int turno = 1;
 int mano = 1;
 int partita = 1;
 bool presente[40];

 // INIZIO GIOCO
 cout << "Inizio gioco! Buon divertimento, " << nome << "!" << endl;
 sleep(TIMER);
 cout << endl;
 while ((punteggio[0] < 11 && punteggio[1] < 11) || ((punteggio[0] == punteggio[1]) && (punteggio[0] >= 11 && punteggio[1] >= 11))) {
  mazzo->riempiCarte(); // Riempe il mazzo con le carte contenenti le directory
  mazzo->mischiaCarte(); // Mischia tali carte
  for (int i = 0; i < 40; i++) {
   presente[i] = false; }
  try { // Mette quattro carte in tavolo
   cout << "[RICONOSCIMENTO CARTE TAVOLO]";
   cout.flush();
   daiCarteTavolo(mazzo, tavolo, presente);
   cout << " - [RICONOSCIMENTO EFFETTUATO!]" << endl; } 
  catch(const std::invalid_argument& e) { // Cattura l'eccezione se le carte non vengono riconosciute
   cout << " - [RICONOSCIMENTO FALLITO!]" << endl;
   cout << e.what() << endl;
   return 1; }

  // INIZIO PARTITA
  while (!mazzo->vuoto()) { // Continua finche' il mazzo con tutte le carte non e' vuoto
   try {
    cout << "[RICONOSCIMENTO CARTE MANO " << nome << "]";
    cout.flush();
    daiCarteMano(mazzo, utente, cpu, true, presente); // Vengono date tre carte in mano al giocatore...
    cout << " - [RICONOSCIMENTO EFFETTUATO!]" << endl;
    cout << "[RICONOSCIMENTO CARTE MANO CPU]";
    cout.flush();
    daiCarteMano(mazzo, utente, cpu, false, presente); // ... e alla CPU!
    cout << " - [RICONOSCIMENTO EFFETTUATO!]" << endl;
    cout << endl; }
   catch(const std::invalid_argument& e) { // Cattura l'eccezione se le carte non vengono riconosciute
    cout << " - [RICONOSCIMENTO FALLITO!]" << endl;
    cout << e.what() << endl;
    return 1; }
   try {
    utente->getMano()->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false);
    tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false);
    if (coperto == true) {
     cpu->getMano()->mostraFotoCarteConcatenateCoperte("Mano CPU", 0); }
    else {
     cpu->getMano()->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); } }
   catch(const std::invalid_argument& e) {
    cout << e.what() << endl;
    return 1; }
 
   // INIZIA MANO
   for (int i = 0; i < 3; i++) { // In una mano, giocatore e CPU tirano tre volte
    cout << "--------------------------------" << endl;
    cout << "Partita: " << partita << " | Mano: " << mano << " | Turno: " << turno << endl;
    cout << "--------------------------------" << endl;
    cout << "--- Carte di " << nome << ": " << endl;
    utente->getMano()->stampaCarte();
    cout << "--- Carte in tavola: " << endl;
    tavolo->stampaCarte();
    cout << "--- Carte della CPU: " << endl;
    if (coperto == true) {
     cpu->getMano()->stampaCarteCoperte(); }
    else {
     cpu->getMano()->stampaCarte(); }
    cout << "--------------------------------" << endl;
    if (giocatoreIniziaPerPrimo) {
     cout << "Inizia per prima " << nome << "!" << endl; 
     cout << "--------------------------------" << endl; }
    else {
     cout << "Inizia per prima la CPU!" << endl;
     cout << "--------------------------------" << endl;
     try {
      istruzione(false); }
     catch(const std::invalid_argument& e) {
      cout << e.what() << endl;
      return 1; } 
     sleep(TIMER); }
    cout << endl;

    if (giocatoreIniziaPerPrimo) { // Il giocatore inizia per prima
     try {
      cartaTirata = toccaCarta(utente, tavolo, cpu); // Il giocatore sceglie una carta
      utente->getMano()->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false);
      pescato = mossaGiocatore(cartaTirata, utente, tavolo, cpu); // La carte viene tirata
      tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); }
     catch(const std::invalid_argument& e) { 
      cout << e.what() << endl;
      return 1; }
     if (pescato) { // Se viene pescato qualcosa, viene aggiornato chi ha pescato per ultimo
      giocatoreHaPescatoPerUltimo = true; }
     if (tavolo->vuoto()) { // Se non c'e' nessuna carta sul tavolo, c'e' stata una scopa!
      cout << "Hai fatto scopa!" << endl;
      utente->setNumeroScope(utente->getNumeroScope()+1);
      scopa(true); } }

    else { // La CPU inizia per prima
     try {
      pescato = mossaCPU(utente, tavolo, cpu); // La CPU tira
      if (coperto == true) {
       cpu->getMano()->mostraFotoCarteConcatenateCoperte("Mano CPU", 0); }
      else {
       cpu->getMano()->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); }
      tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); }
     catch(const std::invalid_argument& e) {
      cout << e.what() << endl;
      return 1; }
     if (pescato) { // Osserva se la CPU ha pescato qualcosa 
      giocatoreHaPescatoPerUltimo = false; }
     if (tavolo->vuoto()) {
      cout << "La CPU ha fatto scopa!" << endl; 
      cpu->setNumeroScope(cpu->getNumeroScope()+1);
      scopa(false); } }
    sleep(TIMER);
    cout << endl;
    
    if (giocatoreIniziaPerPrimo) { // La CPU tira per seconda
     try {
      pescato = mossaCPU(utente, tavolo, cpu); // La CPU tira
      if (coperto == true) {
       cpu->getMano()->mostraFotoCarteConcatenateCoperte("Mano CPU", 0); }
      else {
       cpu->getMano()->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); }
      tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); }
     catch(const std::invalid_argument& e) {
      cout << e.what() << endl;
      return 1; }
     if (pescato) { // Osserva se la CPU ha pescato qualcosa 
      giocatoreHaPescatoPerUltimo = false; }
     if (tavolo->vuoto()) { // Se non c'e' nessuna carta sul tavolo, c'e' stata una scopa!
      cout << "La CPU ha fatto scopa!" << endl; 
      cpu->setNumeroScope(cpu->getNumeroScope()+1);
      scopa(false); } }

    else { // Il giocatore tira per secondo
     try {
      cartaTirata = toccaCarta(utente, tavolo, cpu); // Il giocatore sceglie una carta
      utente->getMano()->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false);
      pescato = mossaGiocatore(cartaTirata, utente, tavolo, cpu); // La carte viene tirata
      tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); }
     catch(const std::invalid_argument& e) { 
      cout << e.what() << endl;
      return 0; }
     if (pescato) { // Se viene pescato qualcosa, viene aggiornato chi ha pescato per ultimo
      giocatoreHaPescatoPerUltimo = true; }
     if (tavolo->vuoto()) { // Se non c'e' nessuna carta sul tavolo, c'e' stata una scopa!
      cout << "Hai fatto scopa!" << endl;
      utente->setNumeroScope(utente->getNumeroScope()+1);
      scopa(true); } }
    sleep(TIMER);
    cout << endl;
    turno = turno + 1; } 

   // FINE MANO
   turno = 1;
   mano = mano + 1; }

  // FINE PARTITA
  if (giocatoreHaPescatoPerUltimo) { // La partita e' finita e le carte sul tavolo vengono assegnate a chi ha pescato per ultimo
   cout << "Le carte nel tavolo vanno a " << nome << "!" << endl;
   utente->getCarteVinte()->aggiungiMazzo(tavolo); }
  else {
   cout << "Le carte nel tavolo vanno alla CPU!" << endl;
   cpu->getCarteVinte()->aggiungiMazzo(tavolo); }
  sleep(TIMER);
  destroyWindow("Mano " + nome);
  destroyWindow("Tavolo");
  destroyWindow("Mano CPU");
  destroyWindow("Istruzione");
  cout << endl;
  cout << "----------------------------------------" << endl;
  cout << ">>>>>>>>> RISULTATI PARTITA " << partita << " <<<<<<<<<" << endl;
  cout << "----------------------------------------" << endl;
  int chiHaVinto;
  try {
   chiHaVinto = punteggioFinale(utente, cpu); } // Vengono stampati su schermo i risultati
  catch(const std::invalid_argument& e) {
   cout << e.what() << endl;
   return 1; }
  cout << "----------------------------------------" << endl;
  cout << endl;
  bool continua;
  try {
   continua = continuaPartita(utente, cpu, chiHaVinto); }
  catch(const std::invalid_argument& e) { 
   cout << e.what() << endl;
   return 1; }
  if (continua == false) {
   cout << "Ciao, " + nome + "! Grazie per aver giocato!" << endl;
   return 0; }
  partita = partita + 1;
  turno = 1;
  mano = 1;
  giocatoreIniziaPerPrimo = !giocatoreIniziaPerPrimo; // Aggiorna chi deve iniziare per primo!
  tavolo->svuota(); // ... mentre il tavolo e le carte vinte dal giocatore e dalla CPU vengono azzerate
  utente->getCarteVinte()->svuota();
  cpu->getCarteVinte()->svuota();
  utente->setNumeroScope(0);
  cpu->setNumeroScope(0);
  punteggio[0] = utente->getPunteggio();
  punteggio[1] = cpu->getPunteggio();
  sleep(TIMER);
  cout << endl; }

 // FINE GIOCO
 cout << endl;
 if (punteggio[0] > punteggio[1]) {
  cout << nome << " ha vinto il gioco! Complimenti!" << endl; }
 else {
  cout << "La CPU ha vinto il gioco! Peccato!" << endl; }
 main(); }
