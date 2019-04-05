#include "Giocatore.hpp"

class CPU : public Giocatore {
 private:
  bool coperto;
 
 public:
  CPU(bool);
  bool getCoperto();
};
