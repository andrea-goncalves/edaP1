//
// Created by jesus on 04/06/2026.
//

#ifndef EDAP1_MENU_H
#define EDAP1_MENU_H
#include "equipa.h"
void menuPrincipal(Equipa& equipa, int& jornada);
void menuJogador();
void menuTreino(Equipa& equipa);
void menuTransferencias();
void menuTatica();
void menuGravarCarregar();
void menuAlteracoesManuais();
int escolherJogador(Equipa& equipa);
void menuAlteracoesManuais(Equipa& equipa);
void menuGestao(Equipa& equipa);
void menuGravarCarregar(Equipa& equipa, int& jornada);
#endif //EDAP1_MENU_H