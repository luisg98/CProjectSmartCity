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
    Grafo grafoMeios;
    Aluguer * listaAlugueres = NULL;
    Gestor * listaGestores = NULL;
    
<<<<<<< HEAD
<<<<<<< HEAD
    /*
    //INPUT
    listaGestores = importarGestores("gestores.txt", listaGestores);
=======
    /*INPUT*/
    //listaGestores = importarGestores("gestores.txt", listaGestores);
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
=======
    /*INPUT*/
    //listaGestores = importarGestores("gestores.txt", listaGestores);
>>>>>>> parent of 4de73ff (adicionada condição para n existirem gestores com o mm nome)
    listaClientes = lerClientes("clientes.bin");
    listaGestores = lerGestores("gestores.bin", listaGestores);
    imprimirGestores(listaGestores);
    listarClientes(listaClientes);
    system("pause");
    bool v = guardarClientes(listaClientes, "clientes.bin");
    listaGestores = guardarGestores("gestores.bin", listaGestores);
    */
   Meio* meio = novoMeio(1, "Carro", 100.0, "Rua Principal");
   printf("cheguei aqui");
   inserirMeio(&grafoMeios, meio, 5);
   meio = novoMeio(2, "Trotinete", 100.0, "Rua do");
   inserirMeio(&grafoMeios, meio, 10);
   imprimirMeios(&grafoMeios);
   printf("uhhhhh");
   system("pause");
      
   

    return 0;
    
}