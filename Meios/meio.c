/**
 * @file meio.c
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
#include "meio.h"

/** 
 * @brief 
 * 
 * @param codigo 
 * @param tipo 
 * @param autonomia 
 * @param geocodigo 
 * @return Meio* 
 */
Meio* criarMeio(int codigo, const char tipo[], int autonomia, const char geocodigo[]) {
    Meio* meio = (Meio*)malloc(sizeof(Meio));
    if (meio == NULL) {
        return NULL;
    }
    meio->codigo = codigo;
    strncpy(meio->tipo, tipo, TAMANHO);
    meio->autonomia = autonomia;
    strncpy(meio->geocodigo, geocodigo, TAMANHO);
    meio->disponibilidade = (autonomia > 50) ? true : false;
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
    char tipo[TAMANHO];
    int autonomia;
    char geocodigo[TAMANHO];
    
    while (fscanf(file, "%d,%[^,],%d,%[^,\n]", &codigo, tipo, &autonomia, geocodigo) == 4) {
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


void libertarLista(Meio* lista) {
    Meio* atual = lista;
    while (atual != NULL) {
        Meio* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}


void imprimirMeios(Meio* lista) {
    Meio* atual = lista;
    while (atual != NULL) {
        printf("Código: %d\n", atual->codigo);
        printf("Tipo: %s\n", atual->tipo);
        printf("Autonomia: %d\n", atual->autonomia);
        printf("Geocódigo: %s\n", atual->geocodigo);
        printf("Disponibilidade: %s\n\n", atual->disponibilidade ? "Disponivel" : "Indisponivel");
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
        fwrite(atual->tipo, sizeof(char), TAMANHO, file);
        fwrite(&(atual->autonomia), sizeof(int), 1, file);
        fwrite(atual->geocodigo, sizeof(char), TAMANHO, file);
        
        atual = atual->proximo;
    }
    
    fclose(file);
    return true;
}

Meio* carregarMeios(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }
    
    Meio* lista = NULL;
    int codigo;
    char tipo[TAMANHO];
    int autonomia;
    char geocodigo[TAMANHO];
    
    while (fread(&codigo, sizeof(int), 1, file) == 1) {
        fread(tipo, sizeof(char), TAMANHO, file);
        fread(&autonomia, sizeof(int), 1, file);
        fread(geocodigo, sizeof(char), TAMANHO, file);
        
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
