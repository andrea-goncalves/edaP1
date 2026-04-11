
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
//J_D
// Devolve quantos jogadores há numa posição específica
int contarJogadoresPosicao(Equipa& equipa, int pos) {
    return equipa.numJogadores[pos];
}

// Verifica se já atingimos o n máximo de jogadores para aquela posição
bool limitePosicaoAtingido(Equipa& equipa, int pos) {
    // Array estático para não estar sempre a criar limites novos
    static const int limites[4] = {GR_MAX, DEF_MAX, MED_MAX, AVA_MAX};

    if(equipa.numJogadores[pos] >= limites[pos]) {
        cout << "[AVISO] Limite da posicao atingido!\n";
        return true;
    }
    return false;
}

// Procura emtodo o plantel se alguém já usa aquele número de camisola
// foi feito desta forma caso num futuro não haja nº de camisolas definidas por posição
bool numeroOcupado(Equipa& equipa, int numero) {
    for(int p = 0; p < 4; p++) {
        for(int i = 0; i < equipa.numJogadores[p]; i++) {
            if(equipa.plantel[p][i].numero == numero) return true;
        }
    }
    return false;
}

// Mostra ao utilizador que números ele pode escolher para a posição escolhida
void listarNumerosLivres(Equipa& equipa, int posicao) {
    const int* numeros;
    int tamanho;

    // Define o numero de números permitidos por posição
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

// Loop para garantir que o utilizador escolhe um número que não esteja a ser usado
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

// Função auxiliar para selecionar um jogador de dentro do plantel
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

// Muda um jogador de posição, atualiza o número da camisola e limpa memória
void mudarPosicao(Equipa& equipa, int posAtual, int idxJogador, int novaPosicao) {
    if (limitePosicaoAtingido(equipa, novaPosicao)) {
        cout << "[ERRO] Nao ha espaco na nova posicao!\n";
        return;
    }

    // Guardamos os dados do jogador antes de mexer no array original
    Jogador j = equipa.plantel[posAtual][idxJogador];

    // Atualiza dados básicos
    int novoNumero = escolherNumero(equipa, novaPosicao);
    j.numero = novoNumero;
    const char* nomesPos[] = {"GR", "DEF", "MED", "AVA"};
    j.posicao = nomesPos[novaPosicao];

    // 1. Remover da posição antiga
    for(int i = idxJogador; i < equipa.numJogadores[posAtual] - 1; i++) {
        equipa.plantel[posAtual][i] = equipa.plantel[posAtual][i+1];
    }
    equipa.numJogadores[posAtual]--;

    // 2. Adicionar à nova posição
    int n = equipa.numJogadores[novaPosicao];
    Jogador* novoArray = new Jogador[n + 1];
    for(int i = 0; i < n; i++) novoArray[i] = equipa.plantel[novaPosicao][i];

    novoArray[n] = j;

    delete[] equipa.plantel[novaPosicao]; // Liberta memória antiga para não haver leaks
    equipa.plantel[novaPosicao] = novoArray;
    equipa.numJogadores[novaPosicao]++;

    ordenarPlantelNumeroJogador(equipa);
    cout << "\n[INFO] " << j.nome << " agora e " << j.posicao << "!\n";
}

// Simula um dia de treino: quem tem dias pendentes melhora a qualidade
void treinar(Equipa& equipa) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            Jogador& jog = equipa.plantel[i][j]; // Uso de referência para o código ficar mais legivel
            if (jog.diasTreino > 0) {
                jog.diasTreino--;
                jog.qualidade = (jog.qualidade + 5>100)?100:jog.qualidade + 5; // Garante que não passa de 100
            }
        }
    }
    cout << "[INFO] Treino concluido. Os jogadores evoluiram!\n";
}

// Função genérica para o utilizador escolher jogadores (serve para Titulares e Suplentes)
void escolherListaManual(Jogador** copiaPlantel, int* disponiveis, Jogador* destino, int* configTatica, int qtd) {
    int idxGeral = 0;
    for (int pos = 0; pos < 4; pos++) {
        int necessarios = configTatica[pos];
        if(necessarios == 0) continue;

        cout << "\n--- Selecao para a Posicao " << pos << " (" << necessarios << " em falta) ---\n";
        for (int n = 0; n < necessarios; n++) {
            for (int i = 0; i < disponiveis[pos]; i++) {
                cout << i << " - " << copiaPlantel[pos][i].nome << " (Q:" << copiaPlantel[pos][i].qualidade << ")\n";
            }

            int esc;
            cout << "Indice do escolhido: "; cin >> esc;

            if (esc < 0 || esc >= disponiveis[pos]) {
                cout << "[ERRO] Invalidade! Tenta outra vez.\n";
                n--; continue;
            }

            destino[idxGeral++] = copiaPlantel[pos][esc];
            // Remove da cópia para não escolherem o mesmo jog duas vezes
            for (int k = esc; k < disponiveis[pos] - 1; k++) {
                copiaPlantel[pos][k] = copiaPlantel[pos][k + 1];
            }
            disponiveis[pos]--;
        }
    }
}

// A função principal de escolha manual que gere a memória da cópia do plantel
void escolherEquipaManual(Equipa& equipa, Tatica& taticaAtual) {
    int disponiveis[4] = {equipa.numJogadores[0], equipa.numJogadores[1], equipa.numJogadores[2], equipa.numJogadores[3]};

    // Valida se há gente suficiente antes de começar a alocar coisas
    if (!validarPlantelDisponible(equipa, taticaAtual)) {
        cout << "[ERRO] Nao tens jogadores suficientes para essa tatica!\n";
        equipa.escolhaManual = false;
        return;
    }

    Jogador** copia = copiarPlantel(equipa, disponiveis);
    ordenarPlantelQualidadeJogador(copia, disponiveis);

    // Limpa escolhas anteriores para não vazar memória
    if (equipa.titulares) delete[] equipa.titulares;
    if (equipa.suplentes) delete[] equipa.suplentes;

    equipa.titulares = new Jogador[MAX_TITULARES];
    equipa.suplentes = new Jogador[MAX_SUPLENTES];

    cout << "\n===== SELECAO DE TITULARES =====";
    escolherListaManual(copia, disponiveis, equipa.titulares, taticaAtual.titulares, 11);

    cout << "\n===== SELECAO DE SUPLENTES =====";
    escolherListaManual(copia, disponiveis, equipa.suplentes, taticaAtual.suplentes, 11);

    equipa.escolhaManual = true;

    // Limpeza da memória temporária
    for (int i = 0; i < 4; i++) delete[] copia[i];
    delete[] copia;

    cout << "\n[OK] Equipa técnica, o plantel esta fechado!\n";
}