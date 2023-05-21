#ifndef MEIO_H
#define MEIO_H
#define SIZE 50

typedef struct registo
{int codigo; // código do meio de mobilidade elétrica
 char tipo[SIZE];
 float bateria;
 float autonomia;
 struct registo* seguinte;
} Meio;


Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut); // Inserção de um novo registo
void listarMeios(Meio* inicio); // listar na consola o conteúdo da lista ligada
int existeMeio(Meio* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Meio* removerMeio(Meio* inicio, int cod); // Remover um meio a partir do seu código
void listarMeiosPorAutonomiaDecrescente(Meio* inicio);
int comparaAutonomia(const void* a, const void* b);

int guardarMeios(Meio* inicio);
Meio* lerMeios();


#endif
