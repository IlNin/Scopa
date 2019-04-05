#include "ScopaUtil.hpp"

using namespace std;

// DICHIARAZIONE VARIABILI GLOBALI
bool lock = true; // Blocca la capacita' del programma di accettare il click del mouse
bool lockMenu = false; // Blocca la capacità dell'utente di utilizzare i pulsanti del menu
int cartaGiocatoreClickSX = 0; // Indica il numero della carta del giocatore cliccata con il pulsante sinistro del mouse
int cartaGiocatoreClickDX = 0; // Indica il numero della carta del giocatore cliccata con il pulsante destro del mouse
int cartaTavoloClickDX = 0; // Indica il numero della carta sul tavolo cliccata con il pulsante destro del mouse
int cartaCPUClickDX = 0; // Indica il numero della carta della CPU cliccata con il pulsante destro del mouse
int inputMenu = 0; // Indica l'opzione scelta dal giocatore nel menu
int inputCombinazione = 0; // Indica la combinazione di carte scelta dal giocatore
int inputContinui = 0; // Indica se il giocatore vuole continuare la partita
bool carteCoperte = false; // Indica se il giocatore vuole giocare con le carte coperte
bool testCarte = false; // Indica se il giocatore ha chiesto di fare un test sulle carte

string inserisciNome() { // Permette all'utente di inserire il proprio nome
 string nome;
 bool flag = false; // Indica se l'inserimento del nome e' stato fallito almeno una volta
 while (true) { // Ciclo infinito finche' non viene scelto un nome corretto
  if (flag == false) { // Il messaggio iniziale viene stampato solo una volta
   cout << "Inserisci il tuo nome! (3-8 caratteri, spazi esclusi)" << endl; }
  else { // Messaggio stampato in caso di nome invalido
   cout << "Nome invalido! Prova di nuovo!" << endl; }
  cout << ">> ";
  getline(cin, nome); // Legge una riga di input (fino a che non viene premuto ENTER) e la salva in 'nome'
  string::iterator it = remove(nome.begin(), nome.end(), ' '); // Sposta tutti gli elementi con spazio dopo 'nome.end()'
  nome.erase(it, nome.end()); // Ridimensiona la stringa fino a 'nome.end()', cancellando di fatto tutti gli elementi con spazio
  if (nome.size() >= 3 && nome.size() <= 8 && nome.compare("CPU") != 0) { // Controlla se il nome contiene il numero giusto di caratteri
   return nome; }
  flag = true; } }
 
void daiCarteMano(Mazzo* mazzo, Utente* utente, CPU* cpu, bool giocatore, bool presente[]) { // Forma una mano per il giocatore o la CPU
 // INIZIALIZZAZIONE VARIABILI
 Mazzo* mano;
 string nome;
 bool coperto;
 if (giocatore == true) { // Controlla a CHI dare le carte
  mano = utente->getMano(); 
  nome = utente->getNome(); }
 else {
  mano = cpu->getMano();
  coperto = cpu->getCoperto(); }
 
 // ASSEGNAMENTO CARTE
 for (int i = 0; i < 3; i++) {
  Carta* attuale = mazzo->rimuoviCarta(1);
  mano->aggiungiCarta(attuale); }

 // MOSTRA CARTE PIXELLATE O COPERTE
 if (giocatore == true) {
  mano->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false); }
 else if (giocatore == false && coperto == false) {
  mano->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); }
 else {
  mano->mostraFotoCarteConcatenateCoperte("Mano CPU", 0); }
 
 // RICONOSCIMENTO CARTE
 for (int i = 0; i < 3; i++) {
  Carta* attuale = mano->getCarta(i+1); 
  attuale->riconosci(); // Riconosce la carta presente nella foto e aggiorna gli attributi dell'oggetto 'carta'
  controllaIntegrita(attuale, presente); // Controlla se la carta e' un doppione
  if (giocatore == true) {
   mano->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false); }
  else if (giocatore == false && coperto == false) {
   mano->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); } } }

void daiCarteTavolo(Mazzo* mazzo, Mazzo* tavolo, bool presente[]) { // Pone le carte in tavolo dal mazzo di gioco
 for (int i = 0; i < 4; i++) { // Toglie le carte del mazzo e le mette in tavola
  Carta* attuale = mazzo->rimuoviCarta(1);
  tavolo->aggiungiCarta(attuale); }
 tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); // Mostra le carte (che sono ancora pixellate)
 for (int i = 0; i < 4; i++) { // Riconosce una ad una tutte le carte sul tavolo
  Carta* attuale = tavolo->getCarta(i+1);
  attuale->riconosci(); // Riconosce la carta presente nella foto e aggiorna gli attributi dell'oggetto 'carta'
  controllaIntegrita(attuale, presente);
  tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); } }

void controllaIntegrita(Carta* carta, bool presente[]) { // Controlla che la carta riconosciuta non sia un doppione
 int id;
 int numero = carta->getNumero()-1;
 string seme = carta->getSeme();
 if (seme.compare("Denara") == 0) {
  id = numero; }
 else if (seme.compare("Spade") == 0) {
  id = numero + 10; }
 else if (seme.compare("Coppe") == 0) {
  id = numero + 20; }
 else if (seme.compare("Bastoni") == 0) {
  id = numero + 30; }
 if (presente[id] == true) {
  throw std::invalid_argument("La carta nella directory " + carta->getDirectory() + " è un doppione"); }
 else {
  presente[id] = true; } }
  
 
