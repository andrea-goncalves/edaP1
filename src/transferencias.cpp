

#include "../include/transferencias.h"
#include "../include/jogador.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../include/ficheiros.h"
#include "../include/utils.h"
#include "../include/equipa.h"
#include "../include/constantes.h"
#include "../include/lesionarSuspender.h"

using namespace std;

/**
 * @brief Converte a posição de um jogador para um índice numérico.
 *
 * @param pos A posição do jogador como string ("GR", "DEF", "MED", "AVA").
 * @return O índice correspondente à posição (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA"), ou -1 se a posição for inválida.
 */
int posicao(std::string pos) {
    if (pos == "GR") return 0;
    if (pos == "DEF") return 1;
    if (pos == "MED") return 2;
    if (pos == "AVA") return 3;
    return -1;
}
/**
 * @brief Calcula o número total de jogadores em uma equipe.
 *
 * @param equipe A equipe para a qual o total de jogadores será calculado.
 * @return O número total de jogadores na equipe.
 */
int totalJogadores(Equipa &equipe) {
    return equipe.numJogadores[0] + equipe.numJogadores[1] + equipe.numJogadores[2] + equipe.numJogadores[3];
}

/**
 * @brief Gera uma nova lista de transferências combinando jogadores novos e antigos.
 *
 * @param novos Um array de jogadores novos a serem adicionados à lista de transferências.
 * @param numNovos O número de jogadores novos no array.
 * @param listaAntiga A lista antiga de jogadores disponíveis para transferência, que será combinada com os novos jogadores.
 * @param totalTransferencias Referência para o número total de transferências realizadas, que será atualizado com o novo total após a combinação.
 * @return Um ponteiro para um novo array de jogadores que combina os jogadores antigos e novos, ordenados por posição e número.
 */
Jogador* gerarTransferencia(Jogador* novos, int numNovos, Jogador* listaAntiga, int &totalTransferencias) {
    int novoTamanho = totalTransferencias + numNovos;
    Jogador* novoVetor = new Jogador[novoTamanho];

    for (int i = 0; i < totalTransferencias; i++) {
        novoVetor[i] = listaAntiga[i];
    }

    for (int i = 0; i < numNovos; i++) {
        novoVetor[totalTransferencias + i] = novos[i];
    }
    int idx1 = novoTamanho - 2;
    int idx2 = novoTamanho - 1;

    if (posicao(novoVetor[idx2].posicao) < posicao(novoVetor[idx1].posicao)) {
        Jogador temp = novoVetor[idx1];
        novoVetor[idx1] = novoVetor[idx2];
        novoVetor[idx2] = temp;
    }
    if (listaAntiga != nullptr) {
        delete[] listaAntiga;
    }

    totalTransferencias = novoTamanho;

    return novoVetor;
}

/**
 * @brief Imprime a lista de jogadores disponíveis para transferência no mercado.
 *
 * @param listaTransf Um array de jogadores disponíveis para transferência.
 * @param totalTransf O número total de jogadores disponíveis para transferência no array.
 */
void imprimirMercado(Jogador* listaTransf, int totalTransf) {

        cout << "\n**********************\n";
        cout << "Transferencias: \n";
        cout << "| N   |Nome                      |Posicao | Idade | ProbLesao | ProbCastigo | Qualidade \n";
        cout << "-----------------------------------------------------------------------------------------\n";
        if (totalTransf == 0 || listaTransf == nullptr) {
            cout << "Nenhum jogador disponivel no mercado.\n";
        } else {
            for (int i = 0; i < totalTransf; i++) {
                cout << left
                    << setw(6)  << (i + 1)<< "| "
                    << setw(25) << eliminarAcentos(listaTransf[i].nome) << "| "
                    << setw(7)  << listaTransf[i].posicao<< "| "
                    << setw(6)  << listaTransf[i].idade << "| "
                    << setw(10)  << listaTransf[i].probLes  << "| "
                    << setw(12) <<listaTransf[i].probSus << "| "
                    << setw(10) << listaTransf[i].qualidade << endl;
            }
        }
            cout << "-----------------------------------------------------------------------------------------\n";
}

