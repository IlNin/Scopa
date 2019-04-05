#include "CPU.hpp"

using namespace std;

CPU::CPU(bool coperto) : Giocatore() {
 this->coperto = coperto; }

bool CPU::getCoperto() {
 return coperto; }
