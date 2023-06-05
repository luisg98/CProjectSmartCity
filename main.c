/**
 * @file main.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief O main dispensa apresentações, é uma função especial e a primeira a ser executada
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "Clientes/cliente.h"
#include "Meios/meio.h"
#include "Gestores/gestor.h"
#include "Alugueres/aluguer.h"
#include "Pontos/pontos.h"
#include "solucao.h"



int main(){

    bool result;

    //Meio* listaMeios = importarMeios("Meios/meios.txt");
    //PtrCliente listaClientes = importarClientes("Clientes/clientes.txt");
    //Gestor * listaGestores = importarGestores("Gestores/gestores.txt");
    //Grafo* grafo = importarGrafo("Pontos/pontos.txt");
    Meio* listaMeios = carregarMeios("Meios/meios.bin");
    PtrCliente listaClientes = carregarClientes("Clientes/clientes.bin");
    //Gestor* listaGestores = carregarGestores("Gestores/gestores.bin");
    //Grafo *grafo = carregarGrafo("Pontos/grafo.bin");
    //grafo-> pontosRecolha = carregarPontosRecolha("Pontos/pontos.bin");
    Fila* filaAlugueres = importarAlugueres("Alugueres/aluguer.txt", listaMeios, listaClientes);
    //Fila* filaAlugueres = carregarAlugueres("Alugueres/aluguer.bin", listaMeios, listaClientes);
   
    //imprimirMeios(listaMeios);
    //imprimirClientes(listaClientes);
    //imprimirGestores(listaGestores);
    //imprimirGrafo(grafo);
    //imprimirMatrizAdjacencias(grafo);
     imprimirAlugueres(filaAlugueres);
    //devolverMeio(123456789, grafo, "polo.de.barcelos", filaAlugueres, listaMeios);
    //imprimirAlugueres(filaAlugueres);

    
    bool v;
    v = guardarMeios("Meios/meios.bin", listaMeios);
    printf("Meios guardados com sucesso: %d\n", v);
    v = guardarClientes("Clientes/clientes.bin", listaClientes);
    printf("Clientes guardados com sucesso: %d\n", v);
    //v = guardarGestores("Gestores/gestores.bin", listaGestores);
    //printf("Gestores guardados com sucesso: %d\n", v);
    //v = guardarGrafo("Pontos/grafo.bin", grafo);
    //printf("Grafo guardado com sucesso: %d\n", v);
    //v = guardarPontosRecolha("Pontos/pontos.bin", grafo->pontosRecolha);
    //printf("Pontos de Recolha guardados com sucesso: %d\n", v);
    //v = guardarAlugueres("Alugueres/aluguer.bin", filaAlugueres);
    //printf("Alugueres guardados com sucesso: %d\n", v);


    return 0;
    
}