#include "conta.h"
#include "lista.h"
#include "io.h" //Para usar consultar_saldo_e_dados

//Função para abrir conta
void abrir_conta(){
    if (total_contas >=MAX_CONTAS){
        printf("\nERRO: Limite máximo de contas atingido (%d).\n", MAX_CONTAS);
        return;
    }

    ContaBancaria nova_conta;
    char cpf_temp[MAX_CPF];

    printf("\n--- Abertura de Conta ---\n");

    //Coletar CPF e validar unicidade
    printf("CPF (apenas números, máx %d dígitos): ", MAX_CPF - 1);
    scanf("%s", cpf_temp);
    while (getchar() != '\n'); // Limpar buffer

    if(!validar_cpf_unico (cpf_temp)){
        printf("ERRO: CPF já cadastrado no sistema.\n");
        return;
    }
    strcpy(nova_conta.cpf, cpf_temp);

    //Coletar Nome
    printf("Nome do titular (máx %d caracteres): ", MAX_NOME - 1);
    fgets(nova_conta.nome, MAX_NOME, stdin);
    nova_conta.nome[strcspn(nova_conta.nome, "\n")] = 0; // Remover nova linha

    //Coletar Telefone
    printf("Telefone (máx %d caracteres): ", MAX_TELEFONE - 1);
    scanf("%s", nova_conta.telefone);
    while(getchar() != '\n');

    //Coletar Agência
    printf("Agência (máx %d caracteres): ", MAX_AGENCIA - 1);
    scanf("%s", nova_conta.agencia);
    while(getchar() != '\n');

    //Coletar Data de nascimento
    printf("Data de nascimento (máx %d caracteres): ", MAX_DATA_NASCIMENTO - 1);
    scanf("%s", nova_conta.data_nascimento);
    while(getchar() != '\n');

    //Coletar CEP
    printf("CEP (máx %d caracteres): ", MAX_CEP - 1);
    scanf("%s", nova_conta.cep);
    while(getchar() != '\n');

    //Coletar Número da casa
    printf("Número da casa (máx %d caracteres): ", MAX_NUMERO_CASA - 1);
    scanf("%s", nova_conta.numero_casa);
    while(getchar() != '\n');

    //Coletar Bairro
    printf("Bairro (máx %d caracteres): ", MAX_BAIRRO- 1);
    scanf("%s", nova_conta.bairro);
    while(getchar() != '\n');

    //Coletar Cidade
    printf("Cidade (máx %d caracteres): ", MAX_CIDADE - 1);
    scanf("%s", nova_conta.cidade);
    while(getchar() != '\n');

    //Coletar Estado
    printf("Estado (máx %d caracteres): ", MAX_ESTADO - 1);
    scanf("%s", nova_conta.estado);
    while(getchar() != '\n');
    
    //Atribuir dados sequenciais e iniciais
    nova_conta.numero = proximo_numero_conta++;
    nova_conta.saldo = 0.0;
    nova_conta.status = ATIVA;

    //Adicionar ao vetor
    contas[total_contas++] = nova_conta;

    printf("\nSUCESSO: Conta aberta!\n");
    printf("Número da Conta: %d\n", nova_conta.numero);
    printf("Saldo Inicial: R$ %.2f\n", nova_conta.saldo);
}

