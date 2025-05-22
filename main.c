#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"

extern int autenticarUsuario(Usuario *usuarios, int total, char *cpf, char *senha);
extern void salvarUsuarios(Usuario *usuarios, int total);
extern int carregarUsuarios(Usuario *usuarios);
extern void salvarExtrato(Usuario usuario);
extern int carregarCriptomoedas(Criptomoeda *criptos);
extern void salvarCriptomoedas(Criptomoeda *criptos, int total);

extern DataHora dataHoraAtual();
extern double gerarVariacaoAleatoria();

void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios, Criptomoeda *criptos, int totalCriptos);
void menuPrincipal(Usuario *usuario, Criptomoeda *criptos, int totalCriptos);
void exibirSaldo(Usuario usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario, Criptomoeda *criptos, int totalCriptos);
void venderCripto(Usuario *usuario, Criptomoeda *criptos, int totalCriptos);
void atualizarCotacoes(Criptomoeda *criptos, int totalCriptos);
void consultarExtrato(Usuario usuario);

int main() {
    Usuario usuarios[MAXIMO_USUARIOS];
    Criptomoeda criptos[MAX_CRIPTOS];
    int totalUsuarios = carregarUsuarios(usuarios);
    int totalCriptos = carregarCriptomoedas(criptos);

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
        menuPrincipal(&usuarios[indiceUsuario], criptos, totalCriptos);
        salvarUsuarios(usuarios, totalUsuarios);
    } else {
        printf("CPF ou senha invalidos.\n");
    }

    return 0;
}

void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios, Criptomoeda *criptos, int totalCriptos) {
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
    novo.totalTransacoes = 0;

    novo.totalCriptos = totalCriptos < MAX_CRIPTOS ? totalCriptos : MAX_CRIPTOS;

    for (int i = 0; i < novo.totalCriptos; i++) {
        strcpy(novo.saldos[i].nomeCripto, criptos[i].nome);
        novo.saldos[i].saldo = 0.0;
    }

    usuarios[*totalUsuarios] = novo;
    (*totalUsuarios)++;

    salvarUsuarios(usuarios, *totalUsuarios);

    printf("Usuario cadastrado com sucesso.\n");
}

void menuPrincipal(Usuario *usuario, Criptomoeda *criptos, int totalCriptos) {
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
                comprarCripto(usuario, criptos, totalCriptos);
                break;
            case 6:
                venderCripto(usuario, criptos, totalCriptos);
                break;
            case 7:
                atualizarCotacoes(criptos, totalCriptos);
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

    for (int i = 0; i < usuario.totalCriptos; i++) {
        printf("%s: %.6lf %s\n", usuario.saldos[i].nomeCripto, usuario.saldos[i].saldo, usuario.saldos[i].nomeCripto);
    }
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
        printf("Saldo insuficiente.\n");
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

void comprarCripto(Usuario *usuario, Criptomoeda *criptos, int totalCriptos){
    int opcao;
    double valorReais, taxa, valorLiquido, quantidadeComprada;
    char senha[TAMANHO_SENHA];
    int indiceMoeda = -1;

    printf("\nComprar cripto\n");
    printf("Escolha o tipo que quer comprar:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%d - %s (R$ %.2lf)\n", i+1, criptos[i].nome, criptos[i].cotacao);
    }
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > totalCriptos) {
        printf("Opcao invalida.\n");
        return;
    }
    indiceMoeda = opcao - 1;

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

    if (strcmp(criptos[indiceMoeda].nome, "BTC") == 0) {
        taxa = valorReais * 0.02;
    } else {
        taxa = valorReais * 0.01;
    }

    valorLiquido = valorReais - taxa;

    quantidadeComprada = valorLiquido / criptos[indiceMoeda].cotacao;

    int encontrou = 0;
    for (int i = 0; i < usuario->totalCriptos; i++) {
        if (strcmp(usuario->saldos[i].nomeCripto, criptos[indiceMoeda].nome) == 0) {
            usuario->saldos[i].saldo += quantidadeComprada;
            encontrou = 1;
            break;
        }
    }
    if (!encontrou) {
        printf("Erro: criptomoeda nao cadastrada para usuario.\n");
        return;
    }

    printf("\nConfirme a compra:\n");
    printf("Moeda: %s\n", criptos[indiceMoeda].nome);
    printf("Cotacao atual: R$ %.2lf\n", criptos[indiceMoeda].cotacao);
    printf("Valor investido: R$ %.2lf\n", valorReais);
    printf("Taxa cobrada: R$ %.2lf\n", taxa);
    printf("Quantidade comprada: %.6lf %s\n", quantidadeComprada, criptos[indiceMoeda].nome);

    char confirmacao;
    printf("Deseja confirmar a compra? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        for (int i = 0; i < usuario->totalCriptos; i++) {
            if (strcmp(usuario->saldos[i].nomeCripto, criptos[indiceMoeda].nome) == 0) {
                usuario->saldos[i].saldo -= quantidadeComprada;
                break;
            }
        }
        printf("Compra cancelada.\n");
        return;
    }

    usuario->saldoReais -= valorReais;
    printf("Compra realizada.\n");

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "COMPRA");
        strcpy(t.tipoMoeda, criptos[indiceMoeda].nome);
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

