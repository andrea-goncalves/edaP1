//
// Created by andre on 05/04/2026.
//

#ifndef EDAP1_CONSTANTES_H
#define EDAP1_CONSTANTES_H


constexpr int MINIMO_JOGADORES = 20;
constexpr int MAXIMO_JOGADORES = 30;
constexpr int MAXIMO_ADD_TRANSFERENCIA = 2;

constexpr int GR_MAX = 3;
constexpr int GR_MIN = 2;
constexpr int DEF_MAX = 10;
constexpr int DEF_MIN = 7;
constexpr int MED_MAX = 10;
constexpr int MED_MIN = 7;
constexpr int AVA_MAX = 7;
constexpr int AVA_MIN = 4;

constexpr int CAMPEONATO_N_EQUIPAS = 18;

constexpr int MAX_GOLOS = 8;


constexpr int MAX_TEMPO_TREINO = 5;
constexpr int MAX_SUBSTITUICOES = 3;


constexpr int MAX_TITULARES = 11;
constexpr int MAX_SUPLENTES = 6;

constexpr int EQUIPA_MIN_GR = 1;
constexpr int EQUIPA_MIN_DEF = 3;
constexpr int EQUIPA_MIN_MED = 2;
constexpr int EQUIPA_MIN_AVA = 1;

constexpr int LIMITE_TEMPO_LESIONADO = 10;
constexpr int LIMITE_TEMPO_SUSPENSO = 10;
constexpr int CHANCE_DE_LESAO_MAX = 15;
constexpr int CHANCE_DE_LESAO_MIN = 0;
constexpr int CHANCE_DE_SUSPENSAO_MAX = 20;
constexpr int CHANCE_DE_SUSPENSAO_MIN = 0;
constexpr int MAX_QUALIDADE = 100;
constexpr int MIN_NUM = 1;
constexpr int MAX_NUM = 99;
constexpr int MIN_IDADE = 18;
constexpr int MAX_IDADE = 40;

enum Posicao {
    POSICAO_GR = 0,
    POSICAO_DEF= 1,
    POSICAO_MED= 2,
    POSICAO_AVA=3,
};

constexpr const char* FILE_EQUIPAS = "../config/equipas.txt";
constexpr const char* FILE_NOMES = "../config/nomes.txt";


constexpr int MAX_PROBLES = 15;
constexpr int MAX_PROBSUS = 20;

#endif //EDAP1_CONSTANTES_H