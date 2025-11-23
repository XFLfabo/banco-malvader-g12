#ifndef LISTA_H
#define LISTA_H

#include "conta.h"

//Protótipos das funções de gerenciamento da lista/vetor
int buscar_conta_por_numero(int numero);
int buscar_conta_por_cpf(const char *cpf);
int validar_cpf_unico(const char *cpf);

#endif // LISTA_H