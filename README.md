
# Projeto4_ExchangeCripto2

João Vitor Alves Escudeiro 24.224.010-9 \
Felipe Pellizzari Vaz Gabriel 24.224.005-9

## Objetivo do projeto

- O projeto tem como principal objetivo o desenvolvimento de um exchange de criptomoedas utilizando a linguagem C. Ele permite que os usuários realizem operações como depósito, saque, compra e venda de criptomoedas, além de consultar saldo e extrato de transações. Agora com 2 programas, um para o investidor, e um para os administradores, o programa do administrador possui funções para manipular criptomoedas e usuários(investidores).


## Forma de compilação e execução do código

- **Para o programa dos administradores:** 
- Para compilar o código do programa do administrador utilize ```gcc mainadmin.c projetoadmin.c projeto.c -o admin``` no terminal.

- Para executar o programa do administrador no terminal utilize ```./admin``` após a compilação.

- **Para o programa dos investidores:**
- Para compilar o código utilize ```gcc main.c projeto.c -o investidor``` no terminal.

- Para executar o projeto no terminal utilize ```./investidor``` após a compilação.


## Forma de uso do programa

- Assim que o programa for executado, ele irá solicitar o login ao usuário utilizando o cpf e a senha.

## Programa do administrador
- **Para fazer testes no programa dos administradores utilize qualquer um dos usuários abaixo:**
- **CPF:** 12345678900  
  **Senha:** admin123

- **CPF:** 12312312300  
  **Senha:** admin321

- Logo após o login bem sucedido, o menu de ações do administrador aparecerá, o usuário pode escolher entre as 8 opções do menu, sendo elas: Cadastrar novo investidor, Excluir investidor, Cadastrar nova criptomoeda, Excluir criptomoeda, Consultar saldo de investidor, Consultar extrato de investidor, Atualizar cotacoes das criptomoedas e Sair


## Programa do investidor
- **Para fazer testes no programa dos investidores utilize qualquer um dos usuários abaixo (é possível adicionar investidores no programa dos administradores):**
- **CPF:** 43805300867  
  **Senha:** 123123

- **CPF:** 11122233344  
  **Senha:** 321321

- Logo após o login bem sucedido, o menu de ações do investidor aparecerá, o usuário pode escolher entre as 8 opções do menu, sendo elas: Consultar saldo, Consultar extrato, Depositar reais, Sacar reais, Comprar criptomoedas, Vender criptomoedas, Atualizar cotacoes das criptomoedas e Sair
