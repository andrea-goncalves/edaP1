

#ifndef EDAP1_LESIONARSUSPENDER_H
#define EDAP1_LESIONARSUSPENDER_H
#include "jogador.h"
#include "equipa.h"

enum TipoEfeito {
    lesao,
    suspensao
};

void inserirJogadorNoPlantel(Equipa& equipa, Jogador* novo);
void inserirJogador(Jogador** arrayDestino, int& numDestino, Jogador* novoJogador);
void les_sus(Jogador* titulares, int numTitulares, TipoEfeito tipo);
void ListaLesSus(Jogador* titulares, int numTitulares, Equipa& equipa, TipoEfeito tipo);
void recuperarLesSus(Equipa& equipa, TipoEfeito tipo) ;

void imprimirJogadoresLesionados(Jogador** lesionados, int numeroLesionados);
void imprimirJogadoresLesionados2(Jogador** lesionados, int numeroLesionados);
void imprimirJogadoresSuspensos1(Jogador** suspensos, int numeroSuspensos);
void imprimirJogadoresSuspensos2(Jogador** suspensos, int numeroSuspensos);

void substituicoes(Jogador* titulares, Jogador* suplentes, int numTitulares, int numSuplentes, Equipa& equipa);
bool verificarDerrota(int lesionadosJornada, int suspensosJornada, int substituicoesJornada);

void aplicarLesaoManual(Equipa& equipa, int numeroJogador, int semanas);
void reduzirLesaoManual(Equipa& equipa, int numeroJogador, int semanas);
void aplicarCastigoManual(Equipa& equipa, int numeroJogador, int semanas);
void reduzirCastigoManual(Equipa& equipa, int numeroJogador, int semanas);
#endif //EDAP1_LESIONARSUSPENDER_H