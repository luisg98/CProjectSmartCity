/**
 * @file solucao.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include "Clientes/cliente.h"
#include "Meios/meio.h"
#include "Gestores/gestor.h"
#include "Alugueres/aluguer.h"
#include "Pontos/pontos.h"
#include "solucao.h"


Meio* encontrarProximoMeio(Meio* meios, Grafo* grafo, const char* geocodigoDestino) {
    Meio* meioAtual = meios;
    Meio* proximoMeio = NULL;
    int menorDistancia = INT_MAX;

    while (meioAtual != NULL) {
        if (meioAtual->autonomia < 50) {
            int distancia = obterDistanciaEntreMeioEDestino(grafo, meioAtual->geocodigo, geocodigoDestino);
            if (distancia != -1 && distancia < menorDistancia) {
                menorDistancia = distancia;
                proximoMeio = meioAtual;
            }
        }
        meioAtual = meioAtual->proximo;
    }

    return proximoMeio;
}

int obterDistanciaEntreMeioEDestino(Grafo* grafo, const char* geocodigoMeio, const char* geocodigoDestino) {
    PontoRecolha* pontoMeio = encontrarPontoRecolhaPorGeocodigo(grafo, geocodigoMeio);
    PontoRecolha* pontoDestino = encontrarPontoRecolhaPorGeocodigo(grafo, geocodigoDestino);

    if (pontoMeio == NULL || pontoDestino == NULL) {
        return -1; // Ponto de recolha do meio ou destino não encontrado
    }

    Aresta* aresta = encontrarArestaPorOrigemEDestino(grafo, pontoMeio->geocodigo, pontoDestino->geocodigo);

    if (aresta == NULL) {
        return -1; // Aresta entre ponto de recolha do meio e destino não encontrada
    }

    return aresta->distancia;
}

PontoRecolha* encontrarPontoRecolhaPorGeocodigo(Grafo* grafo, const char* geocodigo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        if (strcmp(pontoAtual->geocodigo, geocodigo) == 0) {
            return pontoAtual;
        }
        pontoAtual = pontoAtual->proximo;
    }
    return NULL; // Ponto de recolha não encontrado
}

Aresta* encontrarArestaPorOrigemEDestino(Grafo* grafo, const char* geocodigoOrigem, const char* geocodigoDestino) {
    PontoRecolha* origem = encontrarPontoRecolhaPorGeocodigo(grafo, geocodigoOrigem);
    PontoRecolha* destino = encontrarPontoRecolhaPorGeocodigo(grafo, geocodigoDestino);
    if (origem == NULL || destino == NULL) {
        return NULL; // Origem ou destino não encontrado
    }

    Aresta* aresta = origem->adjacencia;
    while (aresta != NULL) {
        if (strcmp(aresta->destino->geocodigo, destino->geocodigo) == 0) {
            return aresta;
        }
        aresta = aresta->proximo;
    }
    return NULL; // Aresta não encontrada
}


bool todosVisitados(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        if (!pontoAtual->visitado) {
            return false;
        }
        pontoAtual = pontoAtual->proximo;
    }
    return true;
}

PontoRecolha* encontrarProximoPonto(PontoRecolha* pontoAtual, Grafo* grafo) {
    Aresta* aresta = pontoAtual->adjacencia;
    while (aresta != NULL) {
        if (!aresta->destino->visitado) {
            return aresta->destino;
        }
        aresta = aresta->proximo;
    }
    return NULL;
}

int calcularDistanciaTotal(Aresta** trajeto, int numPontosRecolha) {
    int distanciaTotal = 0;
    for (int i = 0; i < numPontosRecolha - 1; i++) {
        distanciaTotal += trajeto[i]->distancia;
    }
    return distanciaTotal;
}

Aresta** encontrarMelhorTrajeto(Grafo* grafo, Meio* meios, const char* pontoPartida, int* tamanhoTrajeto) {
    PontoRecolha* pontoAtual = NULL;
    PontoRecolha* pontoInicial = NULL;
    Meio* meioAtual = NULL;
    Aresta** melhorTrajeto = NULL;
    int menorDistanciaTotal = INT_MAX;

    pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        if (strcmp(pontoAtual->geocodigo, pontoPartida) == 0) {
            pontoInicial = pontoAtual;
            break;
        }
        pontoAtual = pontoAtual->proximo;
    }

    meioAtual = encontrarProximoMeio(meios, grafo, pontoInicial->geocodigo);
    while (meioAtual != NULL) {
        pontoAtual = grafo->pontosRecolha;
        while (pontoAtual != NULL) {
            pontoAtual->visitado = false;
            pontoAtual = pontoAtual->proximo;
        }

        Aresta** trajeto = (Aresta**)malloc((grafo->numPontosRecolha) * sizeof(Aresta*));
        int posicaoTrajeto = 0;
        pontoAtual = pontoInicial;
        pontoAtual->visitado = true;

        while (!todosVisitados(grafo)) {
            PontoRecolha* proximoPonto = encontrarProximoPonto(pontoAtual, grafo);
            Aresta* aresta = encontrarArestaPorOrigemEDestino(grafo, pontoAtual->geocodigo, proximoPonto->geocodigo);
            trajeto[posicaoTrajeto++] = aresta;
            pontoAtual = proximoPonto;
            pontoAtual->visitado = true;
        }

        int distanciaTotal = calcularDistanciaTotal(trajeto, grafo->numPontosRecolha);
        if (distanciaTotal < menorDistanciaTotal) {
            menorDistanciaTotal = distanciaTotal;
            if (melhorTrajeto != NULL) {
                free(melhorTrajeto);
            }
            melhorTrajeto = trajeto;
            *tamanhoTrajeto = posicaoTrajeto;
        } else {
            free(trajeto);
        }

        meioAtual = encontrarProximoMeio(meioAtual->proximo, grafo, pontoInicial->geocodigo);
    }

    // Encontrar o último ponto de recolha visitado
    PontoRecolha* ultimoPonto = NULL;
    for (int i = 0; i < *tamanhoTrajeto; i++) {
        if (melhorTrajeto[i] != NULL) {
            ultimoPonto = melhorTrajeto[i]->destino;
        } else {
            break;
        }
    }

    // Adicionar última aresta ao trajeto
    Aresta* ultimaAresta = encontrarArestaPorOrigemEDestino(grafo, ultimoPonto->geocodigo, pontoInicial->geocodigo);
    melhorTrajeto[*tamanhoTrajeto] = ultimaAresta;
    (*tamanhoTrajeto)++;

    return melhorTrajeto;
}



void imprimirMelhorTrajeto(Aresta** trajeto, int tamanhoTrajeto, Grafo* grafo) {
    printf("Melhor trajeto:\n");

    for (int i = 0; i < tamanhoTrajeto; i++) {
        PontoRecolha* origem = trajeto[i]->origem;
        PontoRecolha* destino = trajeto[i]->destino;
        printf("Origem: %s, Destino: %s, Distancia: %d\n", origem->geocodigo, destino->geocodigo, trajeto[i]->distancia);
    }
    printf("Distancia total: %d\n", calcularDistanciaTotal(trajeto, tamanhoTrajeto));
}
