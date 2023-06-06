/**
 * @file pontos.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho do ficheiro .c correspondente
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef PONTOS_H
#define PONTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50

typedef struct PontoRecolha {
    char geocodigo[SIZE];
    struct Aresta* adjacencia;   // Ponteiro para a lista de adjacência do ponto de recolha
    struct PontoRecolha* proximo;   
} PontoRecolha;

// Estrutura de uma aresta
typedef struct Aresta {
    struct PontoRecolha* origem;    // Ponteiro para o ponto de recolha de partida da aresta
    struct PontoRecolha* destino;   // Ponteiro para o ponto de recolha de destino da aresta
    int distancia;               // Distância entre os pontos de recolha de partida e destino
    struct Aresta* proximo;         // Ponteiro para a próxima aresta na lista de adjacência
} Aresta;

// Estrutura do grafo
typedef struct Grafo {
    struct PontoRecolha* pontosRecolha; // Ponteiro para a lista de pontos de recolha do grafo
    int numPontosRecolha;               // Número total de pontos de recolha no grafo
} Grafo;

PontoRecolha* criarPontoRecolha(char geocodigo[]);
bool adicionarPontoRecolha(Grafo* grafo, char geocodigo[]);
Aresta* criarAresta(PontoRecolha* inicio, PontoRecolha* fim, int distancia);
bool adicionarAresta(Grafo* grafo, PontoRecolha* inicio, PontoRecolha* fim, int distancia);
bool libertarGrafo(Grafo* grafo);
Grafo* criarGrafo();
bool importarPontosRecolha(Grafo* grafo, const char* nomeArquivo);
bool importarArestas(Grafo* grafo, const char* nomeArquivo);
void imprimirGrafo(Grafo* grafo);
void imprimirMatrizAdjacencias(Grafo* grafo);
bool carregarArestas(Grafo* grafo, const char* nomeArquivo);
bool guardarPontosRecolha(Grafo* grafo, const char* nomeArquivo);
PontoRecolha* converteGeocodigoPontoRecolha(Grafo* grafo, const char* geocodigo);
bool carregarPontosRecolha(Grafo* grafo, const char* nomeArquivo);
int calcularDistancia(Grafo* grafo, char geocodigo1[], char geocodigo2[]);
bool guardarArestas(Grafo* grafo, const char* nomeArquivo);
PontoRecolha* encontrarPontoRecolha(Grafo* grafo, const char* geocodigo);


#endif