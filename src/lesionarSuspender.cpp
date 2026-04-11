

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
#include "../include/transferencias.h"

using namespace std;
/** * @brief Ordena o plantel da equipe com base no número do jogador, utilizando o algoritmo de ordenação bubble sort.
 *
 * @param equipa Referência para a equipe cujo plantel será ordenado.
 * @return Um ponteiro para o plantel ordenado da equipe.
 */
void inserirJogadorNoPlantel(Equipa& equipa, Jogador* novo) {
    int pos = getPos(novo->posicao);
    int tam = equipa.numJogadores[pos];
	

    Jogador* novoArray = new Jogador[tam + 1];

    for (int i = 0; i < tam; i++) {
        novoArray[i] = equipa.plantel[pos][i];
    }

    novoArray[tam] = *novo;

    delete[] equipa.plantel[pos];
    equipa.plantel[pos] = novoArray;

    equipa.numJogadores[pos]++;

    ordenarPlantelNumeroJogador(equipa);
}
/** * @brief Insere um jogador em um array de jogadores, mantendo a ordem com base na posição e número do jogador.
 *
 * @param arrayDestino O array de jogadores onde o novo jogador será inserido.
 * @param numDestino Referência para o número atual de jogadores no array de destino, que será atualizado após a inserção.
 * @param novoJogador O jogador a ser inserido no array de destino.
 */
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
/** * @brief Simula lesões nos jogadores titulares, atribuindo um número aleatório de semanas até o retorno da lesão com base na probabilidade de lesão de cada jogador.
 *
 * @param titulares Array de jogadores titulares que serão avaliados para lesões.
 * @param numTitulares O número de jogadores titulares no array.
 */
void lesionar(Jogador* titulares, int numTitulares) {
    for (int i = 0; i < numTitulares; i++) {
        titulares[i].semanas_ate_retorno_lesao = 0;
        int probabilidade = numAleatorio(1, 100);
        if (probabilidade <= titulares[i].probLes) {
            titulares[i].semanas_ate_retorno_lesao = numAleatorio(1, LIMITE_TEMPO_LESIONADO)+1;
        }
    }
}

/** * @brief Move os jogadores lesionados dos titulares para a lista de lesionados da equipe, removendo-os do plantel e atualizando o número de jogadores em cada posição.
 *
 * @param titulares Array de jogadores titulares que serão avaliados para lesões e movidos para a lista de lesionados, se necessário.
 * @param numTitulares O número de jogadores titulares no array.
 * @param equipa Referência para a equipe cujo plantel será atualizado com os jogadores lesionados.
 */
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
/** * @brief Recupera os jogadores lesionados, reduzindo o número de semanas até o retorno da lesão e movendo os jogadores de volta para o plantel quando estiverem recuperados.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com os jogadores lesionados que estão se recuperando.
 */
void recuperarLesionados(Equipa& equipa) {
    int i = 0;
    while (i < equipa.numLesionados) {
        equipa.lesionados[i]->semanas_ate_retorno_lesao--;
        if (equipa.lesionados[i]->semanas_ate_retorno_lesao <= 0) {

            Jogador jogadorTemp = *(equipa.lesionados[i]);
            inserirJogadorNoPlantel(equipa, &jogadorTemp);
            delete equipa.lesionados[i];

            for (int k = i; k < equipa.numLesionados - 1; k++)
                equipa.lesionados[k] = equipa.lesionados[k + 1];
            equipa.numLesionados--;
        } else {
            i++;
        }
    }
}

/** * @brief Imprime a lista de jogadores lesionados, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão, qualidade e semanas restantes até o retorno da lesão.
 *
 * @param lesionados Array de ponteiros para os jogadores lesionados que serão impressos.
 * @param numeroLesionados O número de jogadores lesionados no array.
 */
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

/** * @brief Simula suspensões nos jogadores titulares, atribuindo um número aleatório de semanas até o retorno do castigo com base na probabilidade de suspensão de cada jogador.
 *
 * @param titulares Array de jogadores titulares que serão avaliados para suspensões.
 * @param numTitulares O número de jogadores titulares no array.
 */
void suspender(Jogador* titulares, int numTitulares) {
    for (int i = 0; i < numTitulares; i++) {
        titulares[i].semanas_ate_retorno_castigo = 0;
        int probabilidade = numAleatorio(1, 100);
        if (probabilidade <= titulares[i].probSus) {
            titulares[i].semanas_ate_retorno_castigo = numAleatorio(1, LIMITE_TEMPO_SUSPENSO);
        }
    }
}

