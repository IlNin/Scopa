#include "Carta.hpp"

struct node {
 Carta* carta; // Utilizzo un puntatore altrimenti la variabile "carta" viene automaticamente allocata con il costruttore di default
 node* next; }; // Punta al prossimo nodo

class Mazzo {
 private:
  node* begin; // Puntatore all'inizio della lista collegata
  node* end; // Puntatore all'ultimo elemento della lista collegata
  
 public:
  Mazzo(); // Crea un mazzo vuoto
  void riempiCarte(); // Riempe il mazzo con tutte le 40 carte
  void mischiaCarte(); // Mischia le carte presenti nel mazzo
  void svuota(); // Svuota un mazzo
  bool vuoto(); // Controlla se il mazzo e' vuoto
  int numeroCarte(); // Riporta il numero di carte attualmente presenti nel mazzo
  Carta* getCarta(int); // Ottiene la carta alla posizione indicata da int
  void aggiungiCarta(Carta*); // Aggiunge una carta specifica in coda al mazzo
  void aggiungiCarta(Carta*, int); // Aggiunge una carta specifica nella posizione n del mazzo
  void rimuoviCarta(Carta*); // Rimuove una specifica carta dal mazzo
  Carta* rimuoviCarta(int); // Rimuove e restituisce una specifica carta nella posizione n del mazzo
  void aggiungiMazzo(Mazzo*); // Aggiunge un altro mazzo in coda a quello corrente
  bool confrontaMazzi(Mazzo*); // Controlla se due mazzi sono uguali
  int numeroDenara(); // Ritorna il numero di carte "denara" nel mazzo
  bool setteBello(); // Controlla se il 7 Bello e' presente nel mazzo
  int primiera(); // Calcola la primiera 
  int somma(); // Calcola la somma delle carte all'interno del mazzo
  void mostraFotoCarteZoom(string); // Mostra le foto associate alle carte zoomate
  void mostraFotoCarteRettangolo(string); // Mostra le foto con le carte circondate da rettangoli
  Mat concatenaCarte(bool); // Restituisce una foto che mostra le carte concatenate
  void mostraFotoCarteConcatenate(string, string, int, int, bool); // Mostra le carte concatenata tra loro
  void mostraFotoCarteConcatenateCoperte(string, int); // Mostra il RETRO delle carte concatenate
  void stampaCarte(); // Stampa su schermo tutte le carte presenti nel mazzo
  void stampaCarteCoperte(); // Stampa su schermo le carte, ma senza dire nulla su numero e seme
};
