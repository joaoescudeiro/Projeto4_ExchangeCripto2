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
    Cotacao cotacao = {250000.0, 15000.0, 5.0};
    int totalUsuarios = carregarUsuarios(usuarios);
    srand(time(NULL));

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
        menuPrincipal(&usuarios[indiceUsuario], &cotacao);
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

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "DEPOSITO");
        strcpy(t.tipoMoeda, "REAL");
        t.valorOperacao = valor;
        t.taxa = 0.0;
        t.valorFinal = valor;

        usuario->transacoes[usuario->totalTransacoes] = t;
        usuario->totalTransacoes++;

        salvarExtrato(*usuario);
    } else {
        printf("Limite de transacoes atingido.\n");
    }
}

void sacarReais(Usuario *usuario){
    double valor;
    char senha[TAMANHO_SENHA];

    printf("Digite o valor que deseja sacar: R$ ");
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("O valor deve ser maior que zero.\n");
        return;
    }

    if (valor > usuario->saldoReais) {
        printf("Saldo insuficiente.", usuario->saldoReais);
        return;
    }

    printf("Digite a sua senha: ");
    scanf("%s", senha);

    if (strcmp(senha, usuario->senha) != 0) {
        printf("Senha incorreta. Saque cancelado.\n");
        return;
    }

    usuario->saldoReais -= valor;
    printf("Saque realizado. Novo saldo em Reais: R$ %.2lf\n", usuario->saldoReais);

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "SAQUE");
        strcpy(t.tipoMoeda, "REAL");
        t.valorOperacao = valor;
        t.taxa = 0.0;
        t.valorFinal = -valor;

        usuario->transacoes[usuario->totalTransacoes] = t;
        usuario->totalTransacoes++;

        salvarExtrato(*usuario);
    } else {
        printf("Limite de transacoes atingido.\n");
    }

}

void comprarCripto(Usuario *usuario, Cotacao cotacao){
    int opcao;
    double valorReais, taxa, valorLiquido, quantidadeComprada;
    char senha[TAMANHO_SENHA];
    char moeda[10];

    printf("\nComprar cripto\n");
    printf("Escolha o tipo que quer comprar:\n");
    printf("1 - Bitcoin (BTC)\n");
    printf("2 - Ethereum (ETH)\n");
    printf("3 - Ripple (XRP)\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    printf("Digite o valor em reais que quer investir: R$ ");
    scanf("%lf", &valorReais);

    if (valorReais <= 0 || valorReais > usuario->saldoReais) {
        printf("Valor invalido ou saldo insuficiente.\n");
        return;
    }

    printf("Digite a sua senha: ");
    scanf("%s", senha);

    if (strcmp(senha, usuario->senha) != 0) {
        printf("Senha incorreta. Compra cancelada.\n");
        return;
    }

    switch (opcao) {
        case 1:
            taxa = valorReais * 0.02;
            valorLiquido = valorReais - taxa;
            quantidadeComprada = valorLiquido / cotacao.cotacaoBTC;
            usuario->saldoBTC += quantidadeComprada;
            strcpy(moeda, "BTC");
            break;
        case 2:
            taxa = valorReais * 0.01;
            valorLiquido = valorReais - taxa;
            quantidadeComprada = valorLiquido / cotacao.cotacaoETH;
            usuario->saldoETH += quantidadeComprada;
            strcpy(moeda, "ETH");
            break;
        case 3:
            taxa = valorReais * 0.01;
            valorLiquido = valorReais - taxa;
            quantidadeComprada = valorLiquido / cotacao.cotacaoXRP;
            usuario->saldoXRP += quantidadeComprada;
            strcpy(moeda, "XRP");
            break;
        default:
            printf("Opcao invalida.\n");
            return;
    }

    printf("\nConfirme a compra:\n");
    printf("Moeda: %s\n", moeda);
    printf("Cotacao atual: R$ %.2lf\n", 
           (opcao == 1 ? cotacao.cotacaoBTC : (opcao == 2 ? cotacao.cotacaoETH : cotacao.cotacaoXRP)));
    printf("Valor investido: R$ %.2lf\n", valorReais);
    printf("Taxa cobrada: R$ %.2lf\n", taxa);
    printf("Quantidade comprada: %.6lf %s\n", quantidadeComprada, moeda);

    char confirmacao;
    printf("Deseja confirmar a compra? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Compra cancelada.\n");
        if (strcmp(moeda, "BTC") == 0) usuario->saldoBTC -= quantidadeComprada;
        else if (strcmp(moeda, "ETH") == 0) usuario->saldoETH -= quantidadeComprada;
        else if (strcmp(moeda, "XRP") == 0) usuario->saldoXRP -= quantidadeComprada;
        return;
    }

    usuario->saldoReais -= valorReais;
    printf("Compra realizada.\n");

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "COMPRA");
        strcpy(t.tipoMoeda, moeda);
        t.valorOperacao = valorReais;
        t.taxa = taxa;
        t.valorFinal = quantidadeComprada;

        usuario->transacoes[usuario->totalTransacoes] = t;
        usuario->totalTransacoes++;

        salvarExtrato(*usuario);
    } else {
        printf("Limite de transacoes atingido.\n");
    }
}

