#ifndef GESTOR_H
#define GESTOR_H
#define SIZE 50

typedef struct Gestor
{
char username[SIZE];
char password[SIZE];
struct Gestor* anterior;
struct Gestor* seguinte;
} Gestor;


//FUNÇÕES
Gestor* novoGestor(char username[], char password[]);
Gestor* inserirGestor(Gestor* inicioListaGestores, Gestor* gestor);
Gestor* removerGestor(Gestor* gestores, char* idGestor);
Gestor* alterarPasswordGestor(Gestor* gestores, char idGestor[], char novaPassword[]);
Gestor* importarGestores(const char* fileName, Gestor* listaGestores);
Gestor* guardarGestores(const char* fileName, Gestor* inicioListaGestores);
Gestor* lerGestores(const char* fileName, Gestor* listaGestores);
void imprimirGestores(Gestor* listaGestores);

#endif
