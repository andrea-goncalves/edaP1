//
// Created by pablo on 04/04/2026.
//

#ifndef EDAP1_TRANSFERENCIA_H
#define EDAP1_TRANSFERENCIA_H
#include "../include/jogador.h"
#include "../include/equipa.h"

int posicao(std::string pos);
int totalJogadores(Equipa &equipe);
Jogador* gerarTransferencia(Jogador* novos, int numNovos, Jogador* listaAntiga, int &totalTransferencias);
void imprimirMercado(Jogador* listaTransf, int totalTransf);
bool podeAdicionar(Equipa &equipe, int pos);
int escolherCamisaDisponivel(Equipa &equipe, int posIdx);
void adicionarTransferencia(Jogador jogador, Jogador* &listaTransferencia, int &totalTransferencias);
void adicionarJogadorPlantel(Equipa &equipe, Jogador jogador);
bool removerJogadorPlantel(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias, int numCamisa);
Jogador removerTransferencia(Jogador* &listaTransferencia, int &totalTransferencias, int indice);
void contratarJogador(Equipa &equipe, Jogador* &listaTransferencia, int &totalTransferencias);



#endif //EDAP1_TRANSFERENCIA_H