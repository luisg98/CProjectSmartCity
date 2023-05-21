#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "meio.h"


int guardarMeios(Meio* inicio)
{FILE* fp;
 fp = fopen("meios.txt","w");
 if (fp != NULL)
 {
  Meio* aux = inicio;
    
    while (aux != NULL)
    {
      fprintf(fp,"%d;%f;%f;%s\n", aux->codigo, aux->bateria, aux->autonomia, aux->tipo);
      aux = aux->seguinte;
    }

  fclose(fp);

  return 1;
 }
 else return 0;
}

Meio* lerMeios()
{FILE* fp;
 int cod;
 float bat, aut;
 char tipo[50];
 Meio* aux=NULL;
 fp = fopen("meios.txt","r");
 if (fp!=NULL)
 {while (!feof(fp))
  { fscanf(fp,"%d;%f;%f;%[^\n]s\n", &cod, &bat, &aut, tipo);
    aux = inserirMeio(aux, cod, tipo, bat, aut);
  }
  fclose(fp);
 }
 return(aux);
}

// Inserção de um novo registo
Meio* inserirMeio(Meio * inicio, int cod, char tipo[], float bat, float aut)
{
    if (!existeMeio(inicio, cod)){
      
      Meio * novo = malloc(sizeof(struct registo));
      if (novo != NULL)
      {
        novo->codigo = cod;
        strcpy(novo->tipo,tipo);
        novo->bateria = bat;
        novo->autonomia = aut;
        novo->seguinte = inicio;
        return(novo);
      }
    }
    else return(inicio);
}

// listar na consola o conteúdo da lista ligada
void listarMeios(Meio * inicio)
{

  while (inicio != NULL){
  printf("%d %s %.2f %.2f\n", inicio->codigo,inicio->tipo, inicio->bateria, inicio->autonomia);
  inicio = inicio->seguinte;
  }
}


// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->codigo == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

/*
Meio* removerMeio(Meio* inicio, int cod) // Remover um meio a partir do seu código
{while (inicio!=NULL)
 {if (inicio->codigo==cod) 
	 {aux = inicio->seguinte;
          free(inicio);
	  return(aux);
	 }
  else {inicio = removerMeio(inicio->seguinte,cod);
	return(inicio);
       }
 }
}
*/

// Remover um meio a partir do seu código{
Meio* removerMeio(Meio* inicio, int cod) 
{
 Meio *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual->codigo == cod) // remoção do 1º registo
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->codigo!=cod)) 
  {anterior = atual;
   atual = atual->seguinte;
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}

// Função auxiliar para comparar a autonomia de dois meios
int comparaAutonomia(const void* a, const void* b)
{
    Meio* meioA = *(Meio**)a;
    Meio* meioB = *(Meio**)b;
    if (meioA->autonomia < meioB->autonomia) return 1;
    else if (meioA->autonomia > meioB->autonomia) return -1;
    else return 0;
}

// Listar os meios por ordem decrescente de autonomia
void listarMeiosPorAutonomiaDecrescente(Meio* inicio)
{
    // Contar o número de meios na lista
    int numMeios = 0;
    Meio* aux = inicio;
    while (aux != NULL) {
        numMeios++;
        aux = aux->seguinte;
    }

    // Criar um array dinâmico com os ponteiros para os meios
    Meio** arrayMeios = malloc(numMeios * sizeof(Meio*));
    if (arrayMeios == NULL) {
        printf("Erro: não foi possível alocar memória para o array de meios.\n");
        return;
    }

    // Preencher o array com os ponteiros para os meios
    aux = inicio;
    int i = 0;
    while (aux != NULL) {
        arrayMeios[i] = aux;
        aux = aux->seguinte;
        i++;
    }

    // Ordenar o array por ordem decrescente de autonomia
    qsort(arrayMeios, numMeios, sizeof(Meio*), comparaAutonomia);

    // Imprimir os meios ordenados por autonomia
    for (i = 0; i < numMeios; i++) {
        printf("%d %s %.2f %.2f\n", arrayMeios[i]->codigo, arrayMeios[i]->tipo, arrayMeios[i]->bateria, arrayMeios[i]->autonomia);
    }

    // Libertar a memória alocada para o array
    free(arrayMeios);
}





