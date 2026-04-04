
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/equipa.h"
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/utils.h"
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
    if (total != 11) {
        cout << "A tatica deve ter 11 titulares, tem " << total << "\n";
        return false;
    }
    return true;
}

Tatica pedirTatica(Tatica taticaAtual) {
    Tatica tatica= taticaAtual;

    cout << "\nTatica atual: 1-" << tatica.titulares[1] << "-"
         << tatica.titulares[2] << "-" << tatica.titulares[3] << "\n";
    cout << "Deseja alterar a tatica? (s/n): ";

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
                cout << "\n[AVISO CRITICO] Nao existem jogadores suficientes na posicao "
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

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < tatica.titulares[i]; j++) {
            titulares[idx++] = copiaPlantel[i][j];
        }

        for (int j = tatica.titulares[i]; j < disponiveis[i]; j++) {
            copiaPlantel[i][j - tatica.titulares[i]] = copiaPlantel[i][j];
        }
        disponiveis[i] -= tatica.titulares[i];
    }

    return titulares;
}

int getPos(string posicao) {
    if (posicao == "GR") return 0;
    if (posicao == "DEF") return 1;
    if (posicao == "MED") return 2;
    return 3;
}

Jogador* escolherSuplentes(Jogador** copiaPlantel, int* disponiveis, Tatica tatica) {

    Jogador* suplentes = new Jogador[6];
    int idx = 0;

    for (int i = 0; i < 4; i++) {
        int preencher = tatica.suplentes[i];
        for (int j = 0; j < preencher && idx < 6; j++) {
            if (disponiveis[i] > 0) {
                suplentes[idx++] = copiaPlantel[i][0];
                for (int k = 1; k < disponiveis[i]; k++) {
                    copiaPlantel[i][k-1] = copiaPlantel[i][k];
                }
                disponiveis[i]--;
            }
        }
    }


    while (idx < 6) {

        int pos = -1;
        for (int i = 0; i < 4; i++) {
            if (disponiveis[i] > 0) {
                if (pos == -1 || copiaPlantel[i][0].qualidade > copiaPlantel[pos][0].qualidade) {
                    pos = i;
                }
            }
        }
        if (pos != -1) {
            suplentes[idx++] = copiaPlantel[pos][0];
            for (int k = 1; k < disponiveis[pos]; k++) {
                copiaPlantel[pos][k-1] = copiaPlantel[pos][k];
            }
            disponiveis[pos]--;
        } else break;
    }
    for (int i = 0; i < idx - 1; i++) {
        for (int j = 0; j < idx - i - 1; j++) {

            if (getPos(suplentes[j].posicao) > getPos(suplentes[j+1].posicao)) {
                Jogador temp = suplentes[j];
                suplentes[j] = suplentes[j+1];
                suplentes[j+1] = temp;
            }
        }
    }
    return suplentes;
}


void imprimirTitulares(Jogador* titulares, Tatica tatica) {
    cout << "\n*********** Titulares: ***********\n";

    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade | Dias-Treino\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

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
                << setw(10) << titulares[idx].qualidade << "| "
                << titulares[idx].diasTreino << endl;
            idx++;
        }
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
}


void imprimirSuplentes(Jogador* suplentes) {
    cout << "\n*********** Suplentes: ***********\n";
    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade | Dias-Treino\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < 6; i++) {

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
            << setw(10) << suplentes[i].qualidade << "| "
            << suplentes[i].diasTreino << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
}

void inserirJogador(Jogador** arrayDestino, int& numDestino, Jogador* novoJogador) {
    int inserirEm = numDestino;
    for (int k = 0; k < numDestino; k++) {
        if (getPos(arrayDestino[k]->posicao) > getPos(novoJogador->posicao)) {
            inserirEm = k;
            break;
        }
        if (getPos(arrayDestino[k]->posicao) == getPos(novoJogador->posicao) &&
            arrayDestino[k]->numero > novoJogador->numero) {
            inserirEm = k;
            break;
            }
    }
    for (int k = numDestino; k > inserirEm; k--) {
        arrayDestino[k] = arrayDestino[k-1];
    }
    arrayDestino[inserirEm] = novoJogador;
    numDestino++;
}

void inserirJogadorNoPlantel(Equipa& equipa, Jogador* novo) {
    int pos = getPos(novo->posicao);
    int& tam = equipa.numJogadores[pos];

    int i = 0;
    while (i < tam && equipa.plantel[pos][i].numero < novo->numero) {
        i++;
    }
    for (int j = tam; j > i; j--) {
        equipa.plantel[pos][j] = equipa.plantel[pos][j-1];
    }
    equipa.plantel[pos][i] = *novo;
    tam++;
}

