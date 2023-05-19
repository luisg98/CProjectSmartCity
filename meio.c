#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"

Meio* criarMeio(int codigo, const char tipo[], float autonomia, const char geocodigo[]) {
    Meio* meio = (Meio*)malloc(sizeof(Meio));
    if (meio == NULL) {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }
    meio->codigo = codigo;
    strncpy(meio->tipo, tipo, SIZE);
    meio->autonomia = autonomia;
    strncpy(meio->geocodigo, geocodigo, SIZE);
    meio->proximo = NULL;
    return meio;
}

Meio* inserirMeio(Meio** lista, Meio* novoMeio) {
    if (*lista == NULL) {
        *lista = novoMeio;
    } else {
        Meio* atual = *lista;
        
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        
        atual->proximo = novoMeio;
    }
    
    return *lista;
}


Meio* importarMeios(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    Meio* lista = NULL;
    int codigo;
    char tipo[SIZE];
    float autonomia;
    char geocodigo[SIZE];
    
    while (fscanf(file, "%d,%[^,],%f,%[^,\n]", &codigo, tipo, &autonomia, geocodigo) == 4) {
        Meio* novoMeio = criarMeio(codigo, tipo, autonomia, geocodigo);
        if (novoMeio != NULL) {
            lista = inserirMeio(&lista, novoMeio);
        } else {
            break;
        }
    }
    
    fclose(file);
    return lista;
}


void imprimirLista(Meio* lista) {
    Meio* atual = lista;
    while (atual != NULL) {
        printf("Código: %d\n", atual->codigo);
        printf("Tipo: %s\n", atual->tipo);
        printf("Autonomia: %.2f\n", atual->autonomia);
        printf("Geocódigo: %s\n\n", atual->geocodigo);
        atual = atual->proximo;
    }
}