
#ifndef ALUGUER_H
#define ALUGUER_H
#define TAMANHO 50


#include "../Meios/meio.h"

typedef struct Data{
    int ano;
    short mes;
    short dia;
} Data;


typedef struct Aluguer {
    int idCliente;
    int idMeio;
    Data data;
    char geocodigoRecolha[TAMANHO];
    struct Aluguer *proximo;
    struct Aluguer *anterior;
} Aluguer;

typedef struct Fila {
    Aluguer *inicio;
    Aluguer *fim;
} Fila;

Data getDate();

Fila* importarAlugueres(const char* nomeArquivo, Meio* listaMeios);
void imprimirAlugueres(Fila* filaAlugueres);


#endif
