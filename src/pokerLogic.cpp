#include "../include/pokerLogic.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

/*private:
    vector<Carta> cartas;
    vector<Carta*> flop;
    vector<Carta*> juego;
    Operaciones op;

*/



PokerLogic::PokerLogic() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void PokerLogic::genCartas() {
    int pintas[] = {'t', 'c', 'p', 'd'};
    for (int i = 1; i <= 13; i++) {
        for (int pinta : pintas) {
            cartas.emplace_back(i, pinta);
        }
    }
}


void PokerLogic::genJuego() {
    random_device rd;
    mt19937 g(rd());
    shuffle(cartas.begin(), cartas.end(), g);
    flop.clear();
    juego.clear();
    cout << "El flop, turn y river son: " << endl;
    for(int i = 0; i < 5; i++){
        flop.push_back(&cartas[i]);
        cout << " " << op.valorComoTexto(cartas[i].getValor()) << " de " << op.pintaComoTexto(cartas[i].getPinta()) << endl;
    }
    cout << "\nLas hole cards son: " << endl;
    for(int i = 5; i < 7; i++){
        juego.push_back(&cartas[i]);
        cout << " " << op.valorComoTexto(cartas[i].getValor()) << " de " << op.pintaComoTexto(cartas[i].getPinta()) << endl;
    }
}

size_t PokerLogic::Juegos::checkCoincidencia(const vector<Carta*>& flop, const vector<Carta*>& juego) {
    size_t parFlop = 0, parJuego = 0, totalPares = 0;
    valoresFlop.clear();
    valoresJuego.clear();
    pintasFlop.clear();
    pintasJuego.clear();
    valoresEnMesa.clear();
    pintasEnMesa.clear();
    frecuenciasValor.clear();
    frecuenciasPinta.clear();

    for (Carta* c : flop) {
        int valor = c->getValor();
        int pinta = c->getPinta();
        if (count(valoresFlop.begin(), valoresFlop.end(), valor) > 0) parFlop++;
        valoresFlop.push_back(valor);
        pintasFlop.push_back(pinta);
    }

    for (Carta* c : juego) {
        int valor = c->getValor();
        int pinta = c->getPinta();
        if (count(valoresJuego.begin(), valoresJuego.end(), valor) > 0) parJuego++;
        valoresJuego.push_back(valor);
        pintasJuego.push_back(pinta);
    }

    valoresEnMesa = valoresFlop;
    valoresEnMesa.insert(valoresEnMesa.end(), valoresJuego.begin(), valoresJuego.end());
    pintasEnMesa = pintasFlop;
    pintasEnMesa.insert(pintasEnMesa.end(), pintasJuego.begin(), pintasJuego.end());

    for (int val : valoresEnMesa) {
        frecuenciasValor[val]++;
    }
    for (int pin : pintasEnMesa){
        frecuenciasPinta[pin]++;
    }

    for (const auto& par : frecuenciasValor) {
        if (par.second > 1)
            totalPares += (par.second - 1);
    }

    return parFlop + parJuego + totalPares; //Solo juan agogo
}



void PokerLogic::Juegos::checkManos(const vector<Carta*>& flop, const vector<Carta*>& juego, Operaciones& op) {
    checkCoincidencia(flop, juego);
    int numPar = 0;
    bool hayTrio = false;
    bool hayColor = false;
    int pintaParaColor;
    for (const auto& elem : frecuenciasValor) {
        if (elem.second > 1) {
            switch (elem.second) {
                case 2:
                    cout << "La carta " << op.valorComoTexto(elem.first) << " forma un par" << endl;
                    numPar++;
                    break;
                case 3:
                    cout << "La carta " << op.valorComoTexto(elem.first) << " forma un trio" << endl;
                    hayTrio = true;
                    break;
                case 4:
                    cout << "La carta " << op.valorComoTexto(elem.first) << " forma un poker" << endl;
                    break;
            }
        }
    }
    if (numPar >= 2) {
        cout << "En la mesa hay un doble par" << endl;
    } else if (numPar == 1 && hayTrio) {
        cout << "En la mesa hay un Full House" << endl;
    }
    for(const auto& elem : frecuenciasPinta){
        if(elem.second == 5){
            hayColor = true;
            pintaParaColor = elem.first;
        }
    }
    if(hayColor){
        cout << "La pinta " << op.pintaComoTexto(pintaParaColor) << " forma un color" << endl;
    }
}

void PokerLogic::iniciar() {
    genCartas();
    genJuego();
    j.checkManos(flop, juego, op);
}
