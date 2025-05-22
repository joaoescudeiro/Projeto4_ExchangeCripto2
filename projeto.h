#ifndef EXCHANGE_H
#define EXCHANGE_H

#define MAXIMO_USUARIOS 10
#define MAXIMO_TRANSACOES 100
#define TAMANHO_NOME 50
#define TAMANHO_CPF 12
#define TAMANHO_SENHA 20
#define MAX_CRIPTOS 20

typedef struct {
    int dia, mes, ano, hora, min, seg;
} DataHora;

typedef struct {
    DataHora data;
    char tipoTransacao[10];
    char tipoMoeda[20];
    double valorOperacao;
    double taxa;
    double valorFinal;
} Transacao;

typedef struct {
    char nome[20];
    double cotacao;
    double taxaCompra;
    double taxaVenda;
} Criptomoeda;

typedef struct {
    char nomeCripto[20];
    double saldo;
} SaldoCripto;

typedef struct {
    char nome[TAMANHO_NOME];
    char cpf[TAMANHO_CPF];
    char senha[TAMANHO_SENHA];
    SaldoCripto saldos[MAX_CRIPTOS];
    int totalCriptos;           
    double saldoReais;          
    Transacao transacoes[MAXIMO_TRANSACOES];
    int totalTransacoes;
} Usuario;

typedef struct {
    char cpf[TAMANHO_CPF];
    char senha[TAMANHO_SENHA];
} Admin;

int autenticarUsuario(Usuario *usuarios, int total, char *cpf, char *senha);
void salvarUsuarios(Usuario *usuarios, int total);
int carregarUsuarios(Usuario *usuarios);
void salvarExtrato(Usuario usuario);

void cadastrarCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios);
void salvarCriptomoedas(Criptomoeda *criptos, int total);
int carregarCriptomoedas(Criptomoeda *criptos);

DataHora dataHoraAtual();
double gerarVariacaoAleatoria(double cotacaoAtual);

#endif
