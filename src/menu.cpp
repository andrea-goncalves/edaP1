
#include "../include/menu.h"
#include <iostream>
#include <string>

#include "../include/constantes.h"
#include "../include/equipa.h"
#include "../include/lesionarSuspender.h"
#include "../include/ficheiros.h"


using namespace std;

/** * @brief Exibe o menu de treino específico, permitindo ao usuário escolher entre mudar a posição de um jogador ou melhorar a qualidade de um jogador através de semanas de treino.
 *
 * O menu apresenta as opções disponíveis para o usuário e processa a escolha feita. Se o usuário optar por mudar a posição de um jogador, ele será solicitado a escolher um jogador e a nova posição desejada. Se o usuário optar por melhorar a qualidade de um jogador, ele será solicitado a escolher um jogador e o número de semanas de treino que deseja aplicar. O menu continuará sendo exibido até que o usuário escolha voltar.
 *
 * @param equipa Referência para a equipe do jogador, que será modificada com base nas escolhas feitas no menu.
 */
void menuTreino(Equipa& equipa) {
    int opcao;

    do {
        cout << "\n===== TREINO ESPECIFICO =====\n";
        cout << "1 - Mudar posicao\n";
        cout << "2 - Melhorar qualidade (+5 pontos)\n";
        cout << "0 - Voltar\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1: {
                int posAtual, idxJogador;
                escolherJogadorGlobal(equipa, posAtual, idxJogador);

                if(posAtual != -1) {
                    int novaPos;
                    cout << "\nEscolha a nova posicao (0-GR, 1-DEF, 2-MED, 3-AVA): ";
                    cin >> novaPos;
                    mudarPosicao(equipa, posAtual, idxJogador, novaPos);
                }
                break;
            }
            case 2: {
                int posAtual, idxJogador;
                escolherJogadorGlobal(equipa, posAtual, idxJogador);

                if(posAtual != -1) {
                    int semanas;
                    cout << "Quantas semanas de treino deseja? ";
                    cin >> semanas;
                    if (semanas>MAX_TEMPO_TREINO) {
                        semanas = MAX_TEMPO_TREINO;
                        cout << "foi selecionado o maximo de 5 semanas";
                    }
                    equipa.plantel[posAtual][idxJogador].diasTreino = semanas;

                    cout << "[INFO] "
                         << equipa.plantel[posAtual][idxJogador].nome
                         << " vai treinar durante " << semanas << " semanas.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcao invalida!\n";
        }

    } while(opcao != 0);
}

/** * @brief Exibe o menu de gestão física e disciplinar, permitindo ao usuário aplicar ou reduzir lesões e castigos a jogadores específicos da equipe.
 *
 * O menu apresenta as opções disponíveis para o usuário e processa a escolha feita. Se o usuário optar por aplicar ou reduzir uma lesão ou castigo, ele será solicitado a escolher um jogador e o número de semanas que deseja aplicar ou reduzir. O menu continuará sendo exibido até que o usuário escolha voltar.
 *
 * @param equipa Referência para a equipe do jogador, que será modificada com base nas escolhas feitas no menu.
 */
void menuGestao(Equipa& equipa) {
    int opcao;

    do {
        cout << "\n===== GESTAO FISICA E DISCIPLINAR =====\n";
        cout << "1 - Aplicar lesao\n";
        cout << "2 - Reduzir lesao\n";
        cout << "3 - Aplicar castigo\n";
        cout << "4 - Reduzir castigo\n";
        cout << "0 - Voltar\n";
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao >= 1 && opcao <= 4) {
            int numJ, semanas;
            cout << "Numero do jogador: ";
            cin >> numJ;
            cout << "Numero de semanas: ";
            cin >> semanas;

            if (opcao == 1) aplicarLesaoManual(equipa, numJ, semanas);
            else if (opcao == 2) reduzirLesaoManual(equipa, numJ, semanas);
            else if (opcao == 3) aplicarCastigoManual(equipa, numJ, semanas);
            else if (opcao == 4) reduzirCastigoManual(equipa, numJ, semanas);
        } else if (opcao != 0) {
            cout << "Opcao invalida!\n";
        }

    } while(opcao != 0);
}
/** * @brief Exibe o menu de gravação e carregamento, permitindo ao usuário escolher entre gravar o estado atual do campeonato em um arquivo ou carregar um estado previamente salvo.
 *
 * O menu apresenta as opções disponíveis para o usuário e processa a escolha feita. Se o usuário optar por gravar o campeonato, ele será solicitado a fornecer um nome de arquivo para salvar os dados. Se o usuário optar por carregar um campeonato, ele será solicitado a fornecer o nome do arquivo que deseja carregar. O menu continuará sendo exibido até que o usuário escolha voltar.
 *
 * @param equipa Referência para a equipe do jogador, que será modificada com base nas escolhas feitas no menu.
 * @param jornada Referência para a variável que representa a jornada atual do campeonato, que será modificada ao carregar um estado salvo.
 * @param listaTransferencia Ponteiro para a lista de jogadores disponíveis para transferência, que será modificada ao carregar um estado salvo.
 * @param totalTransferencias Referência para a variável que representa o total de transferências realizadas, que será modificada ao carregar um estado salvo.
 */
