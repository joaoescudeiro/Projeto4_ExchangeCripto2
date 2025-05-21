#include <stdio.h>
#include <string.h>
#include "projetoadmin.h"

Investidor investidores[INVESTIDORES];
int total_investidores = 0;

Criptomoeda criptomoedas[CRIPTOMOEDAS];
int total_criptomoedas = 0;

int loginAdmin() {
    char cpf[CPF];
    char senha[SENHA];

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