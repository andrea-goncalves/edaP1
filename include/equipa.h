
#ifndef EDAP1_EQUIPA_H
#define EDAP1_EQUIPA_H
#include "jogador.h"

struct Equipa {
   std:: string nome;
   Jogador**plantel[30];
   Jogador**titulares[11];
   Jogador**suplentes[6];
   Jogador**lesionados[30];
   Jogador**suspensos[30];
   Jogador**transferencias[68];
};

Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA);
void imprimirPlantel(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelNumeroJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelQualidadeJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);

#endif //EDAP1_EQUIPA_H