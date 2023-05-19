#ifndef MEIO_H
#define MEIO_H
#define SIZE 50


typedef struct localizacao{
    float latitude;
    float longitude;
} Local;


<<<<<<< HEAD
typedef struct Meio {
    int codigo;
    char tipo[SIZE];
    float autonomia;
    char localizacao[SIZE];
    struct Ligacao* ligacoes;
=======
typedef struct meio
{int codigo; // código do meio de mobilidade elétrica
 char tipo[SIZE];
 float bateria;
 float autonomia;
 Local localizacao;
 struct meio* seguinte;
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
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

int existeMeio(Meio **inicio, int cod);
bool inserirMeio(Meio ** meios, int cod, char tipo[], float bat, float aut);
bool removerMeio(Meio** inicio, int cod);
void listarMeios(Meio * inicio);


#endif
