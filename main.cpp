#include <iostream>
#include "../include/carta.hpp"
#include "../include/operaciones.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <map>
using namespace std;
vector<Carta> cartas;
Operaciones op;

// NOTA: LAS FUNCIONES GENFLOP Y GENJUEGO PUEDEN TOMAR EL MISMO ELEMENTO DEL VECTOR DE CARTAS. HAY QUE ARREGLAR ESO.



vector<Carta*> flop;
vector<Carta*> juego;

/*ABCDE - Carta Alta
AABCE - Par LISTO
AABBC - Doble Par LISTO
AAABC - Trio LISTO
ABCDE - Escalera (Para A = n y todo n subsiguiente n + 1)
PPPPP (Pinta) - Color
AABBB (par y trio) - Full House LISTO
AAAAB - Póker LISTO
AtBtCtDtEt (Para A = n y todo n subsiguiente n + 1 y con pinta igual) - Escalera de color
10t, Jt, Qt, Kt, At - Escalera Real*/

void genCartas(){
    int pintas[] = {'t', 'c', 'p', 'd'};
    for(int i = 1; i <= 13; i++){
        for(int pinta : pintas){
            cartas.emplace_back(i, pinta);
        }
    }
}



void genFlop(){
    size_t n = 4;
    size_t random;
    for(size_t i = 0; i <= n; i++){
        random = rand() % cartas.size();
        flop.emplace_back(&cartas[random]);
    }
    size_t j = 0;
    for(Carta* c : flop){
        cout << op.valorComoTexto(c->getValor()) << " " << op.pintaComoTexto(c->getPinta()) << endl;
        j++;
    }
}
void genJuego(){
    size_t n = 1;
    size_t random;
    for(size_t i = 0; i <= n; i++){
        random = rand() % cartas.size();
        juego.emplace_back(&cartas[random]);
    }
    size_t j = 0;
    for(Carta* c : juego){
        cout << op.valorComoTexto(c->getValor()) << " " << op.pintaComoTexto(c->getPinta()) << endl;
        j++;
    }
}


struct Juegos{
    vector<int> valoresFlop;
    vector<int> valoresJuego;
    vector<int> cartasEnMesa;
    map<int, int> frecuencias;

    size_t checkCoincidencia(){
        size_t parFlop = 0, parJuego = 0;
        size_t totalPares = 0;
        
        // Clear previous data
        valoresFlop.clear();
        valoresJuego.clear();
        cartasEnMesa.clear();
        frecuencias.clear();
        
        //Lógica del par para flop
        for(Carta* c : flop){
            int valorFlop = c->getValor();
            // Check if this value already exists in valoresFlop
            if(std::count(valoresFlop.begin(), valoresFlop.end(), valorFlop) > 0){
                parFlop++;
            }
            valoresFlop.push_back(valorFlop);
        }
        
        //Lógica del par para juego
        for(Carta* a : juego){
            int valorJuego = a->getValor();
            // Check if this value already exists in valoresJuego
            if(std::count(valoresJuego.begin(), valoresJuego.end(), valorJuego) > 0){
                parJuego++;
            }
            valoresJuego.push_back(valorJuego);
        }
        
        // Create union (all elements from both vectors)
        cartasEnMesa = valoresFlop; // Start with all flop values
        cartasEnMesa.insert(cartasEnMesa.end(), valoresJuego.begin(), valoresJuego.end());
        
        // Count frequencies of all cards
        for(int carta : cartasEnMesa){
            frecuencias[carta]++;
        }

        // Count intersections from frequencies (cards that appear > 1 time due to being in both sets)
        size_t interseccionSize = 0;
        for(const auto& pair : frecuencias){
            if(pair.second > 1){
                // This card appears multiple times, contributing to pairs/intersections
                interseccionSize += (pair.second - 1); // Each extra occurrence beyond 1
            }
        }

        totalPares = parFlop + parJuego + interseccionSize;
        return totalPares;
    }

    void checkManos(){
        checkCoincidencia();
        int numPar = 0;
        bool hayTrio = false;
        for(const auto& elementos : frecuencias){
            if(elementos.second > 1){
                switch(elementos.second){
                    case 2:
                        cout << "La carta " << elementos.first << " forma un par" << endl;
                        numPar++;
                        break;
                    case 3:
                        cout << "La carta " << elementos.first << " forma un trio" << endl;
                        hayTrio = true;
                        break;
                    case 4:
                        cout << "La carta " << elementos.first << " forma un poker" << endl;
                        break;
                }
            }
        }
        if(numPar >= 2){
            cout << "En la mesa hay un doble par" << endl;
        }else if(numPar == 1 && hayTrio){
            cout << "En la mesa hay un Full House" << endl;
        }
    }
};

Juegos j;

int main(){
    srand(time(NULL));
    genCartas();
    genFlop(); 
    cout << "El juego es: " << endl;
    genJuego();
    j.checkManos();



    return 0;
}