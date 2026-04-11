
#include <string>
#include <iomanip>
#include "../include/jogador.h"
#include "../include/utils.h"
#include "../include/constantes.h"

using namespace std;
/** * @brief Gera um nome aleatório para um jogador a partir de um array de nomes disponíveis.
 *
 * Esta função seleciona um nome aleatório do array de nomes fornecido, utilizando a função numAleatorio para gerar um índice aleatório dentro do intervalo do tamanho do array. O nome selecionado é retornado como resultado.
 *
 * @param nomeJogadores Um ponteiro para um array de strings contendo os nomes disponíveis para os jogadores.
 * @param tamanho O número total de nomes disponíveis no array.
 * @return Uma string contendo o nome aleatório selecionado para o jogador.
 */
string nomeAleatorio(string* nomeJogadores, int tamanho) {
    string nomeJogador = nomeJogadores[numAleatorio(0, tamanho - 1)];
    return nomeJogador;
}

/** * @brief Gera um jogador com atributos aleatórios, incluindo nome, idade, qualidade, número da camisa, probabilidade de suspensão e probabilidade de lesão.
 *
 * Esta função cria um novo jogador preenchendo seus atributos com valores aleatórios. O nome do jogador é selecionado aleatoriamente a partir do array de nomes fornecido, enquanto a idade, qualidade, número da camisa, probabilidade de suspensão e probabilidade de lesão são gerados usando a função numAleatorio dentro de intervalos específicos. O jogador gerado é retornado como resultado.
 *
 * @param nomeJogadores Um ponteiro para um array de strings contendo os nomes disponíveis para os jogadores.
 * @param tamanho O número total de nomes disponíveis no array.
 * @param posicao A posição do jogador (GR, DEF, MED, AVA) que será atribuída ao jogador gerado.
 * @param numeroCamisa O número da camisa que será atribuído ao jogador gerado.
 * @return Um objeto Jogador contendo os atributos aleatórios gerados para o jogador.
 */
Jogador gerarUmJogadorPlantel(string* nomeJogadores, int tamanho, string posicao, int numeroCamisa) {
    Jogador novo;

    novo.nome = nomeAleatorio(nomeJogadores,tamanho);
    novo.idade = numAleatorio(MIN_IDADE, MAX_IDADE);
    novo.qualidade = numAleatorio(0, MAX_QUALIDADE);
    novo.numero = numeroCamisa;
    novo.probSus = numAleatorio(CHANCE_DE_LESAO_MAX, CHANCE_DE_SUSPENSAO_MAX);
    novo.probLes = numAleatorio(CHANCE_DE_LESAO_MIN, CHANCE_DE_LESAO_MAX);
    novo.posicao = posicao;
    novo.diasTreino = 0;
    novo.semanas_ate_retorno_castigo = 0;
    novo.semanas_ate_retorno_lesao = 0;

    return novo;
}
/** * @brief Gera um número aleatório para a posição de goleiro (GR) dentro de um intervalo específico.
 *
 * Esta função utiliza a função numAleatorio para gerar um número aleatório entre 2 e 3, representando a quantidade de jogadores na posição de goleiro (GR) que serão gerados para o plantel da equipe.
 *
 * @return Um número inteiro aleatório entre 2 e 3, indicando a quantidade de jogadores na posição de goleiro (GR).
 */
int numeroGR() {
    return numAleatorio(GR_MIN, GR_MAX);
}
/** * @brief Gera um número aleatório para a posição de defensor (DEF) dentro de um intervalo específico.
 *
 * Esta função utiliza a função numAleatorio para gerar um número aleatório entre 7 e 10, representando a quantidade de jogadores na posição de defensor (DEF) que serão gerados para o plantel da equipe.
 *
 * @return Um número inteiro aleatório entre 7 e 10, indicando a quantidade de jogadores na posição de defensor (DEF).
 */
int numeroDEF() {
    return numAleatorio(DEF_MIN, DEF_MAX);
}
/** * @brief Gera um número aleatório para a posição de meio-campista (MED) dentro de um intervalo específico.
 *
 * Esta função utiliza a função numAleatorio para gerar um número aleatório entre 7 e 10, representando a quantidade de jogadores na posição de meio-campista (MED) que serão gerados para o plantel da equipe.
 *
 * @return Um número inteiro aleatório entre 7 e 10, indicando a quantidade de jogadores na posição de meio-campista (MED).
 */
int numeroMED() {
    return numAleatorio(MED_MIN, MED_MAX);
}
/** * @brief Gera um número aleatório para a posição de atacante (AVA) dentro de um intervalo específico.
 *
 * Esta função utiliza a função numAleatorio para gerar um número aleatório entre 4 e 7, representando a quantidade de jogadores na posição de atacante (AVA) que serão gerados para o plantel da equipe.
 *
 * @return Um número inteiro aleatório entre 4 e 7, indicando a quantidade de jogadores na posição de atacante (AVA).
 */
