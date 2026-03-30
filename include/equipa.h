//
// Created by andre on 29/03/2026.
//

#ifndef EDAP1_EQUIPA_H
#define EDAP1_EQUIPA_H
#include "jogador.h"

Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA);
void imprimirPlantel(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelNumeroJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelQualidadeJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);

#endif //EDAP1_EQUIPA_H