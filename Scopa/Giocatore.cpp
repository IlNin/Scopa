#include "Giocatore.hpp"

using namespace std;

Giocatore::Giocatore() {
 mano = new Mazzo();
 carteVinte = new Mazzo();
 numeroScope = 0;
 punteggio = 0; }

Mazzo* Giocatore::getMano() {
 return mano; }

void Giocatore::setMano(Mazzo* mano) {
 this->mano = mano; }

Mazzo* Giocatore::getCarteVinte() {
 return carteVinte; }

void Giocatore::setCarteVinte(Mazzo* carteVinte) {
 this->carteVinte = carteVinte; }

int Giocatore::getNumeroScope() {
 return numeroScope; }

void Giocatore::setNumeroScope(int numeroScope) {
 this->numeroScope = numeroScope; }

int Giocatore::getPunteggio() {
 return punteggio; }

void Giocatore::setPunteggio(int punteggio) {
 this->punteggio = punteggio; }
