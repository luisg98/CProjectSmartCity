/**
 * @file aluguer.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <time.h>
#include <math.h>
#include "aluguer.h"
#include "../Meios/meio.h"


Data getDate() {
    Data dataAtual;

    // Obtém o timestamp atual
    time_t timestamp = time(NULL);

    // Converte o timestamp para uma estrutura tm local
    struct tm *local_time = localtime(&timestamp);

    // Preenche os componentes da data atual
    dataAtual.ano = local_time->tm_year + 1900;
    dataAtual.mes = local_time->tm_mon + 1;
    dataAtual.dia = local_time->tm_mday;

    return dataAtual;
}


Aluguer* criarAluguer(int idCliente, char geocodigoRecolha[TAMANHO]) {  // Corrigido para geocodigoRecolha
    Data dataAtual = getDate();

    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    novoAluguer->idCliente = idCliente;
    novoAluguer->idMeio = -1;  // Valor inicial indicando que o meio não foi encontrado
    novoAluguer->data = dataAtual;
    strncpy(novoAluguer->geocodigoRecolha, geocodigoRecolha, TAMANHO);  // Copia o geocodigoRecolha
    novoAluguer->proximo = NULL;
    novoAluguer->anterior = NULL;

    return novoAluguer;
}

void inserirAluguer(Fila* filaAlugueres, Aluguer* aluguer, Meio* listaMeios) {
    // Procura um meio disponível com o geocódigo correspondente
    Meio* meio = listaMeios;
    bool meioEncontrado = false;  // Variável para verificar se um meio foi encontrado

    while (meio != NULL) {
        if (strcmp(meio->geocodigo, aluguer->geocodigoRecolha) == 0 && meio->disponibilidade) {
            aluguer->idMeio = meio->codigo;
            meio->disponibilidade = false;  // Marca o meio como indisponível
            meioEncontrado = true;  // Indica que um meio foi encontrado
            break;
        }
        meio = meio->proximo;
    }

    // Verifica se um meio foi encontrado
    if (meioEncontrado) {
        // Insere o aluguer na fila de alugueres
        if (filaAlugueres->inicio == NULL) {
            filaAlugueres->inicio = aluguer;
            filaAlugueres->fim = aluguer;
        } else {
            aluguer->anterior = filaAlugueres->fim;
            filaAlugueres->fim->proximo = aluguer;
            filaAlugueres->fim = aluguer;
        }
    } else {
        // Libera a memória alocada para o aluguer
        free(aluguer);
    }
}


Fila* importarAlugueres(const char* nomeArquivo, Meio* listaMeios) {
    
    //Cria uma fila vazia
    Fila* filaAlugueres = (Fila*)malloc(sizeof(Fila));
    filaAlugueres->inicio = NULL;
    filaAlugueres->fim = NULL;

    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return filaAlugueres;
    }

    char linha[100]; // Tamanho máximo da linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrai os campos do aluguer a partir da linha
        int idCliente;
        char geocodigoRecolha[TAMANHO];

        sscanf(linha, "%d %s", &idCliente, geocodigoRecolha);

        // Cria um novo aluguer
        Aluguer* aluguer = criarAluguer(idCliente, geocodigoRecolha);

        // Insere o aluguer na fila
        inserirAluguer(filaAlugueres, aluguer, listaMeios);
    }

    fclose(arquivo);
    return filaAlugueres;
}


void imprimirAlugueres(Fila* filaAlugueres) {
    Aluguer* aluguer = filaAlugueres->inicio;

    while (aluguer != NULL) {
        printf("ID Cliente: %d\n", aluguer->idCliente);
        printf("ID Meio: %d\n", aluguer->idMeio);
        printf("Data: %d-%d-%d\n", aluguer->data.dia, aluguer->data.mes, aluguer->data.ano);
        printf("Geocódigo de Recolha: %s\n", aluguer->geocodigoRecolha);

        aluguer = aluguer->proximo;
    }
}
