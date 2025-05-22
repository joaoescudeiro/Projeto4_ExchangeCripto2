#ifndef PROJETOINVEST_H
#define PROJETOINVEST_H

#include "projeto.h"

int loginAdmin();
int carregarUsuarios(Usuario *usuarios);
void salvarUsuarios(Usuario *usuarios, int total);
void menuAdmin(Usuario *usuarios, int *totalUsuarios);
void cadastrarInvestidor(Usuario *usuarios, int *totalUsuarios);
void excluirInvestidor(Usuario *usuarios, int *totalUsuarios);
void adicionarAdmin();

void cadastrarCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios);
void excluirCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios);
void salvarCriptomoedas(Criptomoeda *criptos, int totalCriptos);
int carregarCriptomoedas(Criptomoeda *criptos);

#endif
