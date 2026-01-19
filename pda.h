#ifndef PDA_H
#define PDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

typedef struct Transicao{
    int estado_Destino; // Estado para qual vai ir
    char precisaLer; // O que precisa ler na palavra para fazer a transição
    char pop, push[5]; // pop = elemento para retirar da pilha, push = elementos para colocar na pilha
    struct Transicao *prox; // Próxima transição na lista
}Transicao;

typedef struct Computacao{
    int estado;
    char palavra[101];
    Pilha *pilha;
}Computacao;

Transicao** cria_listaAdj(int numEstados);// Aloca memoria para uma lista de afj

Transicao* criaTransicao();// Aloca memoria para uma trasiçao

void preenche_ListaAdj(Transicao **listaAdj, Transicao *transicao, int estadoAtual);// Coloca uma transiçao na seus estado na lista de adj

int verificaFinal(int *estadosFinais, int numEstadosFinais, int estadoAtual);// Percorre o vetor vendo so o estado e final

void arrumaComp(Computacao *comp, int *tam, int estado_ini, char *palavra, Pilha *pilha);// Coloca uma computaçao no vetor delas

int Dfs_PDA(Transicao **lista_Adj, char *palavra, int estado_ini, Pilha *pilha, int *estadosFinais, int numEstadosFinais, Computacao *comp, int *tam, int *tamMax);
// Faz uma busca em profundidade adaptada para ver se a palavra é aceita

void liberaLista(Transicao *transicao);// Recebe uma lista e libera ela 

void libera_ListaAdj(Transicao **listaAdj, int numEstados);// Chama a funçao liberaLista para cada posiçao da lista de adj

void printaComp(Computacao *comp, int i);// Printa a sequencia de computaçao

#endif 