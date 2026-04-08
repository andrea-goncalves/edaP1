#include <string>
#include <iostream>
#include <iomanip>
#include "../include/simulacao.h"
#include "../include/jogador.h"
#include "../include/ficheiros.h"
#include "../include/equipa.h"
#include "../include/constantes.h"
#include "../include/lesionarSuspender.h"
#include "../include/utils.h"
#include "../include/equipasAdversarias.h"
#include "../include/menu.h"
#include "../include/transferencias.h"


using namespace std;

void inicializarEquipa(Equipa& edaFC) {
    int tamanho = tamArq("../data/nomes.txt");
    string* nomeJogadores = leituraArq("../data/nomes.txt", tamanho);

    int numGR = numeroGR();
    int numDEF = numeroDEF();
    int numMED = numeroMED();
    int numAVA = numeroAVA();

    Jogador* gr  = criarJogadores(nomeJogadores, tamanho, numGR,  "GR",  CAMISAS_GR,  3);
    Jogador* def = criarJogadores(nomeJogadores, tamanho, numDEF, "DEF", CAMISAS_DEF, 10);
    Jogador* med = criarJogadores(nomeJogadores, tamanho, numMED, "MED", CAMISAS_MED, 10);
    Jogador* ava = criarJogadores(nomeJogadores, tamanho, numAVA, "AVA", CAMISAS_AVA, 7);

    edaFC.nome="EDA FC";
    edaFC.numJogadores[0] = numGR;
    edaFC.numJogadores[1] = numDEF;
    edaFC.numJogadores[2] = numMED;
    edaFC.numJogadores[3] = numAVA;

    edaFC.plantel = gerarPlantel(gr, def, med, ava, numGR, numDEF, numMED, numAVA);
    ordenarPlantelNumeroJogador(edaFC);
    delete[] gr; delete[] def; delete[] med; delete[] ava;

    edaFC.titulares = nullptr;
    edaFC.suplentes = nullptr;
    edaFC.pontos = 0;
    edaFC.numLesionados = 0;
    edaFC.numSuspensos = 0;

    for (int i = 0; i < 30; i++) {
        edaFC.lesionados[i] = nullptr;
        edaFC.suspensos[i] = nullptr;
    }

    delete[] nomeJogadores;
}

void inicializarAdversarios(equipasAdversarias*& adversarios,equipasAdversarias*& adversariosFase2,int& numEquipas) {

    numEquipas = tamArq("../data/equipas.txt");
    string* nomes = leituraArq("../data/equipas.txt", numEquipas);

    adversarios = new equipasAdversarias[numEquipas];
    for (int i = 0; i < numEquipas; i++) {
        adversarios[i].nome = nomes[i];
    }

    adversariosFase2 = new equipasAdversarias[34];

    for (int i = 0; i < 17; i++) {
        adversariosFase2[i] = escolher(adversarios, numEquipas);
        adversariosFase2[17 + i] = adversariosFase2[i];
    }

    delete[] nomes;
}



