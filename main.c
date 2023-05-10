/*
        Author: Luís Gonçalves
        Data: de FEV/2023 a JUN/2023 
        Projeto elaborado no âmbito da disciplina de Estrutura de Dados Avançados
        Sistema de Gestão de meios de mobilidade sustentável
        Mais informações sobre o projeto no pdf incluído
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "cliente.h"
#include "meio.h"
#include "gestor.h"
#include "aluguer.h"



int main(){


    PtrCliente listaClientes = NULL;
    Meio * listaMeios = NULL;
    Aluguer * listaAlugueres = NULL;
    Gestor * listaGestores = NULL;


    listaGestores = importarGestores(listaGestores, "gestores.txt");
    //INPUT
    listaClientes = lerClientes("clientes.bin");

    //listaClientes = importarClientes("clientes.txt");

    listarClientes(listaClientes);
    
    bool v = guardarClientes(listaClientes, "clientes.bin");

    return 0;
    
}