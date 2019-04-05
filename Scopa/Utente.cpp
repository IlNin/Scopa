#include "Utente.hpp"

using namespace std;

Utente::Utente(string nome) : Giocatore() {
 this->nome = nome; }

string Utente::getNome() {
 return nome; }
 
