//
// Created by andre on 29/03/2026.
//
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/equipa.h"
#include "../include/jogador.h"
#include "../include/ficheiros.h"
using namespace std;

Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA) {

    Jogador** plantel = new Jogador * [4];

    plantel[0] = new Jogador[numGR];
    plantel[1] = new Jogador[numDEF];
    plantel[2] = new Jogador[numMED];
    plantel[3] = new Jogador[numAVA];

    for (int i = 0; i < numGR; i++) {
        plantel[0][i] = gr[i];
    }

    for (int i = 0; i < numDEF; i++) {
        plantel[1][i] = def[i];
    }

    for (int i = 0; i < numMED; i++) {
        plantel[2][i] = med[i];
    }

    for (int i = 0; i < numAVA; i++) {
        plantel[3][i] = ava[i];
    }

    return plantel;
}

Jogador** ordenarPlantelNumeroJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA) {

    int quantidades[4] = { numGR, numDEF, numMED, numAVA };

    for (int i = 0; i < 4; i++) {
        int n = quantidades[i];

        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - j - 1; k++) {

                if (plantel[i][k].numero > plantel[i][k + 1].numero) {
                    swap(plantel[i][k], plantel[i][k + 1]);
                }

            }
        }
    }
    return plantel;
}

Jogador** ordenarPlantelQualidadeJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA) {

    int quantidades[4] = { numGR, numDEF, numMED, numAVA };

    for (int i = 0; i < 4; i++) {
        int n = quantidades[i];

        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - j - 1; k++) {

                if (plantel[i][k].qualidade < plantel[i][k + 1].qualidade) {
                    swap(plantel[i][k], plantel[i][k + 1]);
                }

            }
        }
    }

    return plantel;
}



void imprimirPlantel(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA) {
    cout << "\n*********** Plantel Disponivel: ***********\n";

    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade | Dias-Treino\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    int quantidades[4] = { numGR, numDEF, numMED, numAVA };
    for (int i = 0; i < 4; i++) {
        if (quantidades[i] > 0) {
            string posicaoAtual = plantel[i][0].posicao;

            for (int j = 0; j < quantidades[i]; j++) {
                if (plantel[i][j].posicao != posicaoAtual) {
                    cout << endl;
                    posicaoAtual = plantel[i][j].posicao;
                }

                string strLesao = to_string(plantel[i][j].probLes) + "%";
                string strCastigo = to_string(plantel[i][j].probSus) + "%";

                cout << left
                    << setw(26) << eliminarAcentos(plantel[i][j].nome) << "| "
                    << setw(4)  << plantel[i][j].numero << "| "
                    << setw(8)  << eliminarAcentos(plantel[i][j].posicao) << "| "
                    << setw(6)  << plantel[i][j].idade << "| "
                    << setw(10) << strLesao << "| "
                    << setw(12) << strCastigo << "| "
                    << setw(10) << plantel[i][j].qualidade << "| "
                    << plantel[i][j].diasTreino << endl;
            }
        }
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
}
