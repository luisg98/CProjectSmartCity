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
#include <time.h>
#include "Clientes/cliente.h"
#include "Meios/meio.h"
#include "Gestores/gestor.h"
#include "Alugueres/aluguer.h"
#include "pontos.h"


int main(){

    //Meio* listaMeios = importarMeios("meios.txt");
    //PtrCliente listaClientes = importarClientes("clientes".txt");
    //Gestor * listaGestores = importarGestores("Gestores/gestores.txt");
    Meio* listaMeios = carregarMeios("Meios/meios.bin");
    PtrCliente listaClientes = carregarClientes("Clientes/clientes.bin");
    Gestor* listaGestores = carregarGestores("gestores.bin");
    Grafo* grafo = importarGrafo("pontos.txt");

    imprimirMeios(listaMeios);
    imprimirClientes(listaClientes);
    imprimirGestores(listaGestores);
    imprimirGrafo(grafo);
    imprimirMatrizAdjacencias(grafo);

    Data data = getDate();
    printf("%d-%d-%d", data.dia, data.mes, data.ano);


    bool v = guardarMeios("Meios/meios.bin", listaMeios);
    v = guardarClientes("Clientes/clientes.bin", listaClientes);
    v = guardarGestores("Gestores/gestores.bin", listaGestores);

    return 0;
    
}