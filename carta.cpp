#include "../include/carta.hpp"

Carta::Carta(int v, int p){
    valor = v;
    pinta = p;
}
int Carta::getValor(){
    return valor;
}
int Carta::getPinta(){
    return pinta;
}