void venderCripto(Usuario *usuario, Cotacao cotacao){
    int opcao;
    double valorReais, taxa, valorLiquido, quantidadeVender;
    char senha[TAMANHO_SENHA];
    char moeda[10];
    double cotacaoAtual = 0.0;

    printf("\nVender cripto\n");
    printf("Escolha o tipo que quer vender:\n");
    printf("1 - Bitcoin (BTC)\n");
    printf("2 - Ethereum (ETH)\n");
    printf("3 - Ripple (XRP)\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    printf("Digite o valor que deseja vender em reais: R$ ");
    scanf("%lf", &valorReais);

    printf("Digite a sua senha: ");
    scanf("%s", senha);
    if (strcmp(senha, usuario->senha) != 0) {
        printf("Senha incorreta. Venda cancelada.\n");
        return;
    }

    switch (opcao) {
        case 1:
            cotacaoAtual = cotacao.cotacaoBTC;
            taxa = valorReais * 0.03;
            valorLiquido = valorReais - taxa;
            quantidadeVender = valorReais / cotacaoAtual;
            if (quantidadeVender > usuario->saldoBTC) {
                printf("Saldo insuficiente de BTC.\n");
                return;
            }
            usuario->saldoBTC -= quantidadeVender;
            strcpy(moeda, "BTC");
            break;
        case 2:
            cotacaoAtual = cotacao.cotacaoETH;
            taxa = valorReais * 0.02;
            valorLiquido = valorReais - taxa;
            quantidadeVender = valorReais / cotacaoAtual;
            if (quantidadeVender > usuario->saldoETH) {
                printf("Saldo insuficiente de ETH.\n");
                return;
            }
            usuario->saldoETH -= quantidadeVender;
            strcpy(moeda, "ETH");
            break;
        case 3:
            cotacaoAtual = cotacao.cotacaoXRP;
            taxa = valorReais * 0.01;
            valorLiquido = valorReais - taxa;
            quantidadeVender = valorReais / cotacaoAtual;
            if (quantidadeVender > usuario->saldoXRP) {
                printf("Saldo insuficiente de XRP.\n");
                return;
            }
            usuario->saldoXRP -= quantidadeVender;
            strcpy(moeda, "XRP");
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }

    printf("\nConfirme a venda:\n");
    printf("Moeda: %s\n", moeda);
    printf("Cotacao atual: R$ %.2lf\n", cotacaoAtual);
    printf("Valor da venda: R$ %.2lf\n", valorReais);
    printf("Taxa de venda: R$ %.2lf\n", taxa);
    printf("Valor liquido a receber: R$ %.2lf\n", valorLiquido);
    printf("Quantidade de %s vendida: %.6lf\n", moeda, quantidadeVender);

    char confirmacao;
    printf("Deseja confirmar a venda? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Venda cancelada.\n");
        if (strcmp(moeda, "BTC") == 0) usuario->saldoBTC += quantidadeVender;
        else if (strcmp(moeda, "ETH") == 0) usuario->saldoETH += quantidadeVender;
        else if (strcmp(moeda, "XRP") == 0) usuario->saldoXRP += quantidadeVender;
        return;
    }

    usuario->saldoReais += valorLiquido;
    printf("Venda realizada.\n");

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "VENDA");
        strcpy(t.tipoMoeda, moeda);
        t.valorOperacao = valorReais;
        t.taxa = taxa;
        t.valorFinal = valorLiquido;

        usuario->transacoes[usuario->totalTransacoes] = t;
        usuario->totalTransacoes++;

        salvarExtrato(*usuario);
    } else {
        printf("Limite de transacoes atingido.\n");
    }
}

void atualizarCotacoes(Cotacao *cotacao){
    printf("\nAtualizar cotacoes\n");

    double variacao;

    variacao = gerarVariacaoAleatoria();
    double anteriorBTC = cotacao->cotacaoBTC;
    cotacao->cotacaoBTC *= (1 + variacao);
    printf("BTC: R$ %.2lf -> R$ %.2lf (%.2lf%%)\n", anteriorBTC, cotacao->cotacaoBTC, variacao * 100);

    variacao = gerarVariacaoAleatoria();
    double anteriorETH = cotacao->cotacaoETH;
    cotacao->cotacaoETH *= (1 + variacao);
    printf("ETH: R$ %.2lf -> R$ %.2lf (%.2lf%%)\n", anteriorETH, cotacao->cotacaoETH, variacao * 100);

    variacao = gerarVariacaoAleatoria();
    double anteriorXRP = cotacao->cotacaoXRP;
    cotacao->cotacaoXRP *= (1 + variacao);
    printf("XRP: R$ %.2lf -> R$ %.2lf (%.2lf%%)\n", anteriorXRP, cotacao->cotacaoXRP, variacao * 100);
}

void consultarExtrato(Usuario usuario){
    printf("\nExtrato\n");
    printf("CPF: %s\n", usuario.cpf);
    printf("Total de transacoes: %d\n", usuario.totalTransacoes);

    if (usuario.totalTransacoes == 0) {
        printf("Nenhuma transacao registrada.\n");
        return;
    }

    for (int i = 0; i < usuario.totalTransacoes; i++) {
        Transacao t = usuario.transacoes[i];
        printf("%02d/%02d/%04d %02d:%02d:%02d - %s %s | Valor: R$ %.2lf | Taxa: R$ %.2lf | Final: %.6lf\n",
               t.data.dia, t.data.mes, t.data.ano,
               t.data.hora, t.data.min, t.data.seg,
               t.tipoTransacao, t.tipoMoeda,
               t.valorOperacao, t.taxa, t.valorFinal);
    }
}