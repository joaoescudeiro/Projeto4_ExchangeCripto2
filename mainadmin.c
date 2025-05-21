#include <stdio.h>
#include "projetoadmin.h"

int main() {
    if (loginAdmin()) {
        menuAdmin();
    } else {
        printf("Acesso negado.\n");
    }
    return 0;
}

void menuAdmin() {
    int opcao;
    do {
        printf("\nMenu Administrador\n");

        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                break;
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}