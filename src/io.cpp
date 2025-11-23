#include "io.h"
#include "lista.h"

//Função auxiliar para exibir os dados de uma conta
void exibir_dados_conta(int indice){
    if(indice < 0 || indice >= total_contas){
        printf("ERRO: Índice de conta inválido.\n");
        return;
    }

    printf("\n--- Dados da Conta ---\n");
    printf("Número da Conta: %d\n", contas[indice].numero);
    printf("Nome: %s\n", contas[indice].nome);
    printf("CPF: %s\n", contas[indice].cpf);
    printf("Telefone: %s\n", contas[indice].telefone);
    printf("Agência: %s\n", contas[indice].agencia);
    printf("Data de Nascimento: %s\n", contas[indice].data_nascimento);   
    printf("CEP: %s\n", contas[indice].cep);
    printf("Número da Casa: %s\n", contas[indice].numero_casa);
    printf("Bairro: %s\n", contas[indice].bairro);
    printf("Cidade: %s\n", contas[indice].cidade);
    printf("Estado: %s\n", contas[indice].estado);
    printf("Saldo: R$ %.2f\n", contas[indice].saldo);
    printf("Status: %s\n", contas[indice].status == ATIVA ? "Ativa" : "Encerrada");
    printf("----------------------\n");
}

//Função para listar contas
void listar_contas(int filtro){
    printf("\n--- Listagem de Contas ---\n");
    int encontradas = 0;

    for(int i = 0; i < total_contas; i++){
        //O filtro -1 significa "todas"
        if(filtro == -1 || contas[i].status == filtro){
            printf("conta %d | Nome: %s |CPF: %s |Agência: %s | Saldo: R$ %.2f | Status: %s\n",
                   contas[i].numero,
                   contas[i].nome,
                   contas[i].cpf,
                   contas[i].agencia,
                   contas[i].saldo,
                   contas[i].status == ATIVA ? "ATIVA" : "ENCERRADA");
            encontradas++;
        }
    }
    
    if(encontradas == 0){
        if(filtro == ATIVA) printf("Nenhuma conta ATIVA encontrada.\n");
        else if (filtro == ENCERRADA) printf("Nenhuma conta ENCERRADA encontrada.\n");
        else printf("Nenhuma conta cadastrada.\n");
    }
    printf("---------------------------\n");
}

//Função para consultar saldo e dados
void consultar_saldo_e_dados(){
    int tipo_busca;
    printf("\n--- Consulta de Saldo e Dados ---\n");
    printf("Buscar por:\n");
    printf("1. Número da Conta\n");
    printf("2. CPF\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &tipo_busca) != 1){
        while(getchar() != '\n');
        printf("ERRO: Opção de busca inválida.\n");
        return;
    }
    while (getchar() != '\n');

    int indice = -1;

    if(tipo_busca == 1){
        int numero;
        printf("Digite o número da conta: ");
        if (scanf("%d", &numero) != 1){
            while(getchar() != '\n');
            printf("ERRO: Entrada inválida para o número da conta.\n");
            return;
        }
        while(getchar() != '\n');
        indice = buscar_conta_por_numero(numero);
    } else if (tipo_busca == 2){
        char cpf[MAX_CPF];
        printf("Digite o CPF:");
        scanf("%s", cpf);
        while(getchar()!= '\n');
        indice = buscar_conta_por_cpf(cpf);
    } else{
        printf("ERRO: Opção de busca inválida.\n");
        return;
    }
     
    if(indice != -1){
        exibir_dados_conta(indice);
    } else{
        printf("ERRO: Conta não encontrada.\n");
    }
}

//Funções de menu (implementadas no main.cpp, mas o protótipo está aqui)
void exibir_menu() {
    printf("\n--- Sistema Bancário Simples ---\n");
    printf("1. Abrir Conta\n");
    printf("2. Depositar\n");
    printf("3. Sacar\n");
    printf("4. Transferir\n");
    printf("5. Consultar Saldo e Dados\n");
    printf("6. Atualizar Dados (Telefone e Agência)\n");
    printf("7. Listar Contas\n");
    printf("8. Encerrar Conta\n");
    printf("9. Sair do Programa\n");
    printf("--------------------------------\n");
}

//A função processar_opcao será implementada no main.cpp para chamar as funções de conta.cpp
//Mas para o caso de listar contas, a lógica de filtro está aqui.
void processar_opcao_listar() {
    printf("\n--- Opções de Listagem ---\n");
    printf("1. Todas as Contas\n");
    printf("2. Somente Contas Ativas\n");
    printf("3. Somente Contas Encerradas\n");
    printf("Escolha o filtro: ");
    int filtro;
    if (scanf("%d", &filtro) != 1) {
        while (getchar() != '\n');
        printf("Opção inválida.\n");
        return;
    }
    while(getchar() != '\n'); // Limpar buffer

    if(filtro == 1) listar_contas(-1); // -1 para todas
    else if(filtro == 2) listar_contas(ATIVA);
    else if (filtro == 3) listar_contas(ENCERRADA);
    else printf("Opção de filtro inválida.\n");
}
