#include <stdio.h>
#include "projetoadmin.h"

Criptomoeda criptos[MAX_CRIPTOS];
int totalCriptos = 0;

int main() {
    Usuario usuarios[MAXIMO_USUARIOS];
    int totalUsuarios = 0;

    totalUsuarios = carregarUsuarios(usuarios);
    totalCriptos = carregarCriptomoedas(criptos);

    if (loginAdmin()) {
        menuAdmin(usuarios, &totalUsuarios);
    } else {
        printf("Acesso negado.\n");
    }

    return 0;
}

void menuAdmin(Usuario *usuarios, int *totalUsuarios) {
    int opcao;
    do {
        printf("\nMenu Administrador\n");
        printf("1. Cadastrar novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Cadastrar nova criptomoeda\n");
        printf("4. Excluir criptomoeda\n");
        printf("5. Consultar saldo de investidor\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarInvestidor(usuarios, totalUsuarios, criptos, totalCriptos);
                break;
            case 2:
                excluirInvestidor(usuarios, totalUsuarios);
                break;
            case 3:
                cadastrarCriptomoeda(criptos, &totalCriptos, usuarios, *totalUsuarios);
                break;
            case 4:
                excluirCriptomoeda(criptos, &totalCriptos, usuarios, *totalUsuarios);
                break;
            case 5:
                consultarSaldoInvestidor(usuarios, *totalUsuarios);
                break;
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    salvarUsuarios(usuarios, *totalUsuarios);
    salvarCriptomoedas(criptos, totalCriptos);
}
