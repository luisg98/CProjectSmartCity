#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"


<<<<<<< HEAD
<<<<<<< HEAD
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

void inserirMeio(Grafo* grafo, Meio* meio, float distancia) {
    if (grafo->numVertices == 0) { // Se o grafo estiver vazio, adiciona o meio como primeiro vértice
        grafo->vertices = (Meio**) malloc(sizeof(Meio*)); // Aloca memória para o primeiro vértice
        grafo->vertices[0] = meio;
        grafo->numVertices++;
        return;
    }

    // Adiciona o meio como um novo vértice
    grafo->vertices = (Meio**) realloc(grafo->vertices, (grafo->numVertices + 1) * sizeof(Meio*)); // Realoca memória para adicionar um novo vértice
    grafo->vertices[grafo->numVertices] = meio;
    grafo->numVertices++;

    // Cria ligações entre o novo meio e os meios já existentes no grafo
    for (int i = 0; i < grafo->numVertices - 1; i++) {
        Meio* vertice_atual = grafo->vertices[i];
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
    for (i = 0; i < grafo->numVertices; i++) {
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
    for (i = 0; i < grafo->numVertices; i++) {
        if (grafo->vertices[i] == meio) {
            Meio* temp = grafo->vertices[i];
            grafo->vertices[i] = grafo->vertices[grafo->numVertices - 1];
            grafo->vertices[grafo->numVertices - 1] = temp;
            grafo->numVertices--;
            free(meio);
            break;
        }
    }
}

void imprimirMeios(Grafo* grafo) {
    if (grafo == NULL || grafo->numVertices == 0) {
        printf("Grafo vazio.\n");
        return;
    }

    for (int i = 0; i < grafo->numVertices; i++) {
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

bool importarMeios(Grafo* grafo, char* filename) {
    FILE* file = fopen(filename, "r"); // abre o arquivo para leitura
    if (file == NULL) {
        return false;
    }

    char linha[100];
    while (fgets(linha, 100, file)) { // lê cada linha do arquivo
        char* codigoStr = strtok(linha, ",");
        char* tipo = strtok(NULL, ",");
        char* autonomiaStr = strtok(NULL, ",");
        char* localizacao = strtok(NULL, "\n");

        int codigo = atoi(codigoStr);
        float autonomia = atof(autonomiaStr);
        float distancia;

        // cria um novo meio e o insere no grafo
        Meio* novo = novoMeio(codigo, tipo, autonomia, localizacao);
        inserirMeio(grafo, novo, distancia);
        return true;
    }

    fclose(file); // fecha o arquivo
}

void inserirLigacao(Meio* meio1, Meio* meio2, float distancia) {
    Ligacao* ligacao = (Ligacao*) malloc(sizeof(Ligacao)); // Aloca memória para a nova ligação
    ligacao->destino = meio2;
    ligacao->distancia = distancia;
    ligacao->proximo = NULL;

    // Verifica se o meio1 já possui ligações
    if (meio1->ligacoes == NULL) {
        meio1->ligacoes = ligacao;
    } else {
        // Encontra o último elemento da lista de ligações
        Ligacao* ultimo = meio1->ligacoes;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }

        ultimo->proximo = ligacao;
    }
}
=======
=======
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
#define PI 3.14159265358979323846
#define raioTerra 6371000 // em metros

//Verifica se existe determinado meio com id introduzido
int existeMeio(Meio **inicio, int cod) {
    Meio *atual = *inicio;
    while (atual != NULL) {
        if (atual->codigo == cod) {
            return 1;
        }
        atual = atual->seguinte;
    }
    return 0;
}

//insere numa lista ligada siples uma estrutura do tipo "meio"
bool inserirMeio(Meio ** meios, int cod, char tipo[], float bat, float aut)
{
    if (!existeMeio(meios, cod)) {
        Meio * novo = NULL;
        novo = malloc(sizeof(struct meio));
        if (novo != NULL) {
            novo->codigo = cod;
            strcpy(novo->tipo,tipo);
            novo->bateria = bat;
            novo->autonomia = aut;
            novo->localizacao.latitude = 0.0;
            novo->localizacao.longitude = 0.0;
            novo->seguinte = *meios;
            *meios = novo;  // adiciona o novo nó à lista
            return true;
        }
    }
    return false;
}

//Remove um meio de uma lista
bool removerMeio(Meio** inicio, int cod) {
    Meio *anterior = NULL, *atual = *inicio;
    if (atual == NULL) {
        return false;
    } else if (atual->codigo == cod) { // remoção do 1º registo
        *inicio = atual->seguinte;
        free(atual);
        return true;
    } else {
        while ((atual != NULL) && (atual->codigo != cod)) {
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL) {
            return false;
        } else {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return true;
        }
    }
}

//Escreve no terminal os meios presentes na lista 
void listarMeios(Meio *inicio)
{
    while (inicio != NULL) {
        printf("%d %s %.2f %.2f (%.6f, %.6f)\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->localizacao.latitude, inicio->localizacao.longitude);
        inicio = inicio->seguinte;
    }
}


/*
    Utilizacao de método 'QSORT'
    Referência: https://cplusplus.com/reference/cstdlib/qsort/

        Pointer to a function that compares two elements.
    This function is called repeatedly by qsort to compare two elements. It shall follow the following prototype:

    int compar (const void* p1, const void* p2);

    Taking two pointers as arguments (both converted to const void*). The function defines the order of the elements by returning (in a stable and transitive manner):
    return value	meaning
    <0	The element pointed to by p1 goes before the element pointed to by p2
    0	The element pointed to by p1 is equivalent to the element pointed to by p2
    >0	The element pointed to by p1 goes after the element pointed to by p2

    For types that can be compared using regular relational operators, a general compar function may look like:    	

    int compareMyType (const void * a, const void * b)
    {
      if ( *(MyType*)a <  *(MyType*)b ) return -1;
      if ( *(MyType*)a == *(MyType*)b ) return 0;
      if ( *(MyType*)a >  *(MyType*)b ) return 1;
    }


*/

// Função auxiliar para comparar a autonomia de dois meios
int comparaAutonomia(const void* a, const void* b)
{
    Meio* meioA = *(Meio**) a;
    Meio* meioB = *(Meio**) b;
    if (meioA->autonomia < meioB->autonomia) return 1;
    else if (meioA->autonomia > meioB->autonomia) return -1;
    else return 0;
}

// Listar os meios por ordem decrescente de autonomia
void listarMeiosPorAutonomiaDecrescente(Meio* meios)
{

    // Contador de meios
    int totMeios = 0;
    Meio* aux = meios;
    while (aux != NULL) {
        totMeios++;
        aux = aux->seguinte;
    }

    // Criar um array dinâmico com os ponteiros para os meios
    Meio** arrayMeios = malloc(totMeios * sizeof(Meio*));
    if (arrayMeios == NULL) {
        //printf("Erro: não foi possível alocar memória para o array de meios.\n");
        return;
    }

    //Preencher o array com os ponteiros para os meios
    aux = meios;
    int i = 0;
    while (aux != NULL) {
        arrayMeios[i] = aux;
        aux = aux->seguinte;
        i++;
    }

    // Ordenar o array por ordem decrescente de autonomia
    qsort(meios, totMeios, sizeof(Meio*), comparaAutonomia);

    // Imprimir os meios ordenados por autonomia
    for (i = 0; i < totMeios; i++) {
        printf("%d %s %.2f %.2f\n", arrayMeios[i]->codigo, arrayMeios[i]->tipo, arrayMeios[i]->bateria, arrayMeios[i]->autonomia);
    }

    // Libertar a memória alocada para o array
    free(arrayMeios);
}


// Função auxiliar que calcula a distância em metros entre duas localizações
float calcularDistancia(Local loc1, Local loc2) {
    // Converter as coordenadas de latitude e longitude para radianos
    float lat1 = loc1.latitude * PI / 180.0;
    float lat2 = loc2.latitude * PI / 180.0;
    float lon1 = loc1.longitude * PI / 180.0;
    float lon2 = loc2.longitude * PI / 180.0;
    // Calcular as diferenças de latitude e longitude em radianos
    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;
    // Aplicar a fórmula de Haversine para calcular a distância em metros
    float a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float distancia = raioTerra * c;
    return distancia;
}

// Função que procura meios em um determinado raio de localização
void procurarMeiosNoRaio(Meio *inicio, Local referencia, float raioMaximo) {
    // Percorrer a lista de meios
    while (inicio != NULL) {
        // Calcular a distância entre a localização de referência e a localização do meio atual
        float distancia = calcularDistancia(referencia, inicio->localizacao);
        // Verificar se a distância está dentro do raio máximo
        if (distancia <= raioMaximo) {
            // Imprimir as informações do meio
           // printf("%d %s %.2f %.2f (%.6f, %.6f) - Distancia: %.2f metros\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->localizacao.latitude, inicio->localizacao.longitude, distancia);
        }
        // Avançar para o próximo meio da lista
        inicio = inicio->seguinte;
    }
}

<<<<<<< HEAD
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
=======
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
