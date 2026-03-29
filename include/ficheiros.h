//
// Created by andre on 29/03/2026.
//

#ifndef EDAP1_FICHEIROS_H
#define EDAP1_FICHEIROS_H
#include <string>

int tamArq(const std::string& path);
std::string* leituraArq(const std::string& path, int& tamanho);
std::string eliminarAcentos(const std::string& str);

#endif //EDAP1_FICHEIROS_H