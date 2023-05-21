/**
 * @file aluguer.c
 * @author lugon (a18851@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <time.h>
#include <math.h>
#include "aluguer.h"
#include "../pontos.h"
#include <Curl/curl.h>


Data getDate() {
    Data dataAtual;

    // Obtém o timestamp atual
    time_t timestamp = time(NULL);

    // Converte o timestamp para uma estrutura tm local
    struct tm *local_time = localtime(&timestamp);

    // Preenche os componentes da data atual
    dataAtual.ano = local_time->tm_year + 1900;
    dataAtual.mes = local_time->tm_mon + 1;
    dataAtual.dia = local_time->tm_mday;

    return dataAtual;
}

// Função para fazer a chamada HTTP GET usando a biblioteca curl
size_t curl_callback(void *conteudo, size_t tamanho, size_t nmemb, char *output) {
    memcpy(output, conteudo, tamanho * nmemb);
    return tamanho * nmemb;
}



// Função para converter o geocódigo em coordenadas geográficas usando a API do what3words
int converterParaCoordenadas(const char *geocodigo, double *latitude, double *longitude, const char *apiKey) {
    CURL *curl;
    CURLcode res;
    char url[200];
    char resposta[500];

    sprintf(url, "https://api.what3words.com/v3/convert-to-coordinates?words=%s&key=%s", geocodigo, apiKey);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, resposta);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            printf("Erro ao fazer a chamada HTTP: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
    } else {
        printf("Erro ao inicializar o objeto CURL.\n");
        curl_global_cleanup();
        return 1;
    }

    // Analisar a resposta JSON para obter as coordenadas
    // Você precisará usar uma biblioteca de análise JSON adequada aqui

    // Preencher as variáveis de latitude e longitude com os valores obtidos

    return 0;
}

// Função para calcular a distância entre duas coordenadas geográficas
double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    // Fórmula de Haversine para calcular a distância entre duas coordenadas
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distancia = 6371 * c;

    return distancia;
}

// Função para encontrar o ponto de recolha mais próximo com base nas coordenadas fornecidas
PontoRecolha *encontrarPontoRecolhaMaisProximo(double latitude, double longitude, PontoRecolha *listaPontosRecolha) {
    PontoRecolha *pontoMaisProximo = NULL;
    double menorDistancia = INFINITY;

    PontoRecolha *pontoAtual = listaPontosRecolha;
    while (pontoAtual != NULL) {
        double pontoLatitude, pontoLongitude;
        // Obter as coordenadas do ponto de recolha atual
        if (converterParaCoordenadas(pontoAtual->geocodigo, &pontoLatitude, &pontoLongitude, "sua-chave-de-api") == 0) {
            // Calcular a distância entre as coordenadas fornecidas e as coordenadas do ponto de recolha atual
            double distancia = calcularDistancia(latitude, longitude, pontoLatitude, pontoLongitude);

            // Verificar se a distância é menor do que a menor distância atual
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                pontoMaisProximo = pontoAtual;
            }
        }

        pontoAtual = pontoAtual->proximo;
    }

    return pontoMaisProximo;
}




    