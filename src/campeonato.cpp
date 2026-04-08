//
// Created by pablo on 08/04/2026.
//
#include "campeonato.h"
#include "../include/equipa.h"
#include "../include/constantes.h"

void tabelaPontos (Equipa* principal, Equipa* adversarios, int totalequipes){
    totalequipes = NUMERO_ADVERSARIOS + 1;
    Equipa* tabela[totalequipes];

    tabela[0] = principal;

    for (int i = 0; i < totalequipes; i++) {
        //tabela[i+1] = adversarios[i];
    }
}