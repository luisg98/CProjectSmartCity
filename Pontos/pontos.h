#ifndef PONTOS_H
#define PONTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50

// Estrutura de um ponto de recolha
typedef struct PontoRecolha {
    char geocodigo[SIZE];
    bool visitado; // Adicionado campo "visitado" para controlar se o ponto foi visitado ou não
    struct Aresta* adjacencia;   // Ponteiro para a lista de adjacência do ponto de recolha
    struct PontoRecolha* proximo;   // Ponteiro para o próximo ponto de recolha na lista de pontos de recolha
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
void adicionarPontoRecolha(Grafo* grafo, char geocodigo[]);
Aresta* criarAresta(PontoRecolha* inicio, PontoRecolha* fim, int distancia);
void adicionarAresta(Grafo* grafo, PontoRecolha* inicio, PontoRecolha* fim, int distancia);
bool freeGrafo(Grafo* grafo);
Grafo* importarGrafo(const char* filename);
Grafo* criarGrafo();
void imprimirGrafo(Grafo* grafo);
void imprimirMatrizAdjacencias(Grafo* grafo);
bool guardarGrafo(const char* filename, Grafo* grafo);
Grafo* carregarGrafo(const char* filename);


#endif