///////////////////////////////////////////////
/**
 * @brief Verifica se um jogador pode ser adicionado à equipe com base na posição e nas regras de composição da equipe.
 *
 * @param equipe A equipe à qual o jogador seria adicionado.
 * @param pos O índice da posição do jogador (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @return true se o jogador puder ser adicionado à equipe, ou false se a adição violar as regras de composição da equipe.
 */
bool podeAdicionar(Equipa &equipe, int pos) {
    int numGRsuspensos = 0, numGRlesionados = 0;
    for (int i = 0; i < equipe.numSuspensos; i++) {
        if (equipe.suspensos[i] != nullptr && equipe.suspensos[i]->posicao == "GR") {
            numGRsuspensos++;
        }
    }
    for (int i = 0; i < equipe.numLesionados; i++) {
        if (equipe.lesionados[i] != nullptr && equipe.lesionados[i]->posicao == "GR") {
            numGRlesionados++;
        }
    }
    int totalGRs = equipe.numJogadores[0] + numGRsuspensos + numGRlesionados;
    int numDEFsuspensos = 0, numDEFlesionados = 0;
    for (int i = 0; i < equipe.numSuspensos; i++) {
        if (equipe.suspensos[i] != nullptr && equipe.suspensos[i]->posicao == "DEF") {
            numDEFsuspensos++;
        }
    }
    for (int i = 0; i < equipe.numLesionados; i++) {
        if (equipe.lesionados[i] != nullptr && equipe.lesionados[i]->posicao == "DEF") {
            numDEFlesionados++;
        }
    }
    int totalDEFs = equipe.numJogadores[1] + numDEFsuspensos + numDEFlesionados;
    int numMEDsuspensos = 0, numMEDlesionados = 0;
    for (int i = 0; i < equipe.numSuspensos; i++) {
        if (equipe.suspensos[i] != nullptr && equipe.suspensos[i]->posicao == "MED") {
            numMEDsuspensos++;
        }
    }
    for (int i = 0; i < equipe.numLesionados; i++) {
        if (equipe.lesionados[i] != nullptr && equipe.lesionados[i]->posicao == "MED") {
            numMEDlesionados++;
        }
    }
    int totalMEDs = equipe.numJogadores[2] + numMEDsuspensos + numMEDlesionados;
    int numAVAsuspensos = 0, numAVAlesionados = 0;
    for (int i = 0; i < equipe.numSuspensos; i++) {
        if (equipe.suspensos[i] != nullptr && equipe.suspensos[i]->posicao == "AVA") {
            numAVAsuspensos++;
        }
    }
    for (int i = 0; i < equipe.numLesionados; i++) {
        if (equipe.lesionados[i] != nullptr && equipe.lesionados[i]->posicao == "AVA") {
            numAVAlesionados++;
        }
    }
    int totalAVAs = equipe.numJogadores[3] + numAVAsuspensos + numAVAlesionados;


    if (pos == 0 && totalGRs >= 3) return false;
    if (pos == 1 && totalDEFs >= 10) return false;
    if (pos == 2 && totalMEDs >= 10) return false;
    if (pos == 3 && totalAVAs >= 7) return false;
    return true;
}
/**
 * @brief Escolhe um número de camisa disponível para um jogador com base na posição e nos jogadores já presentes na equipe, incluindo lesionados e suspensos.
 *
 * @param equipe A equipe para a qual o jogador está sendo adicionado.
 * @param posIdx O índice da posição do jogador (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @return O número de camisa disponível escolhido para o jogador, ou -1 se não houver números disponíveis.
 */
int escolherCamisaDisponivel(Equipa &equipe, int posIdx) {
    const int* listaRef;
    int tamRef;

    if (posIdx == 0)      { listaRef = CAMISAS_GR;  tamRef = 3; }
    else if (posIdx == 1) { listaRef = CAMISAS_DEF; tamRef = 10; }
    else if (posIdx == 2) { listaRef = CAMISAS_MED; tamRef = 10; }
    else                  { listaRef = CAMISAS_AVA; tamRef = 7; }

    for (int i = 0; i < tamRef; i++) {
        bool ocupado = false;

        if (compararNumJogador(equipe.plantel[posIdx], listaRef[i], equipe.numJogadores[posIdx])) {
            ocupado = true;
        }

        if (!ocupado) {
            for (int j = 0; j < equipe.numLesionados; j++) {
                if (equipe.lesionados[j] != nullptr && equipe.lesionados[j]->numero == listaRef[i]) {
                    ocupado = true;
                    break;
                }
            }
        }

        if (!ocupado) {
            for (int j = 0; j < equipe.numSuspensos; j++) {
                if (equipe.suspensos[j] != nullptr && equipe.suspensos[j]->numero == listaRef[i]) {
                    ocupado = true;
                    break;
                }
            }
        }

        if (!ocupado) {
            return listaRef[i];
        }
    }
    return -1;
}
/**
 * @brief Adiciona um jogador à lista de transferências, criando um novo array que inclui o jogador e atualizando o total de transferências.
 *
 * @param jogador O jogador a ser adicionado à lista de transferências.
 * @param listaTransferencia Referência para o ponteiro da lista de transferências, que será atualizado para incluir o novo jogador.
 * @param totalTransferencias Referência para o número total de transferências, que será incrementado após a adição do novo jogador.
 */
void adicionarTransferencia(Jogador jogador, Jogador* &listaTransferencia, int &totalTransferencias) {
    Jogador* novoArray = new Jogador[totalTransferencias + 1];

    for (int i = 0; i < totalTransferencias; i++) {
        novoArray[i] = listaTransferencia[i];
    }

    novoArray[totalTransferencias] = jogador;

    delete[] listaTransferencia;
    listaTransferencia = novoArray;

    totalTransferencias++;
}
/**
 * @brief Adiciona um jogador ao plantel da equipe, criando um novo array para a posição do jogador e atualizando o número de jogadores nessa posição.
 *
 * @param equipe Referência para a equipe à qual o jogador será adicionado.
 * @param jogador O jogador a ser adicionado ao plantel da equipe.
 */
void adicionarJogadorPlantel(Equipa &equipe, Jogador jogador) {

    int pos = posicao(jogador.posicao);
    int tam = equipe.numJogadores[pos];

    Jogador* novoArray = new Jogador[tam + 1];

    for (int i = 0; i < tam; i++) {
        novoArray[i] = equipe.plantel[pos][i];
    }

    novoArray[tam] = jogador;

    delete[] equipe.plantel[pos];
    equipe.plantel[pos] = novoArray;

    equipe.numJogadores[pos]++;
}
/**
 * @brief Remove um jogador do plantel da equipe com base no número da camisa, adicionando o jogador removido à lista de transferências e atualizando o número total de transferências.
 *
 * @param equipe Referência para a equipe da qual o jogador será removido.
 * @param listaTransferencia Referência para o ponteiro da lista de transferências, que será atualizado para incluir o jogador removido.
 * @param totalTransferencias Referência para o número total de transferências, que será incrementado após a adição do jogador removido à lista de transferências.
 * @param numCamisa O número da camisa do jogador a ser removido do plantel da equipe.
 * @return true se o jogador foi encontrado e removido com sucesso, ou false se nenhum jogador com o número da camisa especificado foi encontrado no plantel da equipe.
 */
