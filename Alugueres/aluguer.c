/**
 * @file aluguer.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro para tudo relacionado com os alugueres.
 * @version 1.0
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
#include "../Pontos/pontos.h"

/**
 * @brief Get the Date object
 * @return dataRecolha 
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
Aluguer* criarAluguer(int nifCliente, const char geocodigoRecolha[], const char tipo[]) {
    
    Data dataAtual = getDate();
    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    novoAluguer->idCliente = nifCliente;
    novoAluguer->idMeio = -1;  // Valor inicial indicando que o meio não foi encontrado
    novoAluguer->dataRecolha = dataAtual;
    strncpy(novoAluguer->tipoMeio, tipo, TAMANHO);
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
        if (cliente->nif == aluguer->idCliente){
            Meio* meio = listaMeios;
            while (meio != NULL) {
                if (strcmp(meio->geocodigo, aluguer->geocodigoRecolha) == 0 && strcmp(meio->tipo, aluguer->tipoMeio) == 0 && !(meio->alugado) && meio->autonomia >= 50) {
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



/**
 * @brief importa a fila de alugueres- input
 * 
 * @param filename 
 * @param listaMeios 
 * @param listaClientes 
 * @return Fila* 


/**
 * @brief Imprime no terminal a fila de alugueres
 * 
 * @param filaAlugueres 
 */
void imprimirAlugueres(Fila* filaAlugueres) {
    Aluguer* aluguer = filaAlugueres->inicio;

    while (aluguer != NULL) {
        printf("ID Cliente: %d\n", aluguer->idCliente);
        printf("ID Meio: %d\n", aluguer->idMeio);
        printf("dataRecolha: %d-%d-%d\n", aluguer->dataRecolha.dia, aluguer->dataRecolha.mes, aluguer->dataRecolha.ano);
        printf("dataEntrega: %d-%d-%d\n", aluguer->dataEntrega.dia, aluguer->dataEntrega.mes, aluguer->dataEntrega.ano);
        printf("Geocódigo de Recolha: %s\n", aluguer->geocodigoRecolha);
        printf("Geocódigo de Entrega: %s\n", aluguer->geocodigoEntrega);
        printf("A pagar: %.2f\n", aluguer->custo);

        aluguer = aluguer->proximo;
    }
}


/**
 * @brief função que reprenta a devolução da trotinete no ponto de recolha e calcula o valor a pagar
 * 
 * @param idCliente 
 * @param grafo 
 * @param geocodigoEntrega 
 * @param filaAlugueres 
 * @param listaMeios 
 * @return int 
 */
int devolverMeio(int idCliente, Grafo* grafo, char geocodigoEntrega[TAMANHO], Fila* filaAlugueres, Meio* listaMeios, int autonomia) {
    Aluguer* aluguer = filaAlugueres->inicio;

    while (aluguer != NULL) {
        if (aluguer->idCliente == idCliente) {
            aluguer->dataEntrega = getDate();
            strncpy(aluguer->geocodigoEntrega, geocodigoEntrega, TAMANHO - 1);
            aluguer->geocodigoEntrega[TAMANHO - 1] = '\0';
            aluguer->custo = (diferencaEntreDatas(aluguer->dataEntrega, aluguer->dataRecolha)+ TAXA_DIARIA * 1 +
                              calcularDistancia(grafo, geocodigoEntrega, aluguer->geocodigoRecolha) * TAXA_KM);

            Meio* meio = listaMeios;
            while (meio != NULL) {
                if (meio->codigo == aluguer->idMeio) {
                    meio->alugado = false;
                    meio->autonomia = autonomia;
                    strncpy(meio->geocodigo, geocodigoEntrega, TAMANHO);
                    break;
                }
                meio = meio->proximo;
            }

            return aluguer->custo;
        }
        aluguer = aluguer->proximo;
    }

    return 0;
}

/**
 * @brief calcula os dias entre duas datas
 * 
 * @param data1 
 * @param data2 
 * @return int 
 */
int diferencaEntreDatas(Data data1, Data data2) {
    struct tm tm1 = {0}; // Estrutura tm para data1
    struct tm tm2 = {0}; // Estrutura tm para data2

    // Preenche as informações da data1
    tm1.tm_year = data1.ano - 1900; // Ano - 1900
    tm1.tm_mon = data1.mes - 1;     // Mês (0 - 11, janeiro a dezembro)
    tm1.tm_mday = data1.dia;         // Dia do mês (1 - 31)

    // Preenche as informações da data2
    tm2.tm_year = data2.ano - 1900; // Ano - 1900
    tm2.tm_mon = data2.mes - 1;     // Mês (0 - 11, janeiro a dezembro)
    tm2.tm_mday = data2.dia;         // Dia do mês (1 - 31)

    // Converte as datas para o formato de tempo
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // Calcula a diferença em segundos entre as duas datas
    double diffSeconds = difftime(time2, time1);

    // Converte a diferença em segundos para dias
    int diffDays = diffSeconds / (60 * 60 * 24);

    return diffDays;
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
        char tipo[TAMANHO];
        sscanf(linha, "%d %s %s", &idCliente, geocodigoRecolha, tipo);

        Cliente* cliente = listaClientes;
        while (cliente != NULL) {
            if (cliente->nif == idCliente) {
                Aluguer* aluguer = criarAluguer(idCliente, geocodigoRecolha, tipo);
                bool inserido = false;
                filaAlugueres = inserirAluguer(filaAlugueres, aluguer, listaMeios, listaClientes, &inserido);
                break;
            }
            cliente = cliente->proximo;
        }
    }

    fclose(file);
    return filaAlugueres;
}


