#ifndef MEIO_H
#define MEIO_H
#define SIZE 50




typedef struct Meio {
    int codigo;
    char tipo[SIZE];
    float autonomia;
    char localizacao[SIZE];
    struct Ligacao* ligacoes;
} Meio;

typedef struct Ligacao {
    Meio* destino;
    float distancia;
    struct Ligacao* proximo;
} Ligacao;

typedef struct Grafo {
    Meio** vertices;
    int num_vertices;
} Grafo;


Meio* novoMeio(int codigo, char tipo[], float autonomia, char localizacao[]);
void inserirMeio(Grafo* grafo, Meio* meio);
void removerMeio(Grafo* grafo, Meio* meio);
void imprimirMeios(Grafo* grafo);
void importarMeios(Grafo* grafo, char* filename);

#endif
