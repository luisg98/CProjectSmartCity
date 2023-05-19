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

    //Meio* listaMeios = importarMeios("meios.txt");
    //PtrCliente listaClientes = importarClientes("clientes".txt");
    Gestor * listaGestores = importarGestores("gestores.txt");
    Meio* listaMeios = carregarMeios("meios.bin");
    PtrCliente listaClientes = carregarClientes("clientes.bin");
    //Gestor* listaGestores = carregarGestores("gestores.bin");

    imprimirMeios(listaMeios);
    imprimirClientes(listaClientes);
    imprimirGestores(listaGestores);
   
    bool v = guardarMeios("meios.bin", listaMeios);
    v = guardarClientes(listaClientes, "clientes.bin");
    v = guardarGestores("gestores.bin", listaGestores);
    return 0;
    
}