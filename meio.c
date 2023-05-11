#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


Meio* novoMeio(int codigo, char tipo[], float autonomia, char localizacao[]) {
    Meio* novo = (Meio*) malloc(sizeof(Meio)); // Aloca memória para o novo meio

    if (novo == NULL) { // Verifica alocação
        return NULL;
    }

    // Define os atributos do novo meio
    novo->codigo = codigo;
    strcpy(novo->tipo, tipo);
    novo->autonomia = autonomia;
    strcpy(novo->localizacao, localizacao);
    novo->ligacoes = NULL; // Inicializa a lista de ligações como vazia

    return novo;
}

void inserirMeio(Grafo* grafo, Meio* meio) {
    if (grafo->num_vertices == 0) { // Se o grafo estiver vazio, adiciona o meio como primeiro vértice
        grafo->vertices = (Meio**) malloc(sizeof(Meio*)); // Aloca memória para o primeiro vértice
        grafo->vertices[0] = meio;
        grafo->num_vertices++;
        return;
    }

    // Adiciona o meio como um novo vértice
    grafo->vertices = (Meio**) realloc(grafo->vertices, (grafo->num_vertices + 1) * sizeof(Meio*)); // Realoca memória para adicionar um novo vértice
    grafo->vertices[grafo->num_vertices] = meio;
    grafo->num_vertices++;

    // Cria ligações entre o novo meio e os meios já existentes no grafo
    for (int i = 0; i < grafo->num_vertices - 1; i++) {
        Meio* vertice_atual = grafo->vertices[i];
        float distancia = calcularDistancia(meio, vertice_atual); // Função para calcular a distância entre dois meios
        inserirLigacao(meio, vertice_atual, distancia);
        inserirLigacao(vertice_atual, meio, distancia);
    }
}

// Remove um meio do grafo
void removerMeio(Grafo* grafo, Meio* meio) {
    int i;
    Ligacao* ligacao;
    Meio* vertice;

    // Encontra o vértice correspondente ao meio
    for (i = 0; i < grafo->num_vertices; i++) {
        vertice = grafo->vertices[i];
        if (vertice == meio) {
            break;
        }
    }

    // Remove as ligações que apontam para o meio
    ligacao = vertice->ligacoes;
    while (ligacao != NULL) {
        if (ligacao->destino == meio) {
            Ligacao* temp = ligacao;
            vertice->ligacoes = ligacao->proximo;
            free(temp);
        } else {
            Ligacao* prev = ligacao;
            ligacao = ligacao->proximo;
            while (ligacao != NULL) {
                if (ligacao->destino == meio) {
                    prev->proximo = ligacao->proximo;
                    free(ligacao);
                    break;
                }
                prev = ligacao;
                ligacao = ligacao->proximo;
            }
        }
    }

    // Remove o meio da lista de vértices do grafo
    for (i = 0; i < grafo->num_vertices; i++) {
        if (grafo->vertices[i] == meio) {
            Meio* temp = grafo->vertices[i];
            grafo->vertices[i] = grafo->vertices[grafo->num_vertices - 1];
            grafo->vertices[grafo->num_vertices - 1] = temp;
            grafo->num_vertices--;
            free(meio);
            break;
        }
    }
}

void imprimirMeios(Grafo* grafo) {
    if (grafo == NULL || grafo->num_vertices == 0) {
        printf("Grafo vazio.\n");
        return;
    }

    for (int i = 0; i < grafo->num_vertices; i++) {
        Meio* meioAtual = grafo->vertices[i];
        printf("Código: %d\n", meioAtual->codigo);
        printf("Tipo: %s\n", meioAtual->tipo);
        printf("Autonomia: %.2f\n", meioAtual->autonomia);
        printf("Localização: %s\n", meioAtual->localizacao);

        // Imprime as conexões deste meio
        Ligacao* ligacaoAtual = meioAtual->ligacoes;
        while (ligacaoAtual != NULL) {
            printf("  Conexão com código %d (distância %.2f)\n", ligacaoAtual->destino->codigo, ligacaoAtual->distancia);
            ligacaoAtual = ligacaoAtual->proximo;
        }

        printf("\n");
    }
}

void importarMeios(Grafo* grafo, char* filename) {
    FILE* file = fopen(filename, "r"); // abre o arquivo para leitura
    if (file == NULL) {
        return -1;
    }

    char linha[100];
    while (fgets(linha, 100, file)) { // lê cada linha do arquivo
        char* codigo_str = strtok(linha, ",");
        char* tipo = strtok(NULL, ",");
        char* autonomia_str = strtok(NULL, ",");
        char* localizacao = strtok(NULL, "\n");

        int codigo = atoi(codigo_str);
        float autonomia = atof(autonomia_str);

        // cria um novo meio e o insere no grafo
        Meio* novo = novoMeio(codigo, tipo, autonomia, localizacao);
        inserirMeio(grafo, novo);
    }

    fclose(file); // fecha o arquivo
}