void menuGravarCarregar(Equipa& equipa, int& jornada, Jogador*& listaTransferencia, int& totalTransferencias) {
    int opcao;

    do {
        cout << "\n===== GRAVAR / CARREGAR =====\n";
        cout << "1 - Gravar Campeonato\n";
        cout << "2 - Carregar Campeonato\n";
        cout << "0 - Voltar\n";
        cout << "Opcao: ";
        cin >> opcao;

        cin.ignore();

        if (opcao == 1) {
            string ficheiro;
            cout << "Nome do ficheiro para gravar (ex: save.txt): ";
            getline(cin, ficheiro);
            gravarEquipa(equipa, jornada, ficheiro, listaTransferencia, totalTransferencias);
        } else if (opcao == 2) {
            string ficheiro;
            cout << "Nome do ficheiro a carregar: ";
            getline(cin, ficheiro);
            carregarEquipa(equipa, jornada, ficheiro, listaTransferencia, totalTransferencias);
        } else if (opcao != 0) {
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);
}

/*void menuAlteracoesManuais(Equipa& equipa) {
    int opcao;

    do {
        cout << "\n===== ALTERACOES MANUAIS =====\n";
        cout << "1 - Editar atributos de um jogador\n";
        cout << "0 - Voltar\n";
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            int posAtual, idxJogador;

            escolherJogadorGlobal(equipa, posAtual, idxJogador);

            if (posAtual != -1) {

                Jogador& jg = equipa.plantel[posAtual][idxJogador];

                int opEdit;
                do {
                    cout << "\n--- A editar: " << jg.nome << " (Camisola " << jg.numero << ") ---\n";
                    cout << "1 - Nome (Atual: " << jg.nome << ")\n";
                    cout << "2 - Idade (Atual: " << jg.idade << ")\n";
                    cout << "3 - Probabilidade de Lesao (Atual: " << jg.probLes << "%)\n";
                    cout << "4 - Probabilidade de Castigo (Atual: " << jg.probSus << "%)\n";
                    cout << "0 - Concluir Edicao\n";
                    cout << "Opcao: ";
                    cin >> opEdit;

                    if (opEdit == 1) {
                        cout << "Novo nome: ";
                        cin.ignore();
                        getline(cin, jg.nome);
                        cout << "Nome alterado com sucesso!\n";
                    }
                    else if (opEdit == 2) {
                        cout << "Nova idade: ";
                        cin >> jg.idade;
                        cout << "Idade alterada com sucesso!\n";
                    }
                    else if (opEdit == 3) {
                        cout << "Nova probabilidade de lesao (0 a 100): ";
                        cin >> jg.probLes;
                        cout << "Probabilidade alterada!\n";
                    }
                    else if (opEdit == 4) {
                        cout << "Nova probabilidade de castigo (0 a 100): ";
                        cin >> jg.probSus;
                        cout << "Probabilidade alterada!\n";
                    }
                    else if (opEdit != 0) {
                        cout << "[ERRO] Opcao invalida!\n";
                    }

                } while (opEdit != 0);
            }
        }
        else if (opcao != 0) {
            cout << "Opcao invalida!\n";
        }

    } while(opcao != 0);
}

void menuPrincipal(Equipa& equipa, int& jornada) {
    int opcao;

    do {
        cout << "\n===== MENU PRINCIPAL (Jornada " << jornada << ") =====\n";
        cout << "1 - Ver Equipa (Plantel, Lesionados, Suspensos)\n";
        cout << "2 - Treino Especifico\n";
        cout << "3 - Gestao Fisica e Disciplinar\n";
        cout << "4 - Gravar / Carregar Campeonato\n";
        cout << "5 - Alteracoes Manuais (Editar Jogadores)\n";
        cout << "6 - Escolher Convocados\n";
        cout << "0 - Avancar para o Jogo!\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                imprimirPlantel(equipa);
                imprimirJogadoresLesionados(equipa.lesionados, equipa.numLesionados);
                imprimirJogadoresSuspensos1(equipa.suspensos, equipa.numSuspensos);
                break;
            case 2:
                menuTreino(equipa);
                break;
            case 3:
                menuGestao(equipa);
                break;
            case 4:
                //menuGravarCarregar(equipa, jornada);
                break;
            case 5:
                menuAlteracoesManuais(equipa);
                break;
            case 6:
               // escolherEquipaManual(equipa);
                break;
            case 0:
                cout << "A preparar a equipa para entrar em campo...\n";
                break;
            default:
                cout << "Opcao invalida, mister!\n";
        }

    } while(opcao != 0);
}*/