#include "Utente.hpp"
#include "CPU.hpp"

using namespace std;

string inserisciNome(); // Permette all'utente di inserire il proprio nome
void daiCarteMano(Mazzo*, Utente*, CPU*, bool, bool[]); // Forma una mano per il giocatore o la CPU
void daiCarteTavolo(Mazzo*, Mazzo*, bool[]); // Pone le carte nel tavolo dal mazzo di gioco
void controllaIntegrita(Carta*, bool[]); // Controlla che la carta riconosciuta non sia un doppione
void istruzione(bool); // Mostra una finestra che dice se il giocatore puo' tirare
void scopa(bool); // Stampa il messaggio che indica che c'e' stata Scopa
void controllaStatoFinestre(Utente*, Mazzo*, CPU*); // Controlla se le finestre sono state chiuse
Carta* toccaCarta(Utente*, Mazzo*, CPU*); // Chiede al giocatore di toccare una carta per tirarla
Mazzo* scegliCombinazione(vector<Mazzo*>, Utente*, Mazzo*, CPU*); // Chiede al giocatore quale combinazione vuole pescare
bool mossaGiocatore(Carta*, Utente*, Mazzo*, CPU*); // Analizza le conseguenze della carta tirata dal giocatore
bool mossaCPU(Utente*, Mazzo*, CPU*); // Permette alla CPU di tirare una carta sul tavolo di gioco
int assegnaPunteggioPescata(Mazzo*, Utente*, Mazzo*, CPU*); // Assegna un punteggio ad una probabile pescata
int assegnaPunteggioNonPescata(Carta*, Utente*, Mazzo*, CPU*); // Assegna un punteggio ad una carta che non pesca niente
vector<Mazzo*> pescaCarteMultiple(Carta*, Mazzo*, Mazzo*, vector<Mazzo*>, int); // Calcola le carte multiple che possono essere raccolte dal tavolo
int punteggioFinale(Utente*, CPU*); // Assegna i punteggi in base alle carte vinte a fine partita
bool continuaPartita(Utente*, CPU*, int); // Chiede al giocatore se vuole continuare il gioco
int menu(); // Mostra su schermo il menu' principale del gioco
void controllaFoto(); // Controlla che le foto nelle directory siano valide
