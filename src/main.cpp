#include <iostream>
#include <iomanip>
#include <ctime>
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/equipa.h"
#include "../include/equipasAdversarias.h"
#include "../include/utils.h"
#include "../include/transferencia.h"
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
    int golosEDAFC = 0;
    int golosAdversario = 0;



    int numeroCamisaGR[3] = { 1, 13, 30 };
    int numeroCamisaDEF[10] = { 2, 3, 4, 5, 12, 15, 22, 24, 25, 26 };
    int numeroCamisaMED[10] = { 6, 8, 10, 14, 16, 17, 20, 21, 23, 28 };
    int numeroCamisaAVA[7] = { 7, 9, 11, 18, 19, 27, 29 };
    int numGR = numeroGR();
    int numDEF = numeroDEF();
    int numMED = numeroMED();
    int numAVA = numeroAVA();
    int numJogadorPlantel = numGR + numDEF + numMED + numAVA;
    Jogador* gr = criarGR(nomeJogadores, tamanho, numGR, numeroCamisaGR);
    Jogador* def = criarDEF(nomeJogadores, tamanho, numDEF, numeroCamisaDEF);
    Jogador* med = criarMED(nomeJogadores, tamanho, numMED, numeroCamisaMED);
    Jogador* ava = criarAVA(nomeJogadores, tamanho, numAVA, numeroCamisaAVA);

    Equipa edaFC;
    edaFC.nome="EDA FC";
    edaFC.numJogadores[0] = numGR;
    edaFC.numJogadores[1] = numDEF;
    edaFC.numJogadores[2] = numMED;
    edaFC.numJogadores[3] = numAVA;
    edaFC.plantel=gerarPlantel(gr, def, med, ava, numGR, numDEF, numMED, numAVA);
    edaFC.pontos = 0;
    edaFC.titulares = nullptr;
    edaFC.suplentes = nullptr;
    edaFC.pontos = 0;
    Tatica taticaAtual;
    Tatica taticaUsada;



    cout << numJogadorPlantel << endl;
    cout << "Numero de GR: " << numGR << endl;
    cout << "Numero de DEF: " << numDEF << endl;
    cout << "Numero de MED: " << numMED << endl;
    cout << "Numero de AVA: " << numAVA << endl;



    ordenarPlantelNumeroJogador(edaFC);





    for (int i=0; i<17; i++ ) {
        adversariosFase2[i] = escolher(adversarios, numJogosPorFase);
        adversariosFase2[17 + i] = adversariosFase2[i];

    }

    do {

        cout << "\n******************************\n";
        cout << "* EDA FC - " << jornada << "a Jornada - " << edaFC.pontos << " pontos. *\n";
        cout << "******************************\n";


        if (jornada > 1) {

            cout << "Resultado Anterior\n";
            cout << "Resultado: EDA FC:" << golosEDAFC << " - " << eliminarAcentos(adversariosFase2[jornada-2].nome) << ":" << golosAdversario << "\n";
            imprimirTitulares(edaFC.titulares, taticaUsada);
            imprimirSuplentes(edaFC.suplentes);

        }
        imprimirPlantel(edaFC);
        string input;

        do {
            cout << "\n[s] Proxima Jornada\n";
            cout << "[o] Opcoes\n";
            cout << ">> ";
            getline(cin, input);

            if (input == "o") {
                taticaAtual = pedirTatica(taticaAtual);
            }

        } while (input != "s");

        int disponiveis[4] = { edaFC.numJogadores[0], edaFC.numJogadores[1], edaFC.numJogadores[2], edaFC.numJogadores[3] };
        Jogador** copiaPlantel = copiarPlantel(edaFC, disponiveis);
        ordenarPlantelQualidadeJogador(copiaPlantel, disponiveis);

        if (edaFC.titulares != nullptr) delete[] edaFC.titulares;
        if (edaFC.suplentes != nullptr) delete[] edaFC.suplentes;

        taticaUsada = taticaAtual;
        edaFC.titulares = escolherTitulares(copiaPlantel, disponiveis, taticaUsada);
        edaFC.suplentes = escolherSuplentes(copiaPlantel, disponiveis, taticaUsada);

        golosEDAFC = numAleatorio(0,8);
        golosAdversario = numAleatorio(0,8);

        for (int i = 0; i < 4; i++) delete[] copiaPlantel[i];
        delete[] copiaPlantel;

        if (golosEDAFC>golosAdversario) {
            edaFC.pontos += 3;
        } else if (golosEDAFC == golosAdversario) {
            edaFC.pontos += 1;
        }
        jornada++;

    } while (jornada <= 34);

    delete[] edaFC.plantel;
    delete[] edaFC.titulares;
    delete[] edaFC.suplentes;
    delete[] gr;
    delete[] def;
    delete[] med;
    delete[] ava;
    delete[] nomeJogadores;
    delete[] adversarios;
    delete[] adversariosFase2;
    delete[] adversariosNomes;



    return 0;
}

// int main() {
//     srand(time(NULL));
//     int tamanho = tamArq("../data/nomes.txt");
//     string* nomeJogadores = leituraArq("../data/nomes.txt", tamanho);
//
//     Jogador** mercado = nullptr;
//     //For para passar as jornadas
//     for (int jor = 0; jor < 34; jor++) {
//         Jogador* novosSorteados = criarAleatorio(nomeJogadores, tamanho);
//         mercado = gerarTransferencia(novosSorteados);
//     }
//     if (mercado != nullptr) {
//         imprimirListaTransferencias(mercado, 34);
//     }
//     return 0;
// }