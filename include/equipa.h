
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
   int numLesionados = 0;
   int numSuspensos = 0;
   int numSuplentes = 0;
   int pontos;
   int vitorias;
   int empate;
   int derrota;
   Tatica tatica;
   int numJogadores[4];
   std::string sairam[11];
   std::string entraram[11];
   int numSubstituicoes = 0;
   int saldoGols;
};



Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA);
void imprimirPlantel(Equipa& equipa);
Jogador** ordenarPlantelNumeroJogador(Equipa& equipa);
void ordenarPlantelQualidadeJogador(Jogador** plantel, int* disponiveis);
bool validarTatica(Tatica tatica);
Tatica pedirTatica(Tatica taticaAtual);
Jogador** copiarPlantel(Equipa& equipa, int* disponiveis) ;
int getPos(std::string posicao);
Jogador* escolherTitulares(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica);
void imprimirTitulares(Jogador* titulares, Tatica tatica);
Jogador* escolherSuplentes(Jogador** copiaPlantel, int* disponiveis, Tatica tatica, int& numSuplentes);
void imprimirSuplentes(Jogador* suplentes, int numSuplentes);

void escolherJogadorGlobal(Equipa& equipa, int& pos, int& idx);
void mudarPosicao(Equipa& equipa, int posAtual, int idxJogador, int novaPosicao);
int escolherNumero(Equipa& equipa, int posicao);
void listarNumerosLivres(Equipa& equipa, int posicao);
bool numeroOcupado(Equipa& equipa, int numero) ;
bool limitePosicaoAtingido(Equipa& equipa, int pos);
int contarJogadoresPosicao(Equipa& equipa, int pos);
#endif //EDAP1_EQUIPA_H