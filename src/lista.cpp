#include "lista.h"

//Variáveis globais (simulando o armazenamento em memória)
ContaBancaria contas[MAX_CONTAS];
int proximo_numero_conta = 1001;
int total_contas = 0;

//Função auxiliar para buscar conta por número
//Retorna o índice da conta no vetor ou -1 se não encontrar
int buscar_conta_por_numero(int numero){
    for(int i = 0; i < total_contas; i++){
        if(contas[i].numero == numero){
            return i;
        }
    }
    return -1;
}

//Função auxiliar para buscar conta por CPF
//Retorna o índice da conta no vetor ou -1 se não encontrar
int buscar_conta_por_cpf(const char* cpf){
    for(int i = 0; i < total_contas; i++){
        if(strcmp(contas[i].cpf, cpf) == 0){
            return i;
        }
    }
    return -1;
}
 
//Função auxiliar para validar se o CPF já existe (para abertura de conta)
//Retorna 1 se o CPF for único, 0 se já existir
int validar_cpf_unico(const char *cpf){
    for(int i = 0; i < total_contas; i++){
        if(strcmp(contas[i].cpf, cpf) == 0){
            return 0; // CPF já existe
        }
    }
    return 1; // CPF é único
}