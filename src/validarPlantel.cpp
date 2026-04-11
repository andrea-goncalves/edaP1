#include "../include/validarPlantel.h"
#include "../include/equipa.h"
#include "../include/transferencias.h"
#include <iostream>

using namespace std;
/** * @brief Valida se o plantel da equipe é suficiente e compatível com a tática atual.
 *
 * Esta função verifica se o número total de jogadores disponíveis na equipe é suficiente para formar um plantel completo (mínimo de 13 jogadores). Além disso, ela compara o número de jogadores disponíveis em cada posição (goleiro, defensor, meio-campista, atacante) com os requisitos da tática atual. Se o plantel não for suficiente ou não for compatível com a tática, a função exibe mensagens informativas e retorna false. Caso contrário, retorna true.
 *
 * @param equipa Referência para a equipe cujo plantel será validado.
 * @param taticaAtual Referência para a tática atual da equipe, que contém os requisitos de jogadores por posição.
 * @return true se o plantel for válido e compatível com a tática, ou false caso contrário.
 */
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
