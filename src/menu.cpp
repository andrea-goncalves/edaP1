#include "../include/menu.h"
#include <iostream>
#include <string>
#include "../include/equipa.h"
#include "../include/lesionarSuspender.h"
#include "../include/ficheiros.h"

using namespace std;

// Menu para tratar da evolução dos jogadores (mudar posição ou treinar)
void menuTreino(Equipa& equipa) {
    int opcao;
    do {
        cout << "\n===== TREINO ESPECIFICO =====\n";
        cout << "1 - Mudar posicao\n";
        cout << "2 - Melhorar qualidade (+5 pontos)\n";
        cout << "0 - Voltar\n";
        cout << "Opcao: "; cin >> opcao;

        if (opcao == 0) break;

        int pos, idx;
        escolherJogadorGlobal(equipa, pos, idx);

        if (pos != -1) {
            if (opcao == 1) {
                int novaPos;
                cout << "Nova posicao (0-GR, 1-DEF, 2-MED, 3-AVA): "; cin >> novaPos;
                mudarPosicao(equipa, pos, idx, novaPos);
            }
            else if (opcao == 2) {
                int semanas;
                cout << "Semanas de treino: "; cin >> semanas;
                equipa.plantel[pos][idx].diasTreino = semanas;
                cout << "[INFO] " << equipa.plantel[pos][idx].nome << " em treino.\n";
            }
        }
    } while (opcao != 0);
}

// Menu para gerir lesões e castigos manualmente
void menuGestao(Equipa& equipa) {
    int opcao;
    do {
        cout << "\n===== GESTAO FISICA E DISCIPLINAR =====\n";
        cout << "1 - Aplicar lesao\n2 - Reduzir lesao\n3 - Aplicar castigo\n4 - Reduzir castigo\n0 - Voltar\n";
        cout << "Opcao: "; cin >> opcao;

        if (opcao >= 1 && opcao <= 4) {
            int numJ, semanas;
            cout << "Numero do jogador: "; cin >> numJ;
            cout << "Semanas: "; cin >> semanas;

            switch(opcao) {
                case 1: aplicarLesaoManual(equipa, numJ, semanas); break;
                case 2: reduzirLesaoManual(equipa, numJ, semanas); break;
                case 3: aplicarCastigoManual(equipa, numJ, semanas); break;
                case 4: reduzirCastigoManual(equipa, numJ, semanas); break;
            }
        }
    } while (opcao != 0);
}

// Menu para Gravar ou Carregar o estado do campeonato
void menuGravarCarregar(Equipa& equipa, int& jornada, Jogador*& listaTransferencia, int& totalTransferencias) {
    int opcao;
    do {
        cout << "\n===== GRAVAR / CARREGAR =====\n";
        cout << "1 - Gravar Campeonato\n2 - Carregar Campeonato\n0 - Voltar\n";
        cout << "Opcao: "; cin >> opcao;
        cin.ignore(); // Limpa o buffer para o getline seguinte

        if (opcao == 1 || opcao == 2) {
            string ficheiro;
            cout << "Nome do ficheiro (ex: save.txt): ";
            getline(cin, ficheiro);

            if (opcao == 1)
                gravarEquipa(equipa, jornada, ficheiro, listaTransferencia, totalTransferencias);
            else
                carregarEquipa(equipa, jornada, ficheiro, listaTransferencia, totalTransferencias);
        }
    } while (opcao != 0);
}

// Menu para editar dados biográficos do jogador
// void menuAlteracoesManuais(Equipa& equipa) {
//     int pos, idx;
//     escolherJogadorGlobal(equipa, pos, idx);
//     if (pos == -1) return;
//
//     Jogador& jg = equipa.plantel[pos][idx];
//     int opEdit;
//     do {
//         cout << "\n--- Editar: " << jg.nome << " ---\n";
//         cout << "1 - Nome\n2 - Idade\n3 - Prob. Lesao\n4 - Prob. Castigo\n0 - Concluir\n";
//         cout << "Opcao: "; cin >> opEdit;
//
//         switch(opEdit) {
//             case 1: cout << "Novo nome: "; cin.ignore(); getline(cin, jg.nome); break;
//             case 2: cout << "Nova idade: "; cin >> jg.idade; break;
//             case 3: cout << "Nova prob. lesao: "; cin >> jg.probLes; break;
//             case 4: cout << "Nova prob. castigo: "; cin >> jg.probSus; break;
//         }
//     } while (opEdit != 0);
// }

// --- MENU PRINCIPAL ---

void menuPrincipal(Equipa& equipa, int& jornada, Jogador*& listaTransferencia, int& totalTransferencias) {
    int opcao;
    do {
        cout << "\n===== MENU PRINCIPAL (Jornada " << jornada << ") =====\n";
        cout << "1 - Ver Equipa Completa\n";
        cout << "2 - Treino e Posicoes\n";
        cout << "3 - Gestao Fisica/Disciplinar\n";
        cout << "4 - Gravar / Carregar\n";
        cout << "5 - Editar Dados Jogador\n";
        cout << "0 - Sair\n";
        cout << "Opcao: "; cin >> opcao;

        switch(opcao) {
            case 1:
                imprimirPlantel(equipa);
                imprimirJogadoresLesionados(equipa.lesionados, equipa.numLesionados);
                imprimirJogadoresSuspensos1(equipa.suspensos, equipa.numSuspensos);
                break;
            case 2: menuTreino(equipa); break;
            case 3: menuGestao(equipa); break;
            case 4: menuGravarCarregar(equipa, jornada, listaTransferencia, totalTransferencias); break;
            case 5: //menuAlteracoesManuais(equipa);
                break;
            case 0: cout << "A encerrar sistema...\n"; break;
            default: cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);
}