#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "exchange.h"

int autenticarUsuario(Usuario *usuarios, int total, char *cpf, char *senha) {
    for (int i = 0; i < total; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

DataHora DataHoraAtual() {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    DataHora data;
    data.dia = tempoLocal->tm_mday;
    data.mes = tempoLocal->tm_mon + 1;
    data.ano = tempoLocal->tm_year + 1900;
    data.hora = tempoLocal->tm_hour;
    data.min = tempoLocal->tm_min;
    data.seg = tempoLocal->tm_sec;
    return data;
}

double gerarVariacaoAleatoria() {
    double variacao = ((rand() % 1001) - 500) / 10000.0;
    return variacao;
}