void temporada(Equipa& edaFC, int argc, char* argv[]) {
    int jornada = 1;
    int golosEDAFC = 0;
    int golosAdversario = 0;

    int tamanhoNomes = tamArq("../data/nomes.txt");
    string* nomesMercado = leituraArq("../data/nomes.txt", tamanhoNomes);
    Jogador* listaTransferencia = nullptr;
    int totalTransferencias = 0;

    Tatica taticaAtual;
    Tatica taticaUsada;

    equipasAdversarias* adversarios = nullptr;
    equipasAdversarias* adversariosFase2 = nullptr;
    int numEquipas;

    inicializarAdversarios(adversarios, adversariosFase2, numEquipas);


    if (argc > 1) {
        string ficheiroSave = argv[1];
        cout << "\n[INFO] A tentar carregar save do argumento: " << ficheiroSave << "\n";
        carregarEquipa(edaFC, jornada, ficheiroSave);
    }

    do {
        recuperarLesSus(edaFC, lesao);
        recuperarLesSus(edaFC, suspensao);

        cout << "\n******************************\n";
        cout << "* EDA FC - " << jornada << "a Jornada - " << edaFC.pontos << " pontos. *\n";
        cout << "******************************\n";

        if (jornada > 1) {

            cout << "Resultado Anterior\n";
            cout << "Resultado: EDA FC:" << golosEDAFC << " - " << eliminarAcentos(adversariosFase2[jornada-2].nome) << ":" << golosAdversario << "\n";
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
            imprimirMercado(listaTransferencia, totalTransferencias);
        }
        /////////////////////////////////
        cout<<edaFC.numJogadores[0]<<endl;
        cout<<edaFC.numJogadores[1]<<endl;
        cout<<edaFC.numJogadores[2]<<endl;
        cout<<edaFC.numJogadores[3]<<endl;
        /////////////////////////////////
        imprimirPlantel(edaFC);
        if (jornada > 1) {
            imprimirJogadoresSuspensos2(edaFC.suspensos, edaFC.numSuspensos);
            imprimirJogadoresLesionados2(edaFC.lesionados, edaFC.numLesionados);
            imprimirMercado(listaTransferencia, totalTransferencias);
        }
        string input;

        do {
            cout << "\n[s] Proxima Jornada\n";
            cout << "[o] Opcoes\n";
            cout << "[t] Transferencias (Contratar)\n";
            cout << "[1] Aplicar Lesao Manual\n";
            cout << "[2] Reduzir Lesao Manual\n";
            cout << "[3] Aplicar Castigo Manual\n";
            cout << "[4] Reduzir Castigo Manual\n";
            cout << "[g] Gravar Equipa\n";
            cout << "[c] Carregar Equipa\n";
            cout << ">> ";
            getline(cin, input);

            if (input == "o") {
                taticaAtual = pedirTatica(taticaAtual);
            }
            else if (input == "t") {
                contratarJogador(edaFC, listaTransferencia, totalTransferencias);
                ordenarPlantelNumeroJogador(edaFC);
                imprimirPlantel(edaFC);
                imprimirMercado(listaTransferencia, totalTransferencias);
            }
            else if (input == "1" || input == "2" || input == "3" || input == "4") {
                int numJ, semanas;
                cout << "Numero do jogador: ";
                cin >> numJ;
                cout << "Numero de semanas: ";
                cin >> semanas;
                cin.ignore();

                if (input == "1") aplicarLesaoManual(edaFC, numJ, semanas);
                else if (input == "2") reduzirLesaoManual(edaFC, numJ, semanas);
                else if (input == "3") aplicarCastigoManual(edaFC, numJ, semanas);
                else if (input == "4") reduzirCastigoManual(edaFC, numJ, semanas);
            }else if (input == "g") {
                string ficheiro;
                cout << "Nome do ficheiro para gravar (ex: save.txt): ";
                getline(cin, ficheiro);
                gravarEquipa(edaFC, jornada, ficheiro);
            }else if (input == "c") {
                string ficheiro;
                cout << "Nome do ficheiro a carregar: ";
                getline(cin, ficheiro);
                carregarEquipa(edaFC, jornada, ficheiro);
            }

        } while (input != "s");

        int disponiveis[4] = { edaFC.numJogadores[0], edaFC.numJogadores[1], edaFC.numJogadores[2], edaFC.numJogadores[3] };
        Jogador** copiaPlantel = copiarPlantel(edaFC, disponiveis);
        ordenarPlantelQualidadeJogador(copiaPlantel, disponiveis);

        while (true) {
            int totalDisponiveis = disponiveis[0] + disponiveis[1] + disponiveis[2] + disponiveis[3];

            bool minGR = disponiveis[0] >= 1;
            bool minDef = disponiveis[1] >= 3;
            bool minMed = disponiveis[2] >= 2;
            bool minAva = disponiveis[3] >= 1;

            if (totalDisponiveis >= 17 && minGR && minDef && minMed && minAva) break;

            cout << "\nNao ha jogadores suficientes para a tatica atual:\n";
            cout << "GR:  " << disponiveis[0] << " (minimo necessario: " << 1 << ")\n";
            cout << "DEF: " << disponiveis[1] << " (minimo necessario: " << 3 << ")\n";
            cout << "MED: " << disponiveis[2] << " (minimo necessario: " << 2<< ")\n";
            cout << "AVA: " << disponiveis[3] << " (minimo necessario: " << 1 << ")\n";
            cout << "[t] Comprar jogadores\n";
            cout << "[o] Alterar tatica\n>> ";

            string op;
            getline(cin, op);

            if (op == "t") {
                contratarJogador(edaFC, listaTransferencia, totalTransferencias);
                ordenarPlantelNumeroJogador(edaFC);
            }
            else if (op == "o") {
                taticaAtual = pedirTatica(taticaAtual);
            }
            disponiveis[0] = edaFC.numJogadores[0];
            disponiveis[1] = edaFC.numJogadores[1];
            disponiveis[2] = edaFC.numJogadores[2];
            disponiveis[3] = edaFC.numJogadores[3];
        }



        if (edaFC.titulares != nullptr) {
            delete[] edaFC.titulares;
            edaFC.titulares = nullptr;
        }
        if (edaFC.suplentes != nullptr) {
            delete[] edaFC.suplentes;
            edaFC.suplentes = nullptr;
        }

        taticaUsada = taticaAtual;

        edaFC.titulares = escolherTitulares(copiaPlantel, disponiveis, taticaUsada);
        edaFC.suplentes = escolherSuplentes(copiaPlantel, disponiveis, taticaUsada, edaFC.numSuplentes);
        edaFC.numSubstituicoes = 0;

        Jogador* novosCandidatos = criarAleatorio(nomesMercado, tamanhoNomes, 2);
        listaTransferencia = gerarTransferencia(novosCandidatos, 2, listaTransferencia, totalTransferencias);
        delete[] novosCandidatos;

        int lesionadosAntes = edaFC.numLesionados;
        int suspensosAntes = edaFC.numSuspensos;


        les_sus(edaFC.titulares, 11, lesao);
        les_sus(edaFC.titulares, 11, suspensao);
        ListaLesSus(edaFC.titulares, 11, edaFC, lesao);
        ListaLesSus(edaFC.titulares, 11, edaFC, suspensao);

        int lesionadosJornada = edaFC.numLesionados - lesionadosAntes;
        int suspensosJornada = edaFC.numSuspensos - suspensosAntes;

        substituicoes(edaFC.titulares, edaFC.suplentes, 11, 6, edaFC);


        if (verificarDerrota(lesionadosJornada, suspensosJornada, edaFC.numSubstituicoes)) {
            cout << "\n EDA FC nao tem jogadores suficientes!\n";
            golosEDAFC = 0;
            golosAdversario = numAleatorio(1, 5);
        } else {
            golosEDAFC = numAleatorio(0, 8);
            golosAdversario = numAleatorio(0, 8);
        }

        for (int i = 0; i < 4; i++) delete[] copiaPlantel[i];
        delete[] copiaPlantel;

        if (golosEDAFC>golosAdversario) {
            edaFC.pontos += 3;
        } else if (golosEDAFC == golosAdversario) {
            edaFC.pontos += 1;
        }
        jornada++;

    } while (jornada <= 34);

    delete[] nomesMercado;
    delete[] listaTransferencia;
    delete[] adversarios;
    delete[] adversariosFase2;
}



void libertarMemoria(Equipa& edaFC) {
    for (int i = 0; i < edaFC.numLesionados; i++) delete edaFC.lesionados[i];
    for (int i = 0; i < edaFC.numSuspensos; i++) delete edaFC.suspensos[i];

    if (edaFC.plantel != nullptr) {
        for (int i = 0; i < 4; i++) {
            delete[] edaFC.plantel[i];
        }
        delete[] edaFC.plantel;
    }

    delete[] edaFC.titulares;
    delete[] edaFC.suplentes;

}