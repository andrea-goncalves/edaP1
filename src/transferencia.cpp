#include "../include/transferencia.h"
#include "../include/jogador.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../include/ficheiros.h"
#include "../include/utils.h"
#include "../include/equipa.h"

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
    if (totalTransf == 0 || listaTransf == nullptr) {
        std::cout << "Transferencias: \n";
        return;
    }

    std::cout << "Transferencias: \n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(26) << "Nome"
              << std::setw(10) << "Posicao"
              << std::setw(8)  << "Idade"
              << std::setw(12) << "Qualidade"
              << std::setw(14) << "Prob. Lesao"
              << std::setw(14) << "Prob. Castigo" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < totalTransf; i++) {

        std::cout << std::left
                  << std::setw(6)  << (i + 1)
                  << std::setw(26) << eliminarAcentos(listaTransf[i].nome)
                  << std::setw(10) << listaTransf[i].posicao
                  << std::setw(8)  << listaTransf[i].idade
                  << std::setw(12) << listaTransf[i].qualidade
                  << listaTransf[i].probLes << "%" << std::setw(13) << "" // Alinhamento manual após o %
                  << listaTransf[i].probSus << "%" << std::endl;
    }
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";
}

bool podeAdicionar(Equipa &equipe, int pos) {
    if (pos == 0 && equipe.numJogadores[0] >= 3) return false;
    if (pos == 1 && equipe.numJogadores[1] >= 10) return false;
    if (pos == 2 && equipe.numJogadores[2] >= 10) return false;
    if (pos == 3 && equipe.numJogadores[3] >= 7) return false;
    return true;
}

int escolherCamisaDisponivel(Equipa &equipe, int posIdx) {

    int nGR[3] = { 1, 13, 30 };
    int nDEF[10] = { 2, 3, 4, 5, 12, 15, 22, 24, 25, 26 };
    int nMED[10] = { 6, 8, 10, 14, 16, 17, 20, 21, 23, 28 };
    int nAVA[7] = { 7, 9, 11, 18, 19, 27, 29 };

    int* listaRef;
    int tamRef;

    if (posIdx == 0) { listaRef = nGR; tamRef = 3; }
    else if (posIdx == 1) { listaRef = nDEF; tamRef = 10; }
    else if (posIdx == 2) { listaRef = nMED; tamRef = 10; }
    else { listaRef = nAVA; tamRef = 7; }

    for (int i = 0; i < tamRef; i++) {
        int numeroCandidato = listaRef[i];

        if (!compararNumJogador(equipe.plantel[posIdx], numeroCandidato, equipe.numJogadores[posIdx])) {
            return numeroCandidato;
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

void contratarJogador(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias) {
    int indice;
    cout << "Escolha o ID do jogador (1 a " << totalTransferencias << "): ";
    cin >> indice;

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