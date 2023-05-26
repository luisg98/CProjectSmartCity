/**
 * @file solucao.h
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SOLUCAO_H
#define SOLUCAO_H
#define CAPACIDADE_CAMIAO 10

int calcularDistanciaTotal(Aresta** trajeto, int numPontosRecolha);
PontoRecolha* encontrarProximoPonto(PontoRecolha* pontoAtual, Grafo* grafo);
bool todosVisitados(Grafo* grafo);
Aresta* encontrarArestaPorOrigemEDestino(Grafo* grafo, const char* geocodigoOrigem, const char* geocodigoDestino);
PontoRecolha* encontrarPontoRecolhaPorGeocodigo(Grafo* grafo, const char* geocodigo);
Meio* encontrarProximoMeio(Meio* meios, Grafo* grafo, const char* geocodigoDestino);
int obterDistanciaEntreMeioEDestino(Grafo* grafo, const char* geocodigoMeio, const char* geocodigoDestino);
Aresta** encontrarMelhorTrajeto(Grafo* grafo, Meio* meios, const char* pontoPartida, int* tamanhoTrajeto);
void imprimirMelhorTrajeto(Aresta** trajeto, int tamanhoTrajeto, Grafo* grafo);


#endif
