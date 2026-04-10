//
// Created by andre on 29/03/2026.
//

#ifndef EDAP1_FICHEIROS_H
#define EDAP1_FICHEIROS_H
#include <string>
#include "../include/equipa.h"

int tamArq(const std::string& path);
std::string* leituraArq(const std::string& path, int& tamanho);
std::string eliminarAcentos(const std::string& str);

void gravarEquipa(const Equipa& equipa, const int jornada, const std::string& nomeFicheiro, Jogador* listaTransferencia, int totalTransferencias);
bool carregarEquipa(Equipa& equipa, int& jornada, const std::string& nomeFicheiro, Jogador*& listaTransferencia, int& totalTransferencias);
#endif //EDAP1_FICHEIROS_H