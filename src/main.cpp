#include "../include/pokerLogic.hpp"
#include <iostream>
using namespace std;

int main(){
    int opcion;
    PokerLogic juego;
    juego.iniciar();
    for(;;){
    cout << "\n1. Volver a jugar. 2. Salir: ";
    cin >> opcion;
    if(opcion == 1){
        juego.iniciar();
    }else{
        break;
    }
    }
    return 0;
}
