/**
 * @file gestor.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief ficheiro que trata dos gestores
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "gestor.h"


/**
 * @brief Criar um novo gestor
 * 
 * @param username 
 * @param password 
 * @return Gestor* 
 */
Gestor* novoGestor(char username[], char password[])
{
    Gestor* novo = (Gestor*) malloc(sizeof(Gestor));

    if (novo == NULL) { 
        return NULL;
    }

    strcpy(novo->username, username);
    strcpy(novo->password, password);

    novo->anterior = NULL; 
    novo->seguinte = NULL; 

    return novo;
}


/**
 * @brief Insere um gestor no final da lista
 * 
 * @param inicioListaGestores 
 * @param gestor 
 * @return Gestor* 
 */
Gestor* inserirGestor(Gestor* inicioListaGestores, Gestor* gestor) {
    Gestor* atual = inicioListaGestores; 

    if (atual == NULL) { 
        inicioListaGestores = gestor; 
    } else {
        while (atual -> seguinte != NULL) { 
            atual = atual -> seguinte;
        }
        atual -> seguinte = gestor; 
        gestor -> anterior = atual; 
    }
    return inicioListaGestores; 
}



/**
 * @brief Remove da lista um gestor e liberta memória
 * 
 * @param listaGestores 
 * @param userNameGestor 
 * @return Gestor* 
 */
Gestor* removerGestor(Gestor* listaGestores, char* userNameGestor) {
    Gestor* atual = listaGestores;
    Gestor* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->username, userNameGestor) == 0) {
            if (anterior == NULL) {
                listaGestores = atual->seguinte;
            } else {
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            return listaGestores;
        }
        
        anterior = atual;
        atual = atual->seguinte;
    }

    return listaGestores;
}

/**
 * @brief Altera password de determinado Gestor
 * 
 * @param listaGestores 
 * @param userName 
 * @param novaPassword 
 * @return Gestor* 
 */
Gestor* alterarPasswordGestor(Gestor* listaGestores, char userName[], char novaPassword[]) {
    Gestor* atual = listaGestores;

    while (atual != NULL) {
        if (strcmp(atual->username, userName) == 0) {
            strcpy(atual->password, novaPassword);
            return listaGestores;
        }

        atual = atual->seguinte;
    }

    return listaGestores;
}

/**
 * @brief Lê um arquivo de texto com os dados dos gestores e insere na lista
 * 
 * @param fileName 
 * @return Gestor* 
 */
Gestor* importarGestores(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }

    Gestor* listaGestores = NULL;
    char nome[50];
    char password[50];
    while (fscanf(file, "%s %s", nome, password) == 2) {
        Gestor* novo = novoGestor(nome, password);
        listaGestores = inserirGestor(listaGestores, novo);
    }

    fclose(file);
    return listaGestores;
}

/**
 * @brief Escreve os dados dos gestores em um arquivo binário
 * 
 * @param fileName 
 * @param listaGestores 
 * @return Gestor* 
 */
Gestor* guardarGestores(const char* fileName, Gestor* listaGestores) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        return listaGestores;
    }

    Gestor * gestores = listaGestores;

    while (gestores != NULL) {
        fwrite(gestores, sizeof(Gestor), 1, file);
        gestores = gestores->seguinte;
    }

    fclose(file);
    return listaGestores;
}


/**
 * @brief Lê os dados dos gestores de um arquivo binário e insere na lista
 * 
 * @param fileName 
 * @return Gestor* 
 */
Gestor* carregarGestores(const char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        return NULL;
    }

    Gestor* listaGestores = NULL;
    Gestor gestor;
    while (fread(&gestor, sizeof(Gestor), 1, file) == 1) {
        Gestor* novo = novoGestor(gestor.username, gestor.password);
        listaGestores = inserirGestor(listaGestores, novo);
    }

    fclose(file);
    return listaGestores;
}


/**
 * @brief Imprime no terminal a lista de gestores
 * 
 * @param listaGestores 
 */
void imprimirGestores(Gestor* listaGestores) {
    Gestor* gestor = listaGestores;
    while (gestor != NULL) {
        printf("Username: %s\n", gestor->username);
        printf("Senha: %s\n\n", gestor->password);
        gestor = gestor->seguinte;
    }
}

