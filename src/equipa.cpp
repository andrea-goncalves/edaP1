
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

/** * @brief Gera o plantel da equipe a partir dos jogadores fornecidos para cada posição.
 *
 * @param gr Array de jogadores para a posição de goleiro (GR).
 * @param def Array de jogadores para a posição de defensor (DEF).
 * @param med Array de jogadores para a posição de meio-campista (MED).
 * @param ava Array de jogadores para a posição de atacante (AVA).
 * @param numGR Número de jogadores na posição de goleiro.
 * @param numDEF Número de jogadores na posição de defensor.
 * @param numMED Número de jogadores na posição de meio-campista.
 * @param numAVA Número de jogadores na posição de atacante.
 * @return Um ponteiro para um array bidimensional contendo os jogadores organizados por posição.
 */
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

/** * @brief Ordena o plantel da equipe com base no número do jogador, utilizando o algoritmo de ordenação bubble sort.
 *
 * @param equipa Referência para a equipe cujo plantel será ordenado.
 * @return Um ponteiro para o plantel ordenado da equipe.
 */
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
/** * @brief Ordena o plantel da equipe com base na qualidade do jogador, utilizando o algoritmo de ordenação bubble sort.
 *
 * @param plantel Ponteiro para o plantel da equipe a ser ordenado.
 * @param disponiveis Array contendo o número de jogadores disponíveis para cada posição no plantel.
 */
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

/** * @brief Imprime o plantel disponível da equipe, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão, qualidade e dias de treino.
 *
 * @param equipa Referência para a equipe cujo plantel será impresso.
 */
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
/** * @brief Valida a tática escolhida para a equipe, verificando se o número total de titulares está dentro dos limites permitidos (entre 7 e 11).
 *
 * @param tatica A tática a ser validada, contendo o número de titulares para cada posição.
 * @return true se a tática for válida, ou false se o número total de titulares estiver fora dos limites permitidos.
 */
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
/** * @brief Permite ao usuário escolher a tática da equipe, exibindo a tática atual e solicitando alterações, se desejado. A função também valida a tática escolhida para garantir que o número total de titulares esteja dentro dos limites permitidos.
 *
 * @param taticaAtual A tática atual da equipe, contendo o número de titulares para cada posição.
 * @return A tática escolhida pelo usuário, que pode ser a mesma tática atual ou uma nova tática alterada pelo usuário, desde que seja válida.
 */
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
/** * @brief Cria uma cópia do plantel da equipe, alocando um novo array bidimensional e copiando os jogadores disponíveis para cada posição.
 *
 * @param equipa Referência para a equipe cujo plantel será copiado.
 * @param disponiveis Array contendo o número de jogadores disponíveis para cada posição no plantel da equipe.
 * @return Um ponteiro para o novo plantel copiado da equipe.
 */
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
/** * @brief Permite ao usuário escolher os titulares da equipe com base na tática escolhida, garantindo que haja jogadores suficientes disponíveis para cada posição. A função também atualiza o número de jogadores disponíveis para cada posição após a escolha dos titulares.
 *
 * @param copiaPlantel Ponteiro para o plantel copiado da equipe, contendo os jogadores disponíveis para cada posição.
 * @param disponiveis Array contendo o número de jogadores disponíveis para cada posição no plantel copiado.
 * @param tatica A tática escolhida para a equipe, contendo o número de titulares para cada posição.
 * @return Um ponteiro para um array contendo os jogadores titulares escolhidos pelo usuário.
 */
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
/** * @brief Retorna um valor inteiro correspondente à posição de um jogador com base em sua string de posição.
 *
 * @param posicao A string representando a posição do jogador (por exemplo, "GR", "DEF", "MED", "AVA").
 * @return Um valor inteiro correspondente à posição do jogador, onde 0 representa goleiro (GR), 1 representa defensor (DEF), 2 representa meio-campista (MED) e 3 representa atacante (AVA). Se a posição não for reconhecida, retorna -1.
 */
