#pragma once
#include "carta.hpp"
#include "operaciones.hpp"
#include <vector>
#include <map>

class PokerLogic {
public:
    PokerLogic();
    void iniciar();

private:
    std::vector<Carta> cartas;
    std::vector<Carta*> flop;
    std::vector<Carta*> juego;
    Operaciones op;

    void genCartas();
    void genJuego();

    struct Juegos {
        std::vector<int> valoresFlop;
        std::vector<int> valoresJuego;
        std::vector<int> pintasFlop;
        std::vector<int> pintasJuego;
        std::vector<int> valoresEnMesa;
        std::vector<int> pintasEnMesa;
        std::map<int, int> frecuenciasValor;
        std::map<int, int> frecuenciasPinta;

        size_t checkCoincidencia(const std::vector<Carta*>& flop, const std::vector<Carta*>& juego);
        void checkManos(const std::vector<Carta*>& flop, const std::vector<Carta*>& juego, Operaciones& op);
    } j;
};

