#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"

extern int autenticarUsuario(Usuario *, int, char *, char *);
extern DataHora dataHoraAtual();
extern double gerarVariacaoAleatoria();
extern void salvarUsuarios(Usuario *, int);
extern int carregarUsuarios(Usuario *);
extern void salvarExtrato(Usuario);

void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios);
void menuPrincipal(Usuario *usuario, Mercado *mercado);
void exibirSaldo(Usuario usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario, Mercado mercado);
void venderCripto(Usuario *usuario, Mercado mercado);
void atualizarCotacoes(Mercado *mercado);
void consultarExtrato(Usuario usuario);


void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios) {
    if (*totalUsuarios >= MAXIMO_USUARIOS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }

    Usuario novo;
    printf("Cadastro de Usuário\n");
    printf("Digite o CPF: ");
    scanf("%s", novo.cpf);

    for (int i = 0; i < *totalUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, novo.cpf) == 0) {
            printf("CPF já cadastrado. Tente novamente.\n");
            return;
        }
    }

    printf("Digite a senha: ");
    scanf("%s", novo.senha);

    novo.saldoReais = 0.0;
    novo.saldoBTC = 0.0;
    novo.saldoETH = 0.0;
    novo.saldoXRP = 0.0;
    novo.totalTransacoes = 0;

    usuarios[*totalUsuarios] = novo;
    (*totalUsuarios)++;

    salvarUsuarios(usuarios, *totalUsuarios);

    printf("Usuário cadastrado com sucesso.\n");
}

int main() {
    Usuario usuarios[MAXIMO_USUARIOS];
    Cotacao mercado = {250000.0, 15000.0, 5.0};
    int totalUsuarios = carregarUsuarios(usuarios);

    char cpf[TAMANHO_CPF];
    char senha[TAMANHO_SENHA];
    int indiceUsuario;

    printf("Exchange de Criptomoedas\n");
    printf("Digite o seu CPF: ");
    scanf("%s", cpf);
    printf("Digite a sua senha: ");
    scanf("%s", senha);

    indiceUsuario = autenticarUsuario(usuarios, totalUsuarios, cpf, senha);

    if (indiceUsuario != -1) {
        printf("Login realizado com sucesso.\n");
        menuPrincipal(&usuarios[indiceUsuario], &mercado);
        salvarUsuarios(usuarios, totalUsuarios);
    } else {
        printf("CPF ou senha inválidos.\n");
    }
    return 0;
}