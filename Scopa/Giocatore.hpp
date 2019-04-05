#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Mazzo.hpp"

class Giocatore {
 private:
  Mazzo* mano;
  Mazzo* carteVinte;
  int numeroScope;
  int punteggio;
 
 public:
  Giocatore();
  Mazzo* getMano();
  void setMano(Mazzo*);
  Mazzo* getCarteVinte();
  void setCarteVinte(Mazzo*);
  int getNumeroScope();
  void setNumeroScope(int);
  int getPunteggio();
  void setPunteggio(int);
};

#endif
