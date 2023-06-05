/**
 * @file meio.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho do ficheiro .c correspondente
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


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


Meio* criarMeio(int codigo, const char tipo[], const char geocodigo[]);
Meio* inserirMeio(Meio** lista, Meio* novoMeio);
Meio* importarMeios(const char* filename);
void imprimirMeios(Meio* lista);
bool guardarMeios(const char* filename, Meio* lista);
Meio* carregarMeios(const char* filename);
void libertarMeios(Meio* lista);


#endif
