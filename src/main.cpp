#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/equipa.h"
using namespace std;

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    int tamanho = tamArq("data/nomes.txt");
    string* nomeJogadores = leituraArq("data/nomes.txt", tamanho);
    int numeroCamisaGR[3] = { 1, 13, 30 };
    int numeroCamisaDEF[10] = { 2, 3, 4, 5, 12, 15, 22, 24, 25, 26 };
    int numeroCamisaMED[10] = { 6, 8, 10, 14, 16, 17, 20, 21, 23, 28 };
    int numeroCamisaAVA[7] = { 7, 9, 11, 18, 19, 27, 29 };
    int numGR = numeroGR();
    int numDEF = numeroDEF();
    int numMED = numeroMED();
    int numAVA = numeroAVA();

    int numJogadorPlantel = numGR + numDEF + numMED + numAVA;
    cout << numJogadorPlantel << endl;
    cout << "Número de GR: " << numGR << endl;
    cout << "Número de DEF: " << numDEF << endl;
    cout << "Número de MED: " << numMED << endl;
    cout << "Número de AVA: " << numAVA << endl;

    Jogador* gr = criarGR(nomeJogadores, tamanho, numGR, numeroCamisaGR);
    Jogador* def = criarDEF(nomeJogadores, tamanho, numDEF, numeroCamisaDEF);
    Jogador* med = criarMED(nomeJogadores, tamanho, numMED, numeroCamisaMED);
    Jogador* ava = criarAVA(nomeJogadores, tamanho, numAVA, numeroCamisaAVA);
    Jogador** plantel = gerarPlantel(gr, def, med, ava, numGR, numDEF, numMED, numAVA);

    ordenarPlantelQualidadeJogador(plantel, numGR, numDEF, numMED, numAVA);
    imprimirPlantel(plantel,numGR, numDEF, numMED, numAVA );

    delete[] gr;  // Recuerda liberar también los arrays intermedios
    delete[] def;
    delete[] med;
    delete[] ava;
    delete[] plantel;
    delete[] nomeJogadores;

    return 0;
}