
#ifndef EDAP1_EQUIPA_H
#define EDAP1_EQUIPA_H
#include "jogador.h"

struct Tatica {
   int titulares[4] = { 1, 4, 4, 2 };
   int suplentes[4] = { 1, 2, 2, 1 };
   int convocados[4] = { 2, 6, 6, 3 };
};

struct Equipa {
   std::string nome;
   Jogador** plantel;
   Jogador* titulares;
   Jogador* suplentes;
   Jogador* lesionados[30];
   Jogador* suspensos[30];
   Tatica tatica;
   int numJogadores[4];
   int numLesionados = 0;
   int numSuspensos = 0;
   int pontos;
};



Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA);
void imprimirPlantel(Equipa& equipa);
Jogador** ordenarPlantelNumeroJogador(Equipa& equipa);
void ordenarPlantelQualidadeJogador(Jogador** plantel, int* disponiveis);
bool validarTatica(Tatica tatica);
Tatica pedirTatica(Tatica taticaAtual);
Jogador** copiarPlantel(Equipa& equipa, int* disponiveis) ;
Jogador* escolherTitulares(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica);
void imprimirTitulares(Jogador* titulares, Tatica tatica);
Jogador* escolherSuplentes(Jogador** copiaPlantel, int* disponiveis, Tatica tatica);
void imprimirSuplentes(Jogador* suplentes);
void calcularLesionados(Equipa& equipa);
void calcularSuspensos(Equipa& equipa);
void recuperarSuspensos(Equipa& equipa);
void recuperarLesionados(Equipa& equipa);
void imprimirLesionados(Equipa& equipa);
void imprimirSuspensos(Equipa& equipa);

#endif //EDAP1_EQUIPA_H