void venderCripto(Usuario *usuario, Criptomoeda *criptos, int totalCriptos){
    int opcao;
    double valorReais, taxa, valorLiquido, quantidadeVender;
    char senha[TAMANHO_SENHA];
    int indiceMoeda = -1;

    printf("\nVender cripto\n");
    printf("Escolha o tipo que quer vender:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%d - %s (R$ %.2lf)\n", i+1, criptos[i].nome, criptos[i].cotacao);
    }
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > totalCriptos) {
        printf("Opcao invalida.\n");
        return;
    }
    indiceMoeda = opcao - 1;

    printf("Digite o valor em reais que deseja receber: R$ ");
    scanf("%lf", &valorReais);

    if (valorReais <= 0) {
        printf("Valor invalido.\n");
        return;
    }

    printf("Digite a sua senha: ");
    scanf("%s", senha);

    if (strcmp(senha, usuario->senha) != 0) {
        printf("Senha incorreta. Venda cancelada.\n");
        return;
    }

    quantidadeVender = valorReais / criptos[indiceMoeda].cotacao;

    int encontrou = 0;
    for (int i = 0; i < usuario->totalCriptos; i++) {
        if (strcmp(usuario->saldos[i].nomeCripto, criptos[indiceMoeda].nome) == 0) {
            if (usuario->saldos[i].saldo < quantidadeVender) {
                printf("Saldo insuficiente da criptomoeda para venda.\n");
                return;
            } else {
                usuario->saldos[i].saldo -= quantidadeVender;
                encontrou = 1;
                break;
            }
        }
    }
    if (!encontrou) {
        printf("Erro: criptomoeda nao cadastrada para usuario.\n");
        return;
    }

    if (strcmp(criptos[indiceMoeda].nome, "BTC") == 0) {
        taxa = valorReais * 0.02;
    } else {
        taxa = valorReais * 0.01;
    }

    valorLiquido = valorReais - taxa;
    usuario->saldoReais += valorLiquido;

    printf("\nVenda realizada.\n");
    printf("Valor bruto: R$ %.2lf\n", valorReais);
    printf("Taxa cobrada: R$ %.2lf\n", taxa);
    printf("Valor liquido recebido: R$ %.2lf\n", valorLiquido);

    if (usuario->totalTransacoes < MAXIMO_TRANSACOES) {
        Transacao t;
        t.data = dataHoraAtual();
        strcpy(t.tipoTransacao, "VENDA");
        strcpy(t.tipoMoeda, criptos[indiceMoeda].nome);
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

void atualizarCotacoes(Criptomoeda *criptos, int totalCriptos) {
    for (int i = 0; i < totalCriptos; i++) {
        double variacao = gerarVariacaoAleatoria(criptos[i].cotacao);
        criptos[i].cotacao += variacao;
        if (criptos[i].cotacao < 0.01) criptos[i].cotacao = 0.01;
    }

    printf("\nCotacoes atualizadas:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%s: R$ %.2lf\n", criptos[i].nome, criptos[i].cotacao);
    }

    salvarCriptomoedas(criptos, totalCriptos);
}

void consultarExtrato(Usuario usuario) {
    printf("\nExtrato de transacoes para CPF: %s\n", usuario.cpf);
    if (usuario.totalTransacoes == 0) {
        printf("Nenhuma transacao realizada.\n");
        return;
    }

    for (int i = 0; i < usuario.totalTransacoes; i++) {
        Transacao t = usuario.transacoes[i];
        printf("%02d/%02d/%04d %02d:%02d:%02d - %s %s R$ %.2lf Taxa: R$ %.2lf Valor Final: %.6lf\n",
            t.data.dia, t.data.mes, t.data.ano, t.data.hora, t.data.min, t.data.seg,
            t.tipoTransacao, t.tipoMoeda, t.valorOperacao, t.taxa, t.valorFinal);
    }
}
