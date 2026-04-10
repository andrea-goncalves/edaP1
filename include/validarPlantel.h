#ifndef EDAP1_VALIDARPLANTEL_H
#define EDAP1_VALIDARPLANTEL_H
#include "equipa.h"

/*
 * Valida si el plantel disponible cumple con las restricciones necesarias para jugar
 * Retorna: true si se puede jugar, false si no
 * 
 * Restricciones:
 * 1. Mínimo 17 jugadores totales
 * 2. Si hay 17 jugadores, deben coincidir con la táctica seleccionada
 */
bool validarPlantelDisponible(Equipa& equipa, Tatica& taticaAtual);

#endif //EDAP1_VALIDARPLANTEL_H
