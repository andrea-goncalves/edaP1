
#include <string>
#include <iomanip>
#include "../include/jogador.h"
#include "../include/utils.h"
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
    novo.numero = numeroCamisa;//após estar criado o plantel, devemos verificar numeros repetidos
    novo.probSus = numAleatorio(0, 20);
    novo.probLes = numAleatorio(0, 15);
    novo.posicao = posicao;
    novo.diasTreino = 0;


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

Jogador* criarGR(string* nomeJogadores, int tamanho, int numGR, int* numeroCamisaGR) {
    Jogador* gr = new Jogador[numGR];
    string posicao = "GR";

    for (int i = 0; i < numGR; i++) {
        bool numeroRepetido = true;
        int num = 0;

        while (numeroRepetido == true) {
            int numero = numAleatorio(0, 2);
            num = numeroCamisaGR[numero];

            numeroRepetido = compararNumJogador(gr, num, i);
        }


        Jogador jogador = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
        gr[i] = jogador;
    }

    return gr;
}

Jogador* criarDEF(string* nomeJogadores, int tamanho, int numDEF, int* numeroCamisaDEF) {
    Jogador* def = new Jogador[numDEF];
    string posicao = "DEF";

    for (int i = 0; i < numDEF; i++) {
        bool numeroRepetido = true;
        int num = 0;

        while (numeroRepetido == true) {
            int numero = numAleatorio(0, 9);
            num = numeroCamisaDEF[numero];

            numeroRepetido = compararNumJogador(def, num, i);
        }


        Jogador jogador = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
        def[i] = jogador;
    }

    return def;
}

Jogador* criarMED(string* nomeJogadores, int tamanho, int numMED, int* numeroCamisaMED) {
    Jogador* med = new Jogador[numMED];
    string posicao = "MED";
    for (int i = 0; i < numMED; i++) {
        bool numeroRepetido = true;
        int num = 0;
        while (numeroRepetido == true) {
            int numero = numAleatorio(0, 9);
            num = numeroCamisaMED[numero];

            numeroRepetido = compararNumJogador(med, num, i);
        }

        Jogador jogador = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
        med[i] = jogador;
    }
    return med;
}

Jogador* criarAVA(string* nomeJogadores, int tamanho, int numAVA, int* numeroCamisaAVA) {
    Jogador* ava = new Jogador[numAVA];
    string posicao = "AVA";
    for (int i = 0; i < numAVA; i++) {
        bool numeroRepetido = true;
        int num = 0;
        while (numeroRepetido == true) {
            int numero = numAleatorio(0, 6);
            num = numeroCamisaAVA[numero];
            numeroRepetido = compararNumJogador(ava, num, i);
        }

        Jogador jogador = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
        ava[i] = jogador;
    }
    return ava;
}

