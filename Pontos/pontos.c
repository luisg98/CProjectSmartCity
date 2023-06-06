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
 * @brief Função para encontrar um ponto de recolha pelo geocódigo
 * 
 * @param grafo O grafo onde o ponto de recolha será procurado
 * @param geocodigo O geocódigo do ponto de recolha a ser encontrado
 * @return O ponteiro para o ponto de recolha encontrado, ou NULL se não for encontrado
 */
PontoRecolha* encontrarPontoRecolha(Grafo* grafo, const char* geocodigo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        if (strcmp(pontoAtual->geocodigo, geocodigo) == 0) {
            return pontoAtual;
        }
        pontoAtual = pontoAtual->proximo;
    }
    return NULL;
}



/**
 * @brief Função para importar os pontos de recolha de um arquivo de texto
 * 
 * @param grafo O grafo onde os pontos de recolha serão adicionados
 * @param nomeArquivo O nome do arquivo de texto
 * @return true se os pontos de recolha foram importados com sucesso, false caso contrário
 */
bool importarPontosRecolha(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    char geocodigo[SIZE];
    while (fgets(geocodigo, SIZE, arquivo) != NULL) {
        // Remove a quebra de linha do final da string
        geocodigo[strcspn(geocodigo, "\n")] = '\0';

        if (!adicionarPontoRecolha(grafo, geocodigo)) {
            printf("Erro ao adicionar o ponto de recolha: %s\n", geocodigo);
        }
    }

    fclose(arquivo);
    return true;
}

/**
 * @brief Função para importar as arestas de um arquivo de texto
 * 
 * @param grafo O grafo onde as arestas serão adicionadas
 * @param nomeArquivo O nome do arquivo de texto
 * @return true se as arestas foram importadas com sucesso, false caso contrário
 */
bool importarArestas(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    char geocodigoInicio[SIZE];
    char geocodigoFim[SIZE];
    int distancia;
    while (fscanf(arquivo, "%s %s %d", geocodigoInicio, geocodigoFim, &distancia) == 3) {
        PontoRecolha* inicio = encontrarPontoRecolha(grafo, geocodigoInicio);
        PontoRecolha* fim = encontrarPontoRecolha(grafo, geocodigoFim);

        if (inicio == NULL || fim == NULL) {
            printf("Erro ao encontrar os pontos de recolha: %s, %s\n", geocodigoInicio, geocodigoFim);
        } else {
            if (!adicionarAresta(grafo, inicio, fim, distancia)) {
                printf("Erro ao adicionar a aresta: %s - %s\n", geocodigoInicio, geocodigoFim);
            }
        }
    }

    fclose(arquivo);
    return true;
}


/**
 * @brief Função para imprimir o grafo
 * 
 * @param grafo O grafo a ser impresso
 */
void imprimirGrafo(Grafo* grafo) {
    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        printf("Ponto de Recolha: %s\n", pontoAtual->geocodigo);
        
        Aresta* arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            printf("    Aresta: %s - %s, Distância: %d\n", pontoAtual->geocodigo, arestaAtual->destino->geocodigo, arestaAtual->distancia);
            arestaAtual = arestaAtual->proximo;
        }

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


/**
 * @brief Função para guardar os pontos de recolha em formato binário
 * 
 * @param grafo O grafo contendo os pontos de recolha a serem salvos
 * @param nomeArquivo O nome do arquivo binário para salvar os pontos de recolha
 * @return true se os pontos de recolha foram salvos com sucesso, false caso contrário
 */
bool guardarPontosRecolha(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        if (fwrite(pontoAtual, sizeof(PontoRecolha), 1, arquivo) != 1) {
            printf("Erro ao escrever os pontos de recolha no arquivo.\n");
            fclose(arquivo);
            return false;
        }
        pontoAtual = pontoAtual->proximo;
    }

    fclose(arquivo);
    return true;
}

/**
 * @brief Função para carregar os pontos de recolha a partir de um arquivo binário
 * 
 * @param grafo O grafo onde os pontos de recolha serão carregados
 * @param nomeArquivo O nome do arquivo binário contendo os pontos de recolha
 * @return true se os pontos de recolha foram carregados com sucesso, false caso contrário
 */
bool carregarPontosRecolha(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        return false;
    }

    PontoRecolha ponto;
    while (fread(&ponto, sizeof(PontoRecolha), 1, arquivo) == 1) {
        PontoRecolha* novoPonto = criarPontoRecolha(ponto.geocodigo);
        if (novoPonto == NULL) {
            fclose(arquivo);
            return false;
        }

        if (grafo->pontosRecolha == NULL) {
            grafo->pontosRecolha = novoPonto;
        } else {
            PontoRecolha* atual = grafo->pontosRecolha;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novoPonto;
        }

        grafo->numPontosRecolha++;
    }

    fclose(arquivo);
    return true;
}

/**
 * @brief Função para guardar as arestas em um arquivo binário
 * 
 * @param grafo O grafo contendo as arestas a serem guardadas
 * @param nomeArquivo O nome do arquivo binário onde as arestas serão guardadas
 * @return true se as arestas foram guardadas com sucesso, false caso contrário
 */
bool guardarArestas(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    PontoRecolha* pontoAtual = grafo->pontosRecolha;
    while (pontoAtual != NULL) {
        Aresta* arestaAtual = pontoAtual->adjacencia;
        while (arestaAtual != NULL) {
            fwrite(pontoAtual->geocodigo, sizeof(char), SIZE, arquivo);
            fwrite(arestaAtual->destino->geocodigo, sizeof(char), SIZE, arquivo);
            fwrite(&arestaAtual->distancia, sizeof(int), 1, arquivo);
            arestaAtual = arestaAtual->proximo;
        }
        pontoAtual = pontoAtual->proximo;
    }

    fclose(arquivo);
    return true;
}


/**
 * @brief Função para carregar as arestas de um arquivo binário
 * 
 * @param grafo O grafo onde as arestas serão carregadas
 * @param nomeArquivo O nome do arquivo binário contendo as arestas
 * @return true se as arestas foram carregadas com sucesso, false caso contrário
 */
bool carregarArestas(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    char geocodigoInicio[SIZE];
    char geocodigoFim[SIZE];
    int distancia;
    while (fread(geocodigoInicio, sizeof(char), SIZE, arquivo) == SIZE &&
           fread(geocodigoFim, sizeof(char), SIZE, arquivo) == SIZE &&
           fread(&distancia, sizeof(int), 1, arquivo) == 1) {
        PontoRecolha* inicio = encontrarPontoRecolha(grafo, geocodigoInicio);
        PontoRecolha* fim = encontrarPontoRecolha(grafo, geocodigoFim);

        if (inicio == NULL || fim == NULL) {
            printf("Erro ao encontrar os pontos de recolha: %s, %s\n", geocodigoInicio, geocodigoFim);
        } else {
            if (!adicionarAresta(grafo, inicio, fim, distancia)) {
                printf("Erro ao adicionar a aresta: %s - %s\n", geocodigoInicio, geocodigoFim);
            }
        }
    }

    fclose(arquivo);
    return true;
}
