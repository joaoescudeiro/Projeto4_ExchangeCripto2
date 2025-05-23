#ifndef PROJETOINVEST_H
#define PROJETOINVEST_H

#include "projeto.h"

int loginAdmin();
int carregarUsuarios(Usuario *usuarios);
void salvarUsuarios(Usuario *usuarios, int total);
void menuAdmin(Usuario *usuarios, int *totalUsuarios);
void cadastrarInvestidor(Usuario *usuarios, int *totalUsuarios, Criptomoeda *criptos, int totalCriptos);
void excluirInvestidor(Usuario *usuarios, int *totalUsuarios);
void adicionarAdmin();

void cadastrarCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios);
void excluirCriptomoeda(Criptomoeda *criptos, int *totalCriptos, Usuario *usuarios, int totalUsuarios);
void salvarCriptomoedas(Criptomoeda *criptos, int totalCriptos);
int carregarCriptomoedas(Criptomoeda *criptos);
void consultarSaldoInvestidor(Usuario *usuarios, int totalUsuarios);
void consultarExtratoInvestidor();
void atualizarCotacoes(Criptomoeda *criptos, int totalCriptos);

#endif
