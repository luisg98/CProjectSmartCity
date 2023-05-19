#ifndef CLIENTE_H
#define CLIENTE_H
#define SIZE 50


typedef struct cliente
{
        char nome[SIZE];
        char morada[SIZE];
        unsigned int nif;
        double saldo;
        struct cliente * next;
    
}Cliente, *PtrCliente;


//Funções
PtrCliente novoCliente(char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente insereCliente(PtrCliente clientes, char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente removerCliente(PtrCliente clientes, unsigned int nif, bool *res);
PtrCliente alterarMoradaCliente(PtrCliente clientes, unsigned int nif, char novaMorada[]);
PtrCliente imprimirClientes(PtrCliente clientes);
void libertarClientes(PtrCliente clientes);
PtrCliente carregarSaldoCliente(PtrCliente clientes, unsigned int nif, double carregamento);
PtrCliente importarClientes(char *nomeArquivo);
bool guardarClientes(PtrCliente clientes, char* nomeArquivo);
PtrCliente carregarClientes(char* nomeArquivo);


#endif