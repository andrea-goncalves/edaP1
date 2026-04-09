
#include <string>
#include <iomanip>
#include "../include/jogador.h"
#include "../include/utils.h"
#include "../include/constantes.h"

using namespace std;

string nomeAleatorio(string* nomeJogadores, int tamanho) {
    string nomeJogador = nomeJogadores[numAleatorio(0, tamanho - 1)];
    return nomeJogador;
}


Jogador gerarUmJogadorPlantel(string* nomeJogadores, int tamanho, string posicao, int numeroCamisa) {
    Jogador novo;

    novo.nome = nomeAleatorio(nomeJogadores,tamanho);
    novo.idade = numAleatorio(18, 40);
    novo.qualidade = numAleatorio(0, 100);
    novo.numero = numeroCamisa;
    novo.probSus = numAleatorio(0, 20);
    novo.probLes = numAleatorio(0, 15);
    novo.posicao = posicao;
    novo.diasTreino = 0;
    novo.semanas_ate_retorno_lesao=0;
    novo.semanas_ate_retorno_castigo=0;


    return novo;
}

int numeroGR() {
    return numAleatorio(2, 3);
}
int numeroDEF() {
    return numAleatorio(7, 10);
}
int numeroMED() {
    return numAleatorio(7, 10);
}
int numeroAVA() {
    return numAleatorio(4, 7);
}

bool compararNumJogador(Jogador* array, int numComparar, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (array[i].numero == numComparar) {
            return true;
        }
    }
    return false;
}


Jogador* criarJogadores(string* nomeJogadores, int tamanho, int numJogadores, const string& posicao, const int* camisas, int numCamisas) {
    Jogador* jogadores = new Jogador[numJogadores];

    for (int i = 0; i < numJogadores; i++) {
        bool numeroRepetido = true;
        int num = 0;

        while (numeroRepetido) {
            int indice = numAleatorio(0, numCamisas - 1);
            num = camisas[indice];
            numeroRepetido = compararNumJogador(jogadores, num, i);
        }

        jogadores[i] = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
    }
    return jogadores;
}

Jogador* criarAleatorio(string* nomeJogadores, int tamanho, int numJogadores) {
    Jogador* aleatorio = new Jogador[numJogadores];
    string posicoes[] = {"GR", "DEF", "MED", "AVA"};

    for (int i = 0; i < numJogadores; i++) {
        string pos = posicoes[numAleatorio(0, 3)];
        aleatorio[i] = gerarUmJogadorPlantel(nomeJogadores, tamanho, pos, 0);
    }
    return aleatorio;
}

