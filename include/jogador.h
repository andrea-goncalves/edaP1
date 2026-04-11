

#ifndef EDAP1_JOGADOR_H
#define EDAP1_JOGADOR_H
#include <string>

/**
 * @brief Estrutura que representa um jogador de futebol, contendo informações sobre o número do jogador, nome, posição, idade, qualidade, probabilidade de lesão, probabilidade de suspensão, dias de treino e semanas até o retorno de lesão ou castigo.
 *
 * A estrutura Jogador armazena os atributos essenciais de um jogador de futebol. O campo "numero" representa o número da camisa do jogador, enquanto "nome" e "posicao" armazenam o nome e a posição do jogador em campo (goleiro, defensor, meio-campista ou atacante). Os campos "idade" e "qualidade" indicam a idade do jogador e sua qualidade geral. As probabilidades de lesão e suspensão são representadas pelos campos "probLes" e "probSus", respectivamente. Além disso, os campos "diasTreino", "semanas_ate_retorno_lesao" e "semanas_ate_retorno_castigo" fornecem informações sobre o tempo necessário para o treinamento e o retorno do jogador após uma lesão ou suspensão.
 */
struct Jogador {
    int numero;
    std::string nome;
    std::string posicao;
    int idade;
    int qualidade;
    int probLes;
    int probSus;
    int diasTreino;
    int semanas_ate_retorno_lesao;
    int semanas_ate_retorno_castigo;
};

std::string nomeAleatorio(std::string* nomeJogadores, int tamanho);
Jogador gerarUmJogadorPlantel(std::string* nomeJogadores, int tamanho, std::string posicao, int numeroCamisa);
bool compararNumJogador(Jogador* array,int numComparar, int tamanho);
int numeroGR();
int numeroDEF();
int numeroMED();
int numeroAVA();
Jogador* criarJogadores(std::string* nomeJogadores, int tamanho, int numJogadores, const std::string& posicao, const int* camisas, int numCamisas);
Jogador* criarAleatorio(std::string* nomeJogadores, int tamanho, int numJogadores);

#endif //EDAP1_JOGADOR_H