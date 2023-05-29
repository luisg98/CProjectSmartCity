/**
 * @file solucao.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SOLUCAO_H
#define SOLUCAO_H
#define CAPACIDADE_CARRINHA 30
#define MAX 99999
#define SIZE 50


typedef struct aRecolher{
    char geocodigo[SIZE];
    int bicicletas;
    int trotinetes;
    struct aRecolher* proximo;
}aRecolher;

aRecolher* procurarMeiosRecolher(Meio* listaMeios);
void imprimirListaMeios(aRecolher* listaMeios);


#endif
