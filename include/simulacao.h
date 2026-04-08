

#ifndef EDAP1_SIMULACAO_H
#define EDAP1_SIMULACAO_H
#include "equipa.h"
#include "equipasAdversarias.h"

void inicializarEquipa(Equipa& edaFC);
void inicializarAdversarios(equipasAdversarias*& adversarios,equipasAdversarias*& adversariosFase2,int& numEquipas);
void temporada(Equipa& edaFC, int argc, char* argv[]);

void libertarMemoria(Equipa& edaFC);

#endif //EDAP1_SIMULACAO_H