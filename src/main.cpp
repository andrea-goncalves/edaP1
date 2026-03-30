#include <iostream>
#include <iomanip>
#include <ctime>
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/equipa.h"
#include "../include/equipasAdversarias.h"
using namespace std;

int main() {
    srand(time(NULL));
    int tamanho = tamArq("../data/nomes.txt");
    string* nomeJogadores = leituraArq("../data/nomes.txt", tamanho);

    int numJogosPorFase= 17;
    int numEquipas=tamArq("../data/equipas.txt") ;
    string*adversariosNomes= leituraArq("../data/equipas.txt", numEquipas);
    equipasAdversarias* adversarios = new equipasAdversarias[numEquipas];
    for (int i = 0; i < numEquipas; i++) {
        adversarios[i].nome = adversariosNomes[i];
    }
    equipasAdversarias* adversariosFase2 = new equipasAdversarias[numEquipas];

    int jornada = 1;
    int puntos = 0;
    int golosEDA = 0, golosAdversario = 0;


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
    cout << "Numero de GR: " << numGR << endl;
    cout << "Numero de DEF: " << numDEF << endl;
    cout << "Numero de MED: " << numMED << endl;
    cout << "Numero de AVA: " << numAVA << endl;

    Jogador* gr = criarGR(nomeJogadores, tamanho, numGR, numeroCamisaGR);
    Jogador* def = criarDEF(nomeJogadores, tamanho, numDEF, numeroCamisaDEF);
    Jogador* med = criarMED(nomeJogadores, tamanho, numMED, numeroCamisaMED);
    Jogador* ava = criarAVA(nomeJogadores, tamanho, numAVA, numeroCamisaAVA);
    Jogador** plantel = gerarPlantel(gr, def, med, ava, numGR, numDEF, numMED, numAVA);

    ordenarPlantelQualidadeJogador(plantel, numGR, numDEF, numMED, numAVA);



    for (int i=0; i<17; i++ ) {
        adversariosFase2[i] = escolher(adversarios, numJogosPorFase);
        adversariosFase2[17 + i] = adversariosFase2[i];

        //cout << "Jogo " << i + 1 << " contra: " << eliminarAcentos(adversarioJornada.nome)<< endl;
    }
    /**Fase 2 (17 jogos, com as mesmas equipas e mesma ordem)
    for (int i = 0; i < 17; i++) {
        cout << "Jogo " << i+18 << " contra: " << eliminarAcentos(adversariosFase2[i].nome) << endl;
    }**/




    do {

        cout << "\n******************************\n";
        cout << "* EDA FC - " << jornada << "a Jornada - " << puntos << " pontos. *\n";
        cout << "******************************\n";

        imprimirPlantel(plantel, numGR, numDEF, numMED, numAVA);

        if (jornada > 1) {
            cout << "Resultado Anterior\n";
            cout << "Resultado: EDA FC:" << golosEDA << " - " << eliminarAcentos(adversariosFase2[jornada-2].nome) << ":" << golosAdversario << "\n";
        }

        string input;
        do {
            cout << "\n[s] Proxima Jornada\n";
            cout << "[o] Opcoes\n";
            cout << ">> ";
            getline(cin, input);

            if (input == "o") {
                cout << "\nGestao da Equipas\n";
            }

        } while (input != "s");

        jornada++;

    } while (jornada <= 34);


    delete[] gr;
    delete[] def;
    delete[] med;
    delete[] ava;
    delete[] plantel;
    delete[] nomeJogadores;
    delete[] adversarios;
    delete[] adversariosFase2;
    delete[] adversariosNomes;

    return 0;
}