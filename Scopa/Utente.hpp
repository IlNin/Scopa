#include "Giocatore.hpp"

class Utente : public Giocatore {
 private:
  string nome;
 
 public:
  Utente(string);
  string getNome();
};