void istruzione(bool flag) { // Mostra una finestra che dice se il giocatore puo' tirare
 Mat istruzione;
 if (flag == true) { // Il giocatore puo' tirare
  istruzione = imread("Grafica/TagliandoToccaATe.jpg", IMREAD_COLOR);
  if (istruzione.empty()) {
   throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/TagliandoToccaATe.jpg"); } }
 else { // Il giocatore deve attendere che arrivi il suo turno
  istruzione = imread("Grafica/TagliandoAspetta.jpg", IMREAD_COLOR);
  if (istruzione.empty()) {
   throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/TagliandoAspetta.jpg"); } }
 namedWindow("Istruzione", CV_GUI_NORMAL);
 resizeWindow("Istruzione", 255, 40); // Per qualche motivo, CV_WINDOW_AUTOSIZE e CV_WINDOW_KEEPRATIO non funzionano correttamente qui
 moveWindow("Istruzione", 80, 30);
 imshow("Istruzione", istruzione);
 waitKey(200); }

void scopa(bool flag) { // Stampa il messaggio che indica che c'e' stata Scopa
 Mat scopa;
 if (flag == true) { // E' stato il giocatore a fare Scopa
  scopa = imread("Grafica/TagliandoScopaGiocatore.jpg", IMREAD_COLOR);
  if (scopa.empty()) {
   throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/TagliandoScopaGiocatore.jpg"); } }
 else { // E' stata la CPU a fare scopa
  scopa = imread("Grafica/TagliandoScopaCPU.jpg", IMREAD_COLOR);
  if (scopa.empty()) {
   throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/TagliandoScopaCPU.jpg"); } }
 namedWindow("Scopa", CV_GUI_NORMAL);
 resizeWindow("Scopa", 255, 40); // Per qualche motivo, CV_WINDOW_AUTOSIZE e CV_WINDOW_KEEPRATIO non funzionano correttamente qui
 moveWindow("Scopa", 190, 310);
 imshow("Scopa", scopa);
 waitKey(800);
 destroyWindow("Scopa"); }
 
void controllaStatoFinestre(Utente* utente, Mazzo* tavolo, CPU* cpu) { // Controlla se le finestre sono state chiuse
 string nome = utente->getNome();
 bool coperto = cpu->getCoperto();
 if (getWindowProperty("Istruzione", WND_PROP_VISIBLE) < 1) {
  cout << "Non chiudere le finestre prego..." << endl;
  istruzione(true); }
 if (getWindowProperty("Mano " + nome, WND_PROP_VISIBLE) < 1) {
  cout << "Non chiudere le finestre prego..." << endl;
  utente->getMano()->mostraFotoCarteConcatenate("Mano " + nome, nome, 80, 100, false); }
 if (getWindowProperty("Tavolo", WND_PROP_VISIBLE) < 1) {
  cout << "Non chiudere le finestre prego..." << endl;
  tavolo->mostraFotoCarteConcatenate("Tavolo", "", 45, 260, false); }
 if (getWindowProperty("Mano CPU", WND_PROP_VISIBLE) < 1) {
  cout << "Non chiudere le finestre prego..." << endl;
  if (coperto == true) {
   cpu->getMano()->mostraFotoCarteConcatenateCoperte("Mano CPU", 0); }
  else {
   cpu->getMano()->mostraFotoCarteConcatenate("Mano CPU", "", 80, 420, false); } } }

// METODO STRETTAMENTE COLLEGATO A toccaCarta
void CallBackManoGiocatore(int event, int x, int y, int flags, void* param) {
 if (event == EVENT_RBUTTONDOWN && lock == false && x > 30) { // Una carta viene toccata con il mouse sinistro
  cartaGiocatoreClickDX = ((x-30)/75)+1; } // I 30 bit di differenza si riferiscono al tagliando prima delle carte
 if (event == EVENT_LBUTTONDOWN && lock == false && x > 30) { // Una carta viene toccata con il mouse destro
  cartaGiocatoreClickSX = ((x-30)/75)+1; } }

// METODO STRETTAMENTE COLLEGATO A toccaCarta
void CallBackTavolo(int event, int x, int y, int flags, void* param) {
 if (event == EVENT_RBUTTONDOWN && lock == false && x > 30) {
  cartaTavoloClickDX = ((x-30)/75)+1; } }

// METODO STRETTAMENTE COLLEGATO A toccaCarta
void CallBackManoCPU(int event, int x, int y, int flags, void* param) { 
 if (event == EVENT_RBUTTONDOWN && lock == false && x > 30) {
  cartaCPUClickDX = ((x-30)/75)+1; } }
 
Carta* toccaCarta(Utente* utente, Mazzo* tavolo, CPU* cpu) { // Chiede al giocatore di toccare una carta per tirarla
 cout << "Clicca la carta che vuoi tirare!" << endl;
 istruzione(true);
 lock = false; // Lock abbassato: ora e' possibile interagire con le carte!
 setMouseCallback("Mano " + utente->getNome(), CallBackManoGiocatore, NULL); // Vengono associati gli eventi ai vari mazzi
 setMouseCallback("Tavolo", CallBackTavolo, NULL);
 setMouseCallback("Mano CPU", CallBackManoCPU, NULL);
 
 Mazzo* manoGiocatore = utente->getMano();
 Mazzo* manoCPU = cpu->getMano();
 while (cartaGiocatoreClickSX == 0) { // Cicla finche' non arriva un input per tirare una carta
  // CONTROLLO STATO FINESTRE
  controllaStatoFinestre(utente, tavolo, cpu); // Controlla se le finestre sono state chiuse
  
  // CONTROLLO PULSANTE DESTRO
  if (cartaGiocatoreClickDX != 0) { // E' stato premuto il pulsante destro sulla mano del giocatore!
   if (manoGiocatore->numeroCarte() == 0) { // Se la mano e' vuota, non fa nulla e ripristina tutto come era prima
    cartaGiocatoreClickDX = 0;
    continue; }
   Carta* attuale = manoGiocatore->getCarta(cartaGiocatoreClickDX); // Prende la carta selezionata
   cartaGiocatoreClickDX = 0; // Ripristina l'input
   attuale->mostraFotoRettangolo("Display"); } // Osserva la carta selezionata!
  else if (cartaTavoloClickDX != 0) { // Come sopra, ma per le carte sul tavolo!
   if (tavolo->numeroCarte() == 0) {
    cartaTavoloClickDX = 0;
    continue; }
   Carta* attuale = tavolo->getCarta(cartaTavoloClickDX);
   cartaTavoloClickDX = 0;
   attuale->mostraFotoRettangolo("Display"); }
  else if (cartaCPUClickDX != 0) { // Come sopra, ma per le carte della CPU!
   if (manoCPU->numeroCarte() == 0) {
    cartaCPUClickDX = 0;
    continue; }
   if (cpu->getCoperto() == true) { // Se la CPU gioca con le carte coperte, ovviamente e' impossibile visualizzarle
    cout << "Non starai mica cercando di barare?!" << endl; }
   else {
    Carta* attuale = manoCPU->getCarta(cartaCPUClickDX);
    attuale->mostraFotoRettangolo("Display"); }
   cartaCPUClickDX = 0; }
  
  // PERMETTE GLI INPUT TRAMITE MOUSE
  waitKey(1); }

 Carta* attuale = manoGiocatore->rimuoviCarta(cartaGiocatoreClickSX); // E' stata scelta la carta da tirare!
 lock = true; // Lock rialzato: ora gli input saranno ignorati!
 cartaGiocatoreClickSX = 0; // Viene ripristinato l'input
 cout << "Hai tirato la carta: ";
 attuale->stampaCarta(); 
 cout << endl;
 return attuale; }
 
// METODO STRETTAMENTE COLLEGATO A scegliCombinazione
void CallBackCombinazione(int event, int x, int y, int flags, void* param) {
 int i = *((int*) param); // Ogni finestra contenente una combinazione avra' un int i totalmente differente!
 if (event == EVENT_LBUTTONDOWN && x > 30) {
  inputCombinazione = i; } } // Si aggiorna inputCombinazione con il valore di i per sapere quale finestra e' stata toccata!
  
Mazzo* scegliCombinazione(vector<Mazzo*> mazziPossibili, Utente* utente, Mazzo* tavolo, CPU* cpu) { // Chiede al giocatore quale combinazione vuole pescare
 vector<Mazzo*>::iterator it = mazziPossibili.begin(); // Crea un iteratore dei mazzi pescabili
 int i = 1; // Ogni mazzo pescabile e' contrassegnato da un int i differente!

 // STAMPA SU SCHERMO DELLE COMBINAZIONI
 while (it != mazziPossibili.end()) { // Cicla i mazzi pescabili
  Mazzo* attuale = *it;
  stringstream ss;
  ss << i;
  string contatore = ss.str(); // Converto i da int a string
  attuale->mostraFotoCarteConcatenate("Combinazione " + contatore, "", 400, 130*i, false); // L'asse y della finestra dipende da i
  int* contrassegnaFinestra = new int(i); // Viene allocata una nuova porzione di memoria per l'int che contrassegna il mazzo pescabile
  setMouseCallback("Combinazione " + contatore, CallBackCombinazione, contrassegnaFinestra); // Viene associato l'evento al mazzo attuale
  i = i + 1;
  it++; }
 
 // ATTESA INPUT
 while (inputCombinazione == 0) {
  controllaStatoFinestre(utente, tavolo, cpu); // Controlla che nessuna finestra sia chiusa...
  for (int x = 1; x <= i-1; x++) { //... comprese quelle che mostrano le combinazioni!
   stringstream ss;
   ss << x;
   string contatore = ss.str();
   if (getWindowProperty("Combinazione " + contatore, WND_PROP_VISIBLE) < 1) {
    cout << "Non chiudere le finestre prego..." << endl;
    mazziPossibili.at(x-1)->mostraFotoCarteConcatenate("Combinazione " + contatore, "", 400, 130*x, false); } }
  waitKey(1); }

 // INPUT RICEVUTO
 for (int x = 1; x <= i-1; x++) { // Dopo aver ricevuto l'input, tutte le finestre con le combinazioni vengono chiuse
  stringstream ss;
  ss << x;
  string contatore = ss.str();
  destroyWindow("Combinazione " + contatore); }
 Mazzo* attuale = mazziPossibili.at(inputCombinazione-1);
 cout << "Hai pescato la combinazione " << inputCombinazione << "!" << endl;
 inputCombinazione = 0; // Viene ripristinato l'input
 return attuale; }

bool mossaGiocatore(Carta* carta, Utente* utente, Mazzo* tavolo, CPU* cpu) { // Analizza le conseguenze della carta tirata dal giocatore
 vector<Mazzo*> mazziPossibili; // Contiene le carte che il giocatore potrebbe pescare. Ogni possibile pescata e' contenuta in un mazzo diverso
 Mazzo* carteVinte = utente->getCarteVinte();
 
 // CONFRONTO CARTA SINGOLA
 for (int i = 1; i <= tavolo->numeroCarte(); i++) { // In Scopa è obbligatorio pescare le carte singole se presenti
  Carta* cartaAttuale = tavolo->getCarta(i);
  if (cartaAttuale->getNumero() == carta->getNumero()) {
   Mazzo* mazzoAttuale = new Mazzo;
   mazzoAttuale->aggiungiCarta(cartaAttuale);
   mazziPossibili.push_back(mazzoAttuale); } }
 
 // CONFRONTO CARTE MULTIPLE
 if (mazziPossibili.empty()) { // Non e' stato possibile pescare una carta singola
  mazziPossibili = pescaCarteMultiple(carta, tavolo, new Mazzo, mazziPossibili, 0); } // Guarda se e' possibile pescare carte multiple
 
 // CONTROLLO CARTE PESCATE
 bool esito;
 if (mazziPossibili.empty()) { // Non e' stato pescato nulla
  cout << "Non hai pescato nulla!" << endl; 
  tavolo->aggiungiCarta(carta);
  esito = false; }

 else if (mazziPossibili.size() == 1) { // E' stata pescata una sola combinazione di carte
  Mazzo* mazzoAttuale = mazziPossibili.front();
  cout << "Hai pescato le seguenti carte: ";
  for (int i = 1; i <= mazzoAttuale->numeroCarte(); i++) {
   Carta* cartaAttuale = mazzoAttuale->getCarta(i);
   cartaAttuale->stampaCarta();
   cout << " ";
   carteVinte->aggiungiCarta(cartaAttuale);
   tavolo->rimuoviCarta(cartaAttuale); } 
  cout << endl;
  carteVinte->aggiungiCarta(carta);
  esito = true; }

 else { // Sono state pescate piu' combinazioni di carte
  vector<Mazzo*>::iterator it = mazziPossibili.begin();
  int contatore = 1;
  cout << "Scegli che combinazione vuoi pescare!" << endl;
  while (it != mazziPossibili.end()) { // Stampa su schermo tutte le possibili combinazioni
   Mazzo* mazzoAttuale = *it;
   cout << "Combinazione " << contatore << ": " << endl; 
   mazzoAttuale->stampaCarte();
   contatore++;
   it++; }
  Mazzo* mazzoAttuale = scegliCombinazione(mazziPossibili, utente, tavolo, cpu); // Fa scegliere una combinazione all'utente
  for (int i = 1; i <= mazzoAttuale->numeroCarte(); i++) {
   Carta* cartaAttuale = mazzoAttuale->getCarta(i);
   carteVinte->aggiungiCarta(cartaAttuale); 
   tavolo->rimuoviCarta(cartaAttuale); }
  carteVinte->aggiungiCarta(carta);
  esito = true; }
 
 istruzione(false);
 return esito; }
 
bool mossaCPU(Utente* utente, Mazzo* tavolo, CPU* cpu) { // Permette alla CPU di tirare una carta 
 istruzione(false); // Stampa messaggio che indica su schermo che l'utente non può tirare
 Mazzo* mano = cpu->getMano();
 Mazzo* carteVinte = cpu->getCarteVinte();
 Mazzo* carteVinteGiocatore = utente->getCarteVinte();
 Mazzo* pescataScelta = new Mazzo; // Mazzo che contiene la pescata scelta dalla CPU
 int indiceCartaScelta = 0;
 int punteggioMax = 0; // Punteggio del mazzo che contiene la pescata scelta dalla CPU

 for (int i = 1; i <= mano->numeroCarte(); i++) { // Scorre tutte le carte in mano della CPU
  vector<Mazzo*> mazziPossibili; // Contiene le carte che la CPU potrebbe pescare. Ogni possibile pescata e' contenuta in un mazzo diverso
  Carta* attualeTirata = mano->getCarta(i); 

  // CONFRONTO CARTA SINGOLA
  for (int j = 1; j <= tavolo->numeroCarte(); j++) { // In Scopa è obbligatorio pescare le carte singole se presenti
   Carta* attualeTavolo = tavolo->getCarta(j);
   if (attualeTirata->getNumero() == attualeTavolo->getNumero()) {
    Mazzo* mazzoAttuale = new Mazzo;
    mazzoAttuale->aggiungiCarta(attualeTavolo);
    mazziPossibili.push_back(mazzoAttuale); } }
  
  // CONFRONTO CARTE MULTIPLE
  if (mazziPossibili.empty()) { // Non e' stato possibile pescare una carta singola
   mazziPossibili = pescaCarteMultiple(attualeTirata, tavolo, new Mazzo, mazziPossibili, 0); }

  // SCELTA PESCATA MEGLIORE
  if (!mazziPossibili.empty()) { // Osserva le possibili pescate con la carta tirata attuale
   vector<Mazzo*>::iterator it = mazziPossibili.begin(); 
   while (it != mazziPossibili.end()) { // Scorre le possibili pescate
    Mazzo* attuale = *it;
    it++;
    attuale->aggiungiCarta(attualeTirata); // La carta tirata viene aggiunta alla pescata attuale (essenziale per calcolare il giusto punteggio)
    int punteggio = assegnaPunteggioPescata(attuale, utente, tavolo, cpu); // Assegna un punteggio alla pescata attuale
    if (punteggio >= punteggioMax) { // Il punteggio attuale supera il record
     punteggioMax = punteggio; // Viene aggiornato il punteggio massimo
     pescataScelta->svuota(); // La pescata migliore precedente viene cancellata...
     indiceCartaScelta = i;
     pescataScelta->aggiungiMazzo(attuale); } } } } // ... e aggiornata con quella attuale
  
 // TIRO CARTA IN CASO LA CPU PESCHI QUALCOSA
 if (!pescataScelta->vuoto()) { 
  int lunghezza = pescataScelta->numeroCarte();
  Carta* tirata = pescataScelta->rimuoviCarta(lunghezza); // L'ultimo elemento di 'pescataScelta' e' sempre la carta tirata
  cout << "La CPU ha tirato la carta: ";
  tirata->stampaCarta();
  cout << endl;
  cout << "La CPU ha pescato le seguenti carte: ";
  for (int i = 1; i <= lunghezza-1; i++) {
   Carta* attuale = pescataScelta->getCarta(i);
   attuale->stampaCarta();
   cout << " ";
   carteVinte->aggiungiCarta(attuale);
   tavolo->rimuoviCarta(attuale); }
  cout << endl;
  carteVinte->aggiungiCarta(tirata);
  if (cpu->getCoperto() == true) { // Se la CPU gioca con le carte coperte, mostro brevemente la carta scoperta prima che sia tirata
   mano->mostraFotoCarteConcatenateCoperte("Mano CPU", indiceCartaScelta); }
  mano->rimuoviCarta(tirata);
  return true; }
 
 // TIRO CARTA NEL CASO IN CUI LA CPU NON POSSA PESCARE NIENTE
 else {
  Carta* tirata;
  if (mano->numeroCarte() == 1) { // La CPU ha solo una carta, quindi tira solo quella
   indiceCartaScelta = 1;
   tirata = mano->getCarta(1); }
   
  else { // La CPU ha piu' di una carta in mano
   int punteggioMin = 1000000; // L'idea e' di tirare la carta meno preziosa
   for (int i = 1; i <= mano->numeroCarte(); i++) {
    Carta* cartaAttuale = mano->getCarta(i);
    int punteggio = assegnaPunteggioNonPescata(cartaAttuale, utente, tavolo, cpu); // Assegna punteggio alla carta attuale
    if (punteggio <= punteggioMin) { // Trovata la nuova carta meno preziosa
      punteggioMin = punteggio;
      indiceCartaScelta = i;
      tirata = cartaAttuale; } } }
    
  cout << "La CPU ha tirato la carta: ";
  tirata->stampaCarta();
  cout << endl;
  cout << "La CPU non ha pescato nulla!" << endl;
  if (cpu->getCoperto() == true) { // Se la CPU gioca con le carte coperte, mostro brevemente la carta scoperta prima che sia tirata
   mano->mostraFotoCarteConcatenateCoperte("Mano CPU", indiceCartaScelta); }
  tavolo->aggiungiCarta(tirata);
  mano->rimuoviCarta(tirata); 
  return false; } }
    
int assegnaPunteggioPescata(Mazzo* mazzo, Utente* utente, Mazzo* tavolo, CPU* cpu) { // Assegna un punteggio ad una probabile pescata
 // INIZIALIZZAZIONE VARIABILI
 int punteggio = 0;
 int numeroCarte = mazzo->numeroCarte(); // Il numero di carte conferisce un bonus al punteggio
 int denaraGiocatore = utente->getCarteVinte()->numeroDenara(); // Se denara >= 6, allora il punto e' gia' perso
 int denaraCPU = cpu->getCarteVinte()->numeroDenara(); // Se denara >= 6, allora il punto e' gia' vinto
 int primieraGiocatore = utente->getCarteVinte()->primiera(); // Se primiera == 84 (tutti i 7 pescati), allora il punto e' gia' perso
 int primieraCPU = cpu->getCarteVinte()->primiera(); // Se primiera == 84 (tutti i 7 pescati), allora il punto e' gia' vinto

 // CALCOLO PUNTEGGIO
 punteggio = punteggio + numeroCarte; // Viene dato un bonus iniziale al punteggio in base al numero di carte nel mazzo
 if ((numeroCarte-1) == tavolo->numeroCarte()) { // Viene dato un bonus iniziale se e' scopa 
  punteggio = punteggio + 1000; } // NOTA: Viene tolto 1 al numero di carte perche' il mazzo contiene anche la carta tirata
 for (int i = 1; i <= numeroCarte; i++) { // Scorre tutte le carte del mazzo
  Carta* attuale = mazzo->getCarta(i);
  int numero = attuale->getNumero();
  string seme = attuale->getSeme();
  if (numero == 7 && seme.compare("Denara") == 0) { // Priorita' assoluta al 7 Bello
   punteggio = punteggio + 1000; }
  if (seme.compare("Denara") == 0 && denaraGiocatore < 6 && denaraCPU < 6) { // Punti bonus se la carta e' di "Denara"
   punteggio = punteggio + 10; }
  if (numero == 7) { // La priorita' ora riguarda la primiera
   punteggio = punteggio + 12; }
  else if (numero == 6 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 9; }
  else if (numero == 1 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 7; }
  else if (numero == 5 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 6; }
  else if (numero == 4 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 5; }
  else if (numero == 3 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 4; }
  else if (numero == 2 && primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 2; }
  else if (primieraGiocatore < 84 && primieraCPU < 84) {
   punteggio = punteggio + 1; } }
 return punteggio; }

int assegnaPunteggioNonPescata(Carta* carta, Utente* utente, Mazzo* tavolo, CPU* cpu) { // Assegna il punteggio ad una carta che non pesca nulla
 // INIZIALIZZAZIONE VARIABILI
 int numero = carta->getNumero(); // Il numero della carta determina il punteggio iniziale
 string seme = carta->getSeme();
 int sommaTavolo = tavolo->somma(); // Sapere la somma del tavolo e' utile se si vuole impedire al giocatore di fare Scopa al turno successivo
 int denaraGiocatore = utente->getCarteVinte()->numeroDenara(); // Se denara >= 6, allora il punto e' gia' perso
 int denaraCPU = cpu->getCarteVinte()->numeroDenara(); // Se denara >= 6, allora il punto e' gia' vinto
 int primieraGiocatore = utente->getCarteVinte()->primiera(); // Se primiera == 84 (tutti i 7 pescati), allora il punto e' gia' perso
 int primieraCPU = cpu->getCarteVinte()->primiera(); // Se primiera == 84 (tutti i 7 pescati), allora il punto e' gia' vinto

 // CALCOLO PUNTEGGIO
 int punteggio = numero; // Assegno un punteggio di base in base al numero
 if (numero == 7 && seme.compare("Denara") == 0) {
  punteggio = punteggio + 1000; }
 if (seme.compare("Denara") == 0 && denaraGiocatore < 6 && denaraCPU < 6) {
  punteggio = punteggio + 4; }
 if (sommaTavolo < 11 && (sommaTavolo + numero > 10)) { // Con la carta attuale, si impedisce categoricamente al giocatore di fare Scopa
  punteggio = punteggio - 10; }
 if (numero == 7) {
  punteggio = punteggio + 20; }
 return punteggio; }
 
vector<Mazzo*> pescaCarteMultiple(Carta* carta, Mazzo* tavolo, Mazzo* mazzo, vector<Mazzo*> mazziPossibili, int somma) { // Data una carta, calcola le carte che possono essere raccolte dal mazzo
 for (int i = 1; i <= tavolo->numeroCarte(); i++) {
  Carta* attuale = tavolo->rimuoviCarta(i); // Le carte vengono rimosse per permettere la ricorsione. Verranno riaggiunte in seguito!
  mazzo->aggiungiCarta(attuale); // La carta viene aggiunta al mazzo attuale
  somma = somma + attuale->getNumero(); // Viene aggiornata la somma attuale

  // SOMMA UGUALE AL NUMEROD DELLA CARTA TIRATA
  if (somma == carta->getNumero()) {
   Mazzo* mazzoPossibile = new Mazzo; // Viene creato un altro mazzo uguale a 'mazzo' in quanto quest'ultimo verra' sfaldato successivamente
   mazzoPossibile->aggiungiMazzo(mazzo); // Si evitano quindi side-effects!
   bool doppione = false; // Indica se il mazzoPossibile corrente e' gia' presente in mazziPossibili sotto un'altra combinazione
   vector<Mazzo*>::iterator it = mazziPossibili.begin(); // Crea un iteratore che scorre tutti i mazziPossibili
   while (it != mazziPossibili.end() && doppione == false) { // Scorre tutti i mazziPossibili per vedere se mazzoPossibile e' un doppione
    Mazzo* mazzoAttuale = *it;
    if (mazzoPossibile->confrontaMazzi(mazzoAttuale) == true) { // E' un doppione!
     doppione = true; }
    it++; }
   if (doppione == false) { // Non e' un doppione, viene quindi aggiunto a mazziPossibili
    mazziPossibili.push_back(mazzoPossibile); }
   mazzo->rimuoviCarta(attuale); // La carta viene tolta dal mazzo corrente...
   tavolo->aggiungiCarta(attuale, i); // ... e rimessa al suo posto nel tavolo!
   somma = somma - attuale->getNumero(); // La somma torna quella di prima
   return mazziPossibili; }
  
  // SOMMA DIVERSA DAL NUMERO DELLA CARTA TIRATA
  else {
   if (somma < carta->getNumero()) { // Se la somma e' ancora inferiore, ciclo nuovamente
    mazziPossibili = pescaCarteMultiple(carta, tavolo, mazzo, mazziPossibili, somma); } // mazziPossibili ricorda tutti i risultati!
   mazzo->rimuoviCarta(attuale);
   tavolo->aggiungiCarta(attuale, i);
   somma = somma - attuale->getNumero(); } }
 
 return mazziPossibili; }

int punteggioFinale(Utente* utente, CPU* cpu) { // Assegna i punteggi in base alle carte vinte a fine partita
 // INIZIALIZZAZIONE VARIABILI
 int risultatoGiocatore = 0;
 int risultatoCPU = 0;
 Mazzo* mazzoGiocatore = utente->getCarteVinte();
 Mazzo* mazzoCPU = cpu->getCarteVinte();
 int scopeGiocatore = utente->getNumeroScope();
 int scopeCPU = cpu->getNumeroScope();
 string nome = utente->getNome();
 
 // NUMERO SCOPE
 cout << "--- SCOPE: " << endl;
 cout << "Numero di scope di " << nome << ": " << scopeGiocatore << endl;
 risultatoGiocatore = risultatoGiocatore + scopeGiocatore;
 cout << "Numero di scope della CPU: " << scopeCPU << endl;
 risultatoCPU = risultatoCPU + scopeCPU;

 // CONFRONTO NUMERO CARTE
 cout << "--- NUMERO CARTE: " << endl;
 int numeroCarteGiocatore = mazzoGiocatore->numeroCarte();
 int numeroCarteCPU = mazzoCPU->numeroCarte();
 cout << "Carte pescate da " << nome << ": " << numeroCarteGiocatore << endl;
 cout << "Carte pescate dalla CPU: " << numeroCarteCPU << endl;
 if (numeroCarteGiocatore > numeroCarteCPU) {
  cout << nome << " ha pescato più carte!" << endl;
  risultatoGiocatore = risultatoGiocatore + 1; }
 else if (numeroCarteCPU > numeroCarteGiocatore) {
  cout << "La CPU ha pescato più carte!" << endl;
  risultatoCPU = risultatoCPU + 1; }
 else {
  cout << nome << " e la CPU hanno pescato lo stesso numero di carte!" << endl; }

 // CONFRONTO SETTE BELLO
 cout << "--- SETTE BELLO: " << endl;
 bool setteBelloGiocatore = mazzoGiocatore->setteBello();
 if (setteBelloGiocatore) {
  cout << nome << " ha pescato il 7 Bello!" << endl;
  risultatoGiocatore = risultatoGiocatore + 1; }
 else {
  cout << "La CPU ha pescato il 7 Bello!" << endl;
  risultatoCPU = risultatoCPU + 1; }
 
 // CONFRONTO DENARA
 cout << "--- NUMERO DENARA: " << endl;
 int denaraGiocatore = mazzoGiocatore->numeroDenara();
 int denaraCPU = mazzoCPU->numeroDenara();
 cout << "Denara pescate da " << nome << ": " << denaraGiocatore << endl;
 cout << "Denara pescate dalla CPU: " << denaraCPU << endl;
 if (denaraGiocatore > denaraCPU) {
  cout << nome << " ha pescato più denara!" << endl;
  risultatoGiocatore = risultatoGiocatore + 1; }
 else if (denaraCPU > denaraGiocatore) {
  cout << "La CPU ha pescato più denara!" << endl;
  risultatoCPU = risultatoCPU + 1; }
 else {
  cout << nome << " e la CPU hanno pescato lo stesso numero di denara!" << endl; }

 // CONFRONTO PRIMIERA
 cout << "--- PRIMIERA: " << endl;
 int primieraGiocatore = mazzoGiocatore->primiera();
 int primieraCPU = mazzoCPU->primiera();
 cout << "Primiera di " << nome << ": " << primieraGiocatore << endl;
 cout << "Primiera della CPU: " << primieraCPU << endl;
 if (primieraGiocatore > primieraCPU) {
  cout << nome << " ha realizzato la primiera piu' alta!" << endl;
  risultatoGiocatore = risultatoGiocatore + 1; }
 else if (primieraCPU > primieraGiocatore) {
  cout << "La CPU ha realizzato la primiera piu' alta!" << endl;
  risultatoCPU = risultatoCPU + 1; }
 else {
  cout << nome << " e la CPU hanno realizzato la stessa primiera!" << endl; }

 // RISULTATI PARTITA
 cout << "--- PUNTEGGIO ULTIMA PARTITA: " << endl;
 cout << "Punti realizzati da " << nome << ": " << risultatoGiocatore << endl;
 cout << "Punti realizzati dalla CPU: " << risultatoCPU << endl; 
 int chiHaVinto; // 1: vince il giocatore; 2: vince la CPU; 0: pareggio
 if (risultatoGiocatore > risultatoCPU) {
  chiHaVinto = 1; }
 else if (risultatoCPU > risultatoGiocatore) {
  chiHaVinto = 2; }
 else {
  chiHaVinto = 0; }
 
 // RISULTATI FINALI
 cout << "--- PUNTEGGIO TOTALE: " << endl;
 utente->setPunteggio(utente->getPunteggio() + risultatoGiocatore);
 cpu->setPunteggio(cpu->getPunteggio() + risultatoCPU);
 cout << "Punti realizzati da " << nome << ": " << utente->getPunteggio() << endl;
 cout << "Punti realizzati dalla CPU: " << cpu->getPunteggio() << endl; 
 
 return chiHaVinto; } // chiHaVinto e' necessario per visualizzare la giusta finestra nel metodo continuaPartita

// METODO STRETTAMENTE COLLEGATO A continuaPartita
void CallBackContinui(int event, int x, int y, int flags, void* param) {
 if (event == EVENT_LBUTTONDOWN) {
  if (x >= 24 && x <= 201 && y >= 112 && y <= 172) { // Il giocatore ha premuto 'si'
   inputContinui = 1; }
  else if (x >= 210 && x <= 295 && y >= 112 && y <= 172) { // Il giocatore ha premuto 'no'
   inputContinui = 2; } } }

bool continuaPartita(Utente* utente, CPU* cpu, int chiHaVinto) { // Chiede al giocatore se vuole continuare il gioco
 // STAMPA CARTE VINTE 
 string nome = utente->getNome();
 utente->getCarteVinte()->mostraFotoCarteConcatenate("Carte Pescate " + nome, nome, 80, 100, true);
 cpu->getCarteVinte()->mostraFotoCarteConcatenate("Carte Pescate CPU", "", 80, 210, true);
 
 // STAMPA SCHERMATA ESITO
 string tagliando;
 if (chiHaVinto == 1) {
  tagliando = "Grafica/TagliandoHaiVinto.jpg"; }
 else if (chiHaVinto == 2) {
  tagliando = "Grafica/TagliandoHaiPerso.jpg"; }
 else {
  tagliando = "Grafica/TagliandoPareggio.jpg"; }
 Mat schermataEsito = imread(tagliando, IMREAD_COLOR);
 if (schermataEsito.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Continui.jpg"); }
 namedWindow("Esito", CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
 imshow("Esito", schermataEsito);
 moveWindow("Esito", 80, 300);
 
 // MOSTRA SCHERMATA 'CONTINUI?'
 cout << "Scegli se continuare!" << endl;
 namedWindow("Continui?", CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
 moveWindow("Continui?", 80, 420);
 Mat continui = imread("Grafica/Continui.jpg", IMREAD_COLOR);
 if (continui.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Continui.jpg"); }
 imshow("Continui?", continui);
 setMouseCallback("Continui?", CallBackContinui, NULL);

 // ATTESA INPUT
 while (inputContinui == 0) { // Controlla che nessuna finestra non sia stata chiusa finche' non riceve un'input
  if (getWindowProperty("Continui?", WND_PROP_VISIBLE) < 1) {
   cout << "Non chiudere le finestre prego..." << endl;
   imshow("Continui?", continui);
   moveWindow("Continui?", 80, 420); }
  if (getWindowProperty("Carte Pescate " + nome, WND_PROP_VISIBLE) < 1) {
   cout << "Non chiudere le finestre prego..." << endl;
   utente->getCarteVinte()->mostraFotoCarteConcatenate("Carte Pescate " + nome, nome, 80, 100, true); }
  if (getWindowProperty("Carte Pescate CPU", WND_PROP_VISIBLE) < 1) {
   cout << "Non chiudere le finestre prego..." << endl;
   cpu->getCarteVinte()->mostraFotoCarteConcatenate("Carte Pescate CPU", "", 80, 210, true); }
  if (getWindowProperty("Esito", WND_PROP_VISIBLE) < 1) {
   cout << "Non chiudere le finestre prego..." << endl;
   imshow("Esito", schermataEsito);
   moveWindow("Esito", 80, 300); }
  waitKey(1); }

 // INPUT ARRIVATO
 destroyWindow("Continui?");
 destroyWindow("Esito");
 destroyWindow("Carte Pescate " + nome);
 destroyWindow("Carte Pescate CPU");
 if (inputContinui == 1) {
  cout << "Hai deciso di continuare!" << endl;
  inputContinui = 0;
  return true; }
 else {
  inputContinui = 0;
  return false; } }

// METODO STRETTAMENTE COLLEGATO A menu
void CallBackMenu(int event, int x, int y, int flags, void* param) {
 if (event == EVENT_LBUTTONDOWN && lockMenu == false) {
  // GIOCA
  if (x >= 347 && x <= 451 && y >= 23 && y <= 65) { // E' stato premuto il pulsante 'gioca' e il lockMenu è abbassato
   inputMenu = 2; }
  
  // ABOUT
  else if (x >= 347 && x <= 451 && y >= 75 && y <= 117) { // E' stato premuto il pulsante 'about'
   cout << "-----------------------------------" << endl;
   cout << "|   ___   ___   ___        _____  |" << endl;
   cout << "|  |   | |   | |   | |   |   |    |" << endl;
   cout << "|  |___| |___/ |   | |   |   |    |" << endl;
   cout << "|  |   | |   | |   | |   |   |    |" << endl;
   cout << "|  |   | |___/ |___| |___|   |    |" << endl;
   cout << "|                                 |" << endl;
   cout << "-----------------------------------" << endl;
   cout << "Il classico gioco della Scopa realizzato con C++ e OpenCV!" << endl;
   cout << "Gioca con le tue carte grazie agli strumenti di ricognizione degli oggetti" << endl;
   cout << "di OpenCV e affronta una CPU avversaria che non lascia tregua!" << endl;
   cout << "COMANDI: " << endl;
   cout << "- Usa il pulsante sinistro del mouse per tirare una carta!" << endl;
   cout << "- Usa il pulsante destro del mouse per vedere la foto originale di una carta!" << endl;
   cout << endl; }

  // EXIT
  else if (x >= 366 && x <= 435 && y >= 126 && y <= 153) { // E' stato premuto il pulsante 'esci'
   inputMenu = 1; } 

  // SI
  else if (x >= 21 && x <= 55 && y >= 113 && y <= 136) { // E' stata selezionata l'opzione 'si' di 'carte coperte?'
   if (carteCoperte == false) { // Controlla se l'opzione non era gia' stata scelta prima
    carteCoperte = true;
    Mat menu = imread("Grafica/Menu2.jpg", IMREAD_COLOR);
    if (menu.empty()) {
     throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Menu2.jpg"); }
    imshow("Menu", menu); } }

  // NO
  else if (x >= 66 && x <= 101 && y >= 113 && y <= 136) { // E' stata selezionata l'opzione 'no' di 'carte coperte?'
   if (carteCoperte == true) { // Controlla se l'opzione non era gia' stata scelta prima
    carteCoperte = false;
    Mat menu = imread("Grafica/Menu1.jpg", IMREAD_COLOR);
    if (menu.empty()) {
     throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Menu1.jpg"); }
    imshow("Menu", menu); } }
  
  // TEST CARTE
  else if (x >= 21 && x <= 101 && y >= 33 && y <= 61) { // E' stata selezionata l'opzione 'test carte'
   testCarte = true; } } }

int menu() { // Mostra su schermo il menu' principale del gioco
 namedWindow("Menu", CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
 moveWindow("Menu", 80, 210);
 Mat menu = imread("Grafica/Menu1.jpg", IMREAD_COLOR);
 if (menu.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory Grafica/Menu1.jpg"); }
 imshow("Menu", menu);
 setMouseCallback("Menu", CallBackMenu, NULL);
 while (inputMenu == 0) {
  if (testCarte == true) { // Il giocatore ha richiesto un test delle carte
   lockMenu = true; // Il Menu non puo' essere utilizzato durante il test
   testCarte = false;
   controllaFoto();
   waitKey(200); // Potrebbero essersi accumulati eventi click durante l'esecuzione del metodo controllaFoto(). Vengono quindi smaltiti...
   lockMenu = false; } // ... prima che il blocco sia rialzato!
  if (getWindowProperty("Menu", WND_PROP_VISIBLE) < 1) {
   cout << "Potevi anche premere il pulsante 'Exit'..." << endl;
   inputMenu = 1; }
  waitKey(1); }
 destroyWindow("Menu");
 if (inputMenu == 2) { // Il giocatore vuole giocare
  inputMenu = 0; // Ripristino input
  if (carteCoperte == false) {
   return 1; }
  else {
   return 2; } }
 else if (inputMenu == 1) {
  cout << "Alla prossima volta!" << endl;
  return 0; } }

void controllaFoto() { // Controlla che le foto nelle directory siano valide
 // CREAZIONE SCHERMATA
 string directory;
 if (carteCoperte == false) {
  directory = "Grafica/Test1.jpg"; }
 else {
  directory = "Grafica/Test2.jpg"; }
 Mat menu = imread(directory, IMREAD_COLOR);
 if (menu.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory " + directory); }
 imshow("Menu", menu);
 waitKey(200);

 // CONTROLLO FOTO
 cout << ">>> CONTROLLO FOTO INIZIATO <<<" << endl;
 cout << endl;
 for (int i = 0; i <= 2; i++) { // Controlla una carte per volta
  bool presente[40];
  int errori = 0;
  for (int x = 0; x < 40; x++) {
   presente[x] = false; }
  string cartella;
  if (i == 0) {
   cout << "[CONTROLLO CARTELLA /CarteA]" << endl;
   cartella = "CarteA/";
   cout.flush(); }
  else if (i == 1) {
   cout << "[CONTROLLO CARTELLA /CarteB]" << endl;
   cartella = "CarteB/"; 
   cout.flush(); }
  else {
   cout << "[CONTROLLO CARTELLA /CarteC]" << endl;
   cartella = "CarteC/";
   cout.flush(); }
  bool esito = true; // Se esito == true, nessun problema riscontrato durante il test
  for (int x = 1; x < 41; x++) {
   stringstream ss;
   ss << x;
   string contatore = ss.str();
   string directory = cartella;
   directory.append(contatore);
   directory.append(".jpg");
   Carta* attuale = new Carta(directory);
   try {
    attuale->riconosci();
    cout << directory << ": ";
    attuale->stampaCarta();
    cout << endl;
    controllaIntegrita(attuale, presente); }
   catch(const std::invalid_argument& e) { // Cattura l'eccezione se le carte non vengono riconosciute
    esito = false;
    errori = errori+1;
    cout << e.what() << endl; } }

  if (esito == true) {
   cout << "Nessun problema riscontrato!" << endl; }
  else {
   if (errori == 1) {
    cout << "E' stato trovato un problema!" << endl; }
   else {
    cout << "Sono stati trovati " << errori << " problemi!" << endl; } }
  cout << endl; }

 cout << ">>> CONTROLLO TERMINATO <<<" << endl;
 cout << endl;

 // RIPRISTINO MENU PRINCIPALE
 if (carteCoperte == false) {
  directory = "Grafica/Menu1.jpg"; }
 else {
  directory = "Grafica/Menu2.jpg"; }
 menu = imread(directory, IMREAD_COLOR);
 if (menu.empty()) {
  throw std::invalid_argument("Non e' stata trovata una foto associata alla directory " + directory); }
 imshow("Menu", menu); }
