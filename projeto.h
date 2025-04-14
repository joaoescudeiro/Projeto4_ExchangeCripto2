#ifndef EXCHANGE_H
#define EXCHANGE_H

#define MAXIMO_USUARIOS 10
#define MAXIMO_TRANSACOES 100
#define TAMANHO_CPF 12
#define TAMANHO_SENHA 20

typedef struct {
    int dia, mes, ano, hora, min, seg;
} DataHora;

typedef struct {
    DataHora data;
    char tipoTransacao[10];
    char tipoMoeda[10];
    double valorOperacao;
    double taxa;
    double valorFinal;
} Transacao;

typedef struct {
    char cpf[TAMANHO_CPF];
    char senha[TAMANHO_SENHA];
    double saldoReais;
    double saldoBTC;
    double saldoETH;
    double saldoXRP;
    Transacao transacoes[MAXIMO_TRANSACOES];
    int totalTransacoes;
} Usuario;

typedef struct {
    double cotacaoBTC;
    double cotacaoETH;
    double cotacaoXRP;
} Cotacao;

#endif