int getPos(string posicao) {
    if (posicao == "GR") return 0;
    if (posicao == "DEF") return 1;
    if (posicao == "MED") return 2;
    return 3;
}
/** * @brief Permite ao usuário escolher os suplentes da equipe com base na tática escolhida e nos jogadores disponíveis, garantindo que os suplentes sejam escolhidos de acordo com as posições necessárias para a tática. A função também ordena os suplentes por posição antes de retorná-los.
 *
 * @param copiaPlantel Ponteiro para o plantel copiado da equipe, contendo os jogadores disponíveis para cada posição.
 * @param disponiveis Array contendo o número de jogadores disponíveis para cada posição no plantel copiado.
 * @param tatica A tática escolhida para a equipe, contendo o número de titulares e suplentes para cada posição.
 * @param numSuplentes Referência para um inteiro onde será armazenado o número de suplentes escolhidos pelo usuário.
 * @return Um ponteiro para um array contendo os jogadores suplentes escolhidos pelo usuário, ordenados por posição.
 */
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

/** * @brief Imprime os jogadores titulares da equipe, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão e qualidade. A função organiza os titulares por posição e formata a saída para melhor visualização.
 *
 * @param titulares Ponteiro para um array contendo os jogadores titulares da equipe.
 * @param tatica A tática escolhida para a equipe, contendo o número de titulares para cada posição.
 */
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

/** * @brief Imprime os jogadores suplentes da equipe, exibindo informações como nome, número, posição, idade, probabilidade de lesão, probabilidade de suspensão e qualidade. A função organiza os suplentes por posição e formata a saída para melhor visualização.
 *
 * @param suplentes Ponteiro para um array contendo os jogadores suplentes da equipe.
 * @param numSuplentes O número total de jogadores suplentes no array.
 */
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
/** * @brief Conta o número de jogadores disponíveis em uma determinada posição no plantel da equipe.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param pos O índice da posição a ser verificada (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @return O número de jogadores disponíveis na posição especificada.
 */
int contarJogadoresPosicao(Equipa& equipa, int pos) {
    return equipa.numJogadores[pos];
}
/** * @brief Verifica se o limite máximo de jogadores para uma determinada posição no plantel da equipe foi atingido.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param pos O índice da posição a ser verificada (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @return true se o limite de jogadores para a posição especificada foi atingido, ou false caso contrário.
 */
bool limitePosicaoAtingido(Equipa& equipa, int pos) {

    static const int limites[4] = {GR_MAX, DEF_MAX, MED_MAX, AVA_MAX};

    if(equipa.numJogadores[pos] >= limites[pos]) {
        cout << "Limite da posicao atingido!\n";
        return true;
    }

    return false;
}
/** * @brief Verifica se um número de jogador específico já está ocupado por algum jogador no plantel da equipe.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param numero O número do jogador a ser verificado.
 * @return true se o número do jogador estiver ocupado por algum jogador no plantel, ou false caso contrário.
 */
bool numeroOcupado(Equipa& equipa, int numero) {
    for(int p = 0; p < 4; p++) {
        for(int i = 0; i < equipa.numJogadores[p]; i++) {
            if(equipa.plantel[p][i].numero == numero) return true;
        }
    }
    return false;
}
/** * @brief Lista os números de jogador disponíveis para uma determinada posição no plantel da equipe, exibindo-os para o usuário.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param posicao O índice da posição para a qual os números disponíveis serão listados (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 */
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

/** * @brief Permite ao usuário escolher um número de jogador para uma determinada posição no plantel da equipe, garantindo que o número escolhido não esteja ocupado por outro jogador. A função lista os números disponíveis para a posição especificada e solicita ao usuário que escolha um número, validando a escolha para garantir que seja válida.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param posicao O índice da posição para a qual o número do jogador será escolhido (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @return O número do jogador escolhido pelo usuário, que deve ser um número disponível para a posição especificada e não estar ocupado por outro jogador no plantel.
 */
int escolherNumero(Equipa& equipa, int posicao) {
    int num;
    while (true) {
        listarNumerosLivres(equipa, posicao);
        cout << "Escolha o novo numero: ";
        cin >> num;
        if(!numeroOcupado(equipa, num)) return num;
        cout << "[ERRO] Numero ja esta a ser usado!\n";
    }
}

