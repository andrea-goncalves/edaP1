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
#include "../include/validarPlantel.h"

using namespace std;
void menu(int& jornada, Equipa& edaFC, Tatica& taticaAtual, Jogador* listaTransferencia, int totalTransferencias, Tatica& taticaUsada, int golosEDAFC, int golosAdversario, int tamanho, string* nomeJogadores, equipasAdversarias* adversariosFase2);


////-----------------------------------------MAIN----------------------------------------------------------------///
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int tamanho = tamArq("C:/Users/ale/nina/data/nomes.txt");
    string* nomeJogadores = leituraArq("C:/Users/ale/nina/data/nomes.txt", tamanho);

    int numJogosPorFase = 17;
    int numEquipas = tamArq("C:/Users/ale/nina/data/equipas.txt");
    string* adversariosNomes = leituraArq("C:/Users/ale/nina/data/equipas.txt", numEquipas);
    equipasAdversarias* adversarios = new equipasAdversarias[numEquipas];
    for (int i = 0; i < numEquipas; i++) {
        adversarios[i].nome = adversariosNomes[i];
    }
    equipasAdversarias* adversariosFase2 = new equipasAdversarias[numEquipas];

    Jogador* listaTransferencia = nullptr;
    int totalTransferencias = 0;

    int jornada = 1;
    int golosEDAFC = 0;
    int golosAdversario = 0;


    int numGR = numeroGR();
    int numDEF = numeroDEF();
    int numMED = numeroMED();
    int numAVA = numeroAVA();
    int numJogadorPlantel = numGR + numDEF + numMED + numAVA;
    Jogador* gr = criarJogadores(nomeJogadores, tamanho, numGR, "GR", CAMISAS_GR, 3);
    Jogador* def = criarJogadores(nomeJogadores, tamanho, numDEF, "DEF", CAMISAS_DEF, 10);
    Jogador* med = criarJogadores(nomeJogadores, tamanho, numMED, "MED", CAMISAS_MED, 10);
    Jogador* ava = criarJogadores(nomeJogadores, tamanho, numAVA, "AVA", CAMISAS_AVA, 7);

    Equipa edaFC;
    edaFC.nome = "EDA FC";
    edaFC.numJogadores[0] = numGR;
    edaFC.numJogadores[1] = numDEF;
    edaFC.numJogadores[2] = numMED;
    edaFC.numJogadores[3] = numAVA;
    edaFC.plantel = gerarPlantel(gr, def, med, ava, numGR, numDEF, numMED, numAVA);
    edaFC.pontos = 0;
    edaFC.titulares = nullptr;
    edaFC.suplentes = nullptr;
    edaFC.pontos = 0;
    edaFC.numLesionados = 0;
    edaFC.numSuspensos = 0;
    for (int i = 0; i < 30; i++) {
        edaFC.lesionados[i] = nullptr;
        edaFC.suspensos[i] = nullptr;
    }
    Tatica taticaAtual;
    Tatica taticaUsada;



    cout << numJogadorPlantel << endl;
    cout << "Numero de GR: " << numGR << endl;
    cout << edaFC.numJogadores[0] << endl;
    cout << "Numero de DEF: " << numDEF << endl;
    cout << edaFC.numJogadores[1] << endl;
    cout << "Numero de MED: " << numMED << endl;
    cout << edaFC.numJogadores[2] << endl;
    cout << "Numero de AVA: " << numAVA << endl;
    cout << edaFC.numJogadores[3] << endl;


    ordenarPlantelNumeroJogador(edaFC);
    imprimirPlantel(edaFC);

    if (argc > 1) {
        string ficheiroSave = argv[1];
        cout << "\n[INFO] A tentar carregar save do argumento: " << ficheiroSave << "\n";
        carregarEquipa(edaFC, jornada, ficheiroSave, listaTransferencia, totalTransferencias); // <--- adicionei a jornada aqui
    }

    for (int i = 0; i < 17; i++) {
        adversariosFase2[i] = escolher(adversarios, numJogosPorFase);
        adversariosFase2[17 + i] = adversariosFase2[i];
    }

    //////
    menu(jornada, edaFC, taticaAtual, listaTransferencia, totalTransferencias, taticaUsada, golosEDAFC, golosAdversario, tamanho, nomeJogadores, adversariosFase2);
    ///////

    for (int i = 0; i < edaFC.numLesionados; i++) delete edaFC.lesionados[i];
    for (int i = 0; i < edaFC.numSuspensos; i++) delete edaFC.suspensos[i];
    for (int i = 0; i < 4; i++) delete[] edaFC.plantel[i];
    delete[] edaFC.plantel;
    delete[] edaFC.titulares;
    delete[] edaFC.suplentes;
    delete[] gr;
    delete[] def;
    delete[] med;
    delete[] ava;
    delete[] nomeJogadores;
    delete[] adversarios;
    delete[] adversariosFase2;
    delete[] adversariosNomes;
    delete[] listaTransferencia;

    return 0;
}

void menu(int& jornada, Equipa& edaFC, Tatica& taticaAtual, Jogador* listaTransferencia, int totalTransferencias, Tatica& taticaUsada, int golosEDAFC, int golosAdversario, int tamanho, string* nomeJogadores, equipasAdversarias* adversariosFase2) {


    char opcao;
    int numJ, semanas;
    string ficheiro;
    while (jornada <= 34) {
        cout << "\n******************************\n";
        cout << "* EDA FC - " << jornada << "a Jornada - " << edaFC.pontos << " pontos. *\n";
        cout << "******************************\n";
        std::cout << "[s] Proxima Jornada\n";
        std::cout << "[o] Opcoes\n";
        std::cout << "[t] Transferencias (Contratar)\n";
        std::cout << "[1] Aplicar Lesao Manual\n";
        std::cout << "[2] Reduzir Lesao Manual\n";
        std::cout << "[3] Aplicar Castigo Manual\n";
        std::cout << "[4] Reduzir Castigo Manual\n";
        std::cout << "[g] Gravar Equipa\n";
        std::cout << "[c] Carregar Equipa\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
        case 's': {

            // Validar si el plantel disponible cumple con las restricciones
            if (validarPlantelDisponible(edaFC, taticaAtual)) {
                // El plantel es válido, se puede jugar la jornada
                // TODO: Implementar la lógica de juego de la jornada
                int disponiveis[4] = {
                    edaFC.numJogadores[0],
                    edaFC.numJogadores[1],
                    edaFC.numJogadores[2],
                    edaFC.numJogadores[3]
                };
                Jogador** copiaPlantel = copiarPlantel(edaFC, disponiveis);
                ordenarPlantelQualidadeJogador(copiaPlantel, disponiveis);
                if (edaFC.titulares != nullptr) delete[] edaFC.titulares;
                if (edaFC.suplentes != nullptr) delete[] edaFC.suplentes;

                int lesionadosAntes = edaFC.numLesionados;
                int suspensosAntes = edaFC.numSuspensos;
                taticaUsada = taticaAtual;
                int numTitulares = taticaUsada.titulares[0] + taticaUsada.titulares[1] + taticaUsada.titulares[2] + taticaUsada.titulares[3];
                edaFC.titulares = escolherTitulares(copiaPlantel, disponiveis, taticaUsada);
                edaFC.suplentes = escolherSuplentes(copiaPlantel, disponiveis, taticaUsada, edaFC.numSuplentes);
                edaFC.numSubstituicoes = 0;
                /////
                lesionar(edaFC.titulares, numTitulares);
                ListaLesionados(edaFC.titulares, numTitulares, edaFC);
                suspender(edaFC.titulares, numTitulares);
                ListaSuspensos(edaFC.titulares, numTitulares, edaFC);
                substituicoes(edaFC.titulares, edaFC.suplentes, numTitulares, edaFC.numSuplentes, edaFC);
                int lesionadosJornada = edaFC.numLesionados - lesionadosAntes;
                int suspensosJornada = edaFC.numSuspensos - suspensosAntes;

                if (verificarDerrota(lesionadosJornada, suspensosJornada, edaFC.numSubstituicoes)) {
                    cout << "\n EDA FC nao tem jogadores suficientes!\n";
                    golosEDAFC = 0;
                    golosAdversario = 3;
                }
                else {
                    golosEDAFC = numAleatorio(0, 8);
                    golosAdversario = numAleatorio(0, 8);
                }
                if (golosEDAFC > golosAdversario)       edaFC.pontos += 3;
                else if (golosEDAFC == golosAdversario) edaFC.pontos += 1;
                else 									 edaFC.pontos += 0;
                for (int i = 0; i < 4; i++) delete[] copiaPlantel[i];
                delete[] copiaPlantel;
                cout << "Resultado Anterior\n";
                cout << "Resultado: EDA FC:" << golosEDAFC << " - " << eliminarAcentos(adversariosFase2[jornada - 1].nome) << ":" << golosAdversario << "\n";
                imprimirTitulares(edaFC.titulares, taticaUsada);
                imprimirSuplentes(edaFC.suplentes, edaFC.numSuplentes);
                imprimirJogadoresSuspensos1(edaFC.suspensos, edaFC.numSuspensos);
                imprimirJogadoresLesionados(edaFC.lesionados, edaFC.numLesionados);
                if (edaFC.numSubstituicoes > 0) {
                    cout << "\nSubstituicoes:\n";
                    for (int i = 0; i < edaFC.numSubstituicoes; i++) {
                        cout << eliminarAcentos(edaFC.sairam[i]) << " -> "
                            << eliminarAcentos(edaFC.entraram[i]) << "\n";
                    }
                }
                cout << "\n" << endl;
                cout << "\n" << endl;
                ////////
                Jogador* novosCandidatos = criarAleatorio(nomeJogadores, tamanho, 2);
                listaTransferencia = gerarTransferencia(novosCandidatos, 2, listaTransferencia, totalTransferencias);
                delete[] novosCandidatos;
                ////////
                ordenarPlantelNumeroJogador(edaFC);
                imprimirPlantel(edaFC);
                imprimirJogadoresSuspensos2(edaFC.suspensos, edaFC.numSuspensos);
                imprimirJogadoresLesionados(edaFC.lesionados, edaFC.numLesionados);
                imprimirMercado(listaTransferencia, totalTransferencias);

                jornada++;
                //recuperar jogadores lesionados e suspensos
                recuperarLesionados(edaFC);
                recuperarSuspensos(edaFC);
            }
            else {
                // El plantel no es válido
                cout << "\nNão se pode jogar esta jornada. Necessitas de arranjar o plantel.\n";
                menu(jornada, edaFC, taticaAtual, listaTransferencia, totalTransferencias, taticaUsada, golosEDAFC, golosAdversario, tamanho, nomeJogadores, adversariosFase2);
            }


            break;
        } // fin case 's'

        case 'o':
            taticaAtual = pedirTatica(taticaAtual);
            break;

        case 't':
            contratarJogador(edaFC, listaTransferencia, totalTransferencias);
            ordenarPlantelNumeroJogador(edaFC);
            imprimirPlantel(edaFC);
            imprimirMercado(listaTransferencia, totalTransferencias);
            break;

        case '1':

            cout << "Numero do jogador: ";
            cin >> numJ;
            cout << "Numero de semanas: ";
            cin >> semanas;
            cin.ignore();
            aplicarLesaoManual(edaFC, numJ, semanas);
            break;

        case '2':
            cout << "Numero do jogador: ";
            cin >> numJ;
            cout << "Numero de semanas: ";
            cin >> semanas;
            cin.ignore();
            reduzirLesaoManual(edaFC, numJ, semanas);
            break;

        case '3':
            cout << "Numero do jogador: ";
            cin >> numJ;
            cout << "Numero de semanas: ";
            cin >> semanas;
            cin.ignore();
            aplicarCastigoManual(edaFC, numJ, semanas);
            break;

        case '4':
            cout << "Numero do jogador: ";
            cin >> numJ;
            cout << "Numero de semanas: ";
            cin >> semanas;
            cin.ignore();
            reduzirCastigoManual(edaFC, numJ, semanas);
            break;

        case 'g':

            cout << "Nome do ficheiro para gravar (ex: save.txt): ";
            cin.ignore();
            getline(cin, ficheiro);
            gravarEquipa(edaFC, jornada, ficheiro, listaTransferencia, totalTransferencias); // <--- adicionei a jornada aqui
            break;

        case 'c':

            cout << "Nome do ficheiro a carregar: ";
            cin.ignore();
            getline(cin, ficheiro);
            carregarEquipa(edaFC, jornada, ficheiro, listaTransferencia, totalTransferencias); // <--- adicionei a jornada aqui
            break;

        default:
            std::cout << ">> Opcao invalida. Tente novamente.\n";
            break;
        }
    }
}