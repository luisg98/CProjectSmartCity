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
#include "../Clientes/cliente.h"


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
Aluguer* criarAluguer(int nifCliente, char geocodigoRecolha[TAMANHO]) {
    
    Data dataAtual = getDate();
    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    novoAluguer->idCliente = nifCliente;
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
 * @param listaClientes 
 * @param inserido 
 * @return Fila 
 */
Fila* inserirAluguer(Fila* filaAlugueres, Aluguer* aluguer, Meio* listaMeios, Cliente* listaClientes, bool* inserido) {
    Cliente* cliente = listaClientes;
    while (cliente != NULL) {
        if (cliente->nif == aluguer->idCliente) {
            Meio* meio = listaMeios;
            while (meio != NULL) {
                if (strcmp(meio->geocodigo, aluguer->geocodigoRecolha) == 0 && !(meio->alugado) && meio->autonomia >= 50) {
                    aluguer->idMeio = meio->codigo;
                    meio->alugado = true;

                    if (filaAlugueres->inicio == NULL) {
                        filaAlugueres->inicio = aluguer;
                        filaAlugueres->fim = aluguer;
                    } else {
                        filaAlugueres->fim->proximo = aluguer;
                        aluguer->anterior = filaAlugueres->fim;
                        filaAlugueres->fim = aluguer;
                    }

                    *inserido = true;
                    return filaAlugueres;
                }
                meio = meio->proximo;
            }
        }
        cliente = cliente->proximo;
    }

    *inserido = false;
    return filaAlugueres;
}




Fila* importarAlugueres(const char* filename, Meio* listaMeios, Cliente* listaClientes) {
    Fila* filaAlugueres = (Fila*)malloc(sizeof(Fila));
    filaAlugueres->inicio = NULL;
    filaAlugueres->fim = NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return filaAlugueres;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        int idCliente;
        char geocodigoRecolha[TAMANHO];
        sscanf(linha, "%d %s", &idCliente, geocodigoRecolha);

        Cliente* cliente = listaClientes;
        while (cliente != NULL) {
            if (cliente->nif == idCliente) {
                Aluguer* aluguer = criarAluguer(cliente->nif, geocodigoRecolha);
                bool inserido;
                filaAlugueres = inserirAluguer(filaAlugueres, aluguer, listaMeios, listaClientes, &inserido);
                break;
            }
            cliente = cliente->proximo;
        }
    }

    fclose(file);
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


Fila* carregarAlugueres(const char* filename, Meio* listaMeios, Cliente* listaClientes) {
    Fila* filaAlugueres = (Fila*)malloc(sizeof(Fila));
    filaAlugueres->inicio = NULL;
    filaAlugueres->fim = NULL;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return filaAlugueres;
    }

    Aluguer aluguer;
    while (fread(&aluguer, sizeof(Aluguer), 1, file) == 1) {
        // Encontra o meio correspondente pelo código
        Meio* meio = listaMeios;
        while (meio != NULL) {
            if (meio->codigo == aluguer.idMeio) {
                break;
            }
            meio = meio->proximo;
        }

        // Encontra o cliente correspondente pelo NIF
        Cliente* cliente = listaClientes;
        while (cliente != NULL) {
            if (cliente->nif == aluguer.idCliente) {
                break;
            }
            cliente = cliente->proximo;
        }

        Aluguer* novoAluguer = criarAluguer(aluguer.idCliente, aluguer.geocodigoRecolha);
        bool inserido;
        filaAlugueres = inserirAluguer(filaAlugueres, novoAluguer, meio, cliente, &inserido);
    }

    fclose(file);
    return filaAlugueres;
}



bool guardarAlugueres(const char* filename, Fila* filaAlugueres) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return false;
    }

    Aluguer* aluguer = filaAlugueres->inicio;
    while (aluguer != NULL) {
        fwrite(aluguer, sizeof(Aluguer), 1, file);
        aluguer = aluguer->proximo;
    }

    fclose(file);
    return true;
}
