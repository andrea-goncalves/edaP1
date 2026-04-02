
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

struct Tatica {
   int titulares[4] = { 1, 4, 4, 2 };
   int suplentes[4] = { 1, 2, 2, 1 };
   int convocados[4] = { 2, 6, 6, 3 };
};

Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA);
void imprimirPlantel(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelNumeroJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
Jogador** ordenarPlantelQualidadeJogador(Jogador** plantel, int numGR, int numDEF, int numMED, int numAVA);
bool validarTatica(Tatica tatica);
Tatica pedirTatica(Tatica taticaAtual);
Jogador** copiarPlantel(Jogador** plantel, int* disponiveis);
Jogador* escolherTitulares(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica);
void imprimirTitulares(Jogador* titulares, Tatica tatica);
Jogador* escolherSuplentes(Jogador** copiaPlantel, int* disponiveis, Tatica tatica);
void imprimirSuplentes(Jogador* suplentes);

#endif //EDAP1_EQUIPA_H