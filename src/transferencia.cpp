#include "../include/transferencia.h"
#include "../include/jogador.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../include/ficheiros.h"

using namespace std;


int posicao(std::string posicao) {
    if (posicao == "GOL") return 0;
    if (posicao == "DEF") return 1;
    if (posicao == "MED") return 2;
    if (posicao == "AVA") return 3;
}

Jogador** gerarTransferencia(Jogador* aleatorios) {
    //criação do vetor
    static Jogador** listaTransferencia = new Jogador*[34];//constante jogadores transferencia(tam 34)
    static int indice = 0;

    //criação do vetor de duas dimensões
    listaTransferencia[indice] = new Jogador [2];//Constante numero jogadores Transferencia

    //criação do jogador
    for (int i = 0; i < 2; i++) { //Constante numero jogadores transferencia
        listaTransferencia[indice][i] = aleatorios[i];
    }
    //Selection Sort para ordenar os jogadores por posição
    for (int i = 0; i < 2; i++ ) {//Constante numero jogadores transferencia
        int indiceMenor = i;
        for (int j = i+1 ; j < 2; j++) {
            if (posicao(listaTransferencia[indice][j].posicao) < posicao(listaTransferencia[indice][indiceMenor].posicao)) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            std::swap(listaTransferencia[indice][i],listaTransferencia[indice][indiceMenor]);
        }
    }
    indice ++;
    return listaTransferencia;
}


void imprimirListaTransferencias(Jogador** listaTransferencia, int jornadaAtual) {

    for (int i = 0; i < 34; i++) {

        for (int j = 0; j < 2; j++) {
            cout << left
            << "J" << setw(6) << (i + 1) << "| "
            << setw(26) << eliminarAcentos(listaTransferencia[i][j].nome) << "| "
            << setw(4)  << listaTransferencia[i][j].numero << "| "
            << setw(8)  << eliminarAcentos(listaTransferencia[i][j].posicao) << "| "
            << listaTransferencia[i][j].qualidade <<"| "
            << listaTransferencia[i][j].probLes <<"| "
            << listaTransferencia[i][j].probSus <<"| "
            <<endl;
        }
        cout << "------------------------------------------------------------------\n";
    }
}