/**
 * @file aluguer.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <time.h>
#include <math.h>
#include "aluguer.h"

Data getDate() {
    Data dataAtual;

    // Obtém o timestamp atual
    time_t timestamp = time(NULL);

    // Converte o timestamp para uma estrutura tm local
    struct tm *local_time = localtime(&timestamp);

    // Preenche os componentes da data atual
    dataAtual.ano = local_time->tm_year + 1900;
    dataAtual.mes = local_time->tm_mon + 1;
    dataAtual.dia = local_time->tm_mday;

    return dataAtual;
}