int numeroAVA() {
    return numAleatorio(AVA_MIN, AVA_MAX);
}

/** * @brief Verifica se um número de jogador já está presente em um array de jogadores, comparando o número fornecido com os números dos jogadores no array.
 *
 * Esta função percorre o array de jogadores até o tamanho especificado, comparando o número do jogador fornecido (numComparar) com os números dos jogadores presentes no array. Se encontrar um jogador com o mesmo número, retorna true, indicando que o número já está presente. Caso contrário, retorna false após percorrer todo o array.
 *
 * @param array Um ponteiro para um array de objetos Jogador que será verificado.
 * @param numComparar O número do jogador que será comparado com os números dos jogadores no array.
 * @param tamanho O número total de jogadores presentes no array que será verificado.
 * @return true se o número do jogador estiver presente no array, ou false caso contrário.
 */
bool compararNumJogador(Jogador* array, int numComparar, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (array[i].numero == numComparar) {
            return true;
        }
    }
    return false;
}

/** * @brief Cria um array de jogadores para o plantel da equipe, garantindo que os números dos jogadores sejam únicos e correspondam à posição especificada.
 *
 * Esta função gera um array de jogadores com base nos nomes disponíveis, tamanho do array, número de jogadores a serem criados, posição dos jogadores e uma lista de números de camisa disponíveis. Para cada jogador a ser criado, a função verifica se o número da camisa gerado aleatoriamente já está presente no array de jogadores criado até o momento. Se o número estiver repetido, a função continua gerando um novo número até encontrar um número único. O jogador é então criado com os atributos aleatórios e adicionado ao array de jogadores. O array completo de jogadores é retornado como resultado.
 *
 * @param nomeJogadores Um ponteiro para um array de strings contendo os nomes disponíveis para os jogadores.
 * @param tamanho O número total de nomes disponíveis no array.
 * @param numJogadores O número total de jogadores a serem criados para o plantel da equipe.
 * @param posicao A posição dos jogadores a serem criados (GR, DEF, MED, AVA).
 * @param camisas Um ponteiro para um array de inteiros contendo os números de camisa disponíveis para os jogadores.
 * @param numCamisas O número total de números de camisa disponíveis no array.
 * @return Um ponteiro para um array de objetos Jogador contendo os jogadores criados para o plantel da equipe.
 */
Jogador* criarJogadores(string* nomeJogadores, int tamanho, int numJogadores, const string& posicao, const int* camisas, int numCamisas) {
    Jogador* jogadores = new Jogador[numJogadores];

    for (int i = 0; i < numJogadores; i++) {
        bool numeroRepetido = true;
        int num = 0;

        while (numeroRepetido) {
            int indice = numAleatorio(0, numCamisas - 1);
            num = camisas[indice];
            numeroRepetido = compararNumJogador(jogadores, num, i);
        }

        jogadores[i] = gerarUmJogadorPlantel(nomeJogadores, tamanho, posicao, num);
    }
    return jogadores;
}
/** * @brief Cria um array de jogadores para o plantel da equipe, gerando jogadores com atributos aleatórios e sem garantir a exclusividade dos números de camisa.
 *
 * Esta função gera um array de jogadores com base nos nomes disponíveis, tamanho do array, número de jogadores a serem criados e posição dos jogadores. Para cada jogador a ser criado, a função gera atributos aleatórios, incluindo o número da camisa, sem verificar se os números são exclusivos. O jogador é então criado com os atributos aleatórios e adicionado ao array de jogadores. O array completo de jogadores é retornado como resultado.
 *
 * @param nomeJogadores Um ponteiro para um array de strings contendo os nomes disponíveis para os jogadores.
 * @param tamanho O número total de nomes disponíveis no array.
 * @param numJogadores O número total de jogadores a serem criados para o plantel da equipe.
 * @param posicao A posição dos jogadores a serem criados (GR, DEF, MED, AVA).
 * @return Um ponteiro para um array de objetos Jogador contendo os jogadores criados para o plantel da equipe.
 */
Jogador* criarAleatorio(string* nomeJogadores, int tamanho, int numJogadores) {
    Jogador* aleatorio = new Jogador[numJogadores];
    string posicoes[] = {"GR", "DEF", "MED", "AVA"};

    for (int i = 0; i < numJogadores; i++) {
        string pos = posicoes[numAleatorio(0, 3)];
        aleatorio[i] = gerarUmJogadorPlantel(nomeJogadores, tamanho, pos, 0);
    }
    return aleatorio;
}