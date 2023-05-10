#ifndef GESTOR_H
#define GESTOR_H
#define SIZE 50

typedef struct gestor
{
char userNameGestor[SIZE];
char password[SIZE];
struct Gestor* anterior;
struct Gestor* seguinte;
} Gestor;


//FUNÇÕES
Gestor* novoGestor(char nome[], char password[]);
Gestor* inserirGestor(Gestor* gestores, char nome[], char password[]);
Gestor* removerGestor(Gestor* gestores, char* idGestor);
Gestor* alterarPasswordGestor(Gestor* gestores, char idGestor[], char novaPassword[]);
bool importarGestores(Gestor** gestores, const char* fileName);
bool guardarGestores(Gestor* gestores, const char* fileName);
bool lerGestores(Gestor** gestores, const char* fileName);


#endif
