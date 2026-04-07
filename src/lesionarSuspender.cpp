

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/equipa.h"
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/utils.h"
#include "../include/lesionarSuspender.h"
#include "../include/constantes.h"

using namespace std;

void inserirJogadorNoPlantel(Equipa& equipa, Jogador* novo) {
    int pos = getPos(novo->posicao);
    equipa.plantel[pos][equipa.numJogadores[pos]] = *novo;
    equipa.numJogadores[pos]++;
    ordenarPlantelNumeroJogador(equipa);
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

void lesionar(Jogador* titulares, int numTitulares) {
    for (int i = 0; i < numTitulares; i++) {
        titulares[i].semanas_ate_retorno_lesao = 0;
        int probabilidade = numAleatorio(1, 100);
        if (probabilidade <= titulares[i].probLes) {
            titulares[i].semanas_ate_retorno_lesao = numAleatorio(1, 10);
        }
    }
}


void ListaLesionados(Jogador* titulares, int numTitulares, Equipa& equipa) {
    for (int i = 0; i < numTitulares; i++) {
        if (titulares[i].semanas_ate_retorno_lesao > 0) {
            int pos = getPos(titulares[i].posicao);
            int indexNoPlantel = -1;

            for (int j = 0; j < equipa.numJogadores[pos]; j++) {
                if (equipa.plantel[pos][j].numero == titulares[i].numero) {
                    indexNoPlantel = j;
                    break;
                }
            }
            if (indexNoPlantel == -1) continue;

            Jogador* lesionados = new Jogador(equipa.plantel[pos][indexNoPlantel]);
            lesionados->semanas_ate_retorno_lesao = titulares[i].semanas_ate_retorno_lesao;

            inserirJogador(equipa.lesionados, equipa.numLesionados, lesionados);

            for (int k = indexNoPlantel; k < equipa.numJogadores[pos] - 1; k++)
                equipa.plantel[pos][k] = equipa.plantel[pos][k + 1];
            equipa.numJogadores[pos]--;
        }
    }
}
void recuperarLesionados(Equipa& equipa) {
    int i = 0;
    while (i < equipa.numLesionados) {
        equipa.lesionados[i]->semanas_ate_retorno_lesao--;
        if (equipa.lesionados[i]->semanas_ate_retorno_lesao <= 0) {

            inserirJogadorNoPlantel(equipa, equipa.lesionados[i]);
            delete equipa.lesionados[i];

            for (int k = i; k < equipa.numLesionados - 1; k++)
                equipa.lesionados[k] = equipa.lesionados[k + 1];
            equipa.numLesionados--;
        } else {
            i++;
        }
    }
}


void imprimirJogadoresLesionados(Jogador** lesionados, int numeroLesionados) {
    if (numeroLesionados == 0 || lesionados == nullptr) {
        cout << "\nNenhum jogador se lesionou nesta jornada.\n";
        return;
    }
    cout << "\nJogadores Lesionados:\n";
    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade |Jogos Restantes \n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numeroLesionados; i++) {
        cout << left
            << setw(26) << eliminarAcentos(lesionados[i]->nome) << "| "
            << setw(4)  << lesionados[i]->numero << "| "
            << setw(8)  << eliminarAcentos(lesionados[i]->posicao) << "| "
            << setw(6)  << lesionados[i]->idade << "| "
            << setw(10) << lesionados[i]->probLes<< "| "
            << setw(12) << lesionados[i]->probSus << "| "
            << setw(10) << lesionados[i]->qualidade << "| "
            << setw(10) << lesionados[i]->semanas_ate_retorno_lesao << endl;

    }
     cout << "----------------------------------------------------------------------------------------------------------\n";
}


void suspender(Jogador* titulares, int numTitulares) {
    for (int i = 0; i < numTitulares; i++) {
        titulares[i].semanas_ate_retorno_castigo = 0;
        int probabilidade = numAleatorio(1, 100);
        if (probabilidade <= titulares[i].probSus) {
            titulares[i].semanas_ate_retorno_castigo = numAleatorio(1, 10);
        }
    }
}


