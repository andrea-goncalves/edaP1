
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../include/utils.h"
using namespace std;

int numAleatorio(int min, int max) {
    int J = rand() % (max - min + 1) + min;
    return J;
}
