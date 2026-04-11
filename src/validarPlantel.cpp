#include "../include/validarPlantel.h"
#include "../include/equipa.h"
#include "../include/transferencias.h"
#include <iostream>
#include "../include/constantes.h"
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
        equipa.numJogadores[POSICAO_GR],
        equipa.numJogadores[POSICAO_DEF],
        equipa.numJogadores[POSICAO_MED],
        equipa.numJogadores[POSICAO_AVA]
    };
    
    int totalDisponiveis = disponibles[POSICAO_GR] + disponibles[POSICAO_DEF] + disponibles[POSICAO_MED] + disponibles[POSICAO_AVA];

    if (totalDisponiveis < 13) {
        cout << "\n";
        cout << "Nao ha suficientes jogadores disponiveis.\n";
        cout << "Jogadores disponiveis: " << totalDisponiveis << " / 13 requeridos\n\n";
        cout << "  GR:  " << disponibles[POSICAO_GR] << " (mínimo: 1)\n";
        cout << "  DEF: " << disponibles[POSICAO_DEF] << " (minimo: 3)\n";
        cout << "  MED: " << disponibles[POSICAO_MED] << " (minimo: 2)\n";
        cout << "  AVA: " << disponibles[POSICAO_AVA] << " (minimo: 1)\n";
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
        cout << "Tatica atual: 1-" << taticaAtual.titulares[POSICAO_DEF] << "-"
             << taticaAtual.titulares[POSICAO_MED] << "-" << taticaAtual.titulares[POSICAO_AVA] << "\n";
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
