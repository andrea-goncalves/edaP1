

#ifndef EDAP1_EQUIPASADVERSARIAS_H
#define EDAP1_EQUIPASADVERSARIAS_H
#include <string>

struct equipasAdversarias {
    std::string nome;
};

equipasAdversarias escolher(equipasAdversarias* array, int& disponiveis);
#endif //EDAP1_EQUIPASADVERSARIAS_H