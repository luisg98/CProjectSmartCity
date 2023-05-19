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
    int numVertices;
} Grafo;


Meio* novoMeio(int codigo, char tipo[], float autonomia, char localizacao[]);
void inserirMeio(Grafo* grafo, Meio* meio, float distancia);
void removerMeio(Grafo* grafo, Meio* meio);
bool importarMeios(Grafo* grafo, char* filename);
void inserirLigacao(Meio* meio1, Meio* meio2, float distancia);
void imprimirMeios(Grafo* grafo);

#endif
