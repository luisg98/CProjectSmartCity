/**
 * @file cliente.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Funções para tudo relacionado com os clientes. Com este código será possível:
    - criar, eliminar e alterar dados sobre os clientes
    - importar dados de um file .txt
    - guardar e ler dados num file binário
    - alocar e libertar memória necessária para o programa
 * @version 0.1
 * @date 2023-05-24
 * @copyright Copyright (c) 2023 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "cliente.h"

/**
 * @brief Função para criar um novo cliente
 * @param nome 
 * @param morada 
 * @param nif 
 * @param saldo 
 * @return PtrCliente 
 */
PtrCliente criarCliente(char nome[], char morada[], unsigned int nif)
{
    PtrCliente novoCliente = malloc(sizeof(Cliente));
    strcpy(novoCliente->nome, nome); 
    strcpy(novoCliente->morada, morada);
    novoCliente->nif = nif;
    novoCliente->saldo = 0;
    novoCliente->proximo = NULL;
    return novoCliente;
}

/**
 * @brief insere um cliente que entra como parametro e devolve a lista de clientes(também entra como parametro)
 * 
 * @param clientes 
 * @param novoCliente 
 * @return PtrCliente 
 */
PtrCliente insereCliente(PtrCliente clientes, Cliente *novoCliente)
{
    if (clientes == NULL) {
        // Se a lista estiver vazia, o novo cliente será o primeiro elemento da lista
        return novoCliente;
    } else {
        // Caso contrário, percorre a lista até o último elemento
        PtrCliente aux = clientes;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        // Conecta o novo cliente ao último elemento da lista
        aux->proximo = novoCliente;
        return clientes;
    }
}


/**
 * @brief Remove um cliente de uma lista e liberta a respetiva memória alocada
 * 
 * @param clientes 
 * @param nif 
 * @param res 
 * @return PtrCliente 
 */
PtrCliente removerCliente(PtrCliente clientes, unsigned int nif, bool* res) {
    Cliente* aux = clientes;
    Cliente* anterior = NULL;

    while (aux != NULL) {
        if (aux->nif == nif) {
            if (anterior == NULL) {
                // O cliente a remover é o primeiro da lista
                clientes = aux->proximo;
            } else {
                anterior->proximo = aux->proximo;
            }
            free(aux);

            *res = true;
            return clientes;
        }

        anterior = aux;
        aux = aux->proximo;
    }

    *res = false;
    return clientes;
}



/**
 * @brief Altera a morada de um cliente cujo nif será inserido como parâmetro e devolve a lista atualizada
 * @param clientes 
 * @param nif 
 * @param novaMorada 
 * @return PtrCliente 
 */
PtrCliente alterarMoradaCliente(PtrCliente clientes, unsigned int nif, char novaMorada[], bool *res) {
    
    Cliente *aux = clientes;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            
            strcpy(aux->morada, novaMorada);
            *res = true;

            return clientes;
        }

        aux = aux->proximo;
    }
    
    return clientes; 
}

/**
 * @brief Importa de um txt os clientes- funciona como o input do programa
 * 
 * @param filename 
 * @return PtrCliente 
 */
PtrCliente importarClientes(char *filename) {
    PtrCliente listaClientes = NULL;
    FILE *file = fopen(filename, "r");
    char nome[SIZE], morada[SIZE];
    unsigned int nif;

    if (file == NULL) {
        return NULL;
    }

    char linha[3*SIZE]; // definir um buffer grande para armazenar a linha completa
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^,],%[^,],%u", nome, morada, &nif);
        
        PtrCliente novoCliente = criarCliente(nome, morada, nif);
        listaClientes = insereCliente(listaClientes, novoCliente);
    }

    fclose(file);
    return listaClientes;
}



/**
 * @brief Imprime no terminal a lista de clientes
 * 
 * @param clientes 
 * @return PtrCliente 
 */
void imprimirClientes(PtrCliente clientes) {
    Cliente *aux = clientes;
    while (aux != NULL) {
        printf("\n");
        printf("Nome: %s\n", aux->nome);
        printf("Morada: %s\n", aux->morada);
        printf("NIF: %u\n", aux->nif);
        printf("Saldo: %.2f\n", aux->saldo);
        printf("\n");
        aux = aux->proximo;
    }
}


/**
 * @brief Soma o valor do parâmetro carregamento ao saldo de um determinado cliente
 * 
 * @param clientes 
 * @param nif 
 * @param carregamento 
 * @return PtrCliente 
 */
PtrCliente carregarSaldoCliente(PtrCliente clientes, unsigned int nif, double carregamento){

        Cliente *aux = clientes;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            aux->saldo += carregamento;
            return clientes;
        }

        aux = aux->proximo;
    }
    
    return clientes;

}


/**
 * @brief Liberta a memória alocada para a vertente clientes
 * 
 * @param clientes 
 */
bool libertarClientes(PtrCliente clientes) {
    
    Cliente *aux;

    while (clientes != NULL) {
        aux = clientes;
        clientes = clientes->proximo;
        free(aux);
        return true;
    }
}

/**
 * @brief guarda a lista de clientes num ficheiro binário
 * 
 * @param filename 
 * @param clientes 
 * @return true 
 * @return false 
 */
bool guardarClientes(char *filename, PtrCliente clientes) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return false;
    }

    // Percorre a lista de clientes e escreve cada cliente no arquivo binário
    Cliente *aux = clientes;
    while (aux != NULL) {
        fwrite(aux, sizeof(Cliente), 1, file);
        aux = aux->proximo;
    }

    fclose(file);
    return true;
}

/**
 * @brief carrega de um ficheiro binário os clientes
 * 
 * @param filename 
 * @return PtrCliente 
 */
PtrCliente carregarClientes(char *filename) {
    PtrCliente listaClientes = NULL;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }

    // Lê cada cliente do arquivo binário e insere na lista de clientes
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        PtrCliente novoCliente = criarCliente(cliente.nome, cliente.morada, cliente.nif);
        novoCliente->saldo = cliente.saldo;
        listaClientes = insereCliente(listaClientes, novoCliente);
    }

    fclose(file);
    return listaClientes;
}

Cliente* getCliente(unsigned int idCliente, Cliente * clientes){
    
    Cliente * aux = clientes;

    while (aux != NULL) {

        if (aux->nif == idCliente) {
            return aux;
        }

        aux = aux->proximo;
    }
    
    return clientes;

    
} 