//
// Created by pablo on 08/04/2026.
//
#include "../include/campeonato.h"
#include "../include/equipa.h"
#include "../include/constantes.h"
#include "../include/ficheiros.h"

#include <iostream>
#include <iomanip>

using namespace std;

void tabelaPontos(Equipa* principal, Equipa* adversarios) {
    int totalequipes = NUMERO_ADVERSARIOS + 1;
    Equipa* tabela[totalequipes];

    tabela[0] = principal;

    for (int i = 0; i < NUMERO_ADVERSARIOS; i++) {
        tabela[i + 1] = &adversarios[i];
    }
    for (int i = 0; i < totalequipes - 1; i++) {
        int maiorIdx = i;

        for (int j = i + 1; j < totalequipes; j++) {

            if (tabela[j]->pontos > tabela[maiorIdx]->pontos) {
                maiorIdx = j;
            }
            else if (tabela[j]->pontos == tabela[maiorIdx]->pontos) {
                if (tabela[j]->saldoGols > tabela[maiorIdx]->saldoGols) {
                    maiorIdx = j;
                }
            }
        }
        Equipa* temp = tabela[i];
        tabela[i] = tabela[maiorIdx];
        tabela[maiorIdx] = temp;
    }

    cout << "--------------------------------------------" <<" Tabela de Classificacao " << "--------------------------------------------" << endl;
    cout << left << setw(44) << "Equipa" << " | "
    << setw(10) << "Pontos" << " | "
    << setw(10) << "Vitorias" << " | "
    << setw(10) << "Empates" << " | "
    << setw(10) << "Derrotas" << " | "
    << setw(10) << "Saldo de Gols"
    << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

    for (int k = 0; k < totalequipes; k++) {
        cout << left
        << setw(3) << k+1 << " "
        << setw(40) << eliminarAcentos(tabela[k]->nome) << " | "
        << setw(10) <<tabela[k]->pontos << " | "
        << setw(10) <<  tabela[k]->vitorias << " | "
        << setw(10) <<  tabela[k]->empate << " | "
        << setw(10) <<  tabela[k]->derrota << " | "
        << setw(10) << tabela[k]->saldoGols
        << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
}

