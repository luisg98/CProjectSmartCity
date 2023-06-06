/**
 * @file solucao.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Neste ficheiro vamos tentar implementar a solução do enunciado
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


void adicionarPontoRota(Rota* rota, PontoRecolha* ponto) {
    rota->pontos[rota->numPontos] = ponto;
    rota->numPontos++;
}


PontoRecolha* encontrarPontoMaisProximo(PontoRecolha* pontoAtual, Meio* meios, Grafo * grafo) {
    double menorDistancia = -1.0;
    PontoRecolha* pontoMaisProximo = NULL;

    // Percorre a lista de pontos de recolha e encontra o mais próximo do ponto atual
    while (meios != NULL) {
        if (meios->autonomia < 50 && !meios->alugado) {
            double distancia = calcularDistancia(grafo, pontoAtual->geocodigo, meios->geocodigo);
            if (menorDistancia == -1.0 || distancia < menorDistancia) {
                menorDistancia = distancia;
                pontoMaisProximo = encontrarPontoRecolha(grafo, meios->geocodigo);
            }
        }
        meios = meios->proximo;
    }

    return pontoMaisProximo;
}

Rota* encontrarMelhorRota(Meio* meios, PontoRecolha* pontoInicial, Grafo * grafo) {
    Rota* rota = (Rota*)malloc(sizeof(Rota));
    rota->numPontos = 0;

    PontoRecolha* pontoAtual = pontoInicial;
    adicionarPontoRota(rota, pontoAtual);

    while (meios != NULL) {
        if (meios->autonomia < 50 && !meios->alugado) {
            PontoRecolha* proximoPonto = encontrarPontoMaisProximo(pontoAtual, meios, grafo);
            adicionarPontoRota(rota, proximoPonto);
            pontoAtual = proximoPonto;
            meios->alugado = true;
        }
        meios = meios->proximo;
    }

    // Adiciona o ponto inicial novamente para completar o ciclo da rota
    adicionarPontoRota(rota, pontoInicial);

    return rota;
}

void imprimirRota(Rota* rota) {
    printf("Rota: Início");
    for (int i = 0; i < rota->numPontos; i++) {
        printf(" >>> %s", rota->pontos[i]->geocodigo);
    }
    printf("\n");
}