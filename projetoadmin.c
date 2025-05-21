#include <stdio.h>
#include <string.h>
#include "projetoadmin.h"

int loginAdmin() {
    char cpf[TAMANHO_CPF];
    char senha[TAMANHO_SENHA];

    printf("CPF do administrador: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(cpf, "12345678900") == 0 && strcmp(senha, "admin") == 0) {
        return 1;
    } else {
        printf("CPF ou senha incorretos.\n");
        return 0;
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

void salvarUsuarios(Usuario *usuarios, int total) {
    FILE *arquivo = fopen("usuarios.dat", "wb");
    if (arquivo != NULL) {
        fwrite(&total, sizeof(int), 1, arquivo);
        fwrite(usuarios, sizeof(Usuario), total, arquivo);
        fclose(arquivo);
    }
}

void cadastrarInvestidor(Usuario *usuarios, int *totalUsuarios) {
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

    printf("Investidor cadastrado com sucesso.\n");
}
