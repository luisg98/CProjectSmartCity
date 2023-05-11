#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
//header files
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


// Cria um novo gestor com o nome e a password fornecidos
Gestor* novoGestor(char username[], char password[])
{
    Gestor* novo = (Gestor*) malloc(sizeof(Gestor)); // Aloca memória para o novo gestor

    if (novo == NULL) { // Verifica alocação
        return NULL;
    }

    // Define o nome de usuário e a password do novo gestor
    strcpy(novo->username, username);
    strcpy(novo->password, password);

    //lista duplamente ligada
    novo->anterior = NULL; // Define o ponteiro anterior como NULL
    novo->seguinte = NULL; // Define o ponteiro seguinte como NULL

    return novo;
}


// Insere um gestor no final da lista
Gestor* inserirGestor(Gestor* inicioListaGestores, Gestor* gestor) {
    Gestor* atual = inicioListaGestores; // Define o ponteiro atual para o início da lista

    if (atual == NULL) { // Verifica se a lista está vazia
        inicioListaGestores = gestor; // Se estiver vazia, define o novo gestor como início da lista
    } else {
        while (atual -> seguinte != NULL) { // Percorre a lista até o final
            atual = atual -> seguinte;
        }
        atual -> seguinte = gestor; // Define o próximo gestor como o novo gestor inserido
        gestor -> anterior = atual; // Define o gestor atual como o gestor anterior do novo gestor
    }
    return inicioListaGestores; // Devolve o endereço da cabeça da lista
}



//Remove da lista um gestor e liberta memória
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
        // Se ainda não encontramos o gestor com o nome de usuário correspondente, avança para o próximo
        anterior = atual;
        atual = atual->seguinte;
    }

    // Se chegamos ao final da lista e não encontramos o gestor com o nome de usuário correspondente, retorna a lista sem alterações
    return listaGestores;
}

//Altera password de determinado Gestor
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

// Lê um arquivo de texto com os dados dos gestores e insere na lista
Gestor* importarGestores(const char* fileName, Gestor *listaGestores) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }

    char nome[50];
    char password[50];
    while (fscanf(file, "%s %s", nome, password) == 2) {
        Gestor* novo = novoGestor(nome, password);
        listaGestores = inserirGestor(listaGestores, novo);
    }

    fclose(file);
    return listaGestores;
}


// Escreve os dados dos gestores em um arquivo binário
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


// Lê os dados dos gestores de um arquivo binário e insere na lista
Gestor* lerGestores(const char* fileName, Gestor* listaGestores) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        return listaGestores;
    }

    Gestor gestor;
    while (fread(&gestor, sizeof(Gestor), 1, file) == 1) {
        Gestor* novo = novoGestor(gestor.username, gestor.password);
        listaGestores = inserirGestor(listaGestores, novo);
    }

    fclose(file);
    return listaGestores;
}

//imprimeGestores
void imprimirGestores(Gestor* listaGestores) {
    Gestor* gestor = listaGestores;
    while (gestor != NULL) {
        printf("Nome: %s\n", gestor->username);
        printf("Senha: %s\n\n", gestor->password);
        gestor = gestor->seguinte;
    }
}
