#ifndef MEIO_H
#define MEIO_H
#define TAMANHO 50


typedef struct Meio {
    int codigo;
    char tipo[TAMANHO];
    int autonomia;
    char geocodigo[TAMANHO];
    bool alugado;
    struct Meio * proximo;
}Meio;


Meio* criarMeio(int codigo, const char tipo[], int autonomia, const char geocodigo[]);
Meio* inserirMeio(Meio** lista, Meio* novoMeio);
Meio* importarMeios(const char* filename);
void imprimirMeios(Meio* lista);
bool guardarMeios(const char* filename, Meio* lista);
Meio* carregarMeios(const char* filename);
void libertarMeios(Meio* lista);


#endif
