/**
 * @file solucao.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho do ficheiro .c correspondente
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SOLUCAO_H
#define SOLUCAO_H
#define SIZE 50
#define MAX_VERTICES 100

typedef struct {
    PontoRecolha* pontos[MAX_VERTICES];
    int numPontos;
} Rota;


void imprimirRota(Rota* rota);
Rota* encontrarMelhorRota(Meio* meios, PontoRecolha* pontoInicial, Grafo * grafo);

#endif
