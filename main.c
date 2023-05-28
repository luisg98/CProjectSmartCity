/**
 * @file main.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
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
    PtrCliente listaClientes = carregarClientes("Clientes/clientes.bin", &result);
    Gestor* listaGestores = carregarGestores("Gestores/gestores.bin");
    Grafo* grafo = carregarGrafo("Pontos/pontos.bin");
    //Fila* filaAlugueres = importarAlugueres("Alugueres/aluguer.txt", listaMeios, listaClientes);
    Fila* filaAlugueres = carregarAlugueres("Alugueres/aluguer.bin", listaMeios, listaClientes);

    
   
    //imprimirMeios(listaMeios);
    //imprimirClientes(listaClientes);
    //imprimirGestores(listaGestores);
    imprimirGrafo(grafo);
    imprimirMatrizAdjacencias(grafo);
    //imprimirAlugueres(filaAlugueres);

    //int tamanhoTrajeto = 0;
    //Aresta** melhorTrajeto = encontrarMelhorTrajeto(grafo, listaMeios, "polo.de.barcelos", &tamanhoTrajeto);
    //imprimirMelhorTrajeto(melhorTrajeto, tamanhoTrajeto, grafo);

    bool v;
    v = guardarMeios("Meios/meios.bin", listaMeios);
    printf("Meios guardados com sucesso: %d\n", v);
    v = guardarClientes("Clientes/clientes.bin", listaClientes);
    printf("Clientes guardados com sucesso: %d\n", v);
    v = guardarGestores("Gestores/gestores.bin", listaGestores);
    printf("Gestores guardados com sucesso: %d\n", v);
    v = guardarGrafo("Pontos/pontos.bin", grafo);
    printf("Grafo guardado com sucesso: %d\n", v);
    v = guardarAlugueres("Alugueres/aluguer.bin", filaAlugueres);
    printf("Alugueres guardados com sucesso: %d\n", v);
    


    return 0;
    
}