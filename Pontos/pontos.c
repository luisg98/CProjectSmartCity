/**
 * @file pontos.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief Ficheiro para tudo relacionado com os pontos de recolha
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define SIZE 50
#include "pontos.h"

/**
 * @brief 
 * 
 * @param geocodigo 
 * @return PontoRecolha* 
 */
PontoRecolha* criarPontoRecolha(char geocodigo[]) {
    PontoRecolha* novoPontoRecolha = (PontoRecolha*)malloc(sizeof(PontoRecolha));
    strcpy(novoPontoRecolha->geocodigo, geocodigo);
    novoPontoRecolha->adjacencia = NULL;
    novoPontoRecolha->proximo = NULL;
    return novoPontoRecolha;
}


bool adicionarPontoRecolha(Grafo* grafo, char geocodigo[]) {
    PontoRecolha* novoPontoRecolha = criarPontoRecolha(geocodigo);

    // Verifica se o grafo está vazio
    if (grafo->pontosRecolha == NULL) {
        grafo->pontosRecolha = novoPontoRecolha;
    } else {
        // Percorre a lista de pontos de recolha e adiciona o novo ponto de recolha no final
        PontoRecolha* atual = grafo->pontosRecolha;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoPontoRecolha;
    }

    grafo->numPontosRecolha++;
    return true;
}


/**
 * @brief Função para criar uma nova aresta
 * 
 * @param inicio 
 * @param fim 
 * @param distancia 
 * @return Aresta* 
 */
Aresta* criarAresta(PontoRecolha* inicio, PontoRecolha* fim, int distancia) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->origem = inicio;
    novaAresta->destino = fim;
    novaAresta->distancia = distancia;
    novaAresta->proximo = NULL;
    return novaAresta;
}

/**
 * @brief Função para adicionar uma aresta ao grafo
 * 
 * @param grafo 
 * @param inicio 
 * @param fim 
 * @param distancia 
 */
bool adicionarAresta(Grafo* grafo, PontoRecolha* inicio, PontoRecolha* fim, int distancia) {
    Aresta* novaAresta = criarAresta(inicio, fim, distancia);

    // Verifica se a lista de adjacência do ponto de recolha de partida está vazia
    if (inicio->adjacencia == NULL) {
        inicio->adjacencia = novaAresta;
    } else {
        // Percorre a lista de adjacência até encontrar o último elemento
        Aresta* arestaAtual = inicio->adjacencia;
        while (arestaAtual->proximo != NULL) {
            arestaAtual = arestaAtual->proximo;
        }
        // Adiciona a nova aresta ao final da lista de adjacência
        arestaAtual->proximo = novaAresta;
    }

    return true;
}



/**
 * @brief  Função para libertar a memória alocada para o grafo
 * 
 * @param grafo 
 * @return true 
 * @return false 
 */
bool libertarGrafo(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        PontoRecolha* pontoTemp = pontoAtual;
        Aresta* arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            Aresta* arestaTemp = arestaAtual;
            arestaAtual = arestaAtual->proximo;
            free(arestaTemp);
        }
        pontoAtual = pontoAtual->proximo;
        free(pontoTemp);
    }
    free(grafo);
    return true;
}

/**
 * @brief Cria um grafo
 * 
 * @return Grafo* 
 */
Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        return NULL;
    }
    
    grafo->pontosRecolha = NULL;
    grafo->numPontosRecolha = 0;
    
    return grafo;
}

/**
 * @brief Importa um grafo de um ficheiro txt
 * 
 * @param filename 
 * @return Grafo* 
 */
Grafo* importarGrafo(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    Grafo* grafo = criarGrafo();
    
    char linha[SIZE];
    while (fgets(linha, sizeof(linha), file)) {
        // Remover o caractere de quebra de linha ('\n')
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");
        
        if (strcmp(token, "P") == 0) {
            token = strtok(NULL, ",");
            adicionarPontoRecolha(grafo, token);
        } else if (strcmp(token, "A") == 0) {
            token = strtok(NULL, ",");
            PontoRecolha* origem = NULL;
            PontoRecolha* destino = NULL;
            int distancia;
            
            // Procura o ponto de recolha de origem
            PontoRecolha* atual = grafo->pontosRecolha;
            while (atual != NULL) {
                if (strcmp(atual->geocodigo, token) == 0) {
                    origem = atual;
                    break;
                }
                atual = atual->proximo;
            }
            
            token = strtok(NULL, ",");
            
            // Procura o ponto de recolha de destino
            atual = grafo->pontosRecolha;
            while (atual != NULL) {
                if (strcmp(atual->geocodigo, token) == 0) {
                    destino = atual;
                    break;
                }
                atual = atual->proximo;
            }
            
            token = strtok(NULL, ",");
            distancia = atoi(token);
            
            if (origem != NULL && destino != NULL) {
                adicionarAresta(grafo, origem, destino, distancia);
            }
        }
    }
    
    fclose(file);
    
    return grafo;
}



void imprimirGrafo(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;

    printf("Grafo:\n");
    printf("------\n");

    while (pontoAtual != NULL) {
        printf("Ponto de Recolha: %s\n", pontoAtual->geocodigo);

        Aresta* arestaAtual = pontoAtual->adjacencia;
        if (arestaAtual != NULL) {
            printf("Adjacências:\n");

            while (arestaAtual != NULL) {
                printf("%s --(%d km)--> %s\n", pontoAtual->geocodigo, arestaAtual->distancia, arestaAtual->destino->geocodigo);
                arestaAtual = arestaAtual->proximo;
            }
        } else {
            printf("Sem adjacências\n");
        }

        printf("\n");
        pontoAtual = pontoAtual->proximo;
    }
}

void imprimirMatrizAdjacencias(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;

    printf("Matriz de Adjacências:\n");
    printf("------------------------------------------\n");

    // Imprimir rótulos das colunas
    printf("%-12s", ""); // Espaço vazio para alinhar os rótulos das colunas

    while (pontoAtual != NULL) {
        // Mapear o código geográfico para o nome da cidade correspondente
        if (strcmp(pontoAtual->geocodigo, "polo.de.braga") == 0) {
            printf("%-12s", "BRAGA");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.barcelos") == 0) {
            printf("%-12s", "BARCELOS");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.esposende") == 0) {
            printf("%-12s", "ESPOSENDE");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.famalicao") == 0) {
            printf("%-12s", "FAMALICAO");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.guimaraes") == 0) {
            printf("%-12s", "GUIMARAES");
        } else {
            printf("%-12s", pontoAtual->geocodigo);
        }

        pontoAtual = pontoAtual->proximo;
    }

    printf("\n");
    pontoAtual = grafo->pontosRecolha;

    // Imprimir restante da matriz
    while (pontoAtual != NULL) {
        // Mapear o código geográfico para o nome da cidade correspondente
        if (strcmp(pontoAtual->geocodigo, "polo.de.braga") == 0) {
            printf("%-12s", "BRAGA");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.barcelos") == 0) {
            printf("%-12s", "BARCELOS");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.esposende") == 0) {
            printf("%-12s", "ESPOSENDE");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.famalicao") == 0) {
            printf("%-12s", "FAMALICAO");
        } else if (strcmp(pontoAtual->geocodigo, "polo.de.guimaraes") == 0) {
            printf("%-12s", "GUIMARAES");
        } else {
            printf("%-12s", pontoAtual->geocodigo);
        }

        PontoRecolha* pontoTemp = grafo->pontosRecolha;

        while (pontoTemp != NULL) {
            int distancia = 0;
            Aresta* arestaAtual = pontoAtual->adjacencia;

            while (arestaAtual != NULL) {
                if (arestaAtual->destino == pontoTemp) {
                    distancia = arestaAtual->distancia;
                    break;
                }
                arestaAtual = arestaAtual->proximo;
            }

            if (pontoTemp == pontoAtual) {
                printf("%-12s", " ");
            } else {
                if (distancia > 0) {
                    printf("%-12d", distancia);
                } else {
                    printf("%-12s", "--");
                }
            }

            pontoTemp = pontoTemp->proximo;
        }

        printf("\n");
        pontoAtual = pontoAtual->proximo;
    }

    printf("------------------------------------------\n");
}



PontoRecolha* converteGeocodigoPontoRecolha(Grafo* grafo, const char* geocodigo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;

    while (pontoAtual != NULL) {
        if (strcmp(pontoAtual->geocodigo, geocodigo) == 0) {
            return pontoAtual;
        }
        pontoAtual = pontoAtual->proximo;
    }

    return NULL;
}


// Função para calcular a distância entre dois geocódigos
int calcularDistancia(Grafo* grafo, char geocodigo1[], char geocodigo2[]) {
    PontoRecolha* ponto1 = NULL;
    PontoRecolha* ponto2 = NULL;

    // Procura os pontos de recolha com os geocódigos fornecidos
    PontoRecolha* atual = grafo->pontosRecolha;
    while (atual != NULL) {
        if (strcmp(atual->geocodigo, geocodigo1) == 0) {
            ponto1 = atual;
        }
        if (strcmp(atual->geocodigo, geocodigo2) == 0) {
            ponto2 = atual;
        }

        // Se os dois pontos de recolha foram encontrados, interrompe o loop
        if (ponto1 != NULL && ponto2 != NULL) {
            break;
        }

        atual = atual->proximo;
    }

    // Verifica se os pontos de recolha foram encontrados
    if (ponto1 == NULL || ponto2 == NULL) {
        return -1; // Retorna -1 para indicar que os geocódigos não foram encontrados
    }

    // Verifica se os pontos de recolha são adjacentes
    Aresta* arestaAtual = ponto1->adjacencia;
    while (arestaAtual != NULL) {
        if (arestaAtual->destino == ponto2) {
            return arestaAtual->distancia; // Retorna a distância entre os pontos de recolha
        }
        arestaAtual = arestaAtual->proximo;
    }

    return -1; // Retorna -1 para indicar que os pontos de recolha não são adjacentes
}



bool guardarGrafo(const char* filename, Grafo* grafo) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return false;
    }

    fwrite(&(grafo->numPontosRecolha), sizeof(int), 1, file);

    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        int tamanhoGeocodigo = strlen(pontoAtual->geocodigo);
        fwrite(&tamanhoGeocodigo, sizeof(int), 1, file);
        fwrite(pontoAtual->geocodigo, sizeof(char), tamanhoGeocodigo, file);

        int numAdjacencias = 0;
        Aresta* arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            numAdjacencias++;
            arestaAtual = arestaAtual->proximo;
        }
        fwrite(&numAdjacencias, sizeof(int), 1, file);

        arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            int tamanhoGeocodigoDestino = strlen(arestaAtual->destino->geocodigo);
            fwrite(&tamanhoGeocodigoDestino, sizeof(int), 1, file);
            fwrite(arestaAtual->destino->geocodigo, sizeof(char), tamanhoGeocodigoDestino, file);

            fwrite(&(arestaAtual->distancia), sizeof(int), 1, file);

            arestaAtual = arestaAtual->proximo;
        }

        pontoAtual = pontoAtual->proximo;
    }

    fclose(file);
    return true;
}

