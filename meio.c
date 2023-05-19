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


void imprimirMeios(Meio* lista) {
    Meio* atual = lista;
    while (atual != NULL) {
        printf("Código: %d\n", atual->codigo);
        printf("Tipo: %s\n", atual->tipo);
        printf("Autonomia: %.2f\n", atual->autonomia);
        printf("Geocódigo: %s\n\n", atual->geocodigo);
        atual = atual->proximo;
    }
}



bool guardarMeios(const char* filename, Meio* lista) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return false;
    }
    
    Meio* atual = lista;
    while (atual != NULL) {
        fwrite(&(atual->codigo), sizeof(int), 1, file);
        fwrite(atual->tipo, sizeof(char), SIZE, file);
        fwrite(&(atual->autonomia), sizeof(float), 1, file);
        fwrite(atual->geocodigo, sizeof(char), SIZE, file);
        
        atual = atual->proximo;
    }

    return true;
    fclose(file);
}

Meio* carregarMeios(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }
    
    Meio* lista = NULL;
    int codigo;
    char tipo[SIZE];
    float autonomia;
    char geocodigo[SIZE];
    
    while (fread(&codigo, sizeof(int), 1, file) == 1) {
        fread(tipo, sizeof(char), SIZE, file);
        fread(&autonomia, sizeof(float), 1, file);
        fread(geocodigo, sizeof(char), SIZE, file);
        
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