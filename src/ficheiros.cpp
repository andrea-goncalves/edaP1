
#include <iostream>
#include <string>
#include <fstream>
#include "../include/ficheiros.h"
using namespace std;

/** * @brief Conta o número de linhas em um arquivo.
 *
 * @param path O caminho para o arquivo.
 * @return O número de linhas no arquivo, ou -1 se o arquivo não puder ser aberto.
 */
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

/** * @brief Lê um arquivo e armazena cada linha em um array de strings.
 *
 * @param path O caminho para o arquivo.
 * @param tamanho Referência para armazenar o número de linhas lidas.
 * @return Um ponteiro para um array de strings contendo as linhas do arquivo, ou nullptr se o arquivo não puder ser aberto ou estiver vazio.
 */
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

/** * @brief Remove acentos de uma string.
 *
 * @param str A string de entrada que pode conter acentos.
 * @return Uma nova string com os acentos removidos.
 */
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
/** * @brief Limpa a memória alocada para a equipa, incluindo o plantel, jogadores lesionados e suspensos.
 *
 * @param equipa Referência para a equipa cuja memória deve ser limpa.
 */
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

/** * @brief Grava o estado da equipa e do campeonato em um arquivo.
 *
 * @param equipa A equipa a ser gravada.
 * @param jornada O número da jornada atual.
 * @param nomeFicheiro O nome do arquivo onde os dados serão gravados.
 * @param listaTransferencia A lista de jogadores disponíveis para transferência.
 * @param totalTransferencias O número total de transferências realizadas.
 */
void gravarEquipa(const Equipa& equipa, const int jornada, const string& nomeFicheiro, Jogador* listaTransferencia, int totalTransferencias) {
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
        if (equipa.lesionados[i] != nullptr) {
            Jogador& jg = *(equipa.lesionados[i]);
            out << jg.numero << "\n";
            out << jg.nome << "\n";
            out << jg.posicao << "\n";
            out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " " << jg.probSus << " " << jg.diasTreino << " " << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
        }
    }
     out << equipa.numSuspensos << "\n";
    for (int i = 0; i < equipa.numSuspensos; i++) {
        if (equipa.suspensos[i] != nullptr) {
            Jogador& jg = *(equipa.suspensos[i]);
            out << jg.numero << "\n";
            out << jg.nome << "\n";
            out << jg.posicao << "\n";
            out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " " << jg.probSus << " " << jg.diasTreino << " " << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
        }
    }
    out << totalTransferencias << "\n";
    for (int i = 0; i < totalTransferencias; i++) {
        if (listaTransferencia != nullptr) {
            Jogador& jg = listaTransferencia[i];
            out << jg.numero << "\n";
            out << jg.nome << "\n";
            out << jg.posicao << "\n";
            out << jg.idade << " " << jg.qualidade << " " << jg.probLes << " " << jg.probSus << " " << jg.diasTreino << " " << jg.semanas_ate_retorno_lesao << " " << jg.semanas_ate_retorno_castigo << "\n";
        }
    }
    out.close();
    cout << " Equipa e estado do campeonato gravados com sucesso!\n";
}

/** * @brief Carrega o estado da equipa e do campeonato a partir de um arquivo.
 *
 * @param equipa Referência para a equipa onde os dados serão carregados.
 * @param jornada Referência para o número da jornada atual, que será atualizado com os dados do arquivo.
 * @param nomeFicheiro O nome do arquivo de onde os dados serão carregados.
 * @param listaTransferencia Ponteiro para a lista de jogadores disponíveis para transferência, que será atualizado com os dados do arquivo.
 * @param totalTransferencias Referência para o número total de transferências realizadas, que será atualizado com os dados do arquivo.
 * @return true se o carregamento for bem-sucedido, ou false se houver um erro ao abrir o arquivo.
 */
bool carregarEquipa(Equipa& equipa, int& jornada, const string& nomeFicheiro, Jogador*& listaTransferencia, int& totalTransferencias) {
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
            in.ignore();
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
            in.ignore();
            in >> equipa.numSuspensos;
    for (int i = 0; i < equipa.numSuspensos; i++) {
        Jogador jogadorTemp;
        in >> jogadorTemp.numero;
        in.ignore();
        getline(in, jogadorTemp.nome);
        getline(in, jogadorTemp.posicao);
        in >> jogadorTemp.idade >> jogadorTemp.qualidade >> jogadorTemp.probLes >> jogadorTemp.probSus >> jogadorTemp.diasTreino >> jogadorTemp.semanas_ate_retorno_lesao >> jogadorTemp.semanas_ate_retorno_castigo;

        Jogador* jg = new Jogador(jogadorTemp);
        equipa.suspensos[i] = jg;
    }
    in.ignore();
    in >> totalTransferencias;
    if (totalTransferencias > 0) {
        if (listaTransferencia != nullptr) {
            delete[] listaTransferencia;
        }
        listaTransferencia = new Jogador[totalTransferencias];
        for (int i = 0; i < totalTransferencias; i++) {
            in >> listaTransferencia[i].numero;
            in.ignore();
            getline(in, listaTransferencia[i].nome);
            getline(in, listaTransferencia[i].posicao);
            in >> listaTransferencia[i].idade >> listaTransferencia[i].qualidade >> listaTransferencia[i].probLes >> listaTransferencia[i].probSus >> listaTransferencia[i].diasTreino >> listaTransferencia[i].semanas_ate_retorno_lesao >> listaTransferencia[i].semanas_ate_retorno_castigo;
        }
    } else {
        listaTransferencia = nullptr;
    }
    in.close();
    cout << " Equipa e campeonato carregados! Bem-vindo de volta a jornada " << jornada << "!\n";
    return true;
}