#ifndef ALUGUER_H
#define ALUGUER_H
#define SIZE 50


typedef struct data{
    int ano;
    short mes;
    short dia;
} Data;


typedef struct aluguer
{
int idCliente;
int idMeio; 
Data data;
struct aluguer * next;

} Aluguer;


bool novoAluguer(Aluguer ** alugueres, Meio * meios, int idCliente, int idMeio, int ano, short mes, short dia);
void listarAlugueres(Aluguer *alugueres);


#endif
