#ifndef GESTOR_H
#define GESTOR_H
#define SIZE 50

typedef struct gestor
{
char idGestor[SIZE];
char password[SIZE];
struct registo* seguinte;
} Gestor;


//FUNÇÕES
Gestor* novoGestor(char nome[], char password[]);
Gestor* inserirGestor(Gestor* gestores, char nome[], char password[]);
Gestor* removerGestor(Gestor* gestores, char* idGestor);
Gestor* alterarPasswordGestor(Gestor* gestores, char idGestor[], char novaPassword[]);


#endif
