//
// Created by andre on 29/03/2026.
//
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
        return -1; //podemos colocar exit, mas isso fecharia o programa
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
        int i=0; //o while neste caso é melhor que o for
        while (getline(arquivo,vArquivos[i]) && i < tamanho) {
            i++;
        }
        arquivo.close();
    } else {
        delete[] vArquivos;
        return nullptr; //é preciso que devolva algo se não dá erro
    }
    return vArquivos;
}

string eliminarAcentos(const string& str) {
    string result = str;
    // pares de reemplazo: acentuado -> sin acento
    string acentos[] = {"á","é","í","ó","ú","à","è","ì","ò","ù",
                        "â","ê","î","ô","û","ã","õ","ñ","ü","ç",
                        "Á","É","Í","Ó","Ú","À","È","Ì","Ò","Ù",
                        "Â","Ê","Î","Ô","Û","Ã","Õ","Ñ","Ü","Ç"};
    string sinAcento[] = {"a","e","i","o","u","a","e","i","o","u",
                          "a","e","i","o","u","a","o","n","u","c",
                          "A","E","I","O","U","A","E","I","O","U",
                          "A","E","I","O","U","A","O","N","U","C"};
    int tam = 40;
    for (int i = 0; i < tam; i++) {
        size_t pos;
        while ((pos = result.find(acentos[i])) != string::npos) {
            result.replace(pos, acentos[i].length(), sinAcento[i]);
        }
    }
    return result;
}