/** * @brief Permite ao usuário escolher um jogador do plantel da equipe, solicitando a posição do jogador e o índice do jogador nessa posição. A função também valida as escolhas do usuário para garantir que a posição e o índice sejam válidos dentro do plantel da equipe.
 *
 * @param equipa Referência para a equipe cujo plantel será verificado.
 * @param pos Referência para um inteiro onde será armazenada a posição do jogador escolhida pelo usuário (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
 * @param idx Referência para um inteiro onde será armazenado o índice do jogador escolhido pelo usuário dentro da posição especificada.
 */
void escolherJogadorGlobal(Equipa& equipa, int& pos, int& idx) {
    imprimirPlantel(equipa);
    cout << "\nEscolha a posicao (0-GR, 1-DEF, 2-MED, 3-AVA): ";
    cin >> pos;

    if(pos < 0 || pos > 3) {
        cout << "[ERRO] Posicao inexistente!\n";
        pos = -1; return;
    }

    cout << "Indice (0 a " << equipa.numJogadores[pos] - 1 << "): ";
    cin >> idx;

    if(idx < 0 || idx >= equipa.numJogadores[pos]) {
        cout << "[ERRO] Indice invalido!\n";
        pos = -1; idx = -1;
    }
}
/** * @brief Permite ao usuário mudar a posição de um jogador no plantel da equipe, solicitando a posição atual do jogador, o índice do jogador nessa posição e a nova posição desejada. A função também valida as escolhas do usuário e atualiza o plantel da equipe de acordo com a mudança de posição.
    *
    * @param equipa Referência para a equipe cujo plantel será atualizado.
    * @param posAtual A posição atual do jogador a ser movido (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
    * @param idxJogador O índice do jogador dentro da posição atual.
    * @param novaPosicao A nova posição desejada para o jogador (0 para "GR", 1 para "DEF", 2 para "MED", 3 para "AVA").
    */

void mudarPosicao(Equipa& equipa, int posAtual, int idxJogador, int novaPosicao) {
    if (limitePosicaoAtingido(equipa, novaPosicao)) {
        cout << "[ERRO] Nao ha espaco na nova posicao!\n";
        return;
    }


    Jogador j = equipa.plantel[posAtual][idxJogador];


    int novoNumero = escolherNumero(equipa, novaPosicao);
    j.numero = novoNumero;
    const char* nomesPos[] = {"GR", "DEF", "MED", "AVA"};
    j.posicao = nomesPos[novaPosicao];


    for(int i = idxJogador; i < equipa.numJogadores[posAtual] - 1; i++) {
        equipa.plantel[posAtual][i] = equipa.plantel[posAtual][i+1];
    }
    equipa.numJogadores[posAtual]--;


    int n = equipa.numJogadores[novaPosicao];
    Jogador* novoArray = new Jogador[n + 1];
    for(int i = 0; i < n; i++) novoArray[i] = equipa.plantel[novaPosicao][i];

    novoArray[n] = j;

    delete[] equipa.plantel[novaPosicao];
    equipa.plantel[novaPosicao] = novoArray;
    equipa.numJogadores[novaPosicao]++;

    ordenarPlantelNumeroJogador(equipa);
    cout << "\n[INFO] " << eliminarAcentos(j.nome) << " agora e " << j.posicao << "!\n";
}

/** * @brief Realiza o treino dos jogadores da equipe, reduzindo os dias de treino restantes para cada jogador e aumentando a qualidade dos jogadores que ainda têm dias de treino disponíveis. A função também garante que a qualidade dos jogadores não ultrapasse o valor máximo permitido (100).
 *
 * @param equipa Referência para a equipe cujo plantel será treinado.
 */
void treinar(Equipa& equipa) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            Jogador& jog = equipa.plantel[i][j];
            if (jog.diasTreino > 0) {
                jog.diasTreino--;
                jog.qualidade = (jog.qualidade + 5>100)?100:jog.qualidade + 5;
            }
        }
    }

}

