/**
 * @file gestor.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho do ficheiro .c correspondente
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GESTOR_H
#define GESTOR_H
#define SIZE 50

typedef struct Gestor{
char username[SIZE];
char password[SIZE];
struct Gestor* anterior;
struct Gestor* seguinte;
} Gestor;


Gestor* novoGestor(char username[], char password[]);
Gestor* inserirGestor(Gestor* inicioListaGestores, Gestor* gestor);
Gestor* removerGestor(Gestor* gestores, char* idGestor);
Gestor* alterarPasswordGestor(Gestor* gestores, char idGestor[], char novaPassword[]);
Gestor* importarGestores(const char* fileName);
Gestor* guardarGestores(const char* fileName, Gestor* inicioListaGestores);
Gestor* carregarGestores(const char* fileName);
void imprimirGestores(Gestor* listaGestores);

#endif