void ListaSuspensos(Jogador* titulares, int numTitulares, Equipa& equipa) {
    for (int i = 0; i < numTitulares; i++) {
        if (titulares[i].semanas_ate_retorno_castigo > 0) {
            int pos = getPos(titulares[i].posicao);
            int indexNoPlantel = -1;

            for (int j = 0; j < equipa.numJogadores[pos]; j++) {
                if (equipa.plantel[pos][j].numero == titulares[i].numero) {
                    indexNoPlantel = j;
                    break;
                }
            }
            if (indexNoPlantel == -1) continue;

            Jogador* lesionados = new Jogador(equipa.plantel[pos][indexNoPlantel]);
            lesionados->semanas_ate_retorno_castigo = titulares[i].semanas_ate_retorno_castigo;

            inserirJogador(equipa.suspensos, equipa.numSuspensos, lesionados);

            for (int k = indexNoPlantel; k < equipa.numJogadores[pos] - 1; k++)
                equipa.plantel[pos][k] = equipa.plantel[pos][k + 1];
            equipa.numJogadores[pos]--;
        }
    }
}
void recuperarSuspensos(Equipa& equipa) {
    int i = 0;
    while (i < equipa.numSuspensos) {
        equipa.suspensos[i]->semanas_ate_retorno_castigo--;
        if (equipa.suspensos[i]->semanas_ate_retorno_castigo <= 0) {

            inserirJogadorNoPlantel(equipa, equipa.suspensos[i]);
            delete equipa.suspensos[i];

            for (int k = i; k < equipa.numSuspensos - 1; k++)
                equipa.suspensos[k] = equipa.suspensos[k + 1];
            equipa.numSuspensos--;
        } else {
            i++;
        }
    }
}

void imprimirJogadoresSuspensos1(Jogador** suspensos, int numeroSuspensos) {
    if (numeroSuspensos== 0 || suspensos == nullptr) {
        cout << "\nNenhum jogador foi suspendido nesta jornada.\n";
        return;
    }
    cout << "\nJogadores Suspensos:\n";
    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade |Jogos Restantes \n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numeroSuspensos; i++) {
        cout << left
            << setw(26) << eliminarAcentos(suspensos[i]->nome) << "| "
            << setw(4)  << suspensos[i]->numero << "| "
            << setw(8)  << eliminarAcentos(suspensos[i]->posicao) << "| "
            << setw(6)  << suspensos[i]->idade << "| "
            << setw(10) << suspensos[i]->probLes<< "| "
            << setw(12) << suspensos[i]->probSus << "| "
            << setw(10) << suspensos[i]->qualidade << "| "
            << setw(10) << suspensos[i]->semanas_ate_retorno_castigo << endl;

    }
    cout << "-----------------------------------------------------------------------------------------------------------\n";
}


void imprimirJogadoresSuspensos2(Jogador** suspensos, int numeroSuspensos) {
    if (numeroSuspensos== 0 || suspensos == nullptr) {
        cout << "\nNenhum jogador foi suspendido nesta jornada.\n";
        return;
    }
    cout << "\nJogadores Suspensos:\n";
    cout << "Nome                      | N   | Posicao | Idade | ProbLesao | ProbCastigo | Qualidade |Jogos Restantes |Dias-Treino \n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numeroSuspensos; i++) {
        cout << left
            << setw(26) << eliminarAcentos(suspensos[i]->nome) << "| "
            << setw(4)  << suspensos[i]->numero << "| "
            << setw(8)  << eliminarAcentos(suspensos[i]->posicao) << "| "
            << setw(6)  << suspensos[i]->idade << "| "
            << setw(10) << suspensos[i]->probLes<< "| "
            << setw(12) << suspensos[i]->probSus << "| "
            << setw(10) << suspensos[i]->qualidade << "| "
            << setw(10) << suspensos[i]->semanas_ate_retorno_castigo <<  "| "
            << suspensos[i]->diasTreino << endl;

    }
    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
}


void substituicoes(Jogador* titulares, Jogador* suplentes, int numTitulares, int numSuplentes, Equipa& equipa) {
    int numSubstituicoes = 0;
    bool usado[6] = {false};

    for (int i = 0; i < numTitulares && numSubstituicoes < 3; i++) {
        if (titulares[i].semanas_ate_retorno_lesao > 0) {


            int melhorSuplente = -1;
            int melhorQualidade = -1;

            for (int s = 0; s < numSuplentes; s++) {
                if (!usado[s] && suplentes[s].posicao == titulares[i].posicao && suplentes[s].qualidade > melhorQualidade){
                    melhorQualidade = suplentes[s].qualidade;
                    melhorSuplente = s;
                }
            }

            if (melhorSuplente != -1) {
                equipa.sairam[equipa.numSubstituicoes] = titulares[i].nome;
                equipa.entraram[equipa.numSubstituicoes] = suplentes[melhorSuplente].nome;
                equipa.numSubstituicoes++;
                numSubstituicoes++;
                usado[melhorSuplente] = true;
            }
        }
    }
}

bool verificarDerrota(int lesionadosJornada, int suspensosJornada, int substituicoesJornada) {
    int baixas = lesionadosJornada + suspensosJornada - substituicoesJornada;
    return (11 - baixas) < 7;
}