/** * @brief Permite ao usuário escolher manualmente os jogadores titulares e suplentes da equipe com base na tática escolhida, garantindo que haja jogadores suficientes disponíveis para cada posição. A função exibe as opções de jogadores disponíveis para cada posição e solicita ao usuário que escolha os jogadores, atualizando o plantel da equipe de acordo com as escolhas do usuário.
 *
 * @param copiaPlantel Ponteiro para o plantel copiado da equipe, contendo os jogadores disponíveis para cada posição.
 * @param disponiveis Array contendo o número de jogadores disponíveis para cada posição no plantel copiado.
 * @param destino Ponteiro para um array onde os jogadores escolhidos pelo usuário serão armazenados (pode ser o array de titulares ou suplentes da equipe).
 * @param configTatica Array contendo o número de titulares ou suplentes necessários para cada posição, de acordo com a tática escolhida.
 * @param qtd O número total de jogadores a serem escolhidos (11 para titulares, 6 para suplentes).
 */
void escolherListaManual(Jogador** copiaPlantel, int* disponiveis, Jogador* destino, int* configTatica, int qtd) {
    int idxGeral = 0;
    for (int pos = 0; pos < 4; pos++) {
        int necessarios = configTatica[pos];
        if(necessarios == 0) continue;

        cout << "\n--- Selecao para a Posicao " << pos << " (" << necessarios << " em falta) ---\n";
        for (int n = 0; n < necessarios; n++) {
            for (int i = 0; i < disponiveis[pos]; i++) {
                cout << i << " - " << eliminarAcentos(copiaPlantel[pos][i].nome) << " (Q:" << copiaPlantel[pos][i].qualidade << ")\n";
            }

            int esc;
            cout << "Indice do escolhido: "; cin >> esc;

            if (esc < 0 || esc >= disponiveis[pos]) {
                cout << "[ERRO] Invalidade! Tenta outra vez.\n";
                n--; continue;
            }

            destino[idxGeral++] = copiaPlantel[pos][esc];

            for (int k = esc; k < disponiveis[pos] - 1; k++) {
                copiaPlantel[pos][k] = copiaPlantel[pos][k + 1];
            }
            disponiveis[pos]--;
        }
    }
}


/** * @brief Permite ao usuário escolher manualmente os jogadores titulares e suplentes da equipe com base na tática escolhida, garantindo que haja jogadores suficientes disponíveis para cada posição. A função também atualiza o plantel da equipe de acordo com as escolhas do usuário e libera a memória alocada para a cópia do plantel após a seleção.
 *
 * @param equipa Referência para a equipe cujo plantel será atualizado com as escolhas do usuário.
 * @param taticaAtual A tática atual da equipe, contendo o número de titulares e suplentes para cada posição, que será usada como base para a seleção manual dos jogadores.
 */
void escolherEquipaManual(Equipa& equipa, Tatica& taticaAtual) {
    int disponiveis[4] = {equipa.numJogadores[0], equipa.numJogadores[1], equipa.numJogadores[2], equipa.numJogadores[3]};


    if (!validarPlantelDisponible(equipa, taticaAtual)) {
        cout << "[ERRO] Nao tens jogadores suficientes para essa tatica!\n";
        equipa.escolhaManual = false;
        return;
    }

    Jogador** copia = copiarPlantel(equipa, disponiveis);
    ordenarPlantelQualidadeJogador(copia, disponiveis);


    if (equipa.titulares) delete[] equipa.titulares;
    if (equipa.suplentes) delete[] equipa.suplentes;

    equipa.titulares = new Jogador[MAX_TITULARES];
    equipa.suplentes = new Jogador[MAX_SUPLENTES];

    cout << "\n===== SELECAO DE TITULARES =====";
    escolherListaManual(copia, disponiveis, equipa.titulares, taticaAtual.titulares, 11);

    cout << "\n===== SELECAO DE SUPLENTES =====";
    escolherListaManual(copia, disponiveis, equipa.suplentes, taticaAtual.suplentes, 11);

    equipa.escolhaManual = true;


    for (int i = 0; i < 4; i++) delete[] copia[i];
    delete[] copia;

    cout << "\n[OK] Equipa alterada\n";
}