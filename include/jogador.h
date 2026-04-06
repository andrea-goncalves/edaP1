

#ifndef EDAP1_JOGADOR_H
#define EDAP1_JOGADOR_H
#include <string>

struct Jogador {
    int numero;
    std::string nome;
    std::string posicao;
    int idade;
    int qualidade;
    int probLes;
    int probSus;
    int diasTreino;
    int semanas_ate_retorno;
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