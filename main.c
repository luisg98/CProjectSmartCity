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
    /*INPUT A PARTIR DE FICHEIROS TXT*/
    Meio* listaMeios = importarMeios("Meios/meios.txt");
    //PtrCliente listaClientes = importarClientes("Clientes/clientes.txt");
    //Gestor * listaGestores = importarGestores("Gestores/gestores.txt");
    //Grafo* grafo = importarGrafo("Pontos/pontos.txt");
    //result = importarPontosRecolha(grafo, "Pontos/pontos.txt");
    //result = importarArestas(grafo, "Pontos/arestas.txt");
    
    //Meio* listaMeios = carregarMeios("Meios/meios.bin");
    PtrCliente listaClientes = carregarClientes("Clientes/clientes.bin");
    Gestor* listaGestores = carregarGestores("Gestores/gestores.bin");
    Grafo* grafo = criarGrafo();
    result = carregarPontosRecolha(grafo, "Pontos/pontos.bin");
    result = carregarArestas(grafo, "Pontos/arestas.bin");

    Fila* filaAlugueres = importarAlugueres("Alugueres/aluguer.txt", listaMeios, listaClientes);
    //Fila* filaAlugueres = carregarAlugueres("Alugueres/aluguer.bin", listaMeios, listaClientes);
   
    //imprimirMeios(listaMeios);
    //imprimirClientes(listaClientes);
    //imprimirGestores(listaGestores);
    //imprimirGrafo(grafo);
    //imprimirMatrizAdjacencias(grafo);
    imprimirAlugueres(filaAlugueres);
    devolverMeio(123456789, grafo, "polo.de.barcelos", filaAlugueres, listaMeios, 0);
    devolverMeio(987654321, grafo, "polo.de.guimaraes", filaAlugueres, listaMeios, 0);
    imprimirAlugueres(filaAlugueres);

    PontoRecolha * pontoInicial = encontrarPontoRecolha(grafo, "polo.de.braga");
    Rota * melhorRota = encontrarMelhorRota(listaMeios, pontoInicial, grafo);
    imprimirRota(melhorRota);
    
    bool v;
    v = guardarMeios("Meios/meios.bin", listaMeios);
    printf("Meios guardados com sucesso: %d\n", v);
    v = guardarClientes("Clientes/clientes.bin", listaClientes);
    printf("Clientes guardados com sucesso: %d\n", v);
    v = guardarGestores("Gestores/gestores.bin", listaGestores);
    printf("Gestores guardados com sucesso: %d\n", v);
    v = guardarPontosRecolha(grafo, "Pontos/pontos.bin");
    v = guardarArestas(grafo, "Pontos/arestas.bin");
    printf("Pontos de Recolha guardados com sucesso: %d\n", v);
    //v = guardarAlugueres("Alugueres/aluguer.bin", filaAlugueres);
    //printf("Alugueres guardados com sucesso: %d\n", v);


    return 0;
    
}