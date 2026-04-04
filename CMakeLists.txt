cmake_minimum_required(VERSION 4.1)
project(edaP1)

set(CMAKE_CXX_STANDARD 20)

add_executable(edaP1 src/main.cpp
        src/jogador.cpp
        include/jogador.h
        src/equipa.cpp
        include/equipa.h
        src/ficheiros.cpp
        include/ficheiros.h
        src/utils.cpp
        include/utils.h
        src/equipasAdversarias.cpp
        include/equipasAdversarias.h
        src/transferencia.cpp
        include/transferencia.h)
