#ifndef PONTOS_H
#define PONTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50

typedef struct PontoRecolha {
    char geocodigo[SIZE];
    bool visitado; 
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
Grafo* importarGrafo(const char* filename);
Grafo* criarGrafo();
void imprimirGrafo(Grafo* grafo);
void imprimirMatrizAdjacencias(Grafo* grafo);
bool guardarGrafo(const char* filename, Grafo* grafo);
Grafo* carregarGrafo(const char* filename);
PontoRecolha* carregarPontosRecolha(const char* filename);
bool guardarPontosRecolha(const char* filename, PontoRecolha* pontosRecolha);
PontoRecolha* converteGeocodigoPontoRecolha(Grafo* grafo, const char* geocodigo);
PontoRecolha* carregarPontosRecolha(const char* filename);



#endif