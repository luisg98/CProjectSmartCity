/**
 * @file aluguer.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Funções para tudo relacionado com os alugueres.
 * @version 0.1
 * @date 2023-05-21 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <time.h>
#include "aluguer.h"
#include "../Meios/meio.h"

/**
 * @brief Get the Date object
 * @return Data 
 */
Data getDate() {
    
    Data dataAtual;
    time_t timestamp = time(NULL); // Obtém o timestamp atual
    struct tm *local_time = localtime(&timestamp); // Converte o timestamp para uma estrutura tm local
    dataAtual.ano = local_time->tm_year + 1900;
    dataAtual.mes = local_time->tm_mon + 1;
    dataAtual.dia = local_time->tm_mday;
    return dataAtual;
}

/**
 * @brief Cria um novo aluguer
 * 
 * @param idCliente 
 * @param geocodigoRecolha 
 * @return Aluguer* 
 */
Aluguer* criarAluguer(int idCliente, char geocodigoRecolha[TAMANHO]) {
    
    Data dataAtual = getDate();
    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    novoAluguer->idCliente = idCliente;
    novoAluguer->idMeio = -1;  // Valor inicial indicando que o meio não foi encontrado
    novoAluguer->data = dataAtual;
    strncpy(novoAluguer->geocodigoRecolha, geocodigoRecolha, TAMANHO);
    novoAluguer->proximo = NULL;
    novoAluguer->anterior = NULL;
    return novoAluguer;
}

/**
 * @brief Insere um aluguer numa fila de alugueres
 * 
 * @param filaAlugueres 
 * @param aluguer 
 * @param listaMeios 
 */
void inserirAluguer(Fila* filaAlugueres, Aluguer* aluguer, Meio* listaMeios) {
    
    // Procura um meio disponível com o geocódigo correspondente
    Meio* meio = listaMeios;
    bool meioEncontrado = false; 
    while (meio != NULL) {
        if (strcmp(meio->geocodigo, aluguer->geocodigoRecolha) == 0 && meio->disponibilidade) {
            aluguer->idMeio = meio->codigo;
            meio->disponibilidade = false;  
            meioEncontrado = true;
            break;
        }
        meio = meio->proximo;
    }

    if (meioEncontrado) {
        // Insere o aluguer na fila de alugueres se encontrar o meio
        if (filaAlugueres->inicio == NULL) {
            filaAlugueres->inicio = aluguer;
            filaAlugueres->fim = aluguer;
        } else {
            aluguer->anterior = filaAlugueres->fim;
            filaAlugueres->fim->proximo = aluguer;
            filaAlugueres->fim = aluguer;
        }
    } else {
        free(aluguer);
    }
}
Fila* importarAlugueres(const char* nomeArquivo, Meio* listaMeios) {
    Fila* filaAlugueres = (Fila*)malloc(sizeof(Fila));
    filaAlugueres->inicio = NULL;
    filaAlugueres->fim = NULL;

    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return filaAlugueres;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int idCliente;
        char geocodigoRecolha[TAMANHO];

        sscanf(linha, "%d %s", &idCliente, geocodigoRecolha);

        Aluguer* aluguer = criarAluguer(idCliente, geocodigoRecolha);

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


Fila* carregarAlugueres(const char* nomeArquivo, Meio* listaMeios) {
    Fila* filaAlugueres = (Fila*)malloc(sizeof(Fila));
    filaAlugueres->inicio = NULL;
    filaAlugueres->fim = NULL;

    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        return filaAlugueres;
    }

    Aluguer aluguer;
    while (fread(&aluguer, sizeof(Aluguer), 1, arquivo) == 1) {
        Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
        memcpy(novoAluguer, &aluguer, sizeof(Aluguer));

        // Procura o meio correspondente pelo código
        Meio* meio = listaMeios;
        while (meio != NULL) {
            if (meio->codigo == novoAluguer->idMeio) {
                novoAluguer->anterior = filaAlugueres->fim;
                if (filaAlugueres->inicio == NULL) {
                    filaAlugueres->inicio = novoAluguer;
                    filaAlugueres->fim = novoAluguer;
                } else {
                    filaAlugueres->fim->proximo = novoAluguer;
                    filaAlugueres->fim = novoAluguer;
                }
                break;
            }
            meio = meio->proximo;
        }
    }

    fclose(arquivo);
    return filaAlugueres;
}
bool guardarAlugueres(const char* nomeArquivo, Fila* filaAlugueres) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        return false;
    }

    Aluguer* aluguer = filaAlugueres->inicio;
    while (aluguer != NULL) {
        fwrite(aluguer, sizeof(Aluguer), 1, arquivo);
        aluguer = aluguer->proximo;
    }

    fclose(arquivo);
    return true;
}
