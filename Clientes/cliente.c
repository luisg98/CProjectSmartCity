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
PtrCliente novoCliente(char nome[], char morada[], unsigned int nif, double saldo)
{
    PtrCliente novoCliente = malloc(sizeof(Cliente)); //alocação da memoria
    strcpy(novoCliente->nome, nome); 
    strcpy(novoCliente->morada, morada);
    novoCliente->nif = nif;
    novoCliente->saldo = saldo;
    novoCliente->next = NULL;
    return novoCliente;
}


/**
 * @brief Insere no início de uma lista ligada simples uma nova estrutura que se encarregará de criar com outra função
 * @param clientes 
 * @param nome 
 * @param morada 
 * @param nif 
 * @param saldo 
 * @return PtrCliente 
 */
PtrCliente insereCliente(PtrCliente clientes, char nome[], char morada[], unsigned int nif, double saldo)
{
    PtrCliente novocliente = novoCliente(nome, morada, nif, saldo); // cria o novo cliente

    if (clientes == NULL) // Se a lista estiver vazia, o novo cliente será o primeiro elemento da lista
    { 
        return novocliente;
    }
    else { // Caso contrário, adiciona o novo cliente ao início da lista
        novocliente->next = clientes;
        return novocliente; // devolve o novo cliente como o primeiro elemento da lista
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
PtrCliente removerCliente(PtrCliente clientes, unsigned int nif, bool *res) {
    
    Cliente *aux = clientes;
    Cliente *anterior = NULL;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            if (anterior == NULL)  // se o cliente a remover for o primeiro elemento da lista
            { 
                clientes = aux-> next; // atualiza o ponteiro do início da lista para o próximo elemento
            } 
            else
            {
                anterior->next = aux-> next; // liga o nó anterior ao próximo nó após o que está a ser removido
            }
            free(aux); 

        }

        anterior = aux;
        aux = aux->next;
    }
    
    *res=true;
    return clientes; 
}


/**
 * @brief Altera a morada de um cliente cujo nif será inserido como parâmetro e devolve a lista atualizada
 * @param clientes 
 * @param nif 
 * @param novaMorada 
 * @return PtrCliente 
 */
PtrCliente alterarMoradaCliente(PtrCliente clientes, unsigned int nif, char novaMorada[]) {
    
    Cliente *aux = clientes;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            
            strcpy(aux->morada, novaMorada);
            //strcpy(aux-> nome, novoNome se quiser alterar nome (usar a mesma lógica para alterar qq variavel da estrutura)

            return clientes;
        }

        aux = aux->next;
    }
    
    return clientes; 
}

//Escreve no terminal a lista dos clientes
PtrCliente imprimirClientes(PtrCliente clientes) {
    Cliente *aux = clientes;
    while (aux != NULL) {
        printf("\n");
        printf("Nome: %s\n", aux->nome);
        printf("Morada: %s\n", aux->morada);
        printf("NIF: %u\n", aux->nif);
        printf("Saldo: %.2f\n", aux->saldo);
        printf("\n");
        aux = aux->next;
    }

    return clientes;
}


//Recebe um determinado nif como parâmetro e um determinado valor e soma o valor ao saldo que o cliente relativo ao nif 
PtrCliente carregarSaldoCliente(PtrCliente clientes, unsigned int nif, double carregamento){

        Cliente *aux = clientes;
    
    while (aux != NULL) {

        if (aux->nif == nif) {
            aux->saldo += carregamento;
            return clientes;
        }

        aux = aux->next;
    }
    
    return clientes;

}

//Importa de um file .txt dados de clientes, será este o input para testes 
PtrCliente importarClientes(char *filename) {
    
    PtrCliente listaClientes = NULL;
    FILE *file = fopen(filename, "r"); //leitura do file
            char nome[SIZE], morada[SIZE];
        unsigned int nif;
        double saldo;

    //Verifica a leitura do file
    if (file == NULL) {
        return NULL;
    }

    char linha[3*SIZE]; // definir um buffer grande para armazenar a linha completa
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^,],%[^,],%u,%lf", nome, morada, &nif, &saldo);
        
        listaClientes = insereCliente(listaClientes, nome, morada, nif, saldo);
    }

    fclose(file);
    return listaClientes;
}

//liberta a memória alocada para a vertente clientes
void libertarClientes(PtrCliente clientes) {
    Cliente *aux;

    while (clientes != NULL) {
        aux = clientes;
        clientes = clientes->next;
        free(aux);
    }
}

//guarda num file binário a lista de clientes
bool guardarClientes(char* filename, PtrCliente clientes) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return false; // não consegur abrir file
    }
    Cliente* aux = clientes;
    while (aux != NULL) {
        if (fwrite(aux, sizeof(Cliente), 1, file) != 1) {
            fclose(file);
            return false; 
        }
        aux = aux->next;
    }
    fclose(file);
    return true;
}

//lê de um file binár
PtrCliente carregarClientes(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL; // não conseguiu abrir file
    }

    PtrCliente clientes = NULL;
    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        clientes = insereCliente(clientes, cliente.nome, cliente.morada, cliente.nif, cliente.saldo);
    }

    fclose(file);
    return clientes;
}