void calcularDanos(Equipa& equipa, Jogador** arrayDestino, int& numDestino, const bool lesao) {

    for (int i = 0; i < 11; i++) {
        int pos = getPos(equipa.titulares[i].posicao);
        int indexNoPlantel = -1;
        for (int j = 0; j < equipa.numJogadores[pos]; j++) {
            if (equipa.plantel[pos][j].numero == equipa.titulares[i].numero) {
                indexNoPlantel = j;
                break;
            }
        }
        if (indexNoPlantel == -1)
            continue;
        int probabilidade = numAleatorio(1, 100);
        int probLimite = lesao ? equipa.titulares[i].probLes : equipa.titulares[i].probSus;

        if (probabilidade <= probLimite && numDestino < 30) {

            Jogador* novoJogador = new Jogador(equipa.titulares[i]);
            novoJogador->semanas_ate_retorno = lesao ? numAleatorio(1, 6) : numAleatorio(1, 3);
            inserirJogador(arrayDestino, numDestino, novoJogador);

            for (int k = indexNoPlantel; k < equipa.numJogadores[pos] - 1; k++)
                equipa.plantel[pos][k] = equipa.plantel[pos][k + 1];
            equipa.numJogadores[pos]--;

            if (lesao) {
                if (equipa.numSubstituicoes >= 3) break;
                for (int s = 0; s < 6; s++) {
                    if (equipa.suplentes[s].posicao == equipa.titulares[i].posicao) {
                        equipa.sairam[equipa.numSubstituicoes] = equipa.titulares[i].nome;
                        equipa.entraram[equipa.numSubstituicoes] = equipa.suplentes[s].nome;
                        equipa.indexTitularSaiu[equipa.numSubstituicoes] = i;
                        equipa.suplenteEntrou[equipa.numSubstituicoes] = equipa.suplentes[s];

                        equipa.numSubstituicoes++;

                        break;
                    }
                }
            }

        }
    }
}

void substituicoes(Equipa& equipa) {
    for (int i = 0; i < equipa.numSubstituicoes; i++) {
        int idxTit = equipa.indexTitularSaiu[i];
        equipa.titulares[idxTit] = equipa.suplenteEntrou[i];

        for (int s = 0; s < 6; s++) {
            if (equipa.suplentes[s].numero == equipa.suplenteEntrou[i].numero) {
                for (int k = s; k < 5; k++)
                    equipa.suplentes[k] = equipa.suplentes[k+1];
                break;
            }
        }
    }
}

void calcularLesionados(Equipa& equipa) {
    calcularDanos(equipa, equipa.lesionados, equipa.numLesionados, true);
}

void calcularSuspensos(Equipa& equipa) {
    calcularDanos(equipa, equipa.suspensos, equipa.numSuspensos, false);
}



void recuperar(Equipa& equipa, Jogador** arrayFora, int& numFora) {
    int i = 0;
    while (i < numFora) {
        arrayFora[i]->semanas_ate_retorno--;
        if (arrayFora[i]->semanas_ate_retorno <= 0) {

            inserirJogadorNoPlantel(equipa, arrayFora[i]);
            delete arrayFora[i];
            for (int k = i; k < numFora - 1; k++)
                arrayFora[k] = arrayFora[k + 1];
            numFora--;
        } else
            i++;
    }
}

void recuperarSuspensos(Equipa& equipa) {
    recuperar(equipa, equipa.suspensos, equipa.numSuspensos);
}

void recuperarLesionados(Equipa& equipa) {
    recuperar(equipa, equipa.lesionados, equipa.numLesionados);
}

void imprimirListaFora(Jogador** arrayFora, int numFora, const string& titulo) {
    cout << "\n*********** " << titulo << " (" << numFora << "): ***********\n";

    if (numFora == 0) {
        cout << "Nenhum jogador nesta lista de momento.\n";
        cout << "--------------------------------------------------------------------------------\n";
        return;
    }
    cout << "Nome                      | N   | Posicao | Idade | Qualidade | Semanas a faltar\n";
    cout << "--------------------------------------------------------------------------------\n";

    for (int i = 0; i < numFora; i++) {
        cout << left
            << setw(26) << eliminarAcentos(arrayFora[i]->nome) << "| "
            << setw(4)  << arrayFora[i]->numero << "| "
            << setw(8)  << eliminarAcentos(arrayFora[i]->posicao) << "| "
            << setw(6)  << arrayFora[i]->idade << "| "
            << setw(10) << arrayFora[i]->qualidade << "| "
            << arrayFora[i]->semanas_ate_retorno << endl;
    }
    cout << "--------------------------------------------------------------------------------\n";
}

void imprimirLesionados(Equipa& equipa) {
    imprimirListaFora(equipa.lesionados, equipa.numLesionados, "Jogadores Lesionados");
}

void imprimirSuspensos(Equipa& equipa) {
    imprimirListaFora(equipa.suspensos, equipa.numSuspensos, "Jogadores Suspensos");
}

void imprimirSubstituicoes(string* sairam, string* entraram, int numSubs) {
    if (numSubs == 0) return;
    cout << "\nSubstituicoes:\n";
    for (int i = 0; i < numSubs; i++) {
        cout << eliminarAcentos(sairam[i]) << " -> "
             << eliminarAcentos(entraram[i]) << "\n";
    }
}