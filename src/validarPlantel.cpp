#include "../include/validarPlantel.h"
#include "../include/equipa.h"
#include "../include/transferencias.h"
#include <iostream>

using namespace std;

bool validarPlantelDisponible(Equipa& equipa, Tatica& taticaAtual) {
    int disponibles[4] = {
        equipa.numJogadores[0],
        equipa.numJogadores[1],
        equipa.numJogadores[2],
        equipa.numJogadores[3]
    };
    
    int totalDisponiveis = disponibles[0] + disponibles[1] + disponibles[2] + disponibles[3];

    if (totalDisponiveis < 13) {
        cout << "\n";
        cout << "Nao ha suficientes jogadores disponiveis.\n";
        cout << "Jogadores disponiveis: " << totalDisponiveis << " / 13 requeridos\n\n";
        cout << "  GR:  " << disponibles[0] << " (mínimo: 1)\n";
        cout << "  DEF: " << disponibles[1] << " (minimo: 3)\n";
        cout << "  MED: " << disponibles[2] << " (minimo: 2)\n";
        cout << "  AVA: " << disponibles[3] << " (minimo: 1)\n";
        return false;
    }

    bool compatibleConTactica = true;
    string posiciones[] = {"GR", "DEF", "MED", "AVA"};
    
    for (int i = 0; i < 4; i++) {
        if (disponibles[i] < taticaAtual.convocados[i]) {
            compatibleConTactica = false;
            break;
        }
    }
    
    if (!compatibleConTactica) {
        cout << "\n";
        cout << "Nao coincidem com a tatica selecionada.\n\n";
        cout << "Tatica atual: 1-" << taticaAtual.titulares[1] << "-"
             << taticaAtual.titulares[2] << "-" << taticaAtual.titulares[3] << "\n";
        cout << "Jogadores necessarios (convocados):\n";
        for (int i = 0; i < 4; i++) {
            cout << "  " << posiciones[i] << ": " << taticaAtual.convocados[i] 
                 << " (disponiveis: " << disponibles[i] << ")\n";
        }
        cout << "Alterare a tatica ou compre jogadores\n";
        return false;
    }


    return true;
}
