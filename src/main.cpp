#include "conta.h"
#include "io.h"
#include "lista.h"

//Protótipo da função de consulta (implementada em io.cpp)
void consultar_saldo_e_dados();
//Protótipo da função de listagem (implementada em io.cpp)
void processar_opcao_listar();

void processar_opcao(int opcao){
    switch(opcao){
        case 1:
            abrir_conta();
            break;
        case 2:
            depositar();
            break;
        case 3:
            sacar();
            break;
        case 4:
            transferir();
            break;
        case 5:
            consultar_saldo_e_dados();
            break;
        case 6:
            atualizar_dados();
            break;
        case 7:
            processar_opcao_listar();
            break;
        case 8:
            encerrar_conta();
            break;
        case 9:
           //O loop principal cuida de saída
           break;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

int main(){
    int opcao;

    do{
        exibir_menu();
        printf("Escolha uma opção: ");

        if(scanf("%d", &opcao) != 1){
            //Limpa o buffer em caso de entrada inválida (não numérica)
            while(getchar() != '\n');
            opcao = 0; //Força a repetição do loop
        } else{
            //Limpar o buffer após a leitura do número
            while(getchar() != '\n');
            processar_opcao(opcao);
        }
    } while(opcao != 9);

    printf("\nObrigado por usar o sistema bancário. Saindo...\n");
    return 0;
}