void aplicarLesaoManual(Equipa& equipa, int numeroJogador, int semanas) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            if (equipa.plantel[i][j].numero == numeroJogador) {
                if (equipa.numLesionados < 30) {
                    Jogador* azarado = new Jogador(equipa.plantel[i][j]);
                    azarado->semanas_ate_retorno_lesao = semanas;
                    inserirJogador(equipa.lesionados, equipa.numLesionados, azarado);
                    for (int k = j; k < equipa.numJogadores[i] - 1; k++)
                        equipa.plantel[i][k] = equipa.plantel[i][k + 1];
                    equipa.numJogadores[i]--;
                    cout << "\n[INFO] Lesao aplicada a " << azarado->nome << " por " << semanas << " semanas.\n";
                    return;
                } else {
                    cout << "\n[ERRO] A enfermaria esta cheia!\n";
                    return;
                }
            }
        }
    }
    for (int i = 0; i < equipa.numLesionados; i++) {
        if (equipa.lesionados[i]->numero == numeroJogador) {
            equipa.lesionados[i]->semanas_ate_retorno_lesao += semanas;
            cout << "\n[INFO] Tempo de lesao aumentado para " << equipa.lesionados[i]->nome << ".\n";
            return;
        }
    }
    cout << "\n[ERRO] Jogador nao encontrado ou ja se encontra suspenso.\n";
}

void reduzirLesaoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < equipa.numLesionados; i++) {
        if (equipa.lesionados[i]->numero == numeroJogador) {
            equipa.lesionados[i]->semanas_ate_retorno_lesao -= semanas;
            cout << "\n[INFO] Tempo de lesao reduzido para " << equipa.lesionados[i]->nome << ".\n";
            if (equipa.lesionados[i]->semanas_ate_retorno_lesao <= 0) {
                equipa.lesionados[i]->semanas_ate_retorno_lesao = 0;
                cout << "[INFO] " << equipa.lesionados[i]->nome << " recuperou totalmente e voltou ao plantel!\n";
                inserirJogadorNoPlantel(equipa, equipa.lesionados[i]);
                delete equipa.lesionados[i];
                for (int k = i; k < equipa.numLesionados - 1; k++)
                    equipa.lesionados[k] = equipa.lesionados[k + 1];
                equipa.numLesionados--;
            }
            return;
        }
    }
    cout << "\n[ERRO] Esse jogador nao esta na enfermaria.\n";
}

void aplicarCastigoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            if (equipa.plantel[i][j].numero == numeroJogador) {
                if (equipa.numSuspensos < 30) {
                    Jogador* indisciplinado = new Jogador(equipa.plantel[i][j]);
                    indisciplinado->semanas_ate_retorno_castigo = semanas;
                    inserirJogador(equipa.suspensos, equipa.numSuspensos, indisciplinado);
                    for (int k = j; k < equipa.numJogadores[i] - 1; k++)
                        equipa.plantel[i][k] = equipa.plantel[i][k + 1];
                    equipa.numJogadores[i]--;
                    cout << "\n[INFO] Castigo aplicado a " << indisciplinado->nome << " por " << semanas << " semanas.\n";
                    return;
                } else {
                    cout << "\n[ERRO] A lista de suspensos esta cheia!\n";
                    return;
                }
            }
        }
    }
    for (int i = 0; i < equipa.numSuspensos; i++) {
        if (equipa.suspensos[i]->numero == numeroJogador) {
            equipa.suspensos[i]->semanas_ate_retorno_castigo += semanas;
            cout << "\n[INFO] Pena aumentada para " << equipa.suspensos[i]->nome << ".\n";
            return;
        }
    }
    cout << "\n[ERRO] Jogador nao encontrado ou encontra-se lesionado.\n";
}

void reduzirCastigoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < equipa.numSuspensos; i++) {
        if (equipa.suspensos[i]->numero == numeroJogador) {
            equipa.suspensos[i]->semanas_ate_retorno_castigo -= semanas;
            cout << "\n[INFO] Tempo de castigo reduzido para " << equipa.suspensos[i]->nome << ".\n";
            if (equipa.suspensos[i]->semanas_ate_retorno_castigo <= 0) {
                equipa.suspensos[i]->semanas_ate_retorno_castigo = 0;
                cout << "[INFO] O castigo de " << equipa.suspensos[i]->nome << " terminou! Voltou ao plantel.\n";
                inserirJogadorNoPlantel(equipa, equipa.suspensos[i]);
                delete equipa.suspensos[i];
                for (int k = i; k < equipa.numSuspensos - 1; k++)
                    equipa.suspensos[k] = equipa.suspensos[k + 1];
                equipa.numSuspensos--;
            }
            return;
        }
    }
    cout << "\n[ERRO] Esse jogador nao esta na lista de suspensos.\n";
}