/**
 * @file aluguer.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho do ficheiro .c correspondente
 * @version 1.0
 * @date 2023-05-24
 * @copyright Copyright (c) 2023
 */

#ifndef ALUGUER_H
#define ALUGUER_H
#define TAMANHO 50
#define TAXA_DIARIA 1
#define TAXA_KM 0.06
#include "../Meios/meio.h"
#include "../Clientes/cliente.h"
#include "../Pontos/pontos.h"

typedef struct Data{
    int ano;
    short mes;
    short dia;
} Data;

typedef struct Aluguer {
    int idCliente;
    int idMeio;
    char tipoMeio[TAMANHO];
    Data dataRecolha;
    Data dataEntrega;
    char geocodigoRecolha[TAMANHO];
    char geocodigoEntrega[TAMANHO];
    float custo;
    struct Aluguer *proximo;
    struct Aluguer *anterior;
} Aluguer;

typedef struct Fila {
    Aluguer *inicio;
    Aluguer *fim;
} Fila;

Data getDate();
Aluguer* criarAluguer(int nifCliente, const char geocodigoRecolha[], const char tipo[]);
Fila* inserirAluguer(Fila* filaAlugueres, Aluguer* aluguer, Meio* listaMeios, Cliente* listaClientes, bool* inserido);
Fila* importarAlugueres(const char* filename, Meio* listaMeios, Cliente* listaClientes);
void imprimirAlugueres(Fila* filaAlugueres);
bool guardarAlugueres(const char* filename, Fila* filaAlugueres);
Fila* carregarAlugueres(const char* filename);
int diferencaEntreDatas(Data data1, Data data2);
int devolverMeio(int idCliente,Grafo * grafo, char geocodigoEntrega[TAMANHO],  Fila* filaAlugueres, Meio* listaMeios, Cliente* listaClientes, int autonomia);
#endif