/** * @brief Move os jogadores suspensos dos titulares para a lista de suspensos da equipe, removendo-os do plantel e atualizando o número de jogadores em cada posição.
 *
 * @param titulares Array de jogadores titulares que serão avaliados para suspensões e movidos para a lista de suspensos, se necessário.
 * @param numTitulares O número de jogadores titulares no array.
 * @param equipa Referência para a equipe cujo plantel será atualizado com os jogadores suspensos.
 */
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
/** * @brief Recupera os jogadores suspensos, reduzindo o número de semanas até o retorno do castigo e movendo os jogadores de volta para o plantel quando estiverem recuperados.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com os jogadores suspensos que estão se recuperando.
 */
void recuperarSuspensos(Equipa& equipa) {
    int i = 0;
    while (i < equipa.numSuspensos) {
        equipa.suspensos[i]->semanas_ate_retorno_castigo--;
        if (equipa.suspensos[i]->semanas_ate_retorno_castigo <= 0) {

            Jogador jogadorTemp = *(equipa.suspensos[i]);


            inserirJogadorNoPlantel(equipa, &jogadorTemp);


            delete equipa.suspensos[i];

            for (int k = i; k < equipa.numSuspensos - 1; k++)
                equipa.suspensos[k] = equipa.suspensos[k + 1];
            equipa.numSuspensos--;
        } else {
            i++;
        }
    }
}
/** * @brief Imprime a lista de jogadores suspensos, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão, qualidade e semanas restantes até o retorno do castigo.
 *
 * @param suspensos Array de ponteiros para os jogadores suspensos que serão impressos.
 * @param numeroSuspensos O número de jogadores suspensos no array.
 */
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

/** * @brief Imprime a lista de jogadores suspensos, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão, qualidade, semanas restantes até o retorno do castigo e dias de treino.
 *
 * @param suspensos Array de ponteiros para os jogadores suspensos que serão impressos.
 * @param numeroSuspensos O número de jogadores suspensos no array.
 */
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
            << setw(15) << suspensos[i]->semanas_ate_retorno_castigo <<  "| "
            << suspensos[i]->diasTreino << endl;

    }
    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
}

/** * @brief Realiza substituições nos jogadores titulares que estão lesionados, buscando os melhores suplentes disponíveis para cada posição e atualizando a equipe com as substituições realizadas.
 *
 * @param titulares Array de jogadores titulares que serão avaliados para substituições.
 * @param suplentes Array de jogadores suplentes disponíveis para substituição.
 * @param numTitulares O número de jogadores titulares no array.
 * @param numSuplentes O número de jogadores suplentes no array.
 * @param equipa Referência para a equipe cujo plantel será atualizado com as substituições realizadas.
 */
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

/** * @brief Verifica se a equipe está em situação de derrota, considerando o número de jogadores lesionados, suspensos e as substituições realizadas.
 *
 * @param lesionadosJornada O número de jogadores lesionados na jornada atual.
 * @param suspensosJornada O número de jogadores suspensos na jornada atual.
 * @param substituicoesJornada O número de substituições realizadas na jornada atual.
 * @return true se a equipe estiver em situação de derrota (menos de 7 jogadores disponíveis), ou false caso contrário.
 */
bool verificarDerrota(int lesionadosJornada, int suspensosJornada, int substituicoesJornada) {
    int baixas = lesionadosJornada + suspensosJornada - substituicoesJornada;
    return (11 - baixas) < 7;
}

/** * @brief Aplica uma lesão manual a um jogador específico, movendo-o para a lista de lesionados da equipe e atualizando o plantel e o número de jogadores em cada posição.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com a lesão aplicada.
 * @param numeroJogador O número do jogador que será lesionado.
 * @param semanas O número de semanas até o retorno da lesão que será atribuído ao jogador lesionado.
 */
void aplicarLesaoManual(Equipa& equipa, int numeroJogador, int semanas) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            if (equipa.plantel[i][j].numero == numeroJogador) {
                if (equipa.numLesionados < MAXIMO_JOGADORES) {
                    Jogador* azarado = new Jogador(equipa.plantel[i][j]);
                    azarado->semanas_ate_retorno_lesao = semanas;
                    inserirJogador(equipa.lesionados, equipa.numLesionados, azarado);
                    for (int k = j; k < equipa.numJogadores[i] - 1; k++)
                        equipa.plantel[i][k] = equipa.plantel[i][k + 1];
                    equipa.numJogadores[i]--;
                    cout << "\n Lesao aplicada a " << eliminarAcentos(azarado->nome) << " por " << semanas << " semanas.\n";
                    return;
                } else {
                    cout << "\nA enfermaria esta cheia!\n";
                    return;
                }
            }
        }
    }
    for (int i = 0; i < equipa.numLesionados; i++) {
        if (equipa.lesionados[i]->numero == numeroJogador) {
            equipa.lesionados[i]->semanas_ate_retorno_lesao += semanas;
            cout << "\n Tempo de lesao aumentado para " << eliminarAcentos(equipa.lesionados[i]->nome) << ".\n";
            return;
        }
    }
    cout << "\n Jogador nao encontrado \n";
}
/** * @brief Reduz o tempo de lesão de um jogador específico, atualizando a lista de lesionados da equipe e movendo o jogador de volta para o plantel quando estiver recuperado.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com a redução do tempo de lesão.
 * @param numeroJogador O número do jogador cuja lesão será reduzida.
 * @param semanas O número de semanas que será subtraído do tempo de lesão do jogador.
 */
void reduzirLesaoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < equipa.numLesionados; i++) {
        if (equipa.lesionados[i]->numero == numeroJogador) {
            equipa.lesionados[i]->semanas_ate_retorno_lesao -= semanas;
            cout << "\n Tempo de lesao reduzido para " << eliminarAcentos(equipa.lesionados[i]->nome) << ".\n";
            if (equipa.lesionados[i]->semanas_ate_retorno_lesao <= 0) {
                equipa.lesionados[i]->semanas_ate_retorno_lesao = 0;
                cout << eliminarAcentos(equipa.lesionados[i]->nome) << " recuperou totalmente e voltou ao plantel!\n";
                inserirJogadorNoPlantel(equipa, equipa.lesionados[i]);
                delete equipa.lesionados[i];
                for (int k = i; k < equipa.numLesionados - 1; k++)
                    equipa.lesionados[k] = equipa.lesionados[k + 1];
                equipa.numLesionados--;
            }
            return;
        }
    }
    cout << "\n Esse jogador nao esta na enfermaria.\n";
}

/** * @brief Aplica um castigo manual a um jogador específico, movendo-o para a lista de suspensos da equipe e atualizando o plantel e o número de jogadores em cada posição.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com o castigo aplicado.
 * @param numeroJogador O número do jogador que será suspenso.
 * @param semanas O número de semanas até o retorno do castigo que será atribuído ao jogador suspenso.
 */
void aplicarCastigoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            if (equipa.plantel[i][j].numero == numeroJogador) {
                if (equipa.numSuspensos < MAXIMO_JOGADORES) {
                    Jogador* indisciplinado = new Jogador(equipa.plantel[i][j]);
                    indisciplinado->semanas_ate_retorno_castigo = semanas;
                    inserirJogador(equipa.suspensos, equipa.numSuspensos, indisciplinado);
                    for (int k = j; k < equipa.numJogadores[i] - 1; k++)
                        equipa.plantel[i][k] = equipa.plantel[i][k + 1];
                    equipa.numJogadores[i]--;
                    cout << "\n Castigo aplicado a " <<  eliminarAcentos(indisciplinado->nome) << " por " << semanas << " semanas.\n";
                    return;
                } else {
                    cout << "\n A lista de suspensos esta cheia!\n";
                    return;
                }
            }
        }
    }
    for (int i = 0; i < equipa.numSuspensos; i++) {
        if (equipa.suspensos[i]->numero == numeroJogador) {
            equipa.suspensos[i]->semanas_ate_retorno_castigo += semanas;
            cout << "\n Pena aumentada para " <<  eliminarAcentos(equipa.suspensos[i]->nome) << ".\n";
            return;
        }
    }
    cout << "\n Jogador nao encontrado\n";
}
/** * @brief Reduz o tempo de castigo de um jogador específico, atualizando a lista de suspensos da equipe e movendo o jogador de volta para o plantel quando estiver recuperado.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com a redução do tempo de castigo.
 * @param numeroJogador O número do jogador cujo castigo será reduzido.
 * @param semanas O número de semanas que será subtraído do tempo de castigo do jogador.
 */
void reduzirCastigoManual(Equipa& equipa, const int numeroJogador, const int semanas) {
    for (int i = 0; i < equipa.numSuspensos; i++) {
        if (equipa.suspensos[i]->numero == numeroJogador) {
            equipa.suspensos[i]->semanas_ate_retorno_castigo -= semanas;
            cout << "\n Tempo de castigo reduzido para " <<  eliminarAcentos(equipa.suspensos[i]->nome) << ".\n";
            if (equipa.suspensos[i]->semanas_ate_retorno_castigo <= 0) {
                equipa.suspensos[i]->semanas_ate_retorno_castigo = 0;
                cout << " O castigo de " <<  eliminarAcentos(equipa.suspensos[i]->nome) << " terminou! Voltou ao plantel.\n";
                inserirJogadorNoPlantel(equipa, equipa.suspensos[i]);
                delete equipa.suspensos[i];
                for (int k = i; k < equipa.numSuspensos - 1; k++)
                    equipa.suspensos[k] = equipa.suspensos[k + 1];
                equipa.numSuspensos--;
            }
            return;
        }
    }
    cout << "\n Esse jogador nao esta na lista de suspensos.\n";
}