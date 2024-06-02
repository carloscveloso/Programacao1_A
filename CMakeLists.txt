cmake_minimum_required(VERSION 3.27)
project(Programacao1_A C)

set(CMAKE_C_STANDARD 11)

add_executable( Programacao1_A
        Agendamentos/agendamentos.h
        Agendamentos/agendamentos.c
        Propriedades/propriedades.c
        Propriedades/propriedades.h
        Utilizador/utilizador.c
        Utilizador/utilizador.h
        main.c)