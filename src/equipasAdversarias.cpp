
#include <string>
#include <utility>
#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/equipasAdversarias.h"
using namespace std;
/** * @brief Escolhe uma equipe adversária aleatoriamente a partir de um array de equipes disponíveis, garantindo que cada equipe seja escolhida apenas uma vez.
 *
 * Esta função verifica se ainda há equipes disponíveis para escolher. Se não houver, retorna uma equipe com o nome "SEM_NOMES_DISPONIVEIS". Caso contrário, gera um índice aleatório para selecionar uma equipe do array, troca a equipe escolhida com a última equipe disponível no array e decrementa o número de equipes disponíveis. A equipe escolhida é então retornada.
 *
 * @param array Um ponteiro para um array de equipes adversárias disponíveis para escolha.
 * @param disponiveis Referência para o número de equipes ainda disponíveis no array, que será atualizado após a escolha.
 * @return A equipe adversária escolhida aleatoriamente, ou uma equipe com o nome "SEM_NOMES_DISPONIVEIS" se não houver mais equipes disponíveis.
 */
equipasAdversarias escolher(equipasAdversarias* array, int& disponiveis) {
    if (disponiveis <= 0) {
        return {"SEM_NOMES_DISPONIVEIS"}; //
    }
    int indice = numAleatorio(0, disponiveis - 1);
    equipasAdversarias escolhido = array[indice];
    std::swap(array[indice], array[disponiveis - 1]);
    disponiveis--;
    return escolhido;
}