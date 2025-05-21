#ifndef PROJETOINVEST_H
#define PROJETOINVEST_H

#define INVESTIDORES 100
#define CRIPTOMOEDAS 100
#define NOME 50
#define CPF 15
#define SENHA 20

typedef struct {
    char nome[NOME];
    char cpf[CPF];
    char senha[SENHA];
    float saldo;
} Investidor;

typedef struct {
    char nome[NOME];
    float cotacao;
    float taxa_compra;
    float taxa_venda;
} Criptomoeda;

int loginAdmin();
void menuAdmin();

#endif