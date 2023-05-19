#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pontos.h"

// Função para criar um novo ponto de recolha
PontoRecolha* criarPontoRecolha(char geocodigo[]) {
    PontoRecolha* novoPontoRecolha = (PontoRecolha*)malloc(sizeof(PontoRecolha));
    strcpy(novoPontoRecolha->geocodigo, geocodigo);
    novoPontoRecolha->adjacencia = NULL;
    novoPontoRecolha->proximo = NULL;
    return novoPontoRecolha;
}

// Função para adicionar um ponto de recolha ao grafo
void adicionarPontoRecolha(Grafo* grafo, char geocodigo[]) {
    PontoRecolha* novoPontoRecolha = criarPontoRecolha(geocodigo);

    // Verifica se o grafo está vazio
    if (grafo->pontosRecolha == NULL) {
        grafo->pontosRecolha = novoPontoRecolha;
    } else {
        // Percorre a lista de pontos de recolha e adiciona o novo ponto de recolha no final
        PontoRecolha* atual = grafo->pontosRecolha;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoPontoRecolha;
    }

    grafo->numPontosRecolha++;
}

// Função para criar uma nova aresta
Aresta* criarAresta(PontoRecolha* inicio, PontoRecolha* fim, double distancia) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->origem = inicio;
    novaAresta->destino = fim;
    novaAresta->distancia = distancia;
    novaAresta->proximo = NULL;
    return novaAresta;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo* grafo, PontoRecolha* inicio, PontoRecolha* fim, double distancia) {
    Aresta* novaAresta = criarAresta(inicio, fim, distancia);

    // Adiciona a nova aresta ao final da lista de adjacência do ponto de recolha de partida
    Aresta* arestaAtual = inicio->adjacencia;
    if (arestaAtual == NULL) {
        inicio->adjacencia = novaAresta;
    } else {
        while (arestaAtual->proximo != NULL) {
            arestaAtual = arestaAtual->proximo;
        }
        arestaAtual->proximo = novaAresta;
    }
}

// Função para liberar a memória alocada para o grafo
void freeGrafo(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        PontoRecolha* pontoTemp = pontoAtual;
        Aresta* arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            Aresta* arestaTemp = arestaAtual;
            arestaAtual = arestaAtual->proximo;
            free(arestaTemp);
        }
        pontoAtual = pontoAtual->proximo;
        free(pontoTemp);
    }
    free(grafo);
}

/*
int main() {
    // Criação do grafo
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->pontosRecolha = NULL;
    grafo->numPontosRecolha = 0;

    // Adiciona pontos de recolha de exemplo ao grafo
    adicionarPontoRecolha(grafo, "pointA");
    adicionarPontoRecolha(grafo, "pointB");
    adicionarPontoRecolha(grafo, "pointC");

    // Adiciona arestas de exemplo ao grafo
    PontoRecolha* pontoRecolha1 = grafo->pontosRecolha;
    PontoRecolha* pontoRecolha2 = pontoRecolha1->proximo;
    PontoRecolha* pontoRecolha3 = pontoRecolha2->proximo;
    adicionarAresta(grafo, pontoRecolha1, pontoRecolha2, 10.0);
    adicionarAresta(grafo, pontoRecolha1, pontoRecolha3, 15.0);

    */