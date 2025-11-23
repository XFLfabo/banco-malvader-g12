#ifndef CONTA_H
#define CONTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constantes
#define MAX_CONTAS 100
#define MAX_NOME 50
#define MAX_CPF 12
#define MAX_TELEFONE 15
#define MAX_AGENCIA 5
#define MAX_DATA_NASCIMENTO 11
#define MAX_ENDERECO 100
#define MAX_CEP 10
#define MAX_NUMERO_CASA 4
#define MAX_BAIRRO 50
#define MAX_CIDADE 50
#define MAX_ESTADO 3

//Enum para o status da conta
typedef enum {
    ATIVA,
    ENCERRADA
} StatusConta;

//Estrutura para a conta bancária
typedef struct {
    int numero;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char telefone[MAX_TELEFONE];
    char agencia[MAX_AGENCIA];
    char data_nascimento[MAX_DATA_NASCIMENTO];
    char endereco[MAX_ENDERECO];
    char cep[MAX_CEP];
    char numero_casa[MAX_NUMERO_CASA];
    char bairro[MAX_BAIRRO];
    char cidade[MAX_CIDADE];
    char estado[MAX_ESTADO];
    double saldo;
    StatusConta status;
} ContaBancaria;

//Variáveis globais (simulando o armazenamento em memória)
extern ContaBancaria contas[MAX_CONTAS];
extern int proximo_numero_conta;
extern int total_contas;

//protótipos das funções de operações bancárias 
void abrir_conta();
void depositar();
void sacar();
void transferir();
void atualizar_dados();
void encerrar_conta();

#endif // CONTA_H

 





