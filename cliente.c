#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cliente.h"

bool novocliente(cliente **clientes, char nome[], char morada[], unsigned int nif, float saldo, struct cliente * next) 
{
    //parametros qual é a diferença de usar char *nome, char *morada

    // Verifica se já existe um cliente com o mesmo NIF na lista
        cliente *aux = *clientes;
        while (aux != NULL) {
            if (aux->nif == nif) {
                //printf("Já existe um cliente com este NIF %d na lista.\n", nif);
                return false;
            }
            aux = aux-> next;
        }
        
    cliente *novocliente = malloc(sizeof(cliente)); //alocação da memoria
    strcpy(novocliente->nome, nome); 
    strcpy(novocliente->morada, morada);
    novocliente->nif = nif;
    novocliente->saldo = saldo;
    novocliente->next = NULL; //inserido no fim da fila não nenhum para além dele

    if (*clientes == NULL) { // Se a lista estiver vazia, o novo cliente será o primeiro elemento da lista
        *clientes = novocliente;
    } else { // Caso contrário, adiciona o novocliente ao final da lista
        cliente *aux = *clientes;
        while (aux-> next != NULL) {
            aux = aux-> next;
        }
        aux-> next = novocliente;
    }   
    
    return true;
}


void imprimirClientes(cliente *clientes) {
    cliente *aux = clientes;
    while (aux != NULL) {
        printf("Nome: %s\n", aux->nome);
        printf("Morada: %s\n", aux->morada);
        printf("NIF: %u\n", aux->nif);
        printf("Saldo: %.2f\n", aux->saldo);
        printf("\n");
        aux = aux->next;
    }
}

bool libertarMemoriaListaclientes(cliente **clientes) {
    cliente *aux = *clientes;
    while (aux != NULL) {
        cliente *prox = aux->next;
        free(aux);
        aux = prox;
    }
    *clientes = NULL; // Atualiza o ponteiro para o início da lista para NULL
    
    return true;
}

bool removerCliente(cliente **clientes, unsigned int nif) {
    
    cliente *aux = *clientes;
    cliente *anterior = NULL;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            if (anterior == NULL)  // se o cliente a remover for o primeiro elemento da lista
            { 
                *clientes = aux-> next; // atualiza o ponteiro do início da lista para o próximo elemento
            } 
            else
            {
                anterior->next = aux-> next; // liga o nó anterior ao próximo nó após o que está a ser removido
            }
            free(aux); // libera a memória alocada para o cliente a remover
            return true;
        }

        anterior = aux;
        aux = aux->next;
    }
    
    return false; // se chegar ao fim da lista sem encontrar o cliente com o NIF indicado retorna falso
}

