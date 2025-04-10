#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "projeto.h"

int autenticarUsuario(Usuario *usuarios, int total, char *cpf, char *senha) {
    for (int i = 0; i < total; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

DataHora dataHoraAtual() {
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

void salvarUsuarios(Usuario *usuarios, int total) {
    FILE *arquivo = fopen("usuarios.dat", "wb");
    if (arquivo != NULL) {
        fwrite(&total, sizeof(int), 1, arquivo);
        fwrite(usuarios, sizeof(Usuario), total, arquivo);
        fclose(arquivo);
    }
}

int carregarUsuarios(Usuario *usuarios) {
    FILE *arquivo = fopen("usuarios.dat", "rb");
    int total = 0;
    if (arquivo != NULL) {
        fread(&total, sizeof(int), 1, arquivo);
        fread(usuarios, sizeof(Usuario), total, arquivo);
        fclose(arquivo);
    }
    return total;
}

void salvarExtrato(Usuario usuario) {
    char nomeArquivo[30];
    sprintf(nomeArquivo, "extrato_%s.txt", usuario.cpf);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "Extrato do usuário CPF: %s\n", usuario.cpf);
        for (int i = 0; i < usuario.totalTransacoes; i++) {
            Transacao t = usuario.transacoes[i];
            fprintf(arquivo, "%02d/%02d/%04d %02d:%02d:%02d - %s %s | Valor: R$ %.2lf | Taxa: R$ %.2lf | Final: %.6lf\n",
                t.data.dia, t.data.mes, t.data.ano,
                t.data.hora, t.data.min, t.data.seg,
                t.tipoTransacao, t.tipoMoeda, t.valorOperacao, t.taxa, t.valorFinal);
        }
        fclose(arquivo);
    }
}