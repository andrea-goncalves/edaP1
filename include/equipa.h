
#ifndef EDAP1_EQUIPA_H
#define EDAP1_EQUIPA_H
#include "jogador.h"
/**
 * @brief Estrutura que representa a tática de uma equipe, contendo informações sobre o número de titulares, suplentes e convocados para cada posição (goleiro, defensor, meio-campista, atacante).
 *
 * A estrutura Tatica armazena os requisitos de jogadores para cada posição em um formato de array. Os arrays "titulares", "suplentes" e "convocados" indicam o número de jogadores necessários para cada posição na formação titular, no banco de reservas e no total convocado para um jogo, respectivamente. Esta estrutura é fundamental para validar a composição do plantel da equipe e garantir que ela esteja alinhada com a tática escolhida.
 */
struct Tatica {
   int titulares[4] = { 1, 4, 4, 2 };
   int suplentes[4] = { 1, 2, 2, 1 };
   int convocados[4] = { 2, 6, 6, 3 };
};
/**
 * @brief Estrutura que representa uma equipe de futebol, contendo informações sobre o nome da equipe, plantel de jogadores, titulares, suplentes, jogadores lesionados e suspensos, pontos acumulados, tática adotada e histórico de substituições.
 *
 * A estrutura Equipa armazena o nome da equipe e um plantel organizado por posição (goleiro, defensor, meio-campista, atacante). Ela também mantém arrays para os titulares e suplentes escolhidos para cada jogo, bem como listas de jogadores lesionados e suspensos. A estrutura inclui contadores para o número de jogadores em cada categoria (lesionados, suspensos, suplentes) e um campo para os pontos acumulados pela equipe. Além disso, a estrutura possui um campo para a tática adotada pela equipe e arrays para registrar os jogadores que saíram e entraram durante as substituições realizadas ao longo da temporada.
 */
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
   int pontos=0;
   Tatica tatica;
   int numJogadores[4];
   std::string sairam[11];
   std::string entraram[11];
   int numSubstituicoes = 0;
   bool escolhaManual = false;
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

void treinar(Equipa& equipa);
Jogador* escolherSuplentesManual(Jogador** copiaPlantel, int* disponiveis, int& numSuplentes);
Jogador* escolherTitularesManual(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica);
void escolherEquipaManual(Equipa& equipa, Tatica& taticaAtual);

#endif //EDAP1_EQUIPA_H