#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct nodoPilha{
    char letra;
    struct nodoPilha *prox;
}nodoPilha;

typedef struct Pilha{
    nodoPilha *topo;
}Pilha;

Pilha* cria_Pilha();// Aloca memoria para a pilha

void push_Pilha(char letra, Pilha *pilha);// Coloca um elemento na pilha

void inicia_Pilha(Pilha *pilha);// Inicia a pilha com o 'Z'

char pop_Pilha(Pilha *pilha);// Retira um elemento da pilha

int pilha_Vazia(Pilha *pilha);// verifica se a pilha so tem o elemento 'Z'

char topo(Pilha *pilha);// Retorna o elemento do topo da pilha

Pilha* copia_Pilha(Pilha *pilha);// Faz uma copia de uma pilha

void libera_Pilha(Pilha *pilha);// Retira todos os elementos da pilha

void printa_Pilha(Pilha *pilha);// Printa pilha em sequencia

#endif