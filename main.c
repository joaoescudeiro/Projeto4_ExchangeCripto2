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
void menuPrincipal(Usuario *usuario, Cotacao *cotacao);
void exibirSaldo(Usuario usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario, Cotacao cotacao);
void venderCripto(Usuario *usuario, Cotacao cotacao);
void atualizarCotacoes(Cotacao *cotacao);
void consultarExtrato(Usuario usuario);


void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios) {
    if (*totalUsuarios >= MAXIMO_USUARIOS) {
        printf("Limite maximo de usuarios atingido.\n");
        return;
    }

    Usuario novo;
    printf("Cadastro de Usuario\n");
    printf("Digite o CPF: ");
    scanf("%s", novo.cpf);

    for (int i = 0; i < *totalUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, novo.cpf) == 0) {
            printf("CPF ja cadastrado. Tente novamente.\n");
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

    printf("Usuario cadastrado com sucesso.\n");
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
        printf("CPF ou senha invalidos.\n");
    }
    return 0;
}

void menuPrincipal(Usuario *usuario, Cotacao *cotacao) {
    int opcao;
    do {
        printf("\nMenu\n");
        printf("1. Consultar saldo\n");
        printf("2. Consultar extrato\n");
        printf("3. Depositar reais\n");
        printf("4. Sacar reais\n");
        printf("5. Comprar criptomoedas\n");
        printf("6. Vender criptomoedas\n");
        printf("7. Atualizar cotacoes das criptomoedas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirSaldo(*usuario);
                break;
            case 2:
                consultarExtrato(*usuario);
                break;
            case 3:
                depositarReais(usuario);
                break;
            case 4:
                sacarReais(usuario);
                break;
            case 5:
                comprarCripto(usuario, *cotacao);
                break;
            case 6:
                venderCripto(usuario, *cotacao);
                break;
            case 7:
                atualizarCotacoes(cotacao);
                break;
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

void exibirSaldo(Usuario usuario){
    printf("\nConsulta saldo:\n");
    printf("CPF: %s\n", usuario.cpf);
    printf("Reais (BRL): R$ %.2lf\n", usuario.saldoReais);
    printf("Bitcoin (BTC): %.5lf BTC\n", usuario.saldoBTC);
    printf("Ethereum (ETH): %.5lf ETH\n", usuario.saldoETH);
    printf("Ripple (XRP): %.5lf XRP\n", usuario.saldoXRP);
}

void depositarReais(Usuario *usuario){
    double valor;

    printf("Digite o valor que deseja depositar: R$ ");
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("O valor deve ser maior que zero.\n");
        return;
    }

    usuario->saldoReais += valor;
    printf("Deposito realizado. Novo saldo em Reais: R$ %.2lf\n", usuario->saldoReais);
}

void sacarReais(Usuario *usuario){

}

void comprarCripto(Usuario *usuario, Cotacao cotacao){

}

void venderCripto(Usuario *usuario, Cotacao cotacao){

}

void atualizarCotacoes(Cotacao *cotacao){

}

void consultarExtrato(Usuario usuario){

}