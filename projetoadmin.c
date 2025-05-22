#include <stdio.h>
#include <string.h>
#include "projetoadmin.h"
#include "projeto.h"

int carregarAdmins(Admin *admins) {
    FILE *fp = fopen("admins.dat", "rb");
    if (!fp) return 0;

    int total = 0;
    while (fread(&admins[total], sizeof(Admin), 1, fp) == 1) {
        total++;
    }

    fclose(fp);
    return total;
}


int loginAdmin() {
    Admin admins[10];
    int totalAdmins = carregarAdmins(admins);
    char cpf[TAMANHO_CPF], senha[TAMANHO_SENHA];

    printf("Login Admin\nCPF: ");
    scanf("%11s", cpf);
    printf("Senha: ");
    scanf("%19s", senha);

    for (int i = 0; i < totalAdmins; i++) {
        if (strcmp(admins[i].cpf, cpf) == 0 && strcmp(admins[i].senha, senha) == 0) {
            return 1;
        }
    }

    return 0;
}

void adicionarAdmin() {
    Admin novo;
    printf("Digite CPF do admin: ");
    scanf("%11s", novo.cpf);
    printf("Digite senha do admin: ");
    scanf("%19s", novo.senha);

    FILE *fp = fopen("admins.dat", "ab");
    fwrite(&novo, sizeof(Admin), 1, fp);
    fclose(fp);
}

void cadastrarInvestidor(Usuario *usuarios, int *totalUsuarios) {
    if (*totalUsuarios >= MAXIMO_USUARIOS) {
        printf("Limite maximo de usuarios atingido.\n");
        return;
    }

    Usuario novo;
    printf("Cadastro de Investidor\n");
    printf("Digite o nome do investidor (max %d caracteres): ", TAMANHO_NOME - 1);
    scanf(" %[^\n]", novo.nome);

    printf("Digite CPF (max %d caracteres): ", TAMANHO_CPF - 1);
    scanf("%s", novo.cpf);

    
    for (int i = 0; i < *totalUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, novo.cpf) == 0) {
            printf("CPF ja cadastrado.\n");
            return;
        }
    }

    printf("Digite senha (max %d caracteres): ", TAMANHO_SENHA - 1);
    scanf("%s", novo.senha);

    
    novo.totalCriptos = 0;
    for (int i = 0; i < MAX_CRIPTOS; i++) {
        novo.saldos[i].saldo = 0.0;
        novo.saldos[i].nomeCripto[0] = '\0';
    }

    novo.saldoReais = 0.0;
    novo.totalTransacoes = 0;

    usuarios[*totalUsuarios] = novo;
    (*totalUsuarios)++;

    salvarUsuarios(usuarios, *totalUsuarios);
    printf("Investidor cadastrado com sucesso.\n");
}


void excluirInvestidor(Usuario *usuarios, int *totalUsuarios) {
    char cpf[TAMANHO_CPF];
    char confirmacao;
    printf("Digite o CPF do investidor a excluir: ");
    scanf("%s", cpf);

    int pos = -1;
    for (int i = 0; i < *totalUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Investidor nao encontrado.\n");
        return;
    }

    printf("\nInvestidor encontrado:\n");
    printf("CPF: %s\n", usuarios[pos].cpf);
    printf("Nome: %s\n", usuarios[pos].nome);
    printf("Saldo em Reais: R$ %.2lf\n", usuarios[pos].saldoReais);
    printf("Criptomoedas cadastradas: %d\n", usuarios[pos].totalCriptos);

    printf("Deseja realmente excluir este investidor? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Exclusao cancelada.\n");
        return;
    }

    for (int i = pos; i < *totalUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    (*totalUsuarios)--;

    salvarUsuarios(usuarios, *totalUsuarios);
    printf("Investidor excluido com sucesso.\n");
}


void cadastrarCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios) {
    if (*totalCriptos >= MAX_CRIPTOS) {
        printf("Limite maximo de criptomoedas atingido.\n");
        return;
    }

    Criptomoeda nova;
    printf("Cadastro de Criptomoeda\n");
    printf("Digite o nome da criptomoeda (max 19 caracteres): ");
    scanf("%19s", nova.nome);

    for (int i = 0; i < *totalCriptos; i++) {
        if (strcmp(criptos[i].nome, nova.nome) == 0) {
            printf("Criptomoeda ja cadastrada.\n");
            return;
        }
    }

    printf("Digite a cotacao inicial: R$ ");
    scanf("%lf", &nova.cotacao);

    if (nova.cotacao <= 0) {
        printf("Cotacao invalida.\n");
        return;
    }

    printf("Digite a taxa de compra (%%): ");
    scanf("%lf", &nova.taxaCompra);

    printf("Digite a taxa de venda (%%): ");
    scanf("%lf", &nova.taxaVenda);

    criptos[*totalCriptos] = nova;
    (*totalCriptos)++;

    for (int i = 0; i < totalUsuarios; i++) {
        usuarios[i].saldos[usuarios[i].totalCriptos].saldo = 0.0;
        strcpy(usuarios[i].saldos[usuarios[i].totalCriptos].nomeCripto, nova.nome);
        usuarios[i].totalCriptos++;
    }

    salvarCriptomoedas(criptos, *totalCriptos);
    salvarUsuarios(usuarios, totalUsuarios);
    printf("Criptomoeda cadastrada com sucesso.\n");
}

void excluirCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios) {
    if (*totalCriptos == 0) {
        printf("Nao ha criptomoedas cadastradas.\n");
        return;
    }

    char nome[20];
    printf("Digite o nome da criptomoeda a ser excluida: ");
    scanf("%19s", nome);

    int pos = -1;
    for (int i = 0; i < *totalCriptos; i++) {
        if (_stricmp(criptos[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Criptomoeda nao encontrada.\n");
        return;
    }


    printf("\nCriptomoeda encontrada:\n");
    printf("Nome: %s\n", criptos[pos].nome);
    printf("Cotacao: R$ %.2lf\n", criptos[pos].cotacao);
    printf("Taxa de compra: %.2lf%%\n", criptos[pos].taxaCompra);
    printf("Taxa de venda: %.2lf%%\n", criptos[pos].taxaVenda);

    char confirmacao;
    printf("Deseja realmente excluir esta criptomoeda? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Operacao cancelada.\n");
        return;
    }

    for (int i = pos; i < *totalCriptos - 1; i++) {
        criptos[i] = criptos[i + 1];
    }
    (*totalCriptos)--;

    for (int i = 0; i < totalUsuarios; i++) {
        int userPos = -1;
        for (int j = 0; j < usuarios[i].totalCriptos; j++) {
            if (strcmp(usuarios[i].saldos[j].nomeCripto, nome) == 0) {
                userPos = j;
                break;
            }
        }

        if (userPos != -1) {
            for (int j = userPos; j < usuarios[i].totalCriptos - 1; j++) {
                usuarios[i].saldos[j] = usuarios[i].saldos[j + 1];
            }
            usuarios[i].totalCriptos--;
        }
    }

    salvarCriptomoedas(criptos, *totalCriptos);
    salvarUsuarios(usuarios, totalUsuarios);

    printf("Criptomoeda excluida com sucesso.\n");
}
