
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/utils.h"
using namespace std;
/** * @brief Gera um número aleatório dentro de um intervalo especificado.
 *
 * Esta função utiliza a função rand() para gerar um número aleatório entre os valores mínimo (min) e máximo (max) fornecidos como parâmetros. O resultado é calculado usando a fórmula: rand() % (max - min + 1) + min, garantindo que o número gerado esteja dentro do intervalo desejado.
 *
 * @param min O valor mínimo do intervalo para o número aleatório.
 * @param max O valor máximo do intervalo para o número aleatório.
 * @return Um número inteiro aleatório dentro do intervalo especificado.
 */
int numAleatorio(int min, int max) {
    int J = rand() % (max - min + 1) + min;
    return J;
}