bool removerJogadorPlantel(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias, int numCamisa) {
    for (int i = 0; i < 4; i++) {

        int tam = equipe.numJogadores[i];

        for (int j = 0; j < tam; j++) {

            if (equipe.plantel[i][j].numero == numCamisa) {

                Jogador removido = equipe.plantel[i][j];
                removido.numero = 0;

                Jogador* novoArray = new Jogador[tam - 1];
                int k = 0;

                for (int x = 0; x < tam; x++) {
                    if (x != j) {
                        novoArray[k++] = equipe.plantel[i][x];
                    }
                }

                delete[] equipe.plantel[i];
                equipe.plantel[i] = novoArray;

                equipe.numJogadores[i]--;

                adicionarTransferencia(removido, listaTransferencia, totalTransferencias);

                return true;
            }
        }
    }

    return false;
}
/**
 * @brief Remove um jogador da lista de transferências com base no índice, criando um novo array que exclui o jogador removido e atualizando o total de transferências.
 *
 * @param listaTransferencia Referência para o ponteiro da lista de transferências, que será atualizado para excluir o jogador removido.
 * @param totalTransferencias Referência para o número total de transferências, que será decrementado após a remoção do jogador da lista de transferências.
 * @param indice O índice do jogador a ser removido da lista de transferências.
 * @return O jogador que foi removido da lista de transferências.
 */
Jogador removerTransferencia(Jogador* &listaTransferencia, int &totalTransferencias, int indice) {

    Jogador escolhido = listaTransferencia[indice];

    Jogador* novoArray = new Jogador[totalTransferencias - 1];

    int k = 0;
    for (int i = 0; i < totalTransferencias; i++) {
        if (i != indice) {
            novoArray[k++] = listaTransferencia[i];
        }
    }

    delete[] listaTransferencia;
    listaTransferencia = novoArray;

    totalTransferencias--;

    return escolhido;
}
/*
void contratarJogador(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias) {
    int indice;
    cout << "Escolha o ID do jogador (1 a " << totalTransferencias << "): ";
    cin >> indice;
    cin.ignore();

    int idx = indice - 1;
    if (idx < 0 || idx >= totalTransferencias) {
        cout << "Indice invalido!\n";
        return;
    }

    Jogador contratado = listaTransferencia[idx];
    int posIdx = posicao(contratado.posicao);

    if (podeAdicionar(equipe, posIdx) && totalJogadores(equipe) < 30) {
        removerTransferencia(listaTransferencia, totalTransferencias, idx);
        contratado.numero = escolherCamisaDisponivel(equipe, posIdx);
        adicionarJogadorPlantel(equipe, contratado);
        cout << "Contratado com sucesso! Numero: " << contratado.numero << endl;
    }
    else {
        int numCamisa;
        cout << "Limite atingido. Numero da camisa de quem sai: ";
        cin >> numCamisa;
        cin.ignore();

        int posJogadorSai = -1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < equipe.numJogadores[i]; j++) {
                if (equipe.plantel[i][j].numero == numCamisa) {
                    posJogadorSai = i;
                    break;
                }
            }
        }
        if (posJogadorSai == -1) {
            cout << "Jogador nao encontrado!\n";
            return;
        }

        if (posJogadorSai != posIdx) {
            cout << "Nao e permitido trocar jogadores de posicoes diferentes!\n";
            return;
        }


        if (removerJogadorPlantel(equipe, listaTransferencia, totalTransferencias, numCamisa)) {

            removerTransferencia(listaTransferencia, totalTransferencias, idx);
            contratado.numero = escolherCamisaDisponivel(equipe, posIdx);
            adicionarJogadorPlantel(equipe, contratado);
            cout << "Troca efetuada com sucesso! Novo numero: " << contratado.numero << endl;
        } else {
            cout << "Jogador para dispensa nao encontrado" << endl;
        }
    }
}
*/
/**
 * @brief Contrata um jogador para a equipe, permitindo a substituição de um jogador existente se o limite de jogadores for atingido.
 *
 * O usuário é solicitado a escolher um jogador da lista de transferências. Se a equipe tiver espaço para o novo jogador, ele é adicionado diretamente ao plantel. Caso contrário, o usuário deve escolher um jogador existente para ser removido da equipe, e o novo jogador é adicionado em seu lugar. A função garante que as posições dos jogadores sejam respeitadas durante a substituição.
 *
 * @param equipe Referência para a equipe à qual o jogador será contratado.
 * @param listaTransferencia Referência para o ponteiro da lista de transferências, que contém os jogadores disponíveis para contratação.
 * @param totalTransferencias Referência para o número total de transferências, que será atualizado conforme os jogadores são contratados ou removidos.
 */
void contratarJogador(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias) {
    int indice;
    cout << "Escolha o ID do jogador (1 a " << totalTransferencias << "): ";
    cin >> indice;
    cin.ignore();

    int idx = indice - 1;
    if (idx < 0 || idx >= totalTransferencias) {
        cout << "Indice invalido!\n";
        return;
    }

    Jogador contratado = listaTransferencia[idx];
    int posIdx = posicao(contratado.posicao);

    if (podeAdicionar(equipe, posIdx) && totalJogadores(equipe) < 30) {
        removerTransferencia(listaTransferencia, totalTransferencias, idx);
        contratado.numero = escolherCamisaDisponivel(equipe, posIdx);
        adicionarJogadorPlantel(equipe, contratado);
        cout << "Contratado com sucesso! Numero: " << contratado.numero << endl;
        return;
    }

    cout << "Limite atingido. Numero da camisa de quem sai: ";
    int numCamisa;
    cin >> numCamisa;
    cin.ignore();


    bool encontrado = false;
    int  posJogadorSai = -1;

    for (int i = 0; i < 4 && !encontrado; i++) {
        for (int j = 0; j < equipe.numJogadores[i] && !encontrado; j++) {
            if (equipe.plantel[i][j].numero == numCamisa) {
                posJogadorSai = i;
                encontrado    = true;
            }
        }
    }

    if (!encontrado) {
        for (int i = 0; i < equipe.numLesionados && !encontrado; i++) {
            if (equipe.lesionados[i] != nullptr &&
                equipe.lesionados[i]->numero == numCamisa) {

                posJogadorSai = posicao(equipe.lesionados[i]->posicao);


                Jogador* salvo = equipe.lesionados[i];
                salvo->numero  = 0;
                adicionarTransferencia(*salvo, listaTransferencia, totalTransferencias);

                for (int k = i; k < equipe.numLesionados - 1; k++)
                    equipe.lesionados[k] = equipe.lesionados[k + 1];

                equipe.lesionados[equipe.numLesionados - 1] = nullptr;
                equipe.numLesionados--;
                delete salvo;

                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        for (int i = 0; i < equipe.numSuspensos && !encontrado; i++) {
            if (equipe.suspensos[i] != nullptr &&
                equipe.suspensos[i]->numero == numCamisa) {

                posJogadorSai = posicao(equipe.suspensos[i]->posicao);


                Jogador* salvo = equipe.suspensos[i];
                salvo->numero  = 0;
                adicionarTransferencia(*salvo, listaTransferencia, totalTransferencias);

                for (int k = i; k < equipe.numSuspensos - 1; k++)
                    equipe.suspensos[k] = equipe.suspensos[k + 1];

                equipe.suspensos[equipe.numSuspensos - 1] = nullptr;
                equipe.numSuspensos--;
                delete salvo;

                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "Jogador nao encontrado!\n";
        return;
    }

    if (posJogadorSai != posIdx) {
        cout << "Nao e permitido trocar jogadores de posicoes diferentes!\n";
        return;
    }

    bool estavaNoPlantel = true;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < equipe.numJogadores[i]; j++)
            if (equipe.plantel[i][j].numero == numCamisa)
                estavaNoPlantel = true;


    removerJogadorPlantel(equipe, listaTransferencia, totalTransferencias, numCamisa);

    int idxActualizado = -1;
    for (int i = 0; i < totalTransferencias; i++) {
        if (listaTransferencia[i].nome == contratado.nome &&
            listaTransferencia[i].posicao == contratado.posicao) {
            idxActualizado = i;
            break;
        }
    }
    if (idxActualizado != -1)
        removerTransferencia(listaTransferencia, totalTransferencias, idxActualizado);

    contratado.numero = escolherCamisaDisponivel(equipe, posIdx);
    adicionarJogadorPlantel(equipe, contratado);
    cout << "Troca efetuada com sucesso! Novo numero: " << contratado.numero << endl;
}