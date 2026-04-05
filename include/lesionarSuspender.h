

#ifndef EDAP1_LESIONARSUSPENDER_H
#define EDAP1_LESIONARSUSPENDER_H
#include "jogador.h"
#include "equipa.h"

void inserirJogadorNoPlantel(Equipa& equipa, Jogador* novo);
void inserirJogador(Jogador** arrayDestino, int& numDestino, Jogador* novoJogador);
void lesionar(Jogador* titulares, int numTitulares);
void ListaLesionados(Jogador* titulares, int numTitulares, Equipa& equipa);
void recuperarLesionados(Equipa& equipa);
void imprimirJogadoresLesionados(Jogador** lesionados, int numeroLesionados);
void suspender(Jogador* titulares, int numTitulares);
void ListaSuspensos(Jogador* titulares, int numTitulares, Equipa& equipa) ;
void recuperarSuspensos(Equipa& equipa);
void imprimirJogadoresSuspensos1(Jogador** suspensos, int numeroSuspensos);
void imprimirJogadoresSuspensos2(Jogador** suspensos, int numeroSuspensos);
void substituicoes(Jogador* titulares, Jogador* suplentes, int numTitulares, int numSuplentes, Equipa& equipa);
bool verificarDerrota(int lesionadosJornada, int suspensosJornada, int substituicoesJornada);

#endif //EDAP1_LESIONARSUSPENDER_H