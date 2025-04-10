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

void menuPrincipal(Usuario *usuario, Mercado *mercado);
void exibirSaldo(Usuario usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario, Mercado mercado);
void venderCripto(Usuario *usuario, Mercado mercado);
void atualizarCotacoes(Mercado *mercado);
void consultarExtrato(Usuario usuario);
void cadastrarUsuario(Usuario *usuarios, int *totalUsuarios);