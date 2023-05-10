/**
 * @file gestor.c
 * @author your name (you@domain.com)
 * @brief Implementa....
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
//header files
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


/**
 * @brief Cria um novo gestor
 * 
 * @param nome 
 * @param password 
 * @return Gestor* 
 */
Gestor* novoGestor(char nome[], char password[])
{
    Gestor* novo = (Gestor*) malloc(sizeof(Gestor)); // Aloca memória para o novo gestor

    if (novo == NULL) { // Verifica alocação
        return NULL;
    }

    // Define o nome e a password do novo gestor
    strcpy(novo->idGestor, nome);
    strcpy(novo->password, password);

    novo->seguinte = NULL; // Define o ponteiro seguinte como NULL

    return novo;
}

//Insere numa lista um gestor criado na função anterior
Gestor* inserirGestor(Gestor* gestores, char nome[], char password[]) {
    Gestor* novo = novoGestor(nome, password); // Cria um novo gestor com os dados fornecidos
    Gestor* atual = gestores; // Define o ponteiro atual para o início da lista

    if (atual == NULL) { // Verifica se a lista está vazia
        gestores = novo; // Se estiver vazia, define o novo gestor como início da lista
    } else {
        while (atual->seguinte != NULL) { // Percorre a lista até o final
            atual = atual->seguinte;
        }
        atual->seguinte = novo; // Define o próximo gestor como o novo gestor inserido
    }
    return gestores; // Devolve o endereço da cabeça da lista
}

//Remove da lista um gestor e liberta memória
Gestor* removerGestor(Gestor* gestores, char* idGestor) {
   
    Gestor* atual = gestores;
    Gestor* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->idGestor, idGestor) == 0) {
            if (anterior == NULL) {
                gestores = atual->seguinte;
            } else {
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            return atual;
        }
        // Se ainda não encontramos o gestor com o ID correspondente, avança para o próximo
        anterior = atual;
        atual = atual->seguinte;
    }

    // Se chegamos ao final da lista e não encontramos o gestor com o ID correspondente, retorna nulo
    return NULL;
}

//Altera password de determinado Gestor
Gestor* alterarPasswordGestor(Gestor* gestores, char idGestor[], char novaPassword[]) {
    Gestor* atual = gestores;

    while (atual != NULL) {
        if (strcmp(atual->idGestor, idGestor) == 0) {
            strcpy(atual->password, novaPassword);
            return gestores;
        }

        atual = atual->seguinte;
    }

    return gestores;
}

