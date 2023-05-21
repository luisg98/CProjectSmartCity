#ifndef CLIENTE_H
#define CLIENTE_H
#define SIZE 50


typedef struct cliente
{
        char nome[SIZE];
        char morada[SIZE];
        unsigned int nif;
        float saldo;
        struct cliente * next;
    
}cliente;


//Funções
bool novocliente(cliente **clientes, char nome[], char morada[], unsigned int nif, float saldo, struct cliente *next);
void imprimirClientes(cliente *clientes);
bool libertarMemoriaListaclientes(cliente **clientes);
bool removerCliente(cliente **clientes, unsigned int nif);


#endif