/**
 * @file cliente.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENTE_H
#define CLIENTE_H
#define SIZE 50

typedef struct Cliente
{
        char nome[SIZE];
        char morada[SIZE];
        unsigned int nif;
        double saldo;
        struct Cliente * proximo;
    
}Cliente, *PtrCliente;

PtrCliente criarCliente(char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente insereCliente(PtrCliente clientes, char nome[], char morada[], unsigned int nif, double saldo);
PtrCliente removerCliente(PtrCliente clientes, unsigned int nif, bool *res);
PtrCliente alterarMoradaCliente(PtrCliente clientes, unsigned int nif, char novaMorada[], bool *res);
void imprimirClientes(PtrCliente clientes);
bool libertarClientes(PtrCliente clientes);
PtrCliente carregarSaldoCliente(PtrCliente clientes, unsigned int nif, double carregamento);
PtrCliente importarClientes(char *filename);
bool guardarClientes(const char* filename, PtrCliente clientes);
PtrCliente carregarClientes(const char* filename, bool* res);


#endif