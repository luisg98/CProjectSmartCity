/**
 * @file aluguer.c
 * @author your name (you@domain.com)
 * @brief 
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
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


//Cria e insere numa lista um novo aluguer
bool novoAluguer(Aluguer ** alugueres, Meio * meios, int idCliente, int idMeio, int ano, short mes, short dia) {
    
   if (existeMeio(&meios, idMeio) == 1){

        // Cria um novo aluguer
        Aluguer *novoAluguer = (Aluguer*) malloc(sizeof(Aluguer));
        if (!novoAluguer) {
            return 0; // Não foi possível alocar memória para o novo aluguer
        }
        novoAluguer->idCliente = idCliente;
        novoAluguer->idMeio = idMeio;
        novoAluguer->data.ano = ano;
        novoAluguer->data.mes = mes;
        novoAluguer->data.dia = dia;
        novoAluguer->next = NULL;
          
        // Insere o novo aluguer no fim da lista
        if (*alugueres == NULL) {
            *alugueres = novoAluguer; // A lista está vazia, então o novo aluguer é o primeiro elemento
        } else {
            Aluguer *ultimo = *alugueres;
            while (ultimo->next != NULL) {
            ultimo = ultimo->next; // Percorre a lista até chegar ao último elemento
            }
            ultimo->next = novoAluguer; // Adiciona o novo aluguer no final da lista
        }

        return 1; // Operação bem sucedida
    
    }else return 0;
}

//Escreve no terminal todos os alugueres da lista de alugueres
void listarAlugueres(Aluguer *alugueres) {
    
    Aluguer *atual = alugueres;
    while (atual != NULL) {
        printf("ID do cliente: %d\n", atual->idCliente);
        printf("ID do meio: %d\n", atual->idMeio);
        printf("Data do aluguer: %d/%d/%d\n", atual->data.dia, atual->data.mes, atual->data.ano);
        printf("\n");
        atual = atual->next;
    }
}



