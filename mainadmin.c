#include <stdio.h>
#include "projetoadmin.h"

int main() {
    Usuario usuarios[MAXIMO_USUARIOS];
    int totalUsuarios = 0;

    totalUsuarios = carregarUsuarios(usuarios);

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
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarInvestidor(usuarios, totalUsuarios);
                break;
            case 2:
                excluirInvestidor(usuarios, totalUsuarios); // chamada da nova função
                break;
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
