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

aRecolher* procurarMeiosRecolher(Meio* listaMeios) {
    aRecolher* novaLista = NULL;
    aRecolher* fimLista = NULL;

    Meio* meioAtual = listaMeios;

    while (meioAtual != NULL) {
        if (meioAtual->autonomia < 50 && !meioAtual->alugado) {
            aRecolher* atual = novaLista;
            while (atual != NULL) {
                if (strcmp(atual->geocodigo, meioAtual->geocodigo) == 0) {
                    if (strcmp(meioAtual->tipo, "Trotinete") == 0) {
                        atual->trotinetes++;
                    } else if (strcmp(meioAtual->tipo, "Bicicleta") == 0) {
                        atual->bicicletas++;
                    }
                    break;
                }
                atual = atual->proximo;
            }
            if (atual == NULL) {
                if (novaLista == NULL) {
                    novaLista = (aRecolher*)malloc(sizeof(aRecolher));
                    strcpy(novaLista->geocodigo, meioAtual->geocodigo);
                    novaLista->bicicletas = 0;
                    novaLista->trotinetes = 0;
                    novaLista->proximo = NULL;
                    fimLista = novaLista;
                } else {
                    fimLista->proximo = (aRecolher*)malloc(sizeof(aRecolher));
                    fimLista = fimLista->proximo;
                    strcpy(fimLista->geocodigo, meioAtual->geocodigo);
                    fimLista->bicicletas = 0;
                    fimLista->trotinetes = 0;
                    fimLista->proximo = NULL;
                    if (strcmp(meioAtual->tipo, "Trotinete") == 0) {
                        fimLista->trotinetes++;
                    } else if (strcmp(meioAtual->tipo, "Bicicleta") == 0) {
                        fimLista->bicicletas++;
                    }
                }
            }
        }

        meioAtual = meioAtual->proximo;
    }

    return novaLista;
}



void imprimirListaMeios(aRecolher* listaMeios) {
    aRecolher* atual = listaMeios;

    printf("Meios a recolher:\n");
    while (atual != NULL) {
        printf("Geocódigo: %s\n", atual->geocodigo);
        printf("Bicicletas: %d\n", atual->bicicletas);
        printf("Trotinetes: %d\n", atual->trotinetes);
        printf("----------------------\n");


        atual = atual->proximo;
    }
}

/*
int calcularDistancia(Grafo* grafo, char[] geocodigoOrigem, char[] geocodigoDestino){
    
    if(grafo->pontosRecolha->geocodigo == geocodigoOrigem){

    }
}*/