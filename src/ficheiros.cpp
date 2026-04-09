
#include <iostream>
#include <string>
#include <fstream>
#include "../include/ficheiros.h"
using namespace std;

int tamArq(const string& path) {
    int contador = 0;
    string linha;

    ifstream arquivo(path);

    if (!arquivo.is_open()) {
        cout << "Nao e possivel abrir o ficheiro "<< path<< endl;
        return -1;
    }
    while (getline(arquivo,linha)) {
        contador++;
    }
    arquivo.close();
    return contador;
}


string* leituraArq(const string& path, int& tamanho) {
    tamanho=tamArq(path);
    if (tamanho <= 0) {
        return nullptr;
    }
    string* vArquivos = new string[tamanho];
    ifstream arquivo(path);
    if (arquivo.is_open()) {
        int i=0;
        while (getline(arquivo,vArquivos[i]) && i < tamanho) {
            i++;
        }
        arquivo.close();
    } else {
        delete[] vArquivos;
        return nullptr;
    }
    return vArquivos;
}

string eliminarAcentos(const string& str) {
    string result = str;

    string acentos[] = {"á","é","í","ó","ú","à","è","ì","ò","ù",
                        "â","ê","î","ô","û","ã","õ","ñ","ü","ç",
                        "Á","É","Í","Ó","Ú","À","È","Ì","Ò","Ù",
                        "Â","Ê","Î","Ô","Û","Ã","Õ","Ñ","Ü","Ç","ø","Ø", "ö"};
    string sinAcento[] = {"a","e","i","o","u","a","e","i","o","u",
                          "a","e","i","o","u","a","o","n","u","c",
                          "A","E","I","O","U","A","E","I","O","U",
                          "A","E","I","O","U","A","O","N","U","C","o","O", "o"};
    int tam = 43;
    for (int i = 0; i < tam; i++) {
        size_t pos;
        while ((pos = result.find(acentos[i])) != string::npos) {
            result.replace(pos, acentos[i].length(), sinAcento[i]);
        }
    }
    return result;
}

void limparMemoriaEquipa(Equipa& equipa) {
    if (equipa.plantel != nullptr) {
        for (int i = 0; i < 4; i++)
            delete[] equipa.plantel[i];
        delete[] equipa.plantel;
        equipa.plantel = nullptr;
    }

    for (int i = 0; i < equipa.numLesionados; i++)
        delete equipa.lesionados[i];
    equipa.numLesionados = 0;

    for (int i = 0; i < equipa.numSuspensos; i++)
        delete equipa.suspensos[i];
    equipa.numSuspensos = 0;
    equipa.numSubstituicoes = 0;
}

void gravarEquipa(const Equipa& equipa, const int jornada, const string& nomeFicheiro) {
    ofstream out(nomeFicheiro);
    if (!out.is_open()) {
        cout << "Erro ao abrir o ficheiro para gravar!\n";
        return;
    }
    out << jornada << "\n";
    out << equipa.nome << "\n";
    out << equipa.pontos << "\n";
    out << equipa.tatica.titulares[0] << " " << equipa.tatica.titulares[1] << " " << equipa.tatica.titulares[2] << " " << equipa.tatica.titulares[3] << "\n";
    out << equipa.numJogadores[0] << " " << equipa.numJogadores[1] << " " << equipa.numJogadores[2] << " " << equipa.numJogadores[3] << "\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            Jogador& jg = equipa.plantel[i][j];
            out << jg.numero << "\n";
            out << jg.nome << "\n";
            out << jg.posicao << "\n";
            out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " "
                << jg.probSus << " " << jg.diasTreino << " "
                << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
        }
    }
    out << equipa.numLesionados << "\n";
    for (int i = 0; i < equipa.numLesionados; i++) {
        Jogador& jg = *(equipa.lesionados[i]);
        out << jg.numero << "\n";
        out << jg.nome << "\n";
        out << jg.posicao << "\n";
        out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " " << jg.probSus << " " << jg.diasTreino << " " << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
    }
    out << equipa.numSuspensos << "\n";
    for (int i = 0; i < equipa.numSuspensos; i++) {
        Jogador& jg = *(equipa.suspensos[i]);
        out << jg.numero << "\n";
        out << jg.nome << "\n";
        out << jg.posicao << "\n";
        out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " " << jg.probSus << " " << jg.diasTreino << " " << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
    }
    out.close();
    cout << " Equipa e estado do campeonato gravados com sucesso!\n";
}

bool carregarEquipa(Equipa& equipa, int& jornada, const string& nomeFicheiro) {
    ifstream in(nomeFicheiro);
    if (!in.is_open()) {
        cout << "Nao foi possivel encontrar o ficheiro: " << nomeFicheiro << "\n";
        return false;
    }
    limparMemoriaEquipa(equipa);
    in >> jornada;
    in.ignore();
    getline(in, equipa.nome);
    in >> equipa.pontos;
    in >> equipa.tatica.titulares[0] >> equipa.tatica.titulares[1] >> equipa.tatica.titulares[2] >> equipa.tatica.titulares[3];
    in >> equipa.numJogadores[0] >> equipa.numJogadores[1] >> equipa.numJogadores[2] >> equipa.numJogadores[3];

    equipa.plantel = new Jogador*[4];
    for (int i = 0; i < 4; i++) {
        equipa.plantel[i] = new Jogador[equipa.numJogadores[i]];

        for (int j = 0; j < equipa.numJogadores[i]; j++) {
            in >> equipa.plantel[i][j].numero;
            in.ignore();
            getline(in, equipa.plantel[i][j].nome);
            getline(in, equipa.plantel[i][j].posicao);
            in >> equipa.plantel[i][j].idade >> equipa.plantel[i][j].qualidade >> equipa.plantel[i][j].probLes >> equipa.plantel[i][j].probSus >> equipa.plantel[i][j].diasTreino >> equipa.plantel[i][j].semanas_ate_retorno_lesao >> equipa.plantel[i][j].semanas_ate_retorno_castigo;
        }
    }
    in >> equipa.numLesionados;
    for (int i = 0; i < equipa.numLesionados; i++) {
        Jogador jogadorTemp;
        in >> jogadorTemp.numero;
        in.ignore();
        getline(in, jogadorTemp.nome);
        getline(in, jogadorTemp.posicao);
        in >> jogadorTemp.idade >> jogadorTemp.qualidade >> jogadorTemp.probLes >> jogadorTemp.probSus >> jogadorTemp.diasTreino >> jogadorTemp.semanas_ate_retorno_lesao >> jogadorTemp.semanas_ate_retorno_castigo;
        Jogador* jg = new Jogador(jogadorTemp);
        equipa.lesionados[i] = jg;
    }
    in >> equipa.numSuspensos;
    for (int i = 0; i < equipa.numSuspensos; i++) {
        Jogador jogadorTemp;
        in >> jogadorTemp.numero;
        in.ignore();
        getline(in, jogadorTemp.nome);
        getline(in, jogadorTemp.posicao);
        in >> jogadorTemp.idade >>jogadorTemp.qualidade >> jogadorTemp.probLes >> jogadorTemp.probSus >> jogadorTemp.diasTreino >> jogadorTemp.semanas_ate_retorno_lesao >> jogadorTemp.semanas_ate_retorno_castigo;

        Jogador* jg = new Jogador(jogadorTemp);
        equipa.suspensos[i] = jg;
    }
    in.close();
    cout << " Equipa e campeonato carregados! Bem-vindo de volta a jornada " << jornada << "!\n";
    return true;
}