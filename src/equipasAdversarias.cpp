
#include <string>
#include <utility>
#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/equipasAdversarias.h"
using namespace std;

equipasAdversarias escolher(equipasAdversarias* array, int& disponiveis) {
    if (disponiveis <= 0) {
        return {"SEM_NOMES_DISPONIVEIS"}; //
    }
    int indice = numAleatorio(0, disponiveis - 1);
    equipasAdversarias escolhido = array[indice];
    std::swap(array[indice], array[disponiveis - 1]);
    disponiveis--;
    return escolhido;
}