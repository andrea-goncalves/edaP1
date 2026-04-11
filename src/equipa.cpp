
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/equipa.h"
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/lesionarSuspender.h"
#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/validarPlantel.h"

using namespace std;

Jogador** gerarPlantel(Jogador* gr, Jogador* def, Jogador* med, Jogador* ava, int numGR, int numDEF, int numMED, int numAVA) {

    Jogador** plantel = new Jogador * [4];

    plantel[0] = new Jogador[numGR];
    plantel[1] = new Jogador[numDEF];
    plantel[2] = new Jogador[numMED];
    plantel[3] = new Jogador[numAVA];

    for (int i = 0; i < numGR; i++) {
        plantel[0][i] = gr[i];
    }

    for (int i = 0; i < numDEF; i++) {
        plantel[1][i] = def[i];
    }


    for (int i = 0; i < numMED; i++) {
        plantel[2][i] = med[i];
    }

    for (int i = 0; i < numAVA; i++) {
        plantel[3][i] = ava[i];
    }

    return plantel;
}

Jogador** ordenarPlantelNumeroJogador(Equipa& equipa) {

    int quantidades[4] =  { equipa.numJogadores[0], equipa.numJogadores[1], equipa.numJogadores[2], equipa.numJogadores[3] };
    for (int i = 0; i < 4; i++) {
        int n = quantidades[i];

        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - j - 1; k++) {

                if (equipa.plantel[i][k].numero > equipa.plantel[i][k + 1].numero) {
                    swap(equipa.plantel[i][k], equipa.plantel[i][k + 1]);
                }

            }
        }
    }
    return equipa.plantel;
}

void ordenarPlantelQualidadeJogador(Jogador** plantel, int* disponiveis) {
    for (int i = 0; i < 4; i++) {
        int n = disponiveis[i];
        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - j - 1; k++) {
                if (plantel[i][k].qualidade < plantel[i][k + 1].qualidade) {
                    swap(plantel[i][k], plantel[i][k + 1]);
                }
            }
        }
    }
}



void imprimirPlantel(Equipa& equipa) {
    cout << "\n*********** Plantel Disponivel: ***********\n";

    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade | Dias-Treino\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    int quantidades[4] = { equipa.numJogadores[0], equipa.numJogadores[1], equipa.numJogadores[2], equipa.numJogadores[3] };
    for (int i = 0; i < 4; i++) {
        if (quantidades[i] > 0) {
            string posicaoAtual =equipa.plantel[i][0].posicao;

            for (int j = 0; j < quantidades[i]; j++) {
                if (equipa.plantel[i][j].posicao != posicaoAtual) {
                    cout << endl;
                    posicaoAtual = equipa.plantel[i][j].posicao;
                }

                string strLesao = to_string(equipa.plantel[i][j].probLes) + "%";
                string strCastigo = to_string(equipa.plantel[i][j].probSus) + "%";

                cout << left
                    << setw(26) << eliminarAcentos(equipa.plantel[i][j].nome) << "| "
                    << setw(4)  << equipa.plantel[i][j].numero << "| "
                    << setw(8)  << eliminarAcentos(equipa.plantel[i][j].posicao) << "| "
                    << setw(6)  << equipa.plantel[i][j].idade << "| "
                    << setw(10) << strLesao << "| "
                    << setw(12) << strCastigo << "| "
                    << setw(10) << equipa.plantel[i][j].qualidade << "| "
                    << equipa.plantel[i][j].diasTreino << endl;
            }
        }
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
}

bool validarTatica(Tatica tatica) {
    int total = 0;
    for (int i = 0; i < 4; i++) {
        total += tatica.titulares[i];
    }
    if (total < 7) {
        cout << "A tatica deve ter minimo 7 titulares, tem " << total << "\n";
        return false;
    }
    if (total>11) {
        cout << "A tatica deve ter no maximo 11 titulares, tem " << total << "\n";
        return false;
    }
    return true;
}

Tatica pedirTatica(Tatica taticaAtual) {
    Tatica tatica= taticaAtual;

    cout << "\nTatica atual: 1-" << tatica.titulares[1] << "-"
         << tatica.titulares[2] << "-" << tatica.titulares[3] << "\n";
    cout << "Deseja alterar a tatica? (s/n): ";
    cin.ignore();
    string input;
    getline(cin, input);

    if (input != "s") return tatica;


    cout << "Numero de DEF (atual: " << tatica.titulares[1] << "): ";
    cin >> tatica.titulares[1];
    cout << "Numero de MED (atual: " << tatica.titulares[2] << "): ";
    cin >> tatica.titulares[2];
    cout << "Numero de AVA (atual: " << tatica.titulares[3] << "): ";
    cin >> tatica.titulares[3];
    cin.ignore();


    for (int i = 0; i < 4; i++) {
        tatica.convocados[i] = tatica.titulares[i] + tatica.suplentes[i];
    }

    if (!validarTatica(tatica)) {
        cout << "Tatica invalida, tatica por defeito 1-4-4-2\n";
        return Tatica{};
    }

    return tatica;
}

Jogador** copiarPlantel(Equipa& equipa, int* disponiveis) {

    Jogador** copia = new Jogador*[4];
    for (int i = 0; i < 4; i++) {
        copia[i] = new Jogador[disponiveis[i]];
        for (int j = 0; j < disponiveis[i]; j++) {
            copia[i][j] = equipa.plantel[i][j];
        }
    }
    return copia;
}

Jogador* escolherTitulares(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica) {

    while (true) {
        bool valido = true;
        for (int i = 0; i < 4; i++) {
            if (disponiveis[i] < tatica.titulares[i]) {
                cout << "\nNao existem jogadores suficientes na posicao "
                    << i << " Altere a tatica\n";
                tatica = pedirTatica(tatica);
                valido = false;
                break;
            }
        }
        if (valido) break;
    }

    Jogador* titulares = new Jogador[11];
    int idx = 0;


    int disponiveisLocais[4] = { disponiveis[0], disponiveis[1], disponiveis[2], disponiveis[3] };

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < tatica.titulares[i]; j++) {
            titulares[idx++] = copiaPlantel[i][j];
        }


        int restantes = disponiveisLocais[i] - tatica.titulares[i];
        for (int j = 0; j < restantes; j++) {
            copiaPlantel[i][j] = copiaPlantel[i][tatica.titulares[i] + j];
        }


        disponiveis[i] = restantes;
    }

    return titulares;
}
int getPos(string posicao) {
    if (posicao == "GR") return 0;
    if (posicao == "DEF") return 1;
    if (posicao == "MED") return 2;
    return 3;
}

Jogador* escolherSuplentes(Jogador** copiaPlantel, int* disponiveis, Tatica tatica, int& numSuplentes) {


    int disp[4] = { disponiveis[0], disponiveis[1], disponiveis[2], disponiveis[3] };

    Jogador* suplentes = new Jogador[6];
    int idx = 0;

    for (int i = 0; i < 4; i++) {
        int preencher = tatica.suplentes[i];
        for (int j = 0; j < preencher && idx < 6; j++) {
            if (disp[i] > 0) {
                suplentes[idx++] = copiaPlantel[i][0];
                for (int k = 1; k < disp[i]; k++) {
                    copiaPlantel[i][k - 1] = copiaPlantel[i][k];
                }
                disp[i]--;
            }
        }
    }

    while (idx < 6) {
        int pos = -1;
        for (int i = 0; i < 4; i++) {
            if (disp[i] > 0) {
                if (pos == -1 || copiaPlantel[i][0].qualidade > copiaPlantel[pos][0].qualidade) {
                    pos = i;
                }
            }
        }
        if (pos != -1) {
            suplentes[idx++] = copiaPlantel[pos][0];
            for (int k = 1; k < disp[pos]; k++) {
                copiaPlantel[pos][k - 1] = copiaPlantel[pos][k];
            }
            disp[pos]--;
        }
        else break;
    }


    for (int i = 0; i < idx - 1; i++) {
        for (int j = 0; j < idx - i - 1; j++) {
            if (getPos(suplentes[j].posicao) > getPos(suplentes[j + 1].posicao)) {
                Jogador temp = suplentes[j];
                suplentes[j] = suplentes[j + 1];
                suplentes[j + 1] = temp;
            }
        }
    }

    numSuplentes = idx;
    return suplentes;
}

void imprimirTitulares(Jogador* titulares, Tatica tatica) {
    cout << "\n*********** Titulares: ***********\n";

    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade \n";
    cout << "-----------------------------------------------------------------------------------------\n";

    string nomesPosicoes[4] = {"GR", "DEF", "MED", "AVA"};
    int idx = 0;

    for (int i = 0; i <4; i++) {
        for (int j = 0; j < tatica.titulares[i]; j++) {
            string strLesao = to_string(titulares[idx].probLes) + "%";
            string strCastigo = to_string(titulares[idx].probSus) + "%";

            cout << left
                << setw(26) << eliminarAcentos(titulares[idx].nome) << "| "
                << setw(4)  << titulares[idx].numero << "| "
                << setw(8)  << eliminarAcentos(titulares[idx].posicao) << "| "
                << setw(6)  << titulares[idx].idade << "| "
                << setw(10) << strLesao << "| "
                << setw(12) << strCastigo << "| "
                << setw(10) << titulares[idx].qualidade << endl;

            idx++;
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}


void imprimirSuplentes(Jogador* suplentes, int numSuplentes) {
    cout << "\n*********** Suplentes: ***********\n";
    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade \n";
    cout << "-----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < numSuplentes; i++) {

        if (i > 0 && suplentes[i].posicao != suplentes[i-1].posicao) {
            cout << endl;
        }

        string strLesao = to_string(suplentes[i].probLes) + "%";
        string strCastigo = to_string(suplentes[i].probSus) + "%";

        cout << left
            << setw(26) << eliminarAcentos(suplentes[i].nome) << "| "
            << setw(4)  << suplentes[i].numero << "| "
            << setw(8)  << eliminarAcentos(suplentes[i].posicao) << "| "
            << setw(6)  << suplentes[i].idade << "| "
            << setw(10) << strLesao << "| "
            << setw(12) << strCastigo << "| "
            << setw(10) << suplentes[i].qualidade << endl;
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

int contarJogadoresPosicao(Equipa& equipa, int pos) {
    return equipa.numJogadores[pos];
}
bool limitePosicaoAtingido(Equipa& equipa, int pos) {

    int limites[4] = {GR_MAX, DEF_MAX, MED_MAX, AVA_MAX};

    if(equipa.numJogadores[pos] >= limites[pos]) {
        cout << "Limite de jogadores nesta posicao atingido!\n";
        return true;
    }

    return false;
}
bool numeroOcupado(Equipa& equipa, int numero) {
    for(int p = 0; p < 4; p++) {
        for(int i = 0; i < equipa.numJogadores[p]; i++) {
            if(equipa.plantel[p][i].numero == numero) return true;
        }
    }
    return false;
}

void listarNumerosLivres(Equipa& equipa, int posicao) {
    const int* numeros;
    int tamanho;
    switch(posicao) {
        case 0: numeros = CAMISAS_GR; tamanho = 3; break;
        case 1: numeros = CAMISAS_DEF; tamanho = 10; break;
        case 2: numeros = CAMISAS_MED; tamanho = 10; break;
        case 3: numeros = CAMISAS_AVA; tamanho = 7; break;
        default: return;
    }

    cout << "\nNumeros disponiveis: ";
    for(int i = 0; i < tamanho; i++) {
        if(!numeroOcupado(equipa, numeros[i])) {
            cout << numeros[i] << " ";
        }
    }
    cout << endl;
}

int escolherNumero(Equipa& equipa, int posicao) {
    int num;
    do {
        listarNumerosLivres(equipa, posicao);
        cout << "Escolha o novo numero: ";
        cin >> num;
        if(numeroOcupado(equipa, num)) cout << " Numero ocupado!\n";
    } while(numeroOcupado(equipa, num));
    return num;
}

void escolherJogadorGlobal(Equipa& equipa, int& pos, int& idx) {
    imprimirPlantel(equipa);
    cout << "\nEscolha a posicao atual do jogador (0-GR, 1-DEF, 2-MED, 3-AVA): ";
    cin >> pos;
    cout << "Indice do jogador nessa posicao (0 a " << equipa.numJogadores[pos] - 1 << "): ";
    cin >> idx;

    if(pos < 0 || pos > 3 || idx < 0 || idx >= equipa.numJogadores[pos]) {
        cout << " Escolha invalida!\n";
        pos = -1;
        idx = -1;
    }
}

void mudarPosicao(Equipa& equipa, int posAtual, int idxJogador, int novaPosicao) {

    Jogador jogador = equipa.plantel[posAtual][idxJogador];

    if (limitePosicaoAtingido(equipa,novaPosicao)) {
        cout << " Vagas da posicao cheias!\n";
        return;
    }
    int novoNumero = escolherNumero(equipa, novaPosicao);
    jogador.numero = novoNumero;
    jogador.posicao = (novaPosicao == 0) ? "GR" : (novaPosicao == 1) ? "DEF" : (novaPosicao == 2) ? "MED" : "AVA";

    for(int i = idxJogador; i < equipa.numJogadores[posAtual] - 1; i++) {
        equipa.plantel[posAtual][i] = equipa.plantel[posAtual][i+1];
    }
    equipa.numJogadores[posAtual]--;

    int tamanhoNovo = equipa.numJogadores[novaPosicao];
    Jogador* novoArray = new Jogador[tamanhoNovo + 1];

    for(int i = 0; i < tamanhoNovo; i++) {
        novoArray[i] = equipa.plantel[novaPosicao][i];
    }

    novoArray[tamanhoNovo] = jogador;

    delete[] equipa.plantel[novaPosicao];
    equipa.plantel[novaPosicao] = novoArray;
    equipa.numJogadores[novaPosicao]++;


    ordenarPlantelNumeroJogador(equipa);

    cout << "\n Posicao alterada com sucesso! O " <<  eliminarAcentos(jogador.nome) << " e agora " << jogador.posicao << ".\n";
}

void treinar(Equipa& equipa) {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {

            if (equipa.plantel[i][j].diasTreino > 0) {
                equipa.plantel[i][j].diasTreino--;
                equipa.plantel[i][j].qualidade += 5;

                if (equipa.plantel[i][j].qualidade > 100)
                    equipa.plantel[i][j].qualidade = 100;
            }
        }
    }
}
Jogador* escolherTitularesManual(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica) {
    /*
           while (true) {
                bool valido = true;
                for (int i = 0; i < 4; i++) {
                    if (disponiveis[i] < tatica.titulares[i]) {
                        cout << "\nNao existem jogadores suficientes na posicao "
                            << i << " Altere a tatica\n";
                        tatica = pedirTatica(tatica);
                        valido = false;
                        break;
                    }
                }
                if (valido) break;
            }
     */

    Jogador* titulares = new Jogador[11];
    int idx = 0;

    for (int pos = 0; pos < 4; pos++) {

        cout << "\n=== Escolher " << tatica.titulares[pos]
             << " jogadores para posicao " << pos << " ===\n";

        for (int n = 0; n < tatica.titulares[pos]; n++) {

            cout << "\nJogadores disponiveis:\n";
            for (int i = 0; i < disponiveis[pos]; i++) {
                cout << i << " - "
                     <<  eliminarAcentos(copiaPlantel[pos][i].nome)
                     << " (" << copiaPlantel[pos][i].numero
                     << ", Q:" << copiaPlantel[pos][i].qualidade << ")\n";
            }

            int escolha;
            cout << "Escolhe indice: ";
            cin >> escolha;

            if (escolha < 0 || escolha >= disponiveis[pos]) {
                cout << " Indice invalido!\n";
                n--;
                continue;
            }

            titulares[idx++] = copiaPlantel[pos][escolha];

            for (int k = escolha; k < disponiveis[pos] - 1; k++) {
                copiaPlantel[pos][k] = copiaPlantel[pos][k + 1];
            }

            disponiveis[pos]--;
        }
    }

    return titulares;
}
Jogador* escolherSuplentesManual(Jogador** copiaPlantel, int* disponiveis, Tatica& tatica) {


        Jogador* suplentes = new Jogador[11];
        int idx = 0;

        for (int pos = 0; pos < 4; pos++) {

            cout << "\n=== Escolher " << tatica.suplentes[pos]
                 << " jogadores para posicao " << pos << " ===\n";

            for (int n = 0; n < tatica.suplentes[pos]; n++) {

                cout << "\nJogadores disponiveis:\n";
                for (int i = 0; i < disponiveis[pos]; i++) {
                    cout << i << " - "
                         <<  eliminarAcentos(copiaPlantel[pos][i].nome)
                         << " (" << copiaPlantel[pos][i].numero
                         << ", Q:" << copiaPlantel[pos][i].qualidade << ")\n";
                }

                int escolha;
                cout << "Escolhe indice: ";
                cin >> escolha;

                if (escolha < 0 || escolha >= disponiveis[pos]) {
                    cout << " Indice invalido!\n";
                    n--;
                    continue;
                }

                suplentes[idx++] = copiaPlantel[pos][escolha];

                for (int k = escolha; k < disponiveis[pos] - 1; k++) {
                    copiaPlantel[pos][k] = copiaPlantel[pos][k + 1];
                }

                disponiveis[pos]--;
            }
        }


    return suplentes;

}
void escolherEquipaManual(Equipa& equipa, Tatica& taticaAtual) {

    int disponiveis[4] = {
        equipa.numJogadores[0],
        equipa.numJogadores[1],
        equipa.numJogadores[2],
        equipa.numJogadores[3]
    };

    Jogador** copiaPlantel = copiarPlantel(equipa, disponiveis);

    ordenarPlantelQualidadeJogador(copiaPlantel, disponiveis);

    if (equipa.titulares) delete[] equipa.titulares;
    if (equipa.suplentes) delete[] equipa.suplentes;
    if (validarPlantelDisponible(equipa, taticaAtual)) {
        cout << "\n===== ESCOLHA MANUAL =====\n";
        cout << "Titulares \n";
        equipa.titulares = escolherTitularesManual(copiaPlantel, disponiveis, equipa.tatica);
        cout << "Suplentes \n";
        equipa.suplentes = escolherSuplentesManual(copiaPlantel, disponiveis, equipa.tatica);
        equipa.escolhaManual = true;
    }
    else {
        cout << "\n Plantel insuficiente para a tatica atual! Escolha manual impossivel.\n";
        equipa.escolhaManual = false;
    }
    cout << "\n Equipa definida manualmente!\n";

    for (int i = 0; i < 4; i++) delete[] copiaPlantel[i];
    delete[] copiaPlantel;
}