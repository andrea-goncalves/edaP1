#include <iostream>
#include <iomanip>
#include <ctime>
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/equipa.h"
#include "../include/equipasAdversarias.h"
#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/lesionarSuspender.h"
#include "../include/transferencias.h"
#include "../include/menu.h"
#include "../include/simulacao.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    //menuPrincipal(edaFC, jornada);

    Equipa edaFC;
    inicializarEquipa( edaFC);
    temporada(edaFC, argc, argv);
    libertarMemoria(edaFC);

    return 0;
}