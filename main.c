/*
        Author: Luís Gonçalves
        Projeto elaborado no âmbito da disciplina de Estrutura de Dados Avançados
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cliente.h"
#include "meio.h"


//CAMADA SUPERIOR
int main(){

    cliente * clientes = NULL; //lista ligada vazia
    Meio * meios = NULL;

   /* lerMeios(meios);

    bool v = novocliente(&clientes, "luis", "rua", 123456789, 0, NULL);
    printf("Inserção: %d\n", v);
    v = novocliente(&clientes, "joao", "rua", 12345678, 0, NULL);
    printf("Inserção: %d\n", v);
    v = removerCliente(&clientes, 123456789);
    printf("Remoção: %d\n", v);

    meios = inserirMeio(meios, 123, "eletrica", 100, 20);

    //Imprimir os dados da lista de meios
    listarMeios(meios);

    // Imprimir os dados da lista de clientes
    printf("\nDados da lista de clientes:\n\n");

    imprimirClientes(clientes);

    libertarMemoriaListaclientes(&clientes);

    guardarMeios(meios);

    */

    meios = inserirMeio(meios, 1, "eletrica", 90, 20);
    meios = inserirMeio(meios, 2, "eletrica", 100, 30);
    meios = inserirMeio(meios, 3, "eletrica", 80, 10);
    listarMeiosPorAutonomiaDecrescente(meios);

    return 0;
    
}