//Função para depositar
void depositar(){
    int numero;
    double valor; 
    printf("\n--- Depósito ---");
    printf("Número da Conta: ");
    if(scanf("%d", &numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta.\n");
        return;        
    }
    while(getchar() != '\n');

    int indice = buscar_conta_por_numero(numero);
    if(indice == -1){
        printf("ERRO: Conta não encontrada.\n");
        return;
    }

    if(contas[indice].status == ENCERRADA){
        printf("ERRO: Não é possível depositar em conta encerrada.\n");
        return;
    }

    printf("Valor do Depósito: R$ ");
    if(scanf("%lf", &valor) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o valor.\n");
        return;
    }
    while (getchar() != '\n');

    if(valor <= 0){
        printf("ERRO: O valor do depósito deve ser maior que zero.\n");
        return;
    }

    contas[indice].saldo +=valor;
    printf("\nSUCESSO: Depósito de R$ %.2f realizado na conta %d.\n", valor, numero);
    printf("Novo Saldo: R$ %.2f\n", contas[indice].saldo);
}

//Função para sacar
void sacar(){
    int numero;
    double valor;
    printf("\n--- Saque ---\n");
    printf("Número da Conta : ");
    if(scanf("%d", &numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta.\n");
        return;
    }
    while(getchar() != '\n');

    int indice = buscar_conta_por_numero(numero);
    if (indice == -1){
        printf("ERRO: Conta não encontrada.\n");
        return;
    }

    if(contas[indice].status == ENCERRADA){
        printf("ERRO: Não é possível sacar de conta encerrada.\n");
        return;
    }

    printf("Valor do Saque: R$ ");
    if(scanf("%lf", &valor) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o valor.\n");
        return;
    }
    while(getchar() != '\n');

    if(valor <= 0){
        printf("ERRO: O valor do saque deve ser maior que zero.\n");
        return;
    }

    if(valor > contas[indice].saldo){
        printf("ERRO: Saldo insuficiente. Saldo atual: R$%.2f\n", contas[indice].saldo);
        return;
    }

    contas[indice].saldo -= valor;
    printf("\nSUCESSO: Saque de R$ %.2f realizado na conta %d.\n", valor, numero);
    printf("Novo Saldo: R$ %.2f\n", contas[indice].saldo);
}

//Função para transferir
void transferir(){
    int origem_numero, destino_numero;
    double valor;

    printf("\n--- Transferência ---\n");

    printf("Número da Conta de Origem: ");
    if(scanf("%d", &origem_numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta de origem.\n");
        return;
    }
    while(getchar() != '\n');

    printf("Número do Conta de Destino:");
    if(scanf("%d", &destino_numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta de destino.\n");
        return;
    }
    while(getchar() != '\n');

    int origem_indice = buscar_conta_por_numero(origem_numero);
    int destino_indice = buscar_conta_por_numero(destino_numero);

    if(origem_indice == -1){
        printf("ERRO: Conta de origem não encontrada.\n");
        return;
    }
    if(destino_indice == -1){
        printf("ERRO: Conta de destino não encontrada.\n");
        return;
    }

    if(contas[origem_indice].status == ENCERRADA){
        printf("ERRO: Conta de origem está encerrada.\n");
        return;
    }
    if(contas[destino_indice].status == ENCERRADA){
        printf("ERRO: Conta de destino está encerrada.\n");
        return;
    }

    printf("Valor da Transferência: R$ ");
    if(scanf("%lf", &valor) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o valor.\n");
        return;
    }
    while(getchar() != '\n');

    if(valor <= 0){
        printf("ERRO: O valor da transferência deve ser maior que zero.\n");
        return;
    }

    if(valor > contas[origem_indice].saldo){
        printf("ERRO: Saldo insuficiente na conta de origem. Saldo atual: R$ %.2f\n", contas[origem_indice].saldo);
        return;
    }

    //Realiza a transferência
    contas[origem_indice].saldo -= valor;
    contas[destino_indice].saldo += valor;

    printf("\nSUCESSO: Transferência de R$ %.2f realizada de %d para %d.\n", valor, origem_numero, destino_numero);
    printf("Novo Saldo (Origem %d): R$ %.2f\n", origem_numero, contas[origem_indice].saldo);
    printf("Novo Saldo (Destino %d): R$ %.2f\n", destino_numero, contas[destino_indice].saldo);
}

//Função para atualizar dados (telefone e agência)
void atualizar_dados(){
    int numero;
    printf("\n--- Atualização de Dados ---\n");
    printf("Número da Conta para atualizar: ");
    if(scanf("%d", &numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta.\n");
        return;
    }
    while(getchar() != '\n');

    int indice = buscar_conta_por_numero(numero);
    if(indice == -1){
        printf("ERRO: Conta não encontrada.\n");
        return;
    }

    if(contas[indice].status == ENCERRADA){
        printf("ERRO: Não é possível atualizar dados de conta encerrada.\n");
        return;
    }

    printf("Conta encontrada. Titular: %s\n", contas[indice].nome);

    char novo_telefone[MAX_TELEFONE];
    printf("Novo Telefone (atual: %s, máx %d caracteres): ", contas[indice].telefone, MAX_TELEFONE - 1);
    scanf("%s", novo_telefone);
    while(getchar() != '\n');
    strcpy(contas[indice].telefone, novo_telefone);

    char nova_agencia[MAX_AGENCIA];
    printf("Nova Agência (atual: %s, máx %d caracteres): ", contas[indice].agencia, MAX_AGENCIA - 1);
    scanf("%s", nova_agencia);
    while(getchar() != '\n');
    strcpy(contas[indice].agencia, nova_agencia);

    printf("\nSUCESSO: Dados da conta %d atualizados.\n", numero);
    exibir_dados_conta(indice);
}

//Função para encerrar conta
void encerrar_conta(){
    int numero;
    printf("\n--- Encerramento de Conta ---\n");
    printf("Número da Conta para encerrar: ");
    if(scanf("%d", &numero) != 1){
        while(getchar() != '\n');
        printf("ERRO: Entrada inválida para o número da conta.\n");
        return;
    }
    while(getchar() != '\n');

    int indice = buscar_conta_por_numero(numero);
    if(indice == -1){
        printf("ERRO: Conta não encontrada.\n");
        return;
    }

    if(contas[indice].status == ENCERRADA){
        printf("ERRO: A conta %d já está encerrada.\n", numero);
        return;
    }

    if(contas[indice].saldo != 0.0){
        printf("ERRO: Saldo deve ser zero para encerrar a conta. Saldo atual: R$ %.2f\n", contas[indice].saldo);
        return;
    }

    //Marca como encerrada
    contas[indice].status = ENCERRADA;
    printf("\nSUCESSO: Conta %d (Titular: %s) encerrada com sucesso.\n", numero, contas[indice].nome);
    printf("Status atual: ENCERRADA\n");
}


