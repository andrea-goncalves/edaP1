

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

int posicao(std::string pos) {
    if (pos == "GR") return 0;
    if (pos == "DEF") return 1;
    if (pos == "MED") return 2;
    if (pos == "AVA") return 3;
    return -1;
}

int totalJogadores(Equipa &equipe) {
    return equipe.numJogadores[0] + equipe.numJogadores[1] + equipe.numJogadores[2] + equipe.numJogadores[3];
}

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
                    << setw(26) << eliminarAcentos(listaTransf[i].nome) << "| "
                    << setw(4)  << listaTransf[i].posicao<< "| "
                    << setw(8)  << listaTransf[i].idade << "| "
                    << setw(6)  << listaTransf[i].probLes  << "| "
                    << setw(10) <<listaTransf[i].probSus << "| "
                    << setw(10) << listaTransf[i].qualidade << endl;
            }
        }
            cout << "-----------------------------------------------------------------------------------------\n";
}


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