#include "../include/operaciones.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

string Operaciones::pintaComoTexto(int p){
    switch (p) {
        case 't': return "Treboles";
        case 'd': return "Diamantes";
        case 'p': return "Picas";
        case 'c': return "Corazones";
        default: return "¿?";
    }

}
string Operaciones::valorComoTexto(int v){
    switch (v){
        case 1: return "As";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: return to_string(v);
    }
}

