#ifndef MEIO_H
#define MEIO_H
#define SIZE 50


typedef struct Meio {
    int codigo;
    char tipo[SIZE];
    float autonomia;
    char geocodigo[SIZE];
    struct Meio * proximo;
}Meio;


Meio* criarMeio(int codigo, const char tipo[], float autonomia, const char geocodigo[]);
Meio* inserirMeio(Meio** lista, Meio* novoMeio);
Meio* importarMeios(const char* filename);
void imprimirLista(Meio* lista);

#endif
