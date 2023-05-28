#ifndef CLIENTE_H
#define CLIENTE_H
#define SIZE 50


typedef struct Cliente
{
        char nome[SIZE];
        char morada[SIZE];
        unsigned int nif;
        double saldo;
        struct cliente * proximo;
    
}Cliente, *PtrCliente;


//Funções
PtrCliente criarCliente(char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente insereCliente(PtrCliente clientes, char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente removerCliente(PtrCliente clientes, unsigned int nif, bool *res);
PtrCliente alterarMoradaCliente(PtrCliente clientes, unsigned int nif, char novaMorada[], bool *res);
void imprimirClientes(PtrCliente clientes);
bool libertarClientes(PtrCliente clientes);
PtrCliente carregarSaldoCliente(PtrCliente clientes, unsigned int nif, double carregamento);
PtrCliente importarClientes(char *filename);
bool guardarClientes(char* filename, PtrCliente clientes);
PtrCliente carregarClientes(char* filename);


#endif