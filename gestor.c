
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
//header files
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


// Inicializa o id do gestor
int idGestor = 0;

// Cria um novo gestor com o nome e a password fornecidos
Gestor* novoGestor(char userNameGestor[], char password[])
{
    Gestor* novo = (Gestor*) malloc(sizeof(Gestor)); // Aloca memória para o novo gestor

    if (novo == NULL) { // Verifica alocação
        return NULL;
    }


    // Define o nome de usuário e a password do novo gestor
    strcpy(novo->userNameGestor, userNameGestor);
    strcpy(novo->password, password);

    novo->anterior = NULL; // Define o ponteiro anterior como NULL
    novo->seguinte = NULL; // Define o ponteiro seguinte como NULL

    return novo;
}

// Insere um gestor na lista
Gestor* inserirGestor(Gestor* gestores, Gestor* gestor) {
    Gestor* atual = gestores; // Define o ponteiro atual para o início da lista

    if (atual == NULL) { // Verifica se a lista está vazia
        gestores = gestor; // Se estiver vazia, define o novo gestor como início da lista
    } else {
        while (atual->seguinte != NULL) { // Percorre a lista até o final
            atual = atual->seguinte;
        }
        atual->seguinte = gestor; // Define o próximo gestor como o novo gestor inserido
        gestor->anterior = atual; // Define o gestor atual como o gestor anterior do novo gestor
    }
    return gestores; // Devolve o endereço da cabeça da lista
}

// Remove da lista um gestor e liberta memória
Gestor* removerGestor(Gestor* gestores, char* userNameGestor) {
    Gestor* atual = gestores;
    Gestor* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->userNameGestor, userNameGestor) == 0) {
            if (anterior == NULL) {
                gestores = atual->seguinte;
            } else {
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            return gestores;
        }
        // Se ainda não encontramos o gestor com o nome de usuário correspondente, avança para o próximo
        anterior = atual;
        atual = atual->seguinte;
    }

    // Se chegamos ao final da lista e não encontramos o gestor com o nome de usuário correspondente, retorna a lista sem alterações
    return gestores;
}

//Altera password de determinado Gestor
Gestor* alterarPasswordGestor(Gestor* gestores, char userName[], char novaPassword[]) {
    Gestor* atual = gestores;

    while (atual != NULL) {
        if (strcmp(atual->userNameGestor, userName) == 0) {
            strcpy(atual->password, novaPassword);
            return gestores;
        }

        atual = atual->seguinte;
    }

    return gestores;
}

// Lê um arquivo de texto com os dados dos gestores e insere na lista
bool importarGestores(Gestor** gestores, const char* fileName) {
    FILE* arquivo = fopen(fileName, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    char nome[50];
    char password[50];
    while (fscanf(arquivo, "%s %s", nome, password) == 2) {
        Gestor* novoGestor = criarGestor(nome, password);
        *gestores = inserirGestor(*gestores, novoGestor);
    }

    fclose(fileName);
    return true;
}

// Escreve os dados dos gestores em um arquivo binário
bool guardarGestoresBinario(Gestor* gestores, const char* fileName) {
    FILE* arquivo = fopen(fileName, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    while (gestores != NULL) {
        fwrite(gestores, sizeof(Gestor), 1, arquivo);
        gestores = gestores->seguinte;
    }

    fclose(arquivo);
    return true;
}

// Lê os dados dos gestores de um arquivo binário e insere na lista
bool importarGestoresBinario(Gestor** gestores, const char* fileName) {
    FILE* arquivo = fopen(fileName, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }

    Gestor gestor;
    while (fread(&gestor, sizeof(Gestor), 1, arquivo) == 1) {
        *gestores = inserirGestor(*gestores, &gestor);
    }

    fclose(arquivo);
